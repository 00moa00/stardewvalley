#include "Items.h"
#include "GameData.h"
#include "Player.h"

//Font* Items::Font_ = nullptr;

Items::Items() :
	ItemRenderer_ (nullptr),
	ItemCollider_ (nullptr),
	MapItemCollider_(nullptr),

	MouseHoldItem_ (false),
	InMouse (false),
	isPossibleHand_(false),
	isDeath_(false),
	MoveFlag_(false),
	InBox (true),

	State_(MOVE::Y_UP),
	Normal_(float4::ZERO),
	targetPos_({}),
	TransformPos_({}),
	FileIndex_(0),
	SellPrice_(0),
	Count_ (1),
	Damage_(5),

	Gravity_({}),
	ItemSpeed_({}),
	ItemPosition_({}),

	Name_ ({""}),
	FileName_({""}),
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
	NextLevelOn();
}


bool Items::IsWall(const float4 pos, const float4 scale, float4 dir)
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

	if (Check >= 200)
	{
		return;
	}


	if (Check <= 20)
	{
		isDeath_ = true;
		Death();
		return;
	}

	Dir.Normal2D();
	SetMove(Dir * GameEngineTime::GetDeltaTime() * 70.0f);


}

void Items::SetReRenderer()
{
	ItemRenderer_ = CreateRenderer();
	ItemRenderer_ = CreateRenderer(FileName_);
	ItemRenderer_->SetIndex(FileIndex_);
	ItemRenderer_->CameraEffectOff();

}

void Items::SetCrushAnimation()
{

}

void Items::SetInitAnimation()
{
}

