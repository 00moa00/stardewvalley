#pragma once
#include "Items.h"

// Ό³Έν :
class MiniWood : public Items
{
public:
	static Font* Font_;
	static MiniWood* MainMiniWood;
	// constrcuter destructer
	MiniWood();
	~MiniWood();

	// delete Function
	MiniWood(const MiniWood& _Other) = delete;
	MiniWood(MiniWood&& _Other) noexcept = delete;
	MiniWood& operator=(const MiniWood& _Other) = delete;
	MiniWood& operator=(MiniWood&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

	void SetItemStateAddItem()
	{
		++Count_;
		Font_->ChangeNumItem(Count_);

	}

	void SubItemCount()override;

	//void MoveToPlayer();
};

