#include "TreeTop.h"

TreeTop::TreeTop() 
	:
	TreeTopState_(TREETOP::INIT)
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


	ItemRenderer_->CreateAnimation("Oak_Tree_AnimaionSheet.bmp", "INIT_OAK", 0, 0, 0.200f, true);
	ItemRenderer_->CreateAnimation("Oak_Tree_AnimaionSheet.bmp", "CRUSH_OAK", 1,6, 0.150f, true);

	ItemRenderer_->CreateAnimation("Mahogany_Tree_AnimaionSheet.bmp", "INIT_MAHOGANY", 0, 0, 0.200f, true);
	ItemRenderer_->CreateAnimation("Mahogany_Tree_AnimaionSheet.bmp", "CRUSH_MAHOGANY", 1, 6, 0.150f, true);

	ItemRenderer_->CreateAnimation("Maple_Tree_AnimationSheet.bmp", "INIT_MAPLE", 0, 0, 0.200f, true);
	ItemRenderer_->CreateAnimation("Maple_Tree_AnimationSheet.bmp", "CRUSH_MAPLE", 1, 6, 0.150f, true);

	ItemRenderer_->CreateAnimation("Fine_Tree_AnimaionSheet.bmp", "INIT_FINE", 0, 0, 0.200f, true);
	ItemRenderer_->CreateAnimation("Fine_Tree_AnimaionSheet.bmp", "CRUSH_FINE", 1, 6, 0.150f, true);

	ItemRenderer_->ChangeAnimation("INIT_OAK");

}

void TreeTop::Update()
{

	switch (TreeTopState_)
	{
	case TREETOP::INIT:

		if (GetNameConstRef() == "Fine_Tree")
		{
			ItemRenderer_->ChangeAnimation("INIT_FINE");
		}

		else if (GetNameConstRef() == "Oak_Tree")
		{
			ItemRenderer_->ChangeAnimation("INIT_OAK");
		}

		else if (GetNameConstRef() == "Maple_Tree")
		{
			ItemRenderer_->ChangeAnimation("INIT_MAPLE");
		}

		else if (GetNameConstRef() == "Mahogany_Tree")
		{
			ItemRenderer_->ChangeAnimation("INIT_MAHOGANY");
		}

		break;
	case TREETOP::CRUSH:

		if (GetNameConstRef() == "Fine_Tree")
		{
			ItemRenderer_->ChangeAnimation("CRUSH_FINE");

			if (ItemRenderer_->IsEndAnimation())
			{
				TreeTopState_ = TREETOP::INIT;
			}
		}

		else if (GetNameConstRef() == "Oak_Tree")
		{
			ItemRenderer_->ChangeAnimation("CRUSH_OAK");

			if (ItemRenderer_->IsEndAnimation())
			{
				TreeTopState_ = TREETOP::INIT;
			}
		}

		else if (GetNameConstRef() == "Maple_Tree")
		{
			ItemRenderer_->ChangeAnimation("CRUSH_MAPLE");

			if (ItemRenderer_->IsEndAnimation())
			{
				TreeTopState_ = TREETOP::INIT;
			}
		}

		else if (GetNameConstRef() == "Mahogany_Tree")
		{
			ItemRenderer_->ChangeAnimation("CRUSH_MAHOGANY");

			if (ItemRenderer_->IsEndAnimation())
			{
				TreeTopState_ = TREETOP::INIT;
			}
		}


		break;
	default:
		break;
	}


}

void TreeTop::SetInitAnimation()
{
	TreeTopState_ = TREETOP::INIT;
}

void TreeTop::SetCrushAnimation()
{
	TreeTopState_ = TREETOP::CRUSH;
}

