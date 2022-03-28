#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class RightArrow : public GameEngineActor
{
public:
	// constrcuter destructer
	RightArrow();
	~RightArrow();

	// delete Function
	RightArrow(const RightArrow& _Other) = delete;
	RightArrow(RightArrow&& _Other) noexcept = delete;
	RightArrow& operator=(const RightArrow& _Other) = delete;
	RightArrow& operator=(RightArrow&& _Other) noexcept = delete;

protected:
	GameEngineRenderer* RightArrow_;

private:

	void Start() override;
	void Update() override;
	void Render() override;

};

