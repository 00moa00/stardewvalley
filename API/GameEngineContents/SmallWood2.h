#pragma once
#include "Items.h"
// Ό³Έν :
class SmallWood2 : public Items
{
public:
	static SmallWood2* MainSmallWood;

	// constrcuter destructer
	SmallWood2();
	~SmallWood2();

	// delete Function
	SmallWood2(const SmallWood2& _Other) = delete;
	SmallWood2(SmallWood2&& _Other) noexcept = delete;
	SmallWood2& operator=(const SmallWood2& _Other) = delete;
	SmallWood2& operator=(SmallWood2&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

	void DropItemInMap() override;
};

