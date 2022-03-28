#pragma once
#include <GameEngine/GameEngineActor.h>

// ���� :
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

protected:
	void Start()override;
	void Render()override;
	void Update() override;

private:
	float Speed_;
	float4 ScaleSpeed_;
	GameEngineRenderer* Logo_;

};

