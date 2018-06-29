#pragma once

class MidPointIntegrator : public BaseIntegrator
{
public:
  ZilchDeclareType(Zilch::TypeCopyMode::ReferenceType);
  
  void Initialize(ZeroEngine::CogInitializer* initializer);
  
  void OnLogicUpdate(ZeroEngine::UpdateEvent* event);

  void RunSubStep(float dt);
  void IntegratePosition(IntegratableObject* body, float dt);
};
