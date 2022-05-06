#include "WildHorseradish.h"

WildHorseradish* WildHorseradish::MainWildHorseradish = nullptr;

WildHorseradish::WildHorseradish(){

}

WildHorseradish::~WildHorseradish()
{
}

void WildHorseradish::Start()
{

	ItemRenderer_= CreateRenderer("springobjects.bmp");
	ItemRenderer_->SetIndex(static_cast<size_t>(ITEM::WILD_HORSERADISH));
	ItemRenderer_->CameraEffectOff();

	ItemCollider_= CreateCollision("Item", { 40, 40 });
	
	SetItemName("WildHorseradish");

	SellPrice_ = 40;

	//핸드 아이템용
	isPossibleHand_ = true;
	FileName_ = "springobjects.bmp";
	FileIndex_ = static_cast<size_t>(ITEM::WILD_HORSERADISH);

}

void WildHorseradish::Update()
{
}

void WildHorseradish::Render()
{
}

void WildHorseradish::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainWildHorseradish = this;
}
