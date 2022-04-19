#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
// Ό³Έν :
class ExitBotton : public GameEngineActor
{
public:
	// constrcuter destructer
	ExitBotton();
	~ExitBotton();

	// delete Function
	ExitBotton(const ExitBotton& _Other) = delete;
	ExitBotton(ExitBotton&& _Other) noexcept = delete;
	ExitBotton& operator=(const ExitBotton& _Other) = delete;
	ExitBotton& operator=(ExitBotton&& _Other) noexcept = delete;


private:
	void Start() override;
	void Update() override;
	void Render() override;

private:

	GameEngineCollision* ExitCollision_;
	GameEngineRenderer* Exit_;

public:

	bool MouseClick();

};

