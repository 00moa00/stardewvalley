#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class FrontMount : public GameEngineActor
{
public:
	// constrcuter destructer
	FrontMount();
	~FrontMount();

	// delete Function
	FrontMount(const FrontMount& _Other) = delete;
	FrontMount(FrontMount&& _Other) noexcept = delete;
	FrontMount& operator=(const FrontMount& _Other) = delete;
	FrontMount& operator=(FrontMount&& _Other) noexcept = delete;

private:

	void Start() override;
	void Update() override;
	void Render() override;

private:
	GameEngineRenderer* FrontMountRenderer_;

};

