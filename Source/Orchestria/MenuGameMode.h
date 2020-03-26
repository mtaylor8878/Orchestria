// Copyright Matthew Taylor 2019

#pragma once

#include "CoreMinimal.h"
#include "TrackList.h"
#include "GameFramework/GameModeBase.h"
#include "MenuGameMode.generated.h"


/**
 * 
 */
UCLASS()
class ORCHESTRIA_API AMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
    AMenuGameMode();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu")
    TArray<FString> ConnectionInfo;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu")
    TArray<int> PlayerRoles;

    UFUNCTION(BlueprintCallable, Category = "Persistent Data")
        FString GetPlayerName() const;

    UFUNCTION(BlueprintCallable, Category = "Persistent Data")
        void SetLocalRole(int roleId);

    UFUNCTION(BlueprintCallable, Category = "Persistent Data")
        ETrackRole GetPersistentRole() const;

    UFUNCTION(BlueprintCallable, Category = "Persistent Data")
        void SetAutoPlay(bool setting);

    UFUNCTION(BlueprintCallable, Category = "Persistent Data")
        void SetShowDebugSetting(bool setting);
};
