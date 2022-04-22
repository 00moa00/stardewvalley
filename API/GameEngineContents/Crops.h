#pragma once
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineNameObject.h>

#include "CropsData.h"
#include "PlayerData.h"


enum class CROPS_UPDATE
{
	INIT,
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

protected:

	int StartDay_;
	int GrowingDay_;

	MINUTE_STATE MinuteState_;
	CROPS_UPDATE CropsUpdateState_;

	GameEngineRenderer* CropRenderer_;

private:

protected:

	void GrowingCropsTime();

public:

	GameEngineRenderer* GetRenderer()
	{
		return CropRenderer_;
	}

	int GetGrowingDay()
	{
		return GrowingDay_;
	}


};

