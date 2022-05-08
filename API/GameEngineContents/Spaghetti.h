#pragma once
#include "Items.h"

// Ό³Έν :
class Spaghetti : public Items
{
public:
	static Spaghetti* MainSpaghetti;
	static Font* Font_;
	static ItemDataBox* MainItemDataBox;

	Spaghetti();
	~Spaghetti();

	// delete Function
	Spaghetti(const Spaghetti& _Other) = delete;
	Spaghetti(Spaghetti&& _Other) noexcept = delete;
	Spaghetti& operator=(const Spaghetti& _Other) = delete;
	Spaghetti& operator=(Spaghetti&& _Other) noexcept = delete;

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

