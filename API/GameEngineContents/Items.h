#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>



// Ό³Έν :
class Items : public GameEngineActor
{
public:
	// constrcuter destructer
	Items();
	~Items();

	// delete Function
	Items(const Items& _Other) = delete;
	Items(Items&& _Other) noexcept = delete;
	Items& operator=(const Items& _Other) = delete;
	Items& operator=(Items&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;

private:
	GameEngineRenderer* Inventroy_;

};

