#pragma once

class BaseIntegrator : public ZeroEngine::ZilchComponent
{
public:
  ZilchDeclareType(Zilch::TypeCopyMode::ReferenceType);
  
  BaseIntegrator();
  
  void Initialize(ZeroEngine::CogInitializer* initializer);
  
  void OnAddIntegratableObject(CustomObjectEvent* e);
  void OnObjectDestroyed(ObjectEvent* e);

  void ComputeGlobalForces();
  void ApplyForces(IntegratableObject* body, float dt);
  void IntegrateVelocity(IntegratableObject* body, float dt);
  void IntegratePosition(IntegratableObject* body, float dt);
  void ClearForces(IntegratableObject* body, float dt);

  Zero::HashSet<ZeroEngine::Cog*> mCogs;
  Real3 mGlobalForces;
  Real3 mGlobalAcceleration;
  int mSubSteps;
};
