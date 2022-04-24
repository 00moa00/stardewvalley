#pragma once
#include "Items.h"

// Ό³Έν :
class Tulip : public Items
{
public:
	static Tulip* MainTulip;
	static Font* Font_;

	// constrcuter destructer
	Tulip();
	~Tulip();

	// delete Function
	Tulip(const Tulip& _Other) = delete;
	Tulip(Tulip&& _Other) noexcept = delete;
	Tulip& operator=(const Tulip& _Other) = delete;
	Tulip& operator=(Tulip&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;


	void AddItemCount() override;
	void SubItemCount() override;
	void UpdateOff() override;

};

