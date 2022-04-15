#include "PlayerHandItem.h"

PlayerHandItem::PlayerHandItem() 
{
}

PlayerHandItem::~PlayerHandItem() 
{
}

void PlayerHandItem::Start()
{
	ItemRenderer_ = CreateRenderer("Empty.bmp");
	ItemRenderer_->CameraEffectOn();
	SetPosition({ 600,600 });
}

void PlayerHandItem::Update()
{
}

