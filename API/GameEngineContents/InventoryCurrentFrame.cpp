#include "InventoryCurrentFrame.h"

InventoryCurrentFrame* InventoryCurrentFrame::MainInventoryCurrentFrame = nullptr;

InventoryCurrentFrame::InventoryCurrentFrame()
	:
	CurrentItem_(nullptr)
{
}

InventoryCurrentFrame::~InventoryCurrentFrame() 
{
}

void InventoryCurrentFrame::Start()
{
	
	CurrentItem_ = CreateRenderer("CurrentItemFrame.bmp");
	CurrentItem_->CameraEffectOff();

}

void InventoryCurrentFrame::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainInventoryCurrentFrame = this;
}

