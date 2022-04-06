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
	bool isMouseClick();
	bool isMouseHold();
	bool isMouseFree();

private:

	float4 CursorPos_;
	POINT pt;
	GameEngineRenderer* MousePoint_;
	GameEngineCollision* MouseCollision_;

	void Start() override;
	void Update() override;
	void Render() override;

};

