#pragma once
#include "GameEngineContents/Items.h"

// Ό³Έν :
class Amethyst : public Items
{
public:
	static Font* Font_;
	static Amethyst* MainAmethyst;

	// constrcuter destructer
	Amethyst();
	~Amethyst();

	// delete Function
	Amethyst(const Amethyst& _Other) = delete;
	Amethyst(Amethyst&& _Other) noexcept = delete;
	Amethyst& operator=(const Amethyst& _Other) = delete;
	Amethyst& operator=(Amethyst&& _Other) noexcept = delete;

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

