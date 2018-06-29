#pragma once

class ExplicitEuler : public BaseIntegrator
{
public:
  ZilchDeclareType(Zilch::TypeCopyMode::ReferenceType);
  
  void Initialize(ZeroEngine::CogInitializer* initializer);
  
  void OnLogicUpdate(ZeroEngine::UpdateEvent* event);
  void RunSubStep(float dt);
};
