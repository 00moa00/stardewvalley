#include "Ruby.h"
#include "Player.h"

Ruby* Ruby::MainRuby = nullptr;
Font* Ruby::Font_;

Ruby::Ruby() 
{
}

Ruby::~Ruby() 
{
}

void Ruby::Start()
{
	ItemSpeed_.x = 1.f;
	ItemSpeed_.y = 5.f;

	ItemRenderer_ = CreateRenderer("springobjects.bmp");
	ItemRenderer_->SetIndex(static_cast<size_t>(ITEM::RUBY));
	ItemRenderer_->CameraEffectOn();

	ItemCollider_ = CreateCollision("Item", { 40.f , 40.f });


	if (Font_ == nullptr)
	{
		Font_ = GetLevel()->CreateActor<Font>((int)PLAYLEVEL::FONT);
	}

	Font_->ChangeWhiteColor();
	Font_->ChangeNumItemLeftSort(ItemCount_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });

	ItemName_ = "DropStone";

	//핸드 아이템용
	isPossibleHand_ = true;
	FileName_ = "springobjects.bmp";
	FileIndex_ = static_cast<size_t>(ITEM::RUBY);

}

void Ruby::Update()
{
	switch (ItemState_)
	{
	case ITEM_STATE::INIT:
		Font_->SetPositionItem({ GetPosition() });

		if (isMove_ == true)
		{

			PrePosition_ = this->GetPosition();
			ItemState_ = ITEM_STATE::ANIMATION;
		}

		break;
	case ITEM_STATE::ANIMATION:

		MoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 700.0f;
		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime());

		if (this->GetPosition().y > PrePosition_.y)
		{
			ItemState_ = ITEM_STATE::MOVETOPLAYER;

		}

		break;
	case ITEM_STATE::MOVETOPLAYER:

		MoveToPlayer();
		if (isMapItemDeath_ == true)
		{
			Player::MainPlayer->GetInventroy()->NewItem<DropStone>();
		}

		break;
	default:
		break;
	}
}

void Ruby::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainRuby = this;
	Font_ = Font_;
}

void Ruby::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Font_->NextLevelOn();
}

void Ruby::AddItemCount()
{
	++ItemCount_;
	Font_->ChangeNumItemLeftSort(ItemCount_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
}

void Ruby::SubItemCount()
{
	if (ItemCount_ == 1)
	{
		ItemCount_ = 0;
		Player::MainPlayer->SetResetPlayerHandItem();
		Inventory::MainInventory->FindAndErasePlayerItemList(this->GetItemNameConstRef());
		Font_ = nullptr;
		this->Death();
	}
	else
	{
		--ItemCount_;
		Font_->ChangeNumItemLeftSort(ItemCount_, { GetPosition().x + 11.f ,GetPosition().y + 11.f });
	}
}

void Ruby::UpdateOff()
{
	this->Off();
	Font_->Off();
}

void Ruby::UpdateOn()
{
	this->On();
	Font_->On();
}
