#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include <vector>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineCollision.h>

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


public:

	 bool MouseClick() {

		return (BoxCollision_->CollisionResult("MouseCursor", ColList, CollisionType::Rect, CollisionType::Rect)
			&& (true == GameEngineInput::GetInst()->IsDown("LeftClick")));

	}

	 bool MouseOver() {

		 return (BoxCollision_->CollisionResult("MouseCursor", ColList, CollisionType::Rect, CollisionType::Rect));

	 }

	 bool InItem() {

		 return (BoxCollision_->CollisionResult("Item", ColList, CollisionType::Rect, CollisionType::Rect));
	 }

	 bool GetInItem()
	 {
		 return InItem_;
	}

	 


protected:


private:
	void Start() override;
	void Update() override;
	void Render() override;

	bool InItem_;

	GameEngineCollision* BoxCollision_;
	GameEngineRenderer* InventoryBox_;

	std::vector<GameEngineCollision*> ColList;
};

