#pragma once
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineInput.h>

#include "DialogueBox.h"
#include "RendererData.h"
#include "NpcMove.h"

enum class NPC_STATE
{
	WAIT,				//기본 서있는 상태
	WALK,				//걷고있음
	DIALOGUE_IDLE,		//대화중
	DIALOGUE_WAIT,		//대화 종료 후 3초 대기
	WAIT_COUNT,			//Wait카운팅용
	MAX
};

// 설명 :
class Npc : public GameEngineActor
{
public:
	// constrcuter destructer
	Npc();
	~Npc();

	// delete Function
	Npc(const Npc& _Other) = delete;
	Npc(Npc&& _Other) noexcept = delete;
	Npc& operator=(const Npc& _Other) = delete;
	Npc& operator=(Npc&& _Other) noexcept = delete;


private:
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;


public:

	virtual void OpenDialogue();
	virtual void DirAnimationChange();
	virtual bool ForAwayPlayer();
	virtual void LoadPennyMoveFlag();
	virtual void LoadLewisMoveFlag();

	virtual void MoveCheck();
	virtual bool MoveRight();
	virtual bool MoveLeft();
	virtual bool MoveDown();
	virtual bool MoveUp();
	virtual bool MoveWait();
	virtual void MoveUpdate();

	virtual void CheckTalkingLimit();

	virtual std::string GetDirString();

private:

protected:

	bool TalkingLimit_;		//하루에 한 번만 대화를 걸 수 있다.

	int WaitCount_;			//몇시 몇번째 멈춤인지에 따라서 행동이 다르다

	float Speed_;
	float WaitTimer_;		//플레이어와 대화 종료후 행동에 다시 들어가는 딜레이 시간

	float4 MoveDir_;		// 걷는 방향
	float4 PrevDir_;		// 플레이어가 대화를 걸고나서 바뀔때 저장하기 위한 변수

	bool DialogueUpdate_;
	bool isWalking_;

	const char* ArrAnimationName[static_cast<int>(NPC_STATE::MAX)];

	NPC_STATE NpcUpdateState_;

	std::vector<GameEngineCollision*> ColList;
	std::vector<NpcMove*> MoveFlagList_;

	GameEngineRenderer* NpcRenderer_;
	GameEngineCollision* NpcCollider_;		//충돌체크용
	GameEngineCollision* PersonalCollider_;	//서브 콜라이더. 현재까지 쓰지 않음


private:

public:
	bool NPCCheck(const float4 pos, const float4 scale);

	//================================
	//     Getter
	//================================

	GameEngineCollision* GetCollision()
	{
		return NpcCollider_;
	}

	GameEngineRenderer* GetRenderer()
	{
		return NpcRenderer_;
	}

	bool GetTalkingLimit()
	{
		return TalkingLimit_;
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

	bool GetDialogueUpdate()
	{
		return DialogueUpdate_;
	}

	//================================
	//    Setter
	//================================

	void SetDialogueUpdate(bool _Flag)
	{
		DialogueUpdate_ = _Flag;
	}


	//------< 마우스, 충돌 관련 >------------------------------------------------------------------


	//bool MouseOver()
	//{
	//	return (PersonalCollider_->CollisionResult("MouseCursor", ColList, CollisionType::Rect, CollisionType::Rect));
	//}


};

