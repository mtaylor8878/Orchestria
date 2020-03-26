// Copyright Matthew Taylor 2019

#pragma once

#include "CoreMinimal.h"
#include "SoundSystem.h"
#include "TrackList.h"
#include "GameFramework/GameModeBase.h"
#include "OrchestriaGameMode.generated.h"

class ANoteMarker;
class ANoteSpawner;
class ASoundSystem;
class UUserWidget;

USTRUCT(BlueprintType)
struct FHitTolerance {
    GENERATED_BODY()
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Note")
    FString Label;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Note")
    FLinearColor LabelColor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Note")
    float ToleranceValue;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Note")
    int ScoreValue;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Note")
    bool ComboBreak;
};

UCLASS(minimalapi)
class AOrchestriaGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AOrchestriaGameMode();

    virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintPure, Category = "Note")
    int GetScore() const;

    UFUNCTION(BlueprintPure, Category = "Note")
    int GetCombo() const;

    UFUNCTION(BlueprintPure, Category = "Playback")
    float GetSongTime() const;

    UFUNCTION(BlueprintPure, Category = "Persistent Data")
    bool GetShowDebug() const;

    UFUNCTION(BlueprintPure, Category = "Persistent Data")
    ETrackRole GetPlayerRole() const;

    UFUNCTION(BlueprintCallable, Category = "Note")
    FString GetFeedbackMessage(int lane);

    UFUNCTION(BlueprintCallable, Category = "Note")
    FLinearColor GetFeedbackColor(int lane);

    UFUNCTION(BlueprintImplementableEvent)
    void ReportReady();

    UFUNCTION(BlueprintImplementableEvent)
    void UpdateStartedState();

    UFUNCTION(BlueprintImplementableEvent)
    void UpdateGameState();

    UFUNCTION(BlueprintImplementableEvent)
    void ReportScore(int scoreVal);

    UFUNCTION(BlueprintImplementableEvent)
    void ShowScoreScreen();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

private:
    UFUNCTION(BlueprintCallable, Category = "Note")
    void tapLane(int laneNumber);

    UFUNCTION(BlueprintCallable, Category = "Playback")
    void setStartDelay(float delay);

    void spawnNextNote();
    void succeedTap(NoteData& noteTapped, const FHitTolerance& successionLevel);
    void pushLaneFeedback(int lane, const FHitTolerance& successLevel);
    void popLaneFeedback(int lane);
    void missNote(int noteIndex);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Playback", Meta = (AllowPrivateAccess = "true"))
    float _startDelay;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Playback", Meta = (AllowPrivateAccess = "true"))
    int _spawnHead;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Playback", Meta = (AllowPrivateAccess = "true"))
    bool _gameStarted;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Note", Meta = (AllowPrivateAccess = "true"))
    float _travelTime;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Note", Meta = (AllowPrivateAccess = "true"))
    TArray<ANoteSpawner*> _spawners;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Note", Meta = (AllowPrivateAccess = "true"))
    TSubclassOf<UUserWidget> _hudWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Note", Meta = (AllowPrivateAccess = "true"))
    TArray<FHitTolerance> _hitTolerance;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Note", Meta = (AllowPrivateAccess = "true"))
    FHitTolerance _missTolerance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Note", Meta = (AllowPrivateAccess = "true"))
    int _teamScore;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Note", Meta = (AllowPrivateAccess = "true"))
    UUserWidget* _currentWidget;

    TArray<NoteData> _timeline;
    ASoundSystem* _soundSystem;
    float _currentTime;
    int _score;
    int _combo;
    bool _doneSpawning;

    TArray<const FHitTolerance*> _laneFeedback;
    TArray<FTimerHandle> _feedbackTimer;
};



