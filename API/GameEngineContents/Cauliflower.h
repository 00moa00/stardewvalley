#pragma once
#include "Items.h"


// Ό³Έν :
class Cauliflower : public Items
{
public:
	static Cauliflower* MainCauliflower;
	static Font* Font_;

	// constrcuter destructer
	Cauliflower();
	~Cauliflower();

	// delete Function
	Cauliflower(const Cauliflower& _Other) = delete;
	Cauliflower(Cauliflower&& _Other) noexcept = delete;
	Cauliflower& operator=(const Cauliflower& _Other) = delete;
	Cauliflower& operator=(Cauliflower&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;


	void AddItemCount() override;
	void SubItemCount() override;
};

