#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class Cloud : public GameEngineActor
{
public:
	// constrcuter destructer
	Cloud();
	~Cloud();

	// delete Function
	Cloud(const Cloud& _Other) = delete;
	Cloud(Cloud&& _Other) noexcept = delete;
	Cloud& operator=(const Cloud& _Other) = delete;
	Cloud& operator=(Cloud&& _Other) noexcept = delete;

private:

	void Start() override;
	void Update() override;
	void Render() override;

private:

};

