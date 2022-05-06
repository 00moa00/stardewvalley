#include "Table.h"

Table::Table() 
{
}

Table::~Table() 
{
}

void Table::Start()
{
	
	ItemRenderer_ = CreateRenderer("Table.bmp");
	ItemRenderer_->CameraEffectOff();
	ItemRenderer_->SetPivotType(RenderPivot::CENTER);
	SetScale({ 90, 50 });
	ItemRenderer_->SetPivot({ GetPosition().x , GetPosition().y - 24.f });

	///ItemRenderer_->SetPivot()
	//ItemCollider_ = CreateCollision("Item", { 40, 40 });
	ObjectType_ = OBJECTTYPE::TOOL;

}

