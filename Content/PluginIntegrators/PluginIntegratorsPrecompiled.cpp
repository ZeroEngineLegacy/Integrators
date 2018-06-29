#include "PluginIntegratorsPrecompiled.hpp"

//***************************************************************************
ZilchDefineStaticLibraryAndPlugin(PluginIntegratorsLibrary, PluginIntegratorsPlugin, ZilchDependencyStub(Core) ZilchDependencyStub(ZeroEngine))
{
  ZilchInitializeType(PluginIntegrators);
  ZilchInitializeType(PluginIntegratorsEvent);
  ZilchInitializeType(BaseIntegrator);
  ZilchInitializeType(ExplicitEuler);
  ZilchInitializeType(IntegratableObject);
  ZilchInitializeType(CustomObjectEvent);
  ZilchInitializeType(SemiImplicitEuler);
  ZilchInitializeType(MidPointIntegrator);
  ZilchInitializeType(VelocityVerlet);
  // Auto Initialize (used by Visual Studio plugins, do not remove this line)
}

//***************************************************************************
void PluginIntegratorsPlugin::Initialize()
{
  // One time startup logic goes here
  // This runs after our plugin library/reflection is built
  Zilch::Console::WriteLine("PluginIntegratorsPlugin::Initialize");
}

//***************************************************************************
void PluginIntegratorsPlugin::Uninitialize()
{
  // One time shutdown logic goes here
  Zilch::Console::WriteLine("PluginIntegratorsPlugin::Uninitialize");
}
