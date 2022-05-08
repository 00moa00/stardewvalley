#pragma once
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameEngineSound.h>

#include "SubHPFont.h"

#include "RendererData.h"
#include "MonsterData.h"


enum class MONSTER_STATE
{
	WAIT,			//대기
	REVIVAL,		//소생

	CHECK,			//사방 충돌 체크
	RE_CHECK,		//사방 충돌 체크
	WALK,			//평상시 걷기
	MOVE_TO_PLAYER,

	MOVE_UP,		//BUG - 위 이동
	MOVE_DOWN,		//BUG - 아래 이동

	BACK,			//공격 받으면 뒤로 이동

	COLL,			//맵 오브젝트에 몬스터가 꼈을때
	DEATH,

	MAX
};

enum class MONSTER_TYPE
{
	OTHER,
	BUG,
	BAT,
	CRAB,
	GOLEM
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
	bool invincibility_;

	float4 PrevPos_;
	float4 MoveDir_;			// 걷는 방향

	GameEngineRandom RandomDir_;	//랜덤 방향전향
	GameEngineRandom RandomTimer_;	//랜덤 방향전향 타이머

	MONSTER_STATE MonsterState_;
	MONSTER_TYPE MonsterType_;

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


	MONSTER_TYPE GetMonsterType()
	{
		return MonsterType_;
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
		if (invincibility_ == false )
		{
			SubHPFont* SubHPFont_;
			SubHPFont_ = GetLevel()->CreateActor<SubHPFont>();


			if (MonsterType_ == MONSTER_TYPE::BUG)
			{
				SubHPFont_->SetPosAndNumGray(this->GetPosition(), 0);
				HP_ -= 0;

			}
			else
			{
				SubHPFont_->SetPosAndNumGray(this->GetPosition(), _Damage);
				HP_ -= _Damage;
			}

			if (HP_ <= 0)
			{			
				isDeath_ = true;
			}
		}
	}

	float4 GetMoveDir()
	{
		return MoveDir_;
	}

	//------< 마우스, 충돌 관련 >------------------------------------------------------------------

};

