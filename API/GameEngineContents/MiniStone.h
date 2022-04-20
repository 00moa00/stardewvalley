#pragma once
#include "Items.h"

// Ό³Έν :
class MiniStone : public Items
{
public:
	static Font* Font_;
	static MiniStone* MainMiniStone;
	// constrcuter destructer
	MiniStone();
	~MiniStone();

	// delete Function
	MiniStone(const MiniStone& _Other) = delete;
	MiniStone(MiniStone&& _Other) noexcept = delete;
	MiniStone& operator=(const MiniStone& _Other) = delete;
	MiniStone& operator=(MiniStone&& _Other) noexcept = delete;

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

	void SubItemCount()
	{
		--Count_;
		Font_->ChangeNumItem(Count_);

	}
	//void MoveToPlayer();

};

