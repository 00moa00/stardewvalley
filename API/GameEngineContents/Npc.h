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
	INIT,
	WALK,
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

private:
	std::vector<NpcMove*> MoveFlagList_;


protected:

	float Speed_;

	float4 MoveDir_;

	bool DialogueUpdate_;

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

