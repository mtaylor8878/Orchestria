#include "OrchestriaNetworkPrivatePCH.h"

DEFINE_LOG_CATEGORY(LogOrchestriaNetwork);

#define LOCTEXT_NAMESPACE "OrchestriaNetwork"

class FOrchestriaNetwork : public IOrchestriaNetwork
{
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE( FOrchestriaNetwork, OrchestriaNetwork )

void FOrchestriaNetwork::StartupModule()
{
#if PLATFORM_ANDROID
	UOrchestriaNetworkFunctions::InitJavaFunctions();
#endif
}


void FOrchestriaNetwork::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE
