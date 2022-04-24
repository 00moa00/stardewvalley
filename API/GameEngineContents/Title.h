#pragma once
#include <GameEngine/GameEngineActor.h>
#include "BackGround.h"
#include "RendererData.h"

// Ό³Έν :
class Title : public GameEngineActor
{
public:
	// constrcuter destructer
	Title();
	~Title();

	// delete Function
	Title(const Title& _Other) = delete;
	Title(Title&& _Other) noexcept = delete;
	Title& operator=(const Title& _Other) = delete;
	Title& operator=(Title&& _Other) noexcept = delete;

private:
	void Start()override;
	void Render()override;
	void Update() override;

private:

	float4 CameraPos_;
	float4 Speed_;
private:
	void SetCamera();
};

