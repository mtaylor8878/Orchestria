// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "OrchestriaGameMode.h"
#include "OrchestriaPlayerController.h"
#include "OrchestriaPawn.h"

AOrchestriaGameMode::AOrchestriaGameMode()
{
	// no pawn by default
	DefaultPawnClass = AOrchestriaPawn::StaticClass();
	// use our own player controller class
	PlayerControllerClass = AOrchestriaPlayerController::StaticClass();
}
