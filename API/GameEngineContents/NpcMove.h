#pragma once
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineInput.h>

// Ό³Έν :
class NpcMove : public GameEngineActor
{
public:
	// constrcuter destructer
	NpcMove();
	~NpcMove();

	// delete Function
	NpcMove(const NpcMove& _Other) = delete;
	NpcMove(NpcMove&& _Other) noexcept = delete;
	NpcMove& operator=(const NpcMove& _Other) = delete;
	NpcMove& operator=(NpcMove&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;

	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

private:
	GameEngineRenderer* MoveRenderer_;
	GameEngineCollision* MoveCollision_;

public:
	void CreateNPCMoveCollision(std::string _CollName);
	void SetNPCMoveImageAndIdex(std::string _FileName, int _Index);
	
};

