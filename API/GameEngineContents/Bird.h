#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>

// Ό³Έν :
class Bird : public GameEngineActor
{
public:
	// constrcuter destructer
	Bird();
	~Bird();

	// delete Function
	Bird(const Bird& _Other) = delete;
	Bird(Bird&& _Other) noexcept = delete;
	Bird& operator=(const Bird& _Other) = delete;
	Bird& operator=(Bird&& _Other) noexcept = delete;

private:
	void Start()override;

private:
	GameEngineRenderer* Bird_;

};

