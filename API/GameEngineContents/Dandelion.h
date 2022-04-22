#pragma once
#include "Items.h"

// Ό³Έν :
class Dandelion : public Items
{
public:
	static Dandelion* MainDandelion;
	static Font* Font_;

	// constrcuter destructer
	Dandelion();
	~Dandelion();

	// delete Function
	Dandelion(const Dandelion& _Other) = delete;
	Dandelion(Dandelion&& _Other) noexcept = delete;
	Dandelion& operator=(const Dandelion& _Other) = delete;
	Dandelion& operator=(Dandelion&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;


	void AddItemCount() override;
	void SubItemCount() override;

};

