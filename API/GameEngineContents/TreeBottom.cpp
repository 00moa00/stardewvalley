#include "TreeBottom.h"

TreeBottom::TreeBottom() 
{
}

TreeBottom::~TreeBottom() 
{
}

void TreeBottom::Start()
{
	ItemRenderer_ = CreateRenderer("Mahogany_Tree_Bottom.bmp");
	ItemRenderer_->SetPivotType(RenderPivot::BOT);

	ItemType_ = ITEMTYPE::ITEM;

	SetScale({ 48.f, 96.f });

	Name_ = "TreeBottom";
}

void TreeBottom::Update()
{
}
