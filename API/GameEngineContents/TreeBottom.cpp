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

		if (GetNameConstRef() == "Fine_Tree")
		{
			Name_ = "Fine_Tree";

			ItemRenderer_->SetImage("Fine_Tree_Bottom.bmp");
			TreeTop_->SetInitAnimation();
			TreeTop_->SetName("Fine_Tree");
		}
		else if (GetNameConstRef() == "Maple_Tree")
		{
			Name_ = "Maple_Tree";
			ItemRenderer_->SetImage("Maple_Tree_Bottom.bmp");
			TreeTop_->SetInitAnimation();
			TreeTop_->SetName("Maple_Tree");

		}
		else if (GetNameConstRef() == "Mahogany_Tree")
		{
			Name_ = "MapMahogany_Treele_Tree";

			ItemRenderer_->SetImage("Mahogany_Tree_Bottom.bmp");
			TreeTop_->SetInitAnimation();
			TreeTop_->SetName("Mahogany_Tree");

		}
		else if (GetNameConstRef() == "Oak_Tree")
		{
			Name_ = "Oak_Tree";

			ItemRenderer_->SetImage("Oak_Tree_Bottom.bmp");
			TreeTop_->SetInitAnimation();
			TreeTop_->SetName("Oak_Tree");

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
	TreeTop_->SetCrushAnimation();

}

void TreeBottom::TreeOff()
{
	this->Off();
	TreeTop_->Off();
}

