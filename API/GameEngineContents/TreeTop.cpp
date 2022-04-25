#include "TreeTop.h"

TreeTop* TreeTop::MainTreeTop = nullptr;

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

		if (GetItemNameConstRef() == "Fine_Tree")
		{
			ItemRenderer_->ChangeAnimation("INIT_FINE");
		}

		else if (GetItemNameConstRef() == "Oak_Tree")
		{
			ItemRenderer_->ChangeAnimation("INIT_OAK");
		}

		else if (GetItemNameConstRef() == "Maple_Tree")
		{
			ItemRenderer_->ChangeAnimation("INIT_MAPLE");
		}

		else if (GetItemNameConstRef() == "Mahogany_Tree")
		{
			ItemRenderer_->ChangeAnimation("INIT_MAHOGANY");
		}

		break;

	case TREETOP::CRUSH:

		if (GetItemNameConstRef() == "Fine_Tree")
		{
			ItemRenderer_->ChangeAnimation("CRUSH_FINE");

			if (ItemRenderer_->IsEndAnimation())
			{
				TreeTopState_ = TREETOP::INIT;
			}
		}

		else if (GetItemNameConstRef() == "Oak_Tree")
		{
			ItemRenderer_->ChangeAnimation("CRUSH_OAK");

			if (ItemRenderer_->IsEndAnimation())
			{
				TreeTopState_ = TREETOP::INIT;
			}
		}

		else if (GetItemNameConstRef() == "Maple_Tree")
		{
			ItemRenderer_->ChangeAnimation("CRUSH_MAPLE");

			if (ItemRenderer_->IsEndAnimation())
			{
				TreeTopState_ = TREETOP::INIT;
			}
		}

		else if (GetItemNameConstRef() == "Mahogany_Tree")
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

void TreeTop::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainTreeTop = this;

}

void TreeTop::SetInitAnimation()
{
	TreeTopState_ = TREETOP::INIT;
}

void TreeTop::SetCrushAnimation()
{
	TreeTopState_ = TREETOP::CRUSH;
}

