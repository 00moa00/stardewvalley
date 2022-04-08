#include "InventroyBox.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <sstream>

InventroyBox::InventroyBox()
	:
	InItem_(false)
{
}

InventroyBox::~InventroyBox() 
{

}

void InventroyBox::CreateBoxCollision(int i,  std::string box /*= "Box"*/)
{
	std::stringstream CollisionBoxNum;
	CollisionBoxNum << i;
	BoxCollision_ = CreateCollision(box, {64, 64});
}


void InventroyBox::Start()
{

	SetPosition(GameEngineWindow::GetScale().Half());

	InventoryBox_ = CreateRenderer("inventoryBox.bmp");

}

void InventroyBox::Update()
{
	//if (BoxCollision_->CollisionResult("Item", ColList, CollisionType::Rect, CollisionType::Rect)) {

	//	InItem_ = true;
	//}
	//else {

	//	InItem_ = false;
	//}

}

void InventroyBox::Render()
{
}
