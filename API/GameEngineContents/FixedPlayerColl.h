#pragma once

#include <windows.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineInput.h>
#include <vector>
// Ό³Έν :
class FixedPlayerColl : public GameEngineActor
{
public:

	// constrcuter destructer
	FixedPlayerColl();
	~FixedPlayerColl();

	// delete Function
	FixedPlayerColl(const FixedPlayerColl& _Other) = delete;
	FixedPlayerColl(FixedPlayerColl&& _Other) noexcept = delete;
	FixedPlayerColl& operator=(const FixedPlayerColl& _Other) = delete;
	FixedPlayerColl& operator=(FixedPlayerColl&& _Other) noexcept = delete;

protected:

public:
	GameEngineRenderer* Renderer() {
		return MousePoint_;
	}
	GameEngineCollision* Collision() {
		return MouseCollision_;
	}


	bool FixedPlayerCollMouse() {

		return (MouseCollision_->CollisionResult("MouseCursor", ColList, CollisionType::Rect, CollisionType::Rect)) && 
			GameEngineInput::GetInst()->IsDown("LeftClick");
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

