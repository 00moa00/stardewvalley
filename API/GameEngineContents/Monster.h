#pragma once
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineInput.h>

#include "RendererData.h"
enum class DIR
{

};

enum class MONSTER_STATE
{
	WAIT,
	WALK,
	MAX
};

// 설명 :
class Monster : public GameEngineActor
{
public:
	// constrcuter destructer
	Monster();
	~Monster();

	// delete Function
	Monster(const Monster& _Other) = delete;
	Monster(Monster&& _Other) noexcept = delete;
	Monster& operator=(const Monster& _Other) = delete;
	Monster& operator=(Monster&& _Other) noexcept = delete;

private:
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

protected:
	GameEngineRenderer* MonsterRenderer_;
	GameEngineCollision* MonsterCollider_;		

	std::vector<GameEngineCollision*> ColList;

	const char* ArrAnimationName[static_cast<int>(MONSTER_STATE::MAX)];

public:
	bool MonsterCheck(const float4 pos, const float4 scale);


	//================================
	//     Getter
	//================================
	GameEngineCollision* GetCollision()
	{
		return MonsterCollider_;
	}

	GameEngineRenderer* GetRenderer()
	{
		return MonsterRenderer_;
	}


	//================================
	//    Setter
	//================================

	//------< 마우스, 충돌 관련 >------------------------------------------------------------------

};

