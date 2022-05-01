#include "Items.h"
#include "GameData.h"
#include "Player.h"

//Font* Items::Font_ = nullptr;

Items::Items() :
	ItemRenderer_ (nullptr),
	ItemCollider_ (nullptr),
	SubRenderer_(nullptr),
	SubCollider_(nullptr),
	MouseHoldItem_ (false),
	InMouse (false),
	isPossibleHand_(false),
	isMapItemDeath_(false),
	isMove_(false),
	InBox (true),

	State_(MOVE::Y_UP),
	Normal_(float4::ZERO),

	AddEnery_(0),
	RamdomDir_(0),
	AddHP_(0),
	FileIndex_(0),
	SellPrice_(0),
	ChangeSpeed_(0),
	ItemCount_ (1),
	Damage_(5),

	ChangeTime_(0.f),

	ItemSpeed_({}),
	ItemPosition_({}),

	RandomItemCount(),
	RandomItemPosX(),
	RamdomItemPosY(),

	ItemName_({""}),
	FileName_({""}),

	DrinkType_(DRINKTYPE::OTHER),
	SeedType_(SEEDTYPE::NONE),
	ItemType_ (ITEMTYPE::ITEM),
	ToolType_ (TOOLTYPE::OTHER),
	ItemState_(ITEM_STATE::INIT)
		
{

}

Items::~Items() 
{

}

void Items::TreeOff()
{

}

void Items::Start()
{


}

void Items::Update()
{

//	ItemRenderer_->GetImage()->;

}

void Items::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	
	//Font_ = Font_;
}

void Items::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	//Font_->NextLevelOn();
	//NextLevelOn();
}


void Items::DropItemInMap()
{
}

Crops* Items::CreateCrops()
{
	return nullptr;
}

void Items::ItemCollPlayer()
{
}

void Items::ItemCollFalsePlayer()
{
}

void Items::CreateMoveFlag(std::string _CollName)
{
}

void Items::ChnageImageFile(std::string _FileName)
{
}

void Items::ChnageImageFileAndIndex(std::string _FileName, ITEM _index)
{
}

bool Items::ItemCheck(const float4 pos, const float4 scale)
{

	int OtherLeft = pos.ix() - scale.hix();
	int OtherRight = pos.ix() + scale.hix();
	int OtherTop = pos.iy() - scale.hiy();
	int OtherBottom = pos.iy() + scale.hiy();

	//	GameEngineRect DebugRect;


	if (GetRight() < OtherLeft)
	{
		return false;
	}

	if (OtherRight < GetLeft())
	{
		return false;
	}

	if (GetBottom() < OtherTop)
	{
		return false;
	}

	if (OtherBottom < GetTop())
	{
		return false;
	}

	return true;
}



void Items::MoveToPlayer()
{
	float4 Dir = Player::MainPlayer->GetPosition() - this->GetPosition();
	float Check = Dir.Len2D();

	if (Check >= 100)
	{
		return;
	}


	if (Check <= 20)
	{
		isMapItemDeath_ = true;
		Death();
		return;
	}

	Dir.Normal2D();
	SetMove(Dir * GameEngineTime::GetDeltaTime() * 150.0f);


}

void Items::SetCrushAnimation()
{

}

void Items::SetInitAnimation()
{
}

void Items::AddItemCount()
{
}

void Items::SubItemCount()
{
}

void Items::SetItemCount(int _Count)
{
}

