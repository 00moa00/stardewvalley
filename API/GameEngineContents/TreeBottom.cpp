#include "TreeBottom.h"
#include "TreeTop.h"
#include "DropWood.h"

TreeBottom* TreeBottom::MainTreeBottom = nullptr;

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

	SubCollider_ = CreateCollision("TreeTop", { 100, 200 });
	SubCollider_->SetPivot({ 0, -120 });

	SubRenderer = GetLevel()->CreateActor<TreeTop>((int)PLAYLEVEL::PLAYER);

	Damage_ = 5;

	SetScale({ 48.f, 48.f });

	ItemType_ = ITEMTYPE::TREE;

}

void TreeBottom::Update()
{
	if (SubRenderer != nullptr)
	{
		if (SubCollider_->CollisionResult("Player", ColList, CollisionType::Rect, CollisionType::Rect) == true)
		{
			SubRenderer->GetRenderer()->SetAlpha(80);
		}
		else
		{
			SubRenderer->GetRenderer()->SetAlpha(255);
		}
	}


	switch (TreeState_)
	{
	case TREESTATE::INIT:

		if (GetItemNameConstRef() == "Fine_Tree")
		{
			ItemName_ = "Fine_Tree";

			ItemRenderer_->SetImage("Fine_Tree_Bottom.bmp");
			SubRenderer->SetInitAnimation();
			SubRenderer->SetItemName("Fine_Tree");
		}
		else if (GetItemNameConstRef() == "Maple_Tree")
		{
			ItemName_ = "Maple_Tree";
			ItemRenderer_->SetImage("Maple_Tree_Bottom.bmp");
			SubRenderer->SetInitAnimation();
			SubRenderer->SetItemName("Maple_Tree");

		}
		else if (GetItemNameConstRef() == "Mahogany_Tree")
		{
			ItemName_ = "MapMahogany_Treele_Tree";

			ItemRenderer_->SetImage("Mahogany_Tree_Bottom.bmp");
			SubRenderer->SetInitAnimation();
			SubRenderer->SetItemName("Mahogany_Tree");

		}
		else if (GetItemNameConstRef() == "Oak_Tree")
		{
			ItemName_ = "Oak_Tree";

			ItemRenderer_->SetImage("Oak_Tree_Bottom.bmp");
			SubRenderer->SetInitAnimation();
			SubRenderer->SetItemName("Oak_Tree");

		}

		SubRenderer->GetRenderer()->SetPivot({ GetPosition().x, GetPosition().y - 11.f });

		TreeState_ = TREESTATE::UPDATE;
		break;
	case TREESTATE::UPDATE:

		if (Damage_ == 2)
		{
			SubRenderer->Death();
			SubRenderer = nullptr;
			TreeState_ = TREESTATE::TREETOP_DIE;
			break;

		}

		break;

	case TREESTATE::TREETOP_DIE:

		

		break;
	default:
		break;
	}



}

void TreeBottom::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainTreeBottom = this;
}

void TreeBottom::SetInitAnimation()
{
	//SubRenderer->SetInitAnimation(_TreeName);
}

void TreeBottom::SetCrushAnimation()
{
	if (SubRenderer != nullptr)
	{
		SubRenderer->SetCrushAnimation();
	}
}

void TreeBottom::DropItemInMap()
{
	Items* DropItem = GetLevel()->CreateActor<DropWood>(static_cast<int>(PLAYLEVEL::TOP_TOP_OBJECT));

	DropItem->SetPosition({ this->GetPosition().x + 15.f , this->GetPosition().y });
	DropItem->SetMoveFlag(true);
	DropItem->GetRenderer()->SetScale({ 40.f, 40.f });

	GameEngineRandom RandomDir;
	int RamdomDir = RandomDir.RandomInt(1, 2);


	if (RamdomDir == 1)
	{
		DropItem->SetMoveDir({ 0, -120 });

	}
	if (RamdomDir == 2)
	{
		DropItem->SetMoveDir({ 0, -120 });

	}
}

void TreeBottom::TreeOff()
{
	this->Death();
	SubRenderer->Death();
}

