#include "PlayerHouse.h"

PlayerHouse::PlayerHouse() 
{
}

PlayerHouse::~PlayerHouse() 
{
}

void PlayerHouse::Start()
{
	ItemRenderer_ = CreateRenderer("house.bmp");
	ItemRenderer_->SetPivotType(RenderPivot::CENTER);
	SetScale({ 300, 300 });

}

void PlayerHouse::Update()
{
}

