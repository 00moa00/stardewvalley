#pragma once

#include <windows.h>
#include <GameEngine/GameEngineRenderer.h>
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

	void MouseOff() {
		this -> Off();
	}

	bool isMouseClick();
	bool isMouseHold();
	bool isMouseFree();

	void SetHoldingItem(bool b) {
		HoldingMouse_ = b;
	}

	bool GetHoldingItem() {
		return HoldingMouse_;
	}

private:

	float4 CursorPos_;
	POINT pt;
	GameEngineRenderer* MousePoint_;
	GameEngineCollision* MouseCollision_;

	bool HoldingMouse_;

	void Start() override;
	void Update() override;
	void Render() override;

};

