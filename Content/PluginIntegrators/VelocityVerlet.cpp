#include "PluginIntegratorsPrecompiled.hpp"

ZilchDefineType(VelocityVerlet, builder, type)
{
  // This is required for component binding
  ZilchBindDestructor();
  ZilchBindConstructor();
  ZilchBindMethod(Initialize);
  
  // Note: All event connection methods must be bound
  ZilchBindMethod(OnLogicUpdate);
}

void VelocityVerlet::Initialize(ZeroEngine::CogInitializer* initializer)
{
  BaseIntegrator::Initialize(initializer);
  ZeroConnectThisTo(this->GetSpace(), "LogicUpdate", "OnLogicUpdate");
}

void VelocityVerlet::OnLogicUpdate(ZeroEngine::UpdateEvent* event)
{
  float dt = event->GetDt() / this->mSubSteps;
  for(int i = 0; i < this->mSubSteps; ++i)
    this->RunSubStep(dt);
}

void VelocityVerlet::RunSubStep(float dt)
{
  ComputeGlobalForces();

  auto range = mCogs.All();
  for(; !range.Empty(); range.PopFront())
  {
    Cog* cog = range.Front();
    IntegratableObject* body = cog->has(IntegratableObject);

    ApplyForces(body, dt);
    IntegrateVelocity(body, dt);
    IntegratePosition(body, dt);
    ClearForces(body, dt);
  }
}

void VelocityVerlet::ApplyForces(IntegratableObject* body, float dt)
{
  BaseIntegrator::ApplyForces(body, dt);
}

void VelocityVerlet::IntegrateVelocity(IntegratableObject* body, float dt)
{
  Real3 velocity = body->mVelocity;
  Real3 acceleration = body->GetAcceleration();

  velocity += 0.5f * (body->mOldAcceleration + acceleration) * dt;

  body->mVelocity = velocity;
}

void VelocityVerlet::IntegratePosition(IntegratableObject* body, float dt)
{
  Real3 position = body->mPosition;
  Real3 velocity = body->mVelocity;
  Real3 acceleration = body->GetAcceleration();

  position += velocity * dt + 0.5f * acceleration * dt * dt;

  body->mPosition = position;
  body->SetWorldPosition();
}

void VelocityVerlet::ClearForces(IntegratableObject* body, float dt)
{
  body->mOldAcceleration = body->GetAcceleration();
  body->mForce = Real3::cZero;
}
