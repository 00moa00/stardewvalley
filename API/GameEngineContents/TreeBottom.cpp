#include "TreeBottom.h"
#include "TreeTop.h"

TreeBottom::TreeBottom() 
	:
	TreeState_(TREESTATE::INIT)

{
}

TreeBottom::~TreeBottom() 
{
}

void TreeBottom::Start()
{
	ItemRenderer_ = CreateRenderer("Mahogany_Tree_Bottom.bmp");
	ItemRenderer_->SetPivotType(RenderPivot::CENTER);
	ItemCollider_ = CreateCollision("MapObject", { 48.f, 48.f });

	TreeTop_ = GetLevel()->CreateActor<TreeTop>((int)PLAYLEVEL::TOP_OBJECT);
	//Name_ = "";

	ItemType_ = ITEMTYPE::ITEM;

	SetScale({ 48.f, 48.f });

}

void TreeBottom::Update()
{
	switch (TreeState_)
	{
	case TREESTATE::INIT:

		if (GetItemNameConstRef() == "Fine_Tree")
		{
			ItemName_ = "Fine_Tree";

			ItemRenderer_->SetImage("Fine_Tree_Bottom.bmp");
			TreeTop_->SetInitAnimation();
			TreeTop_->SetItemName("Fine_Tree");
		}
		else if (GetItemNameConstRef() == "Maple_Tree")
		{
			ItemName_ = "Maple_Tree";
			ItemRenderer_->SetImage("Maple_Tree_Bottom.bmp");
			TreeTop_->SetInitAnimation();
			TreeTop_->SetItemName("Maple_Tree");

		}
		else if (GetItemNameConstRef() == "Mahogany_Tree")
		{
			ItemName_ = "MapMahogany_Treele_Tree";

			ItemRenderer_->SetImage("Mahogany_Tree_Bottom.bmp");
			TreeTop_->SetInitAnimation();
			TreeTop_->SetItemName("Mahogany_Tree");

		}
		else if (GetItemNameConstRef() == "Oak_Tree")
		{
			ItemName_ = "Oak_Tree";

			ItemRenderer_->SetImage("Oak_Tree_Bottom.bmp");
			TreeTop_->SetInitAnimation();
			TreeTop_->SetItemName("Oak_Tree");

		}

		TreeTop_->GetRenderer()->SetPivot({ GetPosition().x, GetPosition().y - 11.f });

		TreeState_ = TREESTATE::UPDATE;
		break;
	case TREESTATE::UPDATE:

		if (Damage_ == 2)
		{
			TreeTop_->Off();
		}

		break;
	default:
		break;
	}



}

void TreeBottom::SetInitAnimation()
{
	//TreeTop_->SetInitAnimation(_TreeName);
}

void TreeBottom::SetCrushAnimation()
{
	if (TreeTop_ != nullptr)
	{
		TreeTop_->SetCrushAnimation();
	}
}

void TreeBottom::TreeOff()
{
	this->Death();
	TreeTop_->Death();
}

