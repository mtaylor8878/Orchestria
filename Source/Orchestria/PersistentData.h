// Copyright Matthew Taylor 2019

#pragma once

#include "CoreMinimal.h"
#include "TrackList.h"

/**
 * Persistent data to set across levels
 */
class ORCHESTRIA_API PersistentData
{
public:
    static void Reset();

    static FString PlayerName;
    static ETrackRole Role;
    static bool AutoPlay;
    static bool ShowDebug;
};
