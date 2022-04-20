#pragma once

#include <windows.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineInput.h>
#include <vector>
// Ό³Έν :
class Mouse : public GameEngineActor
{
public:
	static Mouse* MainMouse;

	// constrcuter destructer
	Mouse();
	~Mouse();

	// delete Function
	Mouse(const Mouse& _Other) = delete;
	Mouse(Mouse&& _Other) noexcept = delete;
	Mouse& operator=(const Mouse& _Other) = delete;
	Mouse& operator=(Mouse&& _Other) noexcept = delete;

private:

	void Start() override;
	void Update() override;
	void Render() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

private:

	float4 CursorPos_;
	POINT pt;

	bool HoldingMouse_;

	GameEngineRenderer* MousePoint_;
	GameEngineCollision* MouseCollision_;
	std::vector<GameEngineCollision*> ColList;

public:

	GameEngineRenderer* Renderer()
	{
		return MousePoint_;
	}

	GameEngineCollision* Collision()
	{
		return MouseCollision_;
	}

	void MouseOff()
	{
		this->Off();
	}

	void SetHoldingItem(bool b)
	{
		HoldingMouse_ = b;
	}

	bool GetHoldingItem()
	{
		return HoldingMouse_;
	}

	bool MouseClickInventoryOut()
	{
		return (isMouseClick() && CursorPos_.y < 600);
	}

	bool MouseClickShopIn()
	{
		return (isMouseClick() && CursorPos_.y < 400);
	}


	bool isMouseClick()
	{
		return (GameEngineInput::GetInst()->IsDown("LeftClick"));
	}

	bool isMouseHold()
	{
		return (GameEngineInput::GetInst()->IsPress("LeftClick"));
	}

	bool isMouseFree()
	{
		return (GameEngineInput::GetInst()->IsUp("LeftClick"));
	}

	bool MouseInItem()
	{
		return (MouseCollision_->CollisionResult("MouseCursor", ColList, CollisionType::Rect, CollisionType::Rect));
	}

	bool MouseInBox()
	{
		return (MouseCollision_->CollisionResult("Box", ColList, CollisionType::Rect, CollisionType::Rect));
	}

	bool MouseClickAndItemColl()
	{
		return (MouseCollision_->CollisionResult("Item", ColList, CollisionType::Rect, CollisionType::Rect))
			&& (isMouseClick() == true);
	}

};

