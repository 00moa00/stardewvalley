#include "Items.h"
#include "GameData.h"
#include "RendererData.h"


Items::Items() :
	ItemRenderer_ (nullptr),
	ItemCollider_ (nullptr),
	MouseHoldItem_ (false),
	InMouse (false),
	InBox (true),
	Count_ (0),

	Name_ ({""}),
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
	Font_ = GetLevel()->CreateActor<Font>((int)PLAYLEVEL::FONT);
	Font_->ChangeNum(Count_);
	Font_->SetPositionItem({GetPosition()});

}

void Items::Update()
{

	switch (ItemState_)
	{
	case ITEM_STATE::INIT :
		break;

	case ITEM_STATE::ADDITEM :
		//Font_->ChangeNum(100);
		//Font_->SetPositionItem({ GetPosition() });

		ItemState_ = ITEM_STATE::INIT;
		break;
	}
	

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