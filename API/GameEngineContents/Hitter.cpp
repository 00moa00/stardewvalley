#include "Hitter.h"

Hitter::Hitter() 
{
}

Hitter::~Hitter() 
{
}

void Hitter::Start()
{
	ItemRenderer_ = CreateRenderer("Hitter.bmp");
	ItemRenderer_->CameraEffectOff();
	SetScale({ 96, 240 });
	///ItemRenderer_->SetPivot()
	//ItemCollider_ = CreateCollision("Item", { 40, 40 });
	ObjectType_ = OBJECTTYPE::TOOL;

}

