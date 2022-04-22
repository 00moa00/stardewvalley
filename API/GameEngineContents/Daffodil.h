#pragma once
#include "Items.h"

// Ό³Έν :
class Daffodil : public Items
{
public:
	static Daffodil* MainDaffodil;
	static Font* Font_;

	// constrcuter destructer
	Daffodil();
	~Daffodil();

	// delete Function
	Daffodil(const Daffodil& _Other) = delete;
	Daffodil(Daffodil&& _Other) noexcept = delete;
	Daffodil& operator=(const Daffodil& _Other) = delete;
	Daffodil& operator=(Daffodil&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;


	void AddItemCount() override;
	void SubItemCount() override;
};

