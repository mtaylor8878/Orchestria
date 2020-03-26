// Copyright Matthew Taylor 2019


#include "NameGenerator.h"

#include "Kismet/KismetMathLibrary.h"

FString NameGenerator::GetRandomName() {
    FString randColour = Colours[FMath::RandRange(0, Colours.Num() - 1)];
    FString randInstrument = Instruments[FMath::RandRange(0, Instruments.Num() - 1)];

    return randColour + " " + randInstrument;
}

const TArray<FString> NameGenerator::Colours = {
    "Red",
    "Orange",
    "Yellow",
    "Green",
    "Blue",
    "Indigo",
    "Violet",
    "Purple",
    "Lavender",
    "Fuchsia",
    "Plum",
    "Orchid",
    "Magenta",
};

const TArray<FString> NameGenerator::Instruments = {
    "Violin",
    "Viola",
    "Cello",
    "Contrabass",
    "Harp",
    "Flute",
    "Piccolo",
    "Oboe",
    "English Horn",
    "Clarinet",
    "Bass Clarinet",
    "Bassoon",
    "Contrabassoon",
    "Trumpet",
    "Trombone",
    "Bass Trombone",
    "French Horn",
    "Tuba",
    "Timpani",
    "Bass Drum",
    "Snare Drum",
    "Triangle",
    "Gong",
    "Cymbal",
    "Marimba",
    "Piano"
};
