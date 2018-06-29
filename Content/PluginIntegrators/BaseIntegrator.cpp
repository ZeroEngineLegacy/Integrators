#include "PluginIntegratorsPrecompiled.hpp"

ZilchDefineType(BaseIntegrator, builder, type)
{
  // This is required for component binding
  ZilchBindDestructor();
  ZilchBindConstructor();
  ZilchBindMethod(Initialize);

  type->AddAttribute("ComponentInterface");
  
  // Note: All event connection methods must be bound
  ZilchBindMethod(OnAddIntegratableObject);
  ZilchBindMethod(OnObjectDestroyed);
  ZilchBindMember(mSubSteps);
}

BaseIntegrator::BaseIntegrator()
{
  mSubSteps = 1;
}

void BaseIntegrator::Initialize(ZeroEngine::CogInitializer* initializer)
{
  ZeroConnectThisTo(this->GetSpace(), "AddIntegratableObject", "OnAddIntegratableObject");
}

void BaseIntegrator::OnAddIntegratableObject(CustomObjectEvent* e)
{
  Cog* cog = e->mCog;
  mCogs.Insert(cog);
  
  ZeroConnectThisTo(cog, "CogDestroy", "OnObjectDestroyed");
}

void BaseIntegrator::OnObjectDestroyed(ObjectEvent* e)
{
  Cog* cog = e->GetSource().Get<Cog*>();
  mCogs.Erase(cog);
}

void BaseIntegrator::ComputeGlobalForces()
{
  mGlobalForces = Real3::cZero;
  mGlobalAcceleration = Real3::cZero;

  Cog* levelSettings = GetOwner()->GetLevelSettings();
  ZeroEngine::GravityEffect* gravityEffect = levelSettings->has(ZeroEngine::GravityEffect);
  if(gravityEffect != nullptr)
  {
    Real3 acceleration = gravityEffect->GetWorldDirection() * gravityEffect->GetStrength();
    mGlobalAcceleration += acceleration;
  }

  Zilch::HandleOf<CustomObjectEvent> toSend = ZilchAllocate(CustomObjectEvent);
  toSend->mCog = GetOwner();
  this->GetSpace()->DispatchEvent("ApplyGlobalForces", toSend);
}

void BaseIntegrator::ApplyForces(IntegratableObject* body, float dt)
{
  if(body->mMass != 0)
    body->mForce += mGlobalAcceleration / body->mMass + mGlobalForces;
}

void BaseIntegrator::IntegrateVelocity(IntegratableObject* body, float dt)
{
  Real3 velocity = body->mVelocity;
  float mass = body->mMass;

  Real3 acceleration = body->GetAcceleration();
  velocity += dt * acceleration;
  body->mVelocity = velocity;
}

void BaseIntegrator::IntegratePosition(IntegratableObject* body, float dt)
{
  Real3 velocity = body->mVelocity;
  Real3 pos = body->mPosition;

  pos += dt * velocity;

  body->mPosition = pos;
  body->SetWorldPosition();
}

void BaseIntegrator::ClearForces(IntegratableObject* body, float dt)
{
  body->mForce = Real3(0, 0, 0);
}
