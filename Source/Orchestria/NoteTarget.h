// Copyright Matthew Taylor 2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NoteTarget.generated.h"

UCLASS()
class ORCHESTRIA_API ANoteTarget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANoteTarget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
    // Volume denoting where the note is trying to reach
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Note", meta = (AllowPrivateAccess = "true"))
    class UBoxComponent* _targetVolume;
};
