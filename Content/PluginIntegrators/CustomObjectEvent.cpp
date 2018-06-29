#include "PluginIntegratorsPrecompiled.hpp"

//***************************************************************************
ZilchDefineType(CustomObjectEvent, builder, type)
{
  // This is required for event binding
  ZilchBindDestructor();
  ZilchBindConstructor();

  ZilchBindMemberProperty(mCog);
}

//***************************************************************************
CustomObjectEvent::CustomObjectEvent()
{
}

//***************************************************************************
CustomObjectEvent::~CustomObjectEvent()
{
}
