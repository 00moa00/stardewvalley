#include "WildHorseradish.h"


WildHorseradish::WildHorseradish(){

}

WildHorseradish::~WildHorseradish()
{
}

void WildHorseradish::Start()
{
	//SetPosition(GameEngineWindow::GetScale().Half());

	ItemRenderer_= CreateRenderer("springobjects.bmp");
	ItemRenderer_->SetIndex(static_cast<size_t>(ITEM::WILD_HORSERADISH));
	ItemRenderer_->CameraEffectOff();

	ItemCollider_= CreateCollision("Item", { 40, 40 });
	ItemType_ = ITEMTYPE::ITEM;

}

void WildHorseradish::Update()
{
}

void WildHorseradish::Render()
{
}
