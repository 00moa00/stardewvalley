#include "GiftBox.h"
GiftBox* GiftBox::MainGiftBox = nullptr;

GiftBox::GiftBox() 
	:
	OpenUpdate_(OPEN_UPDATE::WAIT)
{
}

GiftBox::~GiftBox() 
{
}

void GiftBox::Start()
{
	ItemRenderer_ = CreateRenderer("Giftbox.bmp");
	ItemRenderer_->SetIndex(static_cast<size_t>(ITEM::PARSNIP));
	ItemRenderer_->CameraEffectOn();

	ItemRenderer_->CreateAnimation("Giftbox.bmp", "OPEN", 0, 9 , 0.200f, false);
	ItemRenderer_->CreateAnimation("Giftbox.bmp", "INIT", 0, 0, 0.200f, false);
	ItemRenderer_->ChangeAnimation("INIT");


	ItemCollider_ = CreateCollision("GiftBox", { 60, 40 });

	ItemName_ = "GiftBox";
}

void GiftBox::Update()
{

	switch (OpenUpdate_)
	{
	case OPEN_UPDATE::WAIT:

		if (ItemCollider_->CollisionResult("Player", ColList, CollisionType::Rect, CollisionType::Rect)
			&& GameEngineInput::GetInst()->IsDown("LeftClick"))
		{
			OpenUpdate_ = OPEN_UPDATE::OPEN;
			ItemRenderer_->ChangeAnimation("OPEN");
		}

		break;
	case OPEN_UPDATE::OPEN:

		if (ItemRenderer_->IsEndAnimation())
		{
			this->Death();
		}

		break;
	default:
		break;
	}
	
}

void GiftBox::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainGiftBox = this;
}

void GiftBox::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}
