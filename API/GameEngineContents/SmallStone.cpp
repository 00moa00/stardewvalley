#include "SmallStone.h"
#include "DropStone.h"
#include "Ruby.h"
#include "Amethyst.h"
#include "Aquamarine.h"
#include "Copper.h"

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

	ObjectType_ = OBJECTTYPE::STONE;
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

void SmallStone::DropItemInMap(STONETYPE _StoneType)
{
	Items* DropItem = nullptr;


	if (_StoneType == STONETYPE::RUBY)
	{
		DropItem = GetLevel()->CreateActor<Ruby>(static_cast<int>(PLAYLEVEL::TOP_TOP_OBJECT));
	}
	else if (_StoneType == STONETYPE::AMETHYST)
	{
		DropItem = GetLevel()->CreateActor<Amethyst>(static_cast<int>(PLAYLEVEL::TOP_TOP_OBJECT));
	}
	else if (_StoneType == STONETYPE::AQUAMARINE)
	{
		DropItem = GetLevel()->CreateActor<Aquamarine>(static_cast<int>(PLAYLEVEL::TOP_TOP_OBJECT));
	}
	else if (_StoneType == STONETYPE::COPPER)
	{
		DropItem = GetLevel()->CreateActor<Copper>(static_cast<int>(PLAYLEVEL::TOP_TOP_OBJECT));
	}
	else
	{
		DropItem = GetLevel()->CreateActor<DropStone>(static_cast<int>(PLAYLEVEL::TOP_TOP_OBJECT));
	}

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

