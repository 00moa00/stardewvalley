#include "Items.h"
#include "GameData.h"

bool Items::IsWall(const float4 pos, const float4 scale,  float4 dir)
{


	//float4 CheckPos = float4::ZERO;
	float4 Margin = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	dir.Normal2D();

	if (dir.CompareInt2D(float4::RIGHT)) {
		Margin += float4(8.f, 0.f);
	}
	if (dir.CompareInt2D(float4::LEFT)) {
		Margin += float4(-8.f, 0.f);
	}
	if (dir.CompareInt2D(float4::UP)) {
		Margin += float4(0.f, -8.f);
	}
	if (dir.CompareInt2D(float4::DOWN)) {
		Margin += float4(0.f, 8.f);
	}


	//if (this->GetItemType() == ITEMTYPE::BLOCK) {

	//	if (dir == float4::RIGHT) {
	//		Margin = float4(0.10f, 0.f);
	//	}
	//	if (dir == float4::LEFT) {
	//		Margin = float4(-0.10f, 0.f);
	//	}
	//	if (dir == float4::UP) {
	//		Margin = float4(0.f, -0.10f);
	//	}
	//	if (dir == float4::DOWN) {
	//		Margin = float4(0.f, 10.f);
	//	}
	//}
	float4 NextPos = pos + (dir * GameEngineTime::GetDeltaTime() * 150.f);

	CheckPos+= NextPos + Margin;
	
	int OtherLeft = CheckPos.ix() - scale.hix();
	int OtherRight = CheckPos.ix() + scale.hix();
	int OtherTop = CheckPos.iy() - scale.hiy();
	int OtherBottom = CheckPos.iy() + scale.hiy();

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

