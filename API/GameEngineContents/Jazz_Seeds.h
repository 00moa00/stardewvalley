#pragma once
#include "Items.h"

// Ό³Έν :
class Jazz_Seeds : public Items
{
public:
	static Jazz_Seeds* MainJazzSeeds;
	static Font* Font_;

	// constrcuter destructer
	Jazz_Seeds();
	~Jazz_Seeds();

	// delete Function
	Jazz_Seeds(const Jazz_Seeds& _Other) = delete;
	Jazz_Seeds(Jazz_Seeds&& _Other) noexcept = delete;
	Jazz_Seeds& operator=(const Jazz_Seeds& _Other) = delete;
	Jazz_Seeds& operator=(Jazz_Seeds&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;


	void AddItemCount() override;
	void SubItemCount() override;

};

