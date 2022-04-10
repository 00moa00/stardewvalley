#include "InventoryCurrentFrame.h"

InventoryCurrentFrame::InventoryCurrentFrame() 
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

