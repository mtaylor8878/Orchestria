// Copyright Matthew Taylor 2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NoteSpawner.generated.h"

UENUM(BlueprintType)
enum class ENoteType : uint8 {
    ETap
};

UCLASS()
class ORCHESTRIA_API ANoteSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANoteSpawner();

    // Spawns a note at this spawner
    UFUNCTION(BlueprintCallable, Category = "Note")
    class ANoteMarker* SpawnNote(ENoteType type);

    UFUNCTION(BlueprintPure, Category = "Note")
    FVector GetMoveVector() const;

    UFUNCTION(BlueprintPure, Category = "Note")
    int GetLaneNumber() const;

    UFUNCTION(BlueprintCallable, Category = "Note")
    void SetLaneSpeed(float speed);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
    // Volume denoting where to spawn notes
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Note", meta = (AllowPrivateAccess = "true"))
    class UBoxComponent* _spawnVolume;

    UPROPERTY(EditAnywhere, Category = "Note", meta = (AllowPrivateAccess = "true"))
    class ANoteTarget* _target;

    // Marker to spawn for Tap notes
    UPROPERTY(EditAnywhere, Category = "Note")
    TSubclassOf<class ANoteMarker> _tapMarker;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Note", meta = (AllowPrivateAccess = "true"))
    int _laneNumber;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Note", meta = (AllowPrivateAccess = "true"))
    float _noteSpeed;
};
