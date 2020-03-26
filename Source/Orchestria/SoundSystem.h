// Copyright Matthew Taylor 2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SoundSystem.generated.h"

UENUM(BlueprintType)
enum class EDynamic : uint8 {
    EFortissimo,
    EForte,
    EMezzoForte,
    EMezzoPiano,
    EPiano,
    EPianissimo
};

UENUM(BlueprintType)
enum class EInstrument : uint8 {
    ETrumpet,
    EFHorn,
    ETrombone,
    ETuba,
    EDrumKit,
    EMarimba,
    ETimpani,
};

UENUM(BlueprintType)
enum class ENoteLength : uint8 {
    EDoubleWhole,
    EWhole,
    EDotHalf,
    EHalf,
    EDotQuarter,
    EQuarter,
    EQuarterStacc,
    EEighth,
    EEighthStacc,
    ESixteenth
};

UENUM(BlueprintType)
enum class ENoteName : uint8 {
    ENoteA,
    ENoteAS,
    ENoteB,
    ENoteC,
    ENoteCS,
    ENoteD,
    ENoteDS,
    ENoteE,
    ENoteF,
    ENoteFS,
    ENoteG,
    ENoteGS,
    ERimShot,
    EKickDrum,
    ECrashCymbal,
};

USTRUCT(BlueprintType)
struct FSoundIdentifier {
    GENERATED_BODY()

    FSoundIdentifier(EInstrument instrument = EInstrument::EDrumKit, ENoteName name = ENoteName::ERimShot, int octave = 0, ENoteLength length = ENoteLength::EQuarter)
        : Instrument(instrument), Name(name), Octave(octave), Length(length) { }

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoundLibrary")
        EInstrument Instrument;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoundLibrary")
        ENoteName Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoundLibrary")
        int Octave;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoundLibrary")
        ENoteLength Length;
};

UCLASS()
class ORCHESTRIA_API ASoundSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASoundSystem();

    UFUNCTION(BlueprintImplementableEvent)
    void PlaySoundFromLibrary(EDynamic dynamic, const FSoundIdentifier& sound);
};
