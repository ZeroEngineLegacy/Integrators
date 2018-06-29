#include "PluginIntegratorsPrecompiled.hpp"

ZilchDefineType(MidPointIntegrator, builder, type)
{
  // This is required for component binding
  ZilchBindDestructor();
  ZilchBindConstructor();
  ZilchBindMethod(Initialize);
  
  // Note: All event connection methods must be bound
  ZilchBindMethod(OnLogicUpdate);
}

void MidPointIntegrator::Initialize(ZeroEngine::CogInitializer* initializer)
{
  BaseIntegrator::Initialize(initializer);
  ZeroConnectThisTo(this->GetSpace(), "LogicUpdate", "OnLogicUpdate");
}

void MidPointIntegrator::OnLogicUpdate(ZeroEngine::UpdateEvent* event)
{
  float dt = event->GetDt() / this->mSubSteps;
  for(int i = 0; i < this->mSubSteps; ++i)
    this->RunSubStep(dt);
}

void MidPointIntegrator::RunSubStep(float dt)
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

void MidPointIntegrator::IntegratePosition(IntegratableObject* body, float dt)
{
  Real3 velocity = body->mVelocity;
  Real3 pos = body->mPosition;
  Real3 acceleration = body->GetAcceleration();
  float mass = body->mMass;

  pos += (velocity + dt * 0.5f *acceleration) * dt;

  body->mPosition = pos;
  body->SetWorldPosition();
}
