// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "OrchestriaGameMode.h"

#include "NoteMarker.h"
#include "NoteSpawner.h"
#include "OrchestriaPawn.h"
#include "OrchestriaPlayerController.h"
#include "PersistentData.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"

AOrchestriaGameMode::AOrchestriaGameMode()
{
    PrimaryActorTick.bCanEverTick = true;

	// no pawn by default
	DefaultPawnClass = AOrchestriaPawn::StaticClass();
	// use our own player controller class
	PlayerControllerClass = AOrchestriaPlayerController::StaticClass();

    _startDelay = 3.0f;
    _spawnHead = 0;
    _travelTime = 1.0f;
    _currentTime = 0.0f;
    _score = 0;
    _combo = 0;
    _gameStarted = false;
    _doneSpawning = false;

    switch (PersistentData::Role) {
    case ETrackRole::ERhythm:
        _timeline.Append(TrackList::GERUDO_VALLEY_RHYTHM, TrackList::GERUDO_VALLEY_RHYTHM_LEN);
        break;
    case ETrackRole::EBass:
        _timeline.Append(TrackList::GERUDO_VALLEY_BASS, TrackList::GERUDO_VALLEY_BASS_LEN);
        break;
    case ETrackRole::EMelody:
        _timeline.Append(TrackList::GERUDO_VALLEY_MELODY, TrackList::GERUDO_VALLEY_MELODY_LEN);
        break;
    case ETrackRole::EChorus:
        _timeline.Append(TrackList::GERUDO_VALLEY_CHORUS, TrackList::GERUDO_VALLEY_CHORUS_LEN);
        break;
    }
}

void AOrchestriaGameMode::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);

    if (!_gameStarted) {
        UpdateStartedState();
        return;
    }

    _currentTime += DeltaTime;
    UpdateGameState();
    if (_doneSpawning) {
        return;
    }

    if (_currentTime >= (_timeline[_spawnHead].TimeStamp - _travelTime)) {
        spawnNextNote();
    }
}

int AOrchestriaGameMode::GetScore() const {
    return _score;
}

int AOrchestriaGameMode::GetCombo() const {
    return _combo;
}

float AOrchestriaGameMode::GetSongTime() const {
    return _currentTime;
}

bool AOrchestriaGameMode::GetShowDebug() const {
    return PersistentData::ShowDebug;
}

ETrackRole AOrchestriaGameMode::GetPlayerRole() const {
    return PersistentData::Role;
}

FString AOrchestriaGameMode::GetFeedbackMessage(int lane) {
    if (const FHitTolerance* feedback = _laneFeedback[lane]) {
        return feedback->Label;
    }
    return "";
}

FLinearColor AOrchestriaGameMode::GetFeedbackColor(int lane) {
    if (const FHitTolerance* feedback = _laneFeedback[lane]) {
        return feedback->LabelColor;
    }
    return FColor::White;
}

// Called when the game starts or when spawned
void AOrchestriaGameMode::BeginPlay()
{
    Super::BeginPlay();

    TArray<AActor*> soundSystemActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASoundSystem::StaticClass(), soundSystemActors);
    if (soundSystemActors.Num() > 0) {
        if (ASoundSystem* soundSystemActor = static_cast<ASoundSystem*>(soundSystemActors[0])) {
            _soundSystem = soundSystemActor;
        }
        else {
            UE_LOG(LogTemp, Error, TEXT("Couldn't cast actor as ASoudSystem"));
        }
    }
    else {
        UE_LOG(LogTemp, Error, TEXT("No SoundSystem could be found"));
    }

    if (_hudWidgetClass) {
        _currentWidget = CreateWidget<UUserWidget>(GetWorld(), _hudWidgetClass);
        if (_currentWidget) {
            _currentWidget->AddToViewport();
        }
    }

    // Set references to lane spawners
    TArray<AActor*> noteSpawnActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANoteSpawner::StaticClass(), noteSpawnActors);

    _spawners.Init(nullptr, noteSpawnActors.Num());
    _laneFeedback.Init(nullptr, noteSpawnActors.Num());
    _feedbackTimer.Init(FTimerHandle(), noteSpawnActors.Num());

    for (AActor* spawnActor : noteSpawnActors) {
        ANoteSpawner* noteSpawner = static_cast<ANoteSpawner*>(spawnActor);
        int thisLane = noteSpawner->GetLaneNumber();

        if (thisLane < 0) {
            // This is an invalid lane index
            break;
        }

        _spawners[thisLane] = noteSpawner;
        
        noteSpawner->SetLaneSpeed(noteSpawner->GetMoveVector().Size() / _travelTime);
    }

    _currentTime = -_startDelay - _travelTime;
}

void AOrchestriaGameMode::tapLane(int laneNumber) {
    UE_LOG(LogTemp, Display, TEXT("Tapped Lane: %d"), laneNumber);

    NoteData* noteToHit = nullptr;
    for (NoteData& data : _timeline) {
        if (data.NoteActor && data.Lane == laneNumber) {
            noteToHit = &data;
            break;
        }
    }

    if (noteToHit) {
        float diff = FMath::Abs(_currentTime - noteToHit->TimeStamp);
        UE_LOG(LogTemp, Display, TEXT("Off by %.3f"), _currentTime - noteToHit->TimeStamp);

        for (const FHitTolerance& tolerance : _hitTolerance) {
            if (diff < tolerance.ToleranceValue) {
                // Hit
                succeedTap(*noteToHit, tolerance);
                break;
            }
        }
    }
}

void AOrchestriaGameMode::setStartDelay(float delay) {
    _currentTime -= delay;
}

void AOrchestriaGameMode::spawnNextNote() {
    NoteData& spawnNote = _timeline[_spawnHead];
    
    if (ANoteSpawner* laneToSpawn = _spawners[spawnNote.Lane]) {
        spawnNote.NoteActor = laneToSpawn->SpawnNote(spawnNote.NoteType);

        // Create timer to destroy note if it isn't hit in time
        FTimerHandle missHandle;
        GetWorldTimerManager().SetTimer(missHandle, FTimerDelegate::CreateUObject(this, &AOrchestriaGameMode::missNote, _spawnHead), _travelTime + _missTolerance.ToleranceValue, false);

        if (PersistentData::AutoPlay) {
            FTimerHandle autoPlayHandle;
            GetWorldTimerManager().SetTimer(autoPlayHandle, FTimerDelegate::CreateUObject(this, &AOrchestriaGameMode::tapLane, spawnNote.Lane), _travelTime, false);
        }
    }

    if (++_spawnHead < _timeline.Num()) {
        float nextTime = _timeline[_spawnHead].TimeStamp - spawnNote.TimeStamp;

        if (nextTime <= 0.0f) {
            spawnNextNote();
        }
    }
    else {
        _doneSpawning = true;
        FTimerHandle tempHandle;
        GetWorldTimerManager().SetTimer(tempHandle, this, &AOrchestriaGameMode::ShowScoreScreen, 5.0f, false);
    }
}

void AOrchestriaGameMode::succeedTap(NoteData& note, const FHitTolerance& successionLevel) {
    UE_LOG(LogTemp, Display, TEXT("%s"), *successionLevel.Label);
    for (FSoundIdentifier sound : note.Sounds) {
        _soundSystem->PlaySoundFromLibrary(note.Dynamic, sound);
    }
    pushLaneFeedback(note.Lane, successionLevel);
    _score += successionLevel.ScoreValue;
    ReportScore(successionLevel.ScoreValue);

    if (successionLevel.ComboBreak) {
        _combo = 0;
    }
    else {
        _combo++;
    }

    note.NoteActor->Destroy();
    note.NoteActor = nullptr;
}

void AOrchestriaGameMode::pushLaneFeedback(int lane, const FHitTolerance& successLevel) {
    _laneFeedback[lane] = &successLevel;
    GetWorldTimerManager().SetTimer(_feedbackTimer[lane], FTimerDelegate::CreateUObject(this, &AOrchestriaGameMode::popLaneFeedback, lane), 0.2f, false);
}

void AOrchestriaGameMode::popLaneFeedback(int lane) {
    _laneFeedback[lane] = nullptr;
}

void AOrchestriaGameMode::missNote(int noteIndex) {
    NoteData& note = _timeline[noteIndex];
    if (note.NoteActor) {
        pushLaneFeedback(note.Lane, _missTolerance);

        note.NoteActor->Destroy();
        note.NoteActor = nullptr;
    }
}
