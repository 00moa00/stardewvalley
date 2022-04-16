#include "Items.h"
#include "GameData.h"


Items::Items() :
	ItemRenderer_ (nullptr),
	ItemCollider_ (nullptr),

	MouseHoldItem_ (false),
	InMouse (false),
	isPossibleHand_(false),
	isDeath_(false),
	InBox (true),

	FileIndex_(0),
	Count_ (1),

	Gravity_({}),
	ItemSpeed_({}),
	ItemPosition_({}),

	Name_ ({""}),
	FilePath_({""}),
	ItemType_ (ITEMTYPE::ITEM),
	ToolType_ (TOOLTYPE::OTHER),
	ItemState_(ITEM_STATE::INIT)
		
{

}

Items::~Items() 
{
}

void Items::Start()
{


}

void Items::Update()
{

//	ItemRenderer_->GetImage()->;

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