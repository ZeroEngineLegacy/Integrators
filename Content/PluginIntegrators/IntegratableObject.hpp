#pragma once

//-------------------------------------------------------------------IntegratableObject
class IntegratableObject : public ZeroEngine::ZilchComponent
{
public:
  ZilchDeclareType(Zilch::TypeCopyMode::ReferenceType);
  
  IntegratableObject();
  
  void Initialize(ZeroEngine::CogInitializer* initializer);
  
  void OnAllObjectsInitialized(ZeroEngine::Event* e);

  void SetWorldPosition();
  void SendTransformUpdate();
  Real3 GetAcceleration();

  Zilch::HandleOf<Transform> mTransform;
  Real3 mVelocity;
  Real3 mPosition;
  Real3 mForce;
  Real mMass;

  // Velocity Verlet
  Real3 mOldAcceleration;
};
