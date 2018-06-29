#pragma once

//-------------------------------------------------------------------CustomObjectEvent
class CustomObjectEvent : public ZeroEngine::ZilchEvent
{
public:
  ZilchDeclareType(Zilch::TypeCopyMode::ReferenceType);
  
  CustomObjectEvent();
  ~CustomObjectEvent();

  Zilch::HandleOf<Cog> mCog;
};
