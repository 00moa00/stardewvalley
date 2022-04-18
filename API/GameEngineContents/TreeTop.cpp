#include "TreeTop.h"

TreeTop::TreeTop() 
{
}

TreeTop::~TreeTop() 
{
}

void TreeTop::Start()
{
	ItemRenderer_ = CreateRenderer("Mahogany_Tree.bmp");
	ItemRenderer_->SetPivotType(RenderPivot::BOT);

	ItemType_ = ITEMTYPE::ITEM;

	SetScale({ 48.f, 96.f });

	Name_ = "TreeTop";
}

void TreeTop::Update()
{
}

