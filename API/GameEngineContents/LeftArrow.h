#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class LeftArrow : public GameEngineActor
{
public:
	// constrcuter destructer
	LeftArrow();
	~LeftArrow();

	// delete Function
	LeftArrow(const LeftArrow& _Other) = delete;
	LeftArrow(LeftArrow&& _Other) noexcept = delete;
	LeftArrow& operator=(const LeftArrow& _Other) = delete;
	LeftArrow& operator=(LeftArrow&& _Other) noexcept = delete;

protected:

private:
	GameEngineRenderer* LeftArrow_;

	void Start() override;
	void Update() override;
	void Render() override;
};

