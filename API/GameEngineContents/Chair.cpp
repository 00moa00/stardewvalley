#include "Chair.h"

Chair::Chair() 
{
}

Chair::~Chair() 
{
}

void Chair::Start()
{
	ItemRenderer_ = CreateRenderer("Chair.bmp");
	ItemRenderer_->CameraEffectOff();
	SetScale({ 51, 96 });
	///ItemRenderer_->SetPivot()
	//ItemCollider_ = CreateCollision("Item", { 40, 40 });
	ItemRenderer_->SetPivot({ GetPosition().x + 24.f, GetPosition().y });
	ObjectType_ = OBJECTTYPE::TOOL;
}

