#include "EmptyItem.h"

EmptyItem::EmptyItem() 
{
}

EmptyItem::~EmptyItem() 
{
}

void EmptyItem::Start()
{
	ItemRenderer_ = CreateRenderer("Empty.bmp");

}

