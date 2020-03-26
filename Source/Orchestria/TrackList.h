// Copyright Matthew Taylor 2019

#pragma once

#include "CoreMinimal.h"
#include "NoteSpawner.h"
#include "SoundSystem.h"

struct NoteData {
    NoteData(float time, int lane, TArray<FSoundIdentifier> sound, EDynamic dynamic = EDynamic::EMezzoForte, ENoteType type = ENoteType::ETap)
        : NoteActor(nullptr), TimeStamp(time), Lane(lane), NoteType(type), Sounds(sound), Dynamic(dynamic) {}

    ANoteMarker* NoteActor;
    float TimeStamp;
    int Lane;
    ENoteType NoteType;
    TArray<FSoundIdentifier> Sounds;
    EDynamic Dynamic;
};

UENUM(BlueprintType)
enum class ETrackRole : uint8 {
    EUndecided,
    ERhythm,
    EBass,
    EChorus,
    EMelody,
};

/**
 * Track Data
 */
class ORCHESTRIA_API TrackList
{
public:
    static const NoteData GERUDO_VALLEY_RHYTHM[];
    static const size_t GERUDO_VALLEY_RHYTHM_LEN;

    static const NoteData GERUDO_VALLEY_BASS[];
    static const size_t GERUDO_VALLEY_BASS_LEN;

    static const NoteData GERUDO_VALLEY_CHORUS[];
    static const size_t GERUDO_VALLEY_CHORUS_LEN;

    static const NoteData GERUDO_VALLEY_MELODY[];
    static const size_t GERUDO_VALLEY_MELODY_LEN;
};
