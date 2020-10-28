#include "RPPGameModule.h"
 
DEFINE_LOG_CATEGORY(RPPGameModule);
 
#define LOCTEXT_NAMESPACE "FRPPGameModule"
 
void FRPPGameModule::StartupModule()
{
	UE_LOG(RPPGameModule, Warning, TEXT("RPPGameModule module has started!"));
}
 
void FRPPGameModule::ShutdownModule()
{
	UE_LOG(RPPGameModule, Warning, TEXT("RPPGameModule module has shut down"));
}
 
#undef LOCTEXT_NAMESPACE
 
IMPLEMENT_MODULE(FRPPGameModule,RPPGameModule)