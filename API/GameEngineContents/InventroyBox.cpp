#include "InventroyBox.h"
#include <GameEngineBase/GameEngineWindow.h>

InventroyBox::InventroyBox() 
{
}

InventroyBox::~InventroyBox() 
{
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
