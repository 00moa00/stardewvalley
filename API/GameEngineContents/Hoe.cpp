#include "Hoe.h"

Hoe* Hoe::MainHoe = nullptr;

Hoe::Hoe() 
{
}

Hoe::~Hoe() 
{
}

void Hoe::Start()
{
//	Font_ = GetLevel()->CreateActor<Font>((int)PLAYLEVEL::FONT);
	//Font_->ChangeNumItem(1);


	ItemRenderer_ = CreateRenderer("tools.bmp");
	ItemRenderer_->SetIndex(static_cast<size_t>(TOOL::HOE_IN_INVENTROY));
	ItemRenderer_->CameraEffectOff();

	ItemCollider_ = CreateCollision("Item", { 40, 40 });

	ItemType_ = ITEMTYPE::TOOL;
	ToolType_ = TOOLTYPE::HOE;

	SetItemName("Hoe");

	FileName_ = "tools.bmp";
	FileIndex_ = static_cast<size_t>(TOOL::HOE_IN_INVENTROY);

	Power_ = 1;

}

void Hoe::Update()
{

	

}

void Hoe::Render()
{
}

void Hoe::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainHoe = this;


}
