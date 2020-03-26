#pragma once

#include "OrchestriaNetworkFunctions.generated.h"

UCLASS(NotBlueprintable)
class UOrchestriaNetworkFunctions : public UObject {
	GENERATED_BODY()
	
public:

#if PLATFORM_ANDROID
	static void InitJavaFunctions();
#endif

    UFUNCTION(BlueprintCallable, meta = (Keywords = "OrchestriaNetwork ", DisplayName = "Start Advertising"), Category = "OrchestriaNetwork")
        static void OrchestriaNetwork_StartAdvertising();

    UFUNCTION(BlueprintCallable, meta = (Keywords = "OrchestriaNetwork ", DisplayName = "Start Discovery"), Category = "OrchestriaNetwork")
        static void OrchestriaNetwork_StartDiscovery();

    UFUNCTION(BlueprintCallable, meta = (Keywords = "OrchestriaNetwork ", DisplayName = "Get Connection Info"), Category = "OrchestriaNetwork")
        static TArray<FString> OrchestriaNetwork_GetConnectionInfo();

    UFUNCTION(BlueprintCallable, meta = (Keywords = "OrchestriaNetwork ", DisplayName = "Set Player Name"), Category = "OrchestriaNetwork")
        static void OrchestriaNetwork_SetPlayerName(const FString& name);

    UFUNCTION(BlueprintCallable, meta = (Keywords = "OrchestriaNetwork ", DisplayName = "Request Connection"), Category = "OrchestriaNetwork")
        static void OrchestriaNetwork_RequestConnection(const FString& endpointId);

    UFUNCTION(BlueprintCallable, meta = (Keywords = "OrchestriaNetwork ", DisplayName = "Request Connection Status"), Category = "OrchestriaNetwork")
        static int OrchestriaNetwork_RequestConnectionStatus();

    UFUNCTION(BlueprintCallable, meta = (Keywords = "OrchestriaNetwork ", DisplayName = "Disconnect"), Category = "OrchestriaNetwork")
        static void OrchestriaNetwork_Disconnect();

    UFUNCTION(BlueprintCallable, meta = (Keywords = "OrchestriaNetwork ", DisplayName = "Update Clients"), Category = "OrchestriaNetwork")
        static void OrchestriaNetwork_UpdateClients();

    UFUNCTION(BlueprintCallable, meta = (Keywords = "OrchestriaNetwork ", DisplayName = "Request Role"), Category = "OrchestriaNetwork")
        static void OrchestriaNetwork_RequestRole(int roleId);

    UFUNCTION(BlueprintCallable, meta = (Keywords = "OrchestriaNetwork ", DisplayName = "Set Host Role"), Category = "OrchestriaNetwork")
        static void OrchestriaNetwork_SetHostRole(int roleId);

    UFUNCTION(BlueprintCallable, meta = (Keywords = "OrchestriaNetwork ", DisplayName = "Get Roles"), Category = "OrchestriaNetwork")
        static TArray<int> OrchestriaNetwork_GetRoles();

    UFUNCTION(BlueprintCallable, meta = (Keywords = "OrchestriaNetwork ", DisplayName = "Start Game"), Category = "OrchestriaNetwork")
        static void OrchestriaNetwork_StartGame();

    UFUNCTION(BlueprintCallable, meta = (Keywords = "OrchestriaNetwork ", DisplayName = "Report Ready"), Category = "OrchestriaNetwork")
        static void OrchestriaNetwork_ReportReady();

    UFUNCTION(BlueprintCallable, meta = (Keywords = "OrchestriaNetwork ", DisplayName = "Get Game State"), Category = "OrchestriaNetwork")
        static int OrchestriaNetwork_GetGameState();

    UFUNCTION(BlueprintCallable, meta = (Keywords = "OrchestriaNetwork ", DisplayName = "Get Start Delay"), Category = "OrchestriaNetwork")
        static float OrchestriaNetwork_GetStartDelay();

    UFUNCTION(BlueprintCallable, meta = (Keywords = "OrchestriaNetwork ", DisplayName = "Get Score"), Category = "OrchestriaNetwork")
        static int OrchestriaNetwork_GetScore();

    UFUNCTION(BlueprintCallable, meta = (Keywords = "OrchestriaNetwork ", DisplayName = "Report Score"), Category = "OrchestriaNetwork")
        static void OrchestriaNetwork_ReportScore(int value);
};
