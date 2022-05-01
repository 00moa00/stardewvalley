#pragma once
#include "Items.h"

// Ό³Έν :
class SmallStone : public Items
{
public:
	static SmallStone* MainSmallStone;
	// constrcuter destructer

	SmallStone();
	~SmallStone();

	// delete Function
	SmallStone(const SmallStone& _Other) = delete;
	SmallStone(SmallStone&& _Other) noexcept = delete;
	SmallStone& operator=(const SmallStone& _Other) = delete;
	SmallStone& operator=(SmallStone&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

public:
	void DropItemInMap() override;
	void DropItemInMap(STONETYPE _StoneType)override;
	void ChnageImageFileAndIndex(std::string _FileName, ITEM _index)override;
};

