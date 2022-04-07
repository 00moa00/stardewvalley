#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
// Ό³Έν :
class InventoryExit : public GameEngineActor
{
public:
	// constrcuter destructer
	InventoryExit();
	~InventoryExit();

	// delete Function
	InventoryExit(const InventoryExit& _Other) = delete;
	InventoryExit(InventoryExit&& _Other) noexcept = delete;
	InventoryExit& operator=(const InventoryExit& _Other) = delete;
	InventoryExit& operator=(InventoryExit&& _Other) noexcept = delete;

protected:

public:

	bool MouseClick();

private:
	void Start() override;
	void Update() override;
	void Render() override;



	GameEngineCollision* ExitCollision_;
	GameEngineRenderer* Exit_;

};

