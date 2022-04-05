#include "InventroyBox.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <sstream>

InventroyBox::InventroyBox()
{
}

InventroyBox::~InventroyBox() 
{

}

void InventroyBox::CreateBoxCollision(int i,  std::string box /*= "Box"*/)
{
	std::stringstream CollisionBoxNum;
	CollisionBoxNum << i;
	BoxCollision_ = CreateCollision(box + CollisionBoxNum.str(), {64, 64});
}


void InventroyBox::Start()
{

	SetPosition(GameEngineWindow::GetScale().Half());

	InventoryBox_ = CreateRenderer("inventoryBox.bmp");

}

void InventroyBox::Update()
{
}

void InventroyBox::Render()
{
}
