// Copyright Matthew Taylor 2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NoteMarker.generated.h"

UCLASS()
class ORCHESTRIA_API ANoteMarker : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANoteMarker();

    // Called every frame
    virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable, Category = "Note")
    void SetVelocity(const FVector& velocity);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Note", meta = (AllowPrivateAccess = "true"))
    FVector _velocity;

    // Mesh that represents the note marker
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Note", meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* _markerMesh;
};
