#include "PluginIntegratorsPrecompiled.hpp"

ZilchDefineType(SemiImplicitEuler, builder, type)
{
  // This is required for event binding
  ZilchBindDestructor();
  ZilchBindConstructor();

  ZilchBindMethod(Initialize);

  // Note: All event connection methods must be bound
  ZilchBindMethod(OnLogicUpdate);
}

void SemiImplicitEuler::Initialize(ZeroEngine::CogInitializer* initializer)
{
  BaseIntegrator::Initialize(initializer);
  ZeroConnectThisTo(this->GetSpace(), "LogicUpdate", "OnLogicUpdate");
}

void SemiImplicitEuler::OnLogicUpdate(ZeroEngine::UpdateEvent* event)
{
  float dt = event->GetDt() / this->mSubSteps;
  //dt = event->GetDt();
  for(int i = 0; i < this->mSubSteps; ++i)
    this->RunSubStep(dt);
}

void SemiImplicitEuler::RunSubStep(float dt)
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
