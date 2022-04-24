#pragma once
#include "Items.h"

// Ό³Έν :
class Bean : public Items
{
public:
	static Bean* MainBean;
	static Font* Font_;

	// constrcuter destructer
	Bean();
	~Bean();

	// delete Function
	Bean(const Bean& _Other) = delete;
	Bean(Bean&& _Other) noexcept = delete;
	Bean& operator=(const Bean& _Other) = delete;
	Bean& operator=(Bean&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;


	void AddItemCount() override;
	void SubItemCount() override;
	void UpdateOff() override;
	void UpdateOn() override;
};

