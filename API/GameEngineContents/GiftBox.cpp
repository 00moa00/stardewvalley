#include "GiftBox.h"
#include "Inventory.h"
#include "Parsnip_Seeds.h"
#include "KiraEffect.h"

GiftBox* GiftBox::MainGiftBox;

GiftBox::GiftBox() 
	:
	OpenUpdate_(OPEN_UPDATE::WAIT),
	MoveItem(nullptr)
{
}

GiftBox::~GiftBox() 
{
}

void GiftBox::Start()
{
	ItemRenderer_ = CreateRenderer("Giftbox.bmp");
	ItemRenderer_->SetIndex(0);
	ItemRenderer_->CameraEffectOff();
	ItemRenderer_->SetPivotType(RenderPivot::BOT);

	ItemRenderer_->CreateAnimation("Giftbox.bmp", "OPEN", 0, 9 , 0.200f, false);
	ItemRenderer_->CreateAnimation("Giftbox.bmp", "INIT", 0, 0, 0.200f, false);
	ItemRenderer_->ChangeAnimation("INIT");


	ItemCollider_ = CreateCollision("MapObject", { 48, 35 });
	ItemCollider_->SetPivot({ 0, -30 });
	SetScale( { 60, 60 });
	ItemName_ = "GiftBox";

	ObjectType_ = OBJECTTYPE::GETITEM;

}

void GiftBox::Update()
{
	KiraEffect* KiraEffect_;
	switch (OpenUpdate_)
	{
	case OPEN_UPDATE::WAIT:
		break;
	case OPEN_UPDATE::OPEN:

		ItemRenderer_->ChangeAnimation("OPEN");


		OpenUpdate_ = OPEN_UPDATE::GET;
		break;

	case OPEN_UPDATE::GET:

		if (ItemRenderer_->IsEndAnimation())
		{
			MoveItem = GetLevel()->CreateActor<Parsnip_Seeds>(static_cast<int>(PLAYLEVEL::ITEM));
			MoveItem->SetPosition({ Player::MainPlayer->GetPosition().x, Player::MainPlayer->GetPosition().y -80.f });
			
			KiraEffect_ = GetLevel()->CreateActor<KiraEffect>(static_cast<int>(PLAYLEVEL::EFFECT));
			KiraEffect_->SetPosition({ Player::MainPlayer->GetPosition().x, Player::MainPlayer->GetPosition().y - 80.f });
			KiraEffect_->GetRenderer()->CameraEffectOff();
			
			Player::MainPlayer->SetPlayerDirDown();

			ItemRenderer_->Off();

			OpenUpdate_ = OPEN_UPDATE::MOVE_ITEM;
		}

		break;

	case OPEN_UPDATE::MOVE_ITEM:

		MoveItem->SetMove(float4::UP * GameEngineTime::GetDeltaTime() * 30.f);


		if (MoveItem->GetPosition().y < Player::MainPlayer->GetPosition().y - 100.f)
		{
			Items* HandItem = Inventory::MainInventory->NewItem<Parsnip_Seeds>(15);
			GameEngineSound::SoundPlayOneShot("getNewSpecialItem.wav");

			Inventory::MainInventory->SetCurrentItem(HandItem);
			//Ȥ�� ���� ����
			Inventory::MainInventory->SetCurrentItemParsnipSeed();
			Player::MainPlayer->SetUpdateStateInit();

			MoveItem->Death();
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

void GiftBox::ItemCollPlayer()
{
	 OpenUpdate_ = OPEN_UPDATE::OPEN;

}
