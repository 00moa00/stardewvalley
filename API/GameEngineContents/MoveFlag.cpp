#include "MoveFlag.h"

MoveFlag::MoveFlag() 
{
}

MoveFlag::~MoveFlag() 
{
}

void MoveFlag::Start()
{
	ItemRenderer_ = CreateRenderer("block.bmp");
	ItemRenderer_->SetPivotType(RenderPivot::CENTER);
	ItemType_ = ITEMTYPE::FLAG;
}

void MoveFlag::CreateMoveFlag(std::string _CollName)
{
	ItemCollider_ = CreateCollision(_CollName, { 48, 48 });

}

void MoveFlag::ChnageImageFile(std::string _FileName)
{
	ItemRenderer_->SetImage(_FileName);
}

