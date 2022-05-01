#include "SmallStone.h"
#include "DropStone.h"

SmallStone* SmallStone::MainSmallStone = nullptr;


SmallStone::SmallStone() 
{
}

SmallStone::~SmallStone() 
{
}

void SmallStone::Start()
{
	ItemRenderer_ = CreateRenderer("Small_Stone.bmp");
	ItemCollider_ = CreateCollision("MapObject", { 40, 15 });
	ItemCollider_->SetPivot({0, -20});
	SetScale({ 48.f, 48.f });

	ItemName_ = "SmallStone";

	ItemType_ = ITEMTYPE::STONE;
}

void SmallStone::Update()
{


}

void SmallStone::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainSmallStone = this;
}

void SmallStone::DropItemInMap()
{
	Items* DropItem = GetLevel()->CreateActor<DropStone>(static_cast<int>(PLAYLEVEL::TOP_TOP_OBJECT));


	DropItem->SetPosition({ this->GetPosition().x + 15.f , this->GetPosition().y });
	DropItem->SetMoveFlag(true);
	DropItem->GetRenderer()->SetScale({ 35.f, 35.f });

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

void SmallStone::ChnageImageFileAndIndex(std::string _FileName, ITEM _index)
{
	ItemRenderer_->SetImage(_FileName);
	ItemRenderer_->SetIndex(static_cast<int>(_index));
}

