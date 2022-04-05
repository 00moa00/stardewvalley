#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
// Ό³Έν :
class InventroyBox : public GameEngineActor
{
public:
	
	void CreateBoxCollision(int i, std::string box = "Box");
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
	GameEngineCollision* BoxCollision_;
	GameEngineRenderer* InventoryBox_;
};

