// Copyright Matthew Taylor 2019


#include "PersistentData.h"

#include "NameGenerator.h"

void PersistentData::Reset() {
    PlayerName = NameGenerator::GetRandomName();
    Role = ETrackRole::EUndecided;
    AutoPlay = false;
    ShowDebug = false;
}

FString PersistentData::PlayerName = NameGenerator::GetRandomName();
ETrackRole PersistentData::Role = ETrackRole::EUndecided;
bool PersistentData::AutoPlay = false;
bool PersistentData::ShowDebug = false;
