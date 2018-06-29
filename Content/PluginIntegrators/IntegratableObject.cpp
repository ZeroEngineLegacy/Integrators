#include "PluginIntegratorsPrecompiled.hpp"

//-------------------------------------------------------------------IntegratableObject
ZilchDefineType(IntegratableObject, builder, type)
{
  // This is required for component binding
  ZilchBindDestructor();
  ZilchBindConstructor();
  ZilchBindMethod(Initialize);
  
  // Note: All event connection methods must be bound
  ZilchBindMethod(OnAllObjectsInitialized);
  
  ZilchBindMember(mTransform)->AddAttribute("Dependency");
  ZilchBindMemberProperty(mVelocity)->AddAttributeChainable("Serialize");
  ZilchBindMemberProperty(mMass)->AddAttributeChainable("Serialize");
  ZilchBindMember(mForce);
  ZilchBindMember(mPosition);
}

IntegratableObject::IntegratableObject()
{
  mMass = 1;
  mVelocity = Real3::cZero;
  mForce = Real3::cZero;
  mOldAcceleration = Real3::cZero;
}

void IntegratableObject::Initialize(ZeroEngine::CogInitializer* initializer)
{
  ZeroConnectThisTo(initializer, "AllObjectsInitialized", "OnAllObjectsInitialized");

  mTransform = GetOwner()->has(Transform);
  mPosition = mTransform->GetWorldTranslation();
}

void IntegratableObject::OnAllObjectsInitialized(ZeroEngine::Event* e)
{
  Zilch::HandleOf<CustomObjectEvent> toSend = ZilchAllocate(CustomObjectEvent);
  toSend->mCog = GetOwner();
  this->GetSpace()->DispatchEvent("AddIntegratableObject", toSend);
}

void IntegratableObject::SetWorldPosition()
{
  mTransform->SetWorldTranslation(mPosition);
  SendTransformUpdate();
}

void IntegratableObject::SendTransformUpdate()
{
  Cog* owner = GetOwner();
  Zilch::HandleOf<CustomObjectEvent> toSend = ZilchAllocate(CustomObjectEvent);
  toSend->mCog = owner;
  owner->DispatchEvent("TransformIntegrated", toSend);
}

Real3 IntegratableObject::GetAcceleration()
{
  Real3 acceleration = Real3::cZero;
  if(mMass != 0)
    acceleration = mForce / mMass;
  return acceleration;
}
