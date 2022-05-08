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
	ObjectType_ = OBJECTTYPE::FLAG;
}

void MoveFlag::CreateMoveFlag(std::string _CollName)
{
	ItemCollider_ = CreateCollision(_CollName, { 55, 55 });
}

void MoveFlag::ChnageImageFile(std::string _FileName)
{
	ItemRenderer_->SetImage(_FileName);
}

void MoveFlag::CreateSubCollision(std::string _CollName, float4 _Size)
{
	SubCollider_ = CreateCollision(_CollName, {48, 48});
}

