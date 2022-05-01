#pragma once
#include "GameEngineContents/Items.h"

// Ό³Έν :
class Aquamarine : public Items
{
public:
	static Font* Font_;
	static Aquamarine* MainAquamarine;

	// constrcuter destructer
	Aquamarine();
	~Aquamarine();

	// delete Function
	Aquamarine(const Aquamarine& _Other) = delete;
	Aquamarine(Aquamarine&& _Other) noexcept = delete;
	Aquamarine& operator=(const Aquamarine& _Other) = delete;
	Aquamarine& operator=(Aquamarine&& _Other) noexcept = delete;

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

