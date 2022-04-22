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

	GameEngineRenderer* CropRenderer_;

protected:

	float SecondTime_;

	int SecondTimeInt_;
	int PrevSecondTime_;

	int MinuteTime_;
	int HourTime_;
	int Day_;

	MINUTE_STATE MinuteState_;

private:
	void UpdateMinuteTime();
	void UpdateHourTime();
	void UpdateAddDay();

public:

	GameEngineRenderer* GetRenderer()
	{
		return CropRenderer_;
	}

};

