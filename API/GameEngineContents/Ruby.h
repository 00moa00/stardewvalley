#pragma once
#include "GameEngineContents/Items.h"

// Ό³Έν :
class Ruby : public Items
{
public:
	static Font* Font_;
	static Ruby* MainRuby;

	// constrcuter destructer
	Ruby();
	~Ruby();

	// delete Function
	Ruby(const Ruby& _Other) = delete;
	Ruby(Ruby&& _Other) noexcept = delete;
	Ruby& operator=(const Ruby& _Other) = delete;
	Ruby& operator=(Ruby&& _Other) noexcept = delete;

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

