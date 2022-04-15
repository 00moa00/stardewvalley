#include "Items.h"
#include "GameData.h"

bool Items::IsWall(const float4 pos, const float4 scale,  float4 dir)
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

Items::Items() :
	ItemRenderer_(nullptr),
	ItemCollider_(nullptr),
	InMouse(false),
	MouseHoldItem_(false),
	InBox(true),
	Name_({""}),
	ItemType_(ITEMTYPE::ITEM),
	ToolType_(TOOLTYPE::OTHER)
		
{

}

Items::~Items() 
{
}

