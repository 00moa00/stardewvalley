#pragma once
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineNameObject.h>

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

protected:
	std::vector<GameEngineCollision*> ColList;

	GameEngineRenderer* NpcRenderer_;
	GameEngineCollision* NpcCollider_;

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

	//================================
	//    Setter
	//================================




	//------< 마우스, 충돌 관련 >------------------------------------------------------------------


};

