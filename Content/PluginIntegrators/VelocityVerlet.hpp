#pragma once

class VelocityVerlet : public BaseIntegrator
{
public:
  ZilchDeclareType(Zilch::TypeCopyMode::ReferenceType);
  
  void Initialize(ZeroEngine::CogInitializer* initializer);
  
  void OnLogicUpdate(ZeroEngine::UpdateEvent* event);
  void RunSubStep(float dt);

  void ApplyForces(IntegratableObject* body, float dt);
  void IntegrateVelocity(IntegratableObject* body, float dt);
  void IntegratePosition(IntegratableObject* body, float dt);
  void ClearForces(IntegratableObject* body, float dt);
};
