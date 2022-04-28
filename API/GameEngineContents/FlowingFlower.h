#pragma once
#include "Effect.h"
#include "FlowerParticles.h"

enum class CREATE_FLOWER
{
	SET_TIMER,
	TIMER,
	CREATE,
	INIT,


};

// 설명 :
class FlowingFlower : public Effect
{
public:
	// constrcuter destructer
	FlowingFlower();
	~FlowingFlower();

	// delete Function
	FlowingFlower(const FlowingFlower& _Other) = delete;
	FlowingFlower(FlowingFlower&& _Other) noexcept = delete;
	FlowingFlower& operator=(const FlowingFlower& _Other) = delete;
	FlowingFlower& operator=(FlowingFlower&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;

private:
	float CreateTimer_;

	float MaxX_;
	float MinX_;

	float MaxY_;
	float MinY_;

	float CreateMaxY_;

	bool CreateFocusPlayer_;

//	float4 Max_;

	CREATE_FLOWER CreateFlowerState_;

	GameEngineRandom RamdomTimer_;
	GameEngineRandom RamdomPosX_;
	GameEngineRandom RamdomPosY_;

	FlowerParticles* FlowerParticles_;

public:
	void SetMax(float4 _Max);
	void SetMaxFocusPlayer(bool _Flag);

};

//랜덤 위치에, 랜덤한 타이밍에 꽃잎을 생성
//화면 밖으로 나가면 딜리트
//
