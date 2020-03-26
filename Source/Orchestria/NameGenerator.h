// Copyright Matthew Taylor 2019

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class ORCHESTRIA_API NameGenerator
{
public:
    static FString GetRandomName();

private:
    static const TArray<FString> Colours;
    static const TArray<FString> Instruments;
};
