#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineRandom.h>

enum class ANIMATION_UPDATE
{
	RAMDOM,
	INIT,
	RIGHT,
	LEFT
};

// Ό³Έν :
class TitleLogo : public GameEngineActor
{
public:
	// constrcuter destructer
	TitleLogo();
	~TitleLogo();

	// delete Function
	TitleLogo(const TitleLogo& _Other) = delete;
	TitleLogo(TitleLogo&& _Other) noexcept = delete;
	TitleLogo& operator=(const TitleLogo& _Other) = delete;
	TitleLogo& operator=(TitleLogo&& _Other) noexcept = delete;

private:
	void Start()override;
	void Render()override;
	void Update() override;

private:

	int DelayTIme_;

	ANIMATION_UPDATE UpdateState_;
	
	GameEngineRenderer* Logo_;
	GameEngineRandom RamdomAnimation_;
	GameEngineRandom RamdomInitFrame_;

};

