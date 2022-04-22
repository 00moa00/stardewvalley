#pragma once
#include "Items.h"

// Ό³Έν :
class Potato_Seeds : public Items
{
public:

	static Potato_Seeds* MainPotatoSeeds;
	static Font* Font_;

	// constrcuter destructer
	Potato_Seeds();
	~Potato_Seeds();

	// delete Function
	Potato_Seeds(const Potato_Seeds& _Other) = delete;
	Potato_Seeds(Potato_Seeds&& _Other) noexcept = delete;
	Potato_Seeds& operator=(const Potato_Seeds& _Other) = delete;
	Potato_Seeds& operator=(Potato_Seeds&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;


	void AddItemCount() override;
	void SubItemCount() override;
};

