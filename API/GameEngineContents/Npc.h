#pragma once
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineNameObject.h>

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


public:
	virtual void OpenDialogue();
	virtual void DirAnimationChange();
	virtual std::string GetDirString();
	virtual bool ForAwayPlayer();
	virtual void LoadPennyMoveFlag();

	virtual void MoveCheck();

	virtual bool MoveRight();
	virtual bool MoveLeft();
	virtual bool MoveDown();
	virtual bool MoveUp();
	virtual bool MoveWait();

	virtual void MoveUpdate();





private:
	std::vector<NpcMove*> MoveFlagList_;


protected:

	int WaitCount_; //몇시 몇번째 멈춤인지에 따라서 행동이 다르다

	float Speed_;
	float WaitTimer_;

	float4 MoveDir_;
	float4 PrevDir_;

	bool DialogueUpdate_;
	bool isWalking_;

	const char* ArrAnimationName[static_cast<int>(NPC_STATE::MAX)];

	NPC_STATE NpcUpdateState_;

	std::vector<GameEngineCollision*> ColList;

	GameEngineRenderer* NpcRenderer_;

	GameEngineCollision* NpcCollider_;		//충돌체크용
	GameEngineCollision* PersonalCollider_;	//개인 클릭 용


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

