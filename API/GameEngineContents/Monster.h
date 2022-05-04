#pragma once
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineRandom.h>

#include "SubHPFont.h"

#include "RendererData.h"
#include "MonsterData.h"


enum class MONSTER_STATE
{
	WAIT,
	CHECK,
	RE_CHECK,
	WALK,


	MOVE_UP,
	MOVE_DOWN,

	BACK,

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
	
public:
	virtual std::string GetDirString();

	virtual bool CheckMapObject();		//가는 방향에 오브젝트가 있다.

	virtual bool CheckRightObject();
	virtual bool CheckLeftObject();
	virtual bool CheckUpObject();
	virtual bool CheckDownObject();
	virtual void BackMove();
	virtual void SetMonsterStateBack();
	//virtual bool CheckPlayer();

protected:

	int Damage_;
	int HP_;
	int RamdomDirResult_;		//랜덤 값 저장용

	float Speed_;				//이동 스피드
	float Timer_;				//방향 전향 타이머

	bool isDeath_;				//죽었는지 체크
	bool isHit_;				//크랩용 플러그

	float4 PrevPos_;
	float4 MoveDir_;			// 걷는 방향

	GameEngineRandom RandomDir_;	//랜덤 방향전향
	GameEngineRandom RandomTimer_;	//랜덤 방향전향 타이머

	MONSTER_STATE MonsterState_;

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

	bool GetisHit()
	{
		return isHit_;
	}

	int GetDamage()
	{
		return Damage_;
	}

	int GetLeft()
	{
		return GetPosition().ix() - GetScale().hix();
	}

	int GetRight()
	{
		return GetPosition().ix() + GetScale().hix();
	}

	int GetTop()
	{
		return GetPosition().iy() - GetScale().hiy();
	}

	int GetBottom()
	{
		return GetPosition().iy() + GetScale().hiy();
	}

	bool MonsterVSPlayer()
	{
		return	MonsterCollider_->CollisionResult("Player", ColList, CollisionType::Rect, CollisionType::Rect);
	}


	//================================
	//    Setter
	//================================

	void SetIsHit(bool _Flag)
	{
		isHit_ = _Flag;
	}

	void SubHP(int _Damage)
	{
		SubHPFont* SubHPFont_;
		SubHPFont_ = GetLevel()->CreateActor<SubHPFont>();
		SubHPFont_->SetPosAndNumGray(this->GetPosition(), _Damage);

		HP_ -= _Damage;
	}

	float4 GetMoveDir()
	{
		return MoveDir_;
	}

	//------< 마우스, 충돌 관련 >------------------------------------------------------------------

};

