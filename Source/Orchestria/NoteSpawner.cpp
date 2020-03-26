// Copyright Matthew Taylor 2019


#include "NoteSpawner.h"

#include "NoteMarker.h"
#include "NoteTarget.h"
#include "Classes/Components/BoxComponent.h"

// Sets default values
ANoteSpawner::ANoteSpawner()
{
 	// Doesn't need to tick
	PrimaryActorTick.bCanEverTick = false;

    _spawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
    RootComponent = _spawnVolume;

    _laneNumber = 0;
}

ANoteMarker* ANoteSpawner::SpawnNote(ENoteType type) {
    UWorld* world = GetWorld();
    if (!world || !_spawnVolume) {
        return nullptr;
    }

    TSubclassOf<ANoteMarker> markerToSpawn;
    switch (type) {
    case ENoteType::ETap:
        markerToSpawn = _tapMarker;
        break;
    }

    if (markerToSpawn == NULL) {
        return nullptr;
    }

    FActorSpawnParameters spawnParams;
    spawnParams.Owner = this;
    spawnParams.Instigator = Instigator;

    FVector spawnLocation = _spawnVolume->Bounds.Origin;
    ANoteMarker* newNote = world->SpawnActor<ANoteMarker>(markerToSpawn, spawnLocation, FRotator::ZeroRotator, spawnParams);

    // Set speed of newly created note
    FVector direction = GetMoveVector();
    direction.Normalize();
    newNote->SetVelocity(direction * _noteSpeed);

    return newNote;
}

FVector ANoteSpawner::GetMoveVector() const {
    return _target->GetTransform().GetTranslation() - _spawnVolume->Bounds.Origin;
}

int ANoteSpawner::GetLaneNumber() const {
    return _laneNumber;
}

void ANoteSpawner::SetLaneSpeed(float speed) {
    _noteSpeed = speed;
}

// Called when the game starts or when spawned
void ANoteSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}
