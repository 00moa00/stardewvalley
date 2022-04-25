#include "InventroyBox.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <sstream>
#include "GameData.h"

InventroyBox* InventroyBox::MainInventroyBox = nullptr;


InventroyBox::InventroyBox()
	:
	Item_(nullptr),
	BoxCollision_(nullptr)
{

}

InventroyBox::~InventroyBox() 
{

}

void InventroyBox::CreateBoxCollision(int i,  std::string box /*= "Box"*/)
{
}


void InventroyBox::Start()
{
	InventoryBox_ = CreateRenderer("inventoryBox.bmp");
	InventoryBox_ -> CameraEffectOff();
	BoxCollision_ = CreateCollision("Box", { 35, 35 });

}

void InventroyBox::Update()
{

}

void InventroyBox::Render()
{

}

void InventroyBox::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainInventroyBox = this;
}
