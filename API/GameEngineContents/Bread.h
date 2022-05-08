#pragma once
#include "Items.h"

// Ό³Έν :
class Bread : public Items
{
public:
	static Bread* MainBread;
	static Font* Font_;
	static ItemDataBox* MainItemDataBox;

	// constrcuter destructer
	Bread();
	~Bread();

	// delete Function
	Bread(const Bread& _Other) = delete;
	Bread(Bread&& _Other) noexcept = delete;
	Bread& operator=(const Bread& _Other) = delete;
	Bread& operator=(Bread&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

	void AddItemCount() override;
	void SubItemCount() override;
	void UpdateOff() override;
	void UpdateOn() override;

	void DropItemInMap() override;

};

