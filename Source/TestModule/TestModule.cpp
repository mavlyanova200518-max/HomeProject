
#include "TestModule.h"

#define LOCTEXT_NAMESPACE "FTestModule"

void FTestModule::StartupModule()
{
}

void FTestModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FTestModule, TestModule)
