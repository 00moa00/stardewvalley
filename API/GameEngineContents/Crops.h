#pragma once
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineRandom.h>

#include "CropsData.h"
#include "PlayerData.h"
#include"RendererData.h"


enum class CROPS_UPDATE
{
	WAIT,
	DAY_END_WETDIRT_CHECK,
	DAY_OVER_WAIT,
	ADD_GROWING_DAY,
	ADD_GROWING_DAY_INIT
};

// Ό³Έν :
class Crops : public GameEngineActor
{
public:
	// constrcuter destructer
	Crops();
	~Crops();

	// delete Function
	Crops(const Crops& _Other) = delete;
	Crops(Crops&& _Other) noexcept = delete;
	Crops& operator=(const Crops& _Other) = delete;
	Crops& operator=(Crops&& _Other) noexcept = delete;

private:

	void Start() override;
	void Update() override;

private:


protected:

	int StartDay_;
	int GrowingDay_;
	int DirtDay_;

	int TileFindIndex_;

	bool isHarvest_;

	GameEngineRandom RandomItemCount;
	GameEngineRandom RandomItemPosX;
	GameEngineRandom RamdomItemPosY;

	MINUTE_STATE MinuteState_;
	CROPS_UPDATE CropsUpdateState_;

	GameEngineRenderer* CropRenderer_;

private:

protected:
	virtual void CropsDeath();

	void GrowingCropsTime();
	void DeathCropsCheck();

	void DropCropsInMap();

	bool isWetDirt();


public:

	GameEngineRenderer* GetRenderer()
	{
		return CropRenderer_;
	}

	int GetGrowingDay()
	{
		return GrowingDay_;
	}

	bool GetisHarvest()
	{
		return isHarvest_;
	}


	void SetTileFindIndex(int _Index)
	{
		TileFindIndex_ = _Index;
	}

	template<typename Actor>
	Actor* CreateDropItemActor()
	{
		Actor* Item = GetLevel()->CreateActor<Actor>(static_cast<int>(PLAYLEVEL::SEED));
		return Item;
	}
};

