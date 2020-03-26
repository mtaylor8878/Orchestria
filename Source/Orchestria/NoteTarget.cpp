// Copyright Matthew Taylor 2019


#include "NoteTarget.h"
#include "Classes/Components/BoxComponent.h"

// Sets default values
ANoteTarget::ANoteTarget()
{
 	// Doesn't need to tick
	PrimaryActorTick.bCanEverTick = false;

    _targetVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TargetVolume"));
    RootComponent = _targetVolume;
}

// Called when the game starts or when spawned
void ANoteTarget::BeginPlay()
{
	Super::BeginPlay();
	
}
