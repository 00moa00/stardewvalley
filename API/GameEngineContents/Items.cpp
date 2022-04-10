#include "Items.h"
#include "GameData.h"

bool Items::IsWall(float4 pos, float4 scale, float4 dir)
{

	float4 NextPos = pos + (dir * GameEngineTime::GetDeltaTime() * 150.f);

	//float4 CheckPos = float4::ZERO;
	float4 Margin = float4::ZERO;

	if (dir == float4::RIGHT) {
		Margin = float4(8.f, 0.f);
	}
	if (dir == float4::LEFT) {
		Margin = float4(-8.f, 0.f);
	}
	if (dir == float4::UP) {
		Margin = float4(0.f, -2.f);
	}
	if (dir == float4::DOWN) {
		Margin = float4(0.f, 15.f);
	}

	float4 CheckPos = NextPos + Margin;
	
	float OtherLeft = CheckPos.ix() - scale.hix();
	float OtherRight = CheckPos.ix() + scale.hix();
	float OtherTop = CheckPos.iy() - scale.hiy();
	float OtherBottom = CheckPos.iy() + scale.hiy();

//	GameEngineRect DebugRect;


	if (GetRight() < OtherLeft) return false;
	if (OtherRight < GetLeft()) return false;
	if (GetBottom() < OtherTop) return false;
	if (OtherBottom < GetTop()) return false;
	return true;
}

Items::Items() :
	ItemRenderer_(nullptr),
	ItemCollider_(nullptr),
	InMouse(false),
	InBox(true)
{

}

Items::~Items() 
{
}

