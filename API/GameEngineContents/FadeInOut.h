#pragma once
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineTime.h>

// Ό³Έν :
class FadeInOut : public GameEngineActor
{
public:
	// constrcuter destructer
	FadeInOut();
	~FadeInOut();

	// delete Function
	FadeInOut(const FadeInOut& _Other) = delete;
	FadeInOut(FadeInOut&& _Other) noexcept = delete;
	FadeInOut& operator=(const FadeInOut& _Other) = delete;
	FadeInOut& operator=(FadeInOut&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;


private:

	int FadeAlpha_;
	bool FadeIn_;
	bool FadeOut_;
	bool FadeEnd_;

	GameEngineRenderer* FadeRenderer_;

public:
	void SetFadeIn();
	void SetFadeOut();

	bool GetFadeEnd()
	{
		return FadeEnd_;
	}
};

