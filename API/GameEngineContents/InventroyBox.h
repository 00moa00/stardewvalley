#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
// Ό³Έν :
class InventroyBox : public GameEngineActor
{
public:
	// constrcuter destructer
	InventroyBox();
	~InventroyBox();

	// delete Function
	InventroyBox(const InventroyBox& _Other) = delete;
	InventroyBox(InventroyBox&& _Other) noexcept = delete;
	InventroyBox& operator=(const InventroyBox& _Other) = delete;
	InventroyBox& operator=(InventroyBox&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;
	void Render() override;

	GameEngineRenderer* InventoryBox_;
};

