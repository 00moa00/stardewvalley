#pragma once
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineRandom.h>

#include "RendererData.h"

enum class ANIMATION_STATE
{
	INIT,
	MOVE,
	MOVE_END

};
// Ό³Έν :
class Effect : public GameEngineActor
{
public:
	// constrcuter destructer
	Effect();
	~Effect();

	// delete Function
	Effect(const Effect& _Other) = delete;
	Effect(Effect&& _Other) noexcept = delete;
	Effect& operator=(const Effect& _Other) = delete;
	Effect& operator=(Effect&& _Other) noexcept = delete;

public:

	virtual void SetMoveDir(float4 _Dir)
	{
		MoveDir_ = _Dir;
	}


	virtual void SetParticlesPosition(float4 _Position)
	{
		SetPosition(_Position);
	}

private:

protected:
	float4 MoveDir_;
	float4 PrePosition_;

	ANIMATION_STATE AnimationState_;

	GameEngineRenderer* AnimationRenderer_;

public:
	GameEngineRenderer* GetRenderer()
	{
		return AnimationRenderer_;
	}

};

