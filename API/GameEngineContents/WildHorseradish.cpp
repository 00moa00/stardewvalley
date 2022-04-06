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

	ItemCollider_= CreateCollision("Item", { 48, 48 });

}

void WildHorseradish::Update()
{
}

void WildHorseradish::Render()
{
}
