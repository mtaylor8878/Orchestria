// Copyright Matthew Taylor 2019


#include "MenuGameMode.h"

#include "PersistentData.h"

AMenuGameMode::AMenuGameMode() {
    double secs = FTimespan(FDateTime::Now().GetTicks()).GetTotalSeconds();
    int32 seed = (int32)(((int64)secs) % INT_MAX);
    FMath::RandInit(seed);

    PersistentData::Reset();
}

FString AMenuGameMode::GetPlayerName() const {
    return PersistentData::PlayerName;
}

void AMenuGameMode::SetLocalRole(int roleId) {
    PersistentData::Role = static_cast<ETrackRole>(roleId);
}

ETrackRole AMenuGameMode::GetPersistentRole() const {
    return PersistentData::Role;
}

void AMenuGameMode::SetAutoPlay(bool setting) {
    PersistentData::AutoPlay = setting;
}

void AMenuGameMode::SetShowDebugSetting(bool setting) {
    PersistentData::ShowDebug = setting;
}