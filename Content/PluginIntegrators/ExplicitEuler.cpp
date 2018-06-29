#include "PluginIntegratorsPrecompiled.hpp"

ZilchDefineType(ExplicitEuler, builder, type)
{
  // This is required for component binding
  ZilchBindDestructor();
  ZilchBindConstructor();
  ZilchBindMethod(Initialize);
  
  // Note: All event connection methods must be bound
  ZilchBindMethod(OnLogicUpdate);
}

void ExplicitEuler::Initialize(ZeroEngine::CogInitializer* initializer)
{
  BaseIntegrator::Initialize(initializer);
  ZeroConnectThisTo(this->GetSpace(), "LogicUpdate", "OnLogicUpdate");
}

void ExplicitEuler::OnLogicUpdate(ZeroEngine::UpdateEvent* event)
{
  float dt = event->GetDt() / this->mSubSteps;
  for(int i = 0; i < this->mSubSteps; ++i)
    this->RunSubStep(dt);
}

void ExplicitEuler::RunSubStep(float dt)
{
  ComputeGlobalForces();

  auto range = mCogs.All();
  for(; !range.Empty(); range.PopFront())
  {
    Cog* cog = range.Front();
    IntegratableObject* body = cog->has(IntegratableObject);

    ApplyForces(body, dt);
    IntegratePosition(body, dt);
    IntegrateVelocity(body, dt);
    ClearForces(body, dt);
  }
}
