#pragma once
#include "Items.h"
// Ό³Έν :
class Jazz : public Items
{
public:
	static Jazz* MainJazz;
	static Font* Font_;

	// constrcuter destructer
	Jazz();
	~Jazz();

	// delete Function
	Jazz(const Jazz& _Other) = delete;
	Jazz(Jazz&& _Other) noexcept = delete;
	Jazz& operator=(const Jazz& _Other) = delete;
	Jazz& operator=(Jazz&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;


	void AddItemCount() override;
	void SubItemCount() override;
};

