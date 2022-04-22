#pragma once
#include "Items.h"
// Ό³Έν :
class Pasnip : public Items
{
public:
	static Pasnip* MainPasnip;
	static Font* Font_;

	// constrcuter destructer
	Pasnip();
	~Pasnip();

	// delete Function
	Pasnip(const Pasnip& _Other) = delete;
	Pasnip(Pasnip&& _Other) noexcept = delete;
	Pasnip& operator=(const Pasnip& _Other) = delete;
	Pasnip& operator=(Pasnip&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;


	void AddItemCount() override;
	void SubItemCount() override;
};

