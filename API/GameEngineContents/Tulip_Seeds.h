#pragma once
#include "Items.h"

// Ό³Έν :
class Tulip_Seeds : public Items
{
public:

	static Tulip_Seeds* MainTulipSeeds;
	static Font* Font_;
	static ItemDataBox* MainItemDataBox;

	// constrcuter destructer
	Tulip_Seeds();
	~Tulip_Seeds();

	// delete Function
	Tulip_Seeds(const Tulip_Seeds& _Other) = delete;
	Tulip_Seeds(Tulip_Seeds&& _Other) noexcept = delete;
	Tulip_Seeds& operator=(const Tulip_Seeds& _Other) = delete;
	Tulip_Seeds& operator=(Tulip_Seeds&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
	
	Crops* CreateCrops() override;
	void AddItemCount() override;
	void SubItemCount() override;
	void UpdateOff() override;
	void UpdateOn() override;


};

