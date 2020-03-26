// Copyright Matthew Taylor 2019


#include "NoteMarker.h"

#include "Classes/Components/StaticMeshComponent.h"

// Sets default values
ANoteMarker::ANoteMarker()
{
 	// Should tick
	PrimaryActorTick.bCanEverTick = true;

    _markerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MarkerMesh"));
    RootComponent = _markerMesh;

    _velocity = FVector::ZeroVector;
}

// Called every frame
void ANoteMarker::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    SetActorLocation(GetActorTransform().TransformPosition(_velocity * DeltaTime));
}

void ANoteMarker::SetVelocity(const FVector& velocity) {
    _velocity = velocity;
}

// Called when the game starts or when spawned
void ANoteMarker::BeginPlay()
{
	Super::BeginPlay();
	
}
