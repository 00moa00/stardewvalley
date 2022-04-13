#pragma once

#include <windows.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <vector>
// Ό³Έν :
class Mouse : public GameEngineActor
{
public:

	// constrcuter destructer
	Mouse();
	~Mouse();

	// delete Function
	Mouse(const Mouse& _Other) = delete;
	Mouse(Mouse&& _Other) noexcept = delete;
	Mouse& operator=(const Mouse& _Other) = delete;
	Mouse& operator=(Mouse&& _Other) noexcept = delete;

protected:

public:
	GameEngineRenderer* Renderer() {
		return MousePoint_;
	}
	GameEngineCollision* Collision() {
		return MouseCollision_;
	}

	void MouseOff() {
		this -> Off();
	}

	bool isMouseClick();
	bool isMouseHold();
	bool isMouseFree();

	void SetHoldingItem(bool b) 
	{
		HoldingMouse_ = b;
	}

	bool GetHoldingItem() 
	{
		return HoldingMouse_;
	}

	bool MouseClickInventoryOut() {
		return (isMouseClick() && CursorPos_.y < 600);
	}

	bool MouseInItem() {

		return (MouseCollision_->CollisionResult("MouseCursor", ColList, CollisionType::Rect, CollisionType::Rect));
	}


	bool MouseInBox() {

		return (MouseCollision_->CollisionResult("Box", ColList, CollisionType::Rect, CollisionType::Rect));

	}

private:

	float4 CursorPos_;
	POINT pt;
	GameEngineRenderer* MousePoint_;
	GameEngineCollision* MouseCollision_;
	std::vector<GameEngineCollision*> ColList;

	bool HoldingMouse_;

	void Start() override;
	void Update() override;
	void Render() override;

};

