#pragma once
#include "Font.h"

// Ό³Έν :
class SubHPFont : public GameEngineActor
{
public:
	// constrcuter destructer
	SubHPFont();
	~SubHPFont();

	// delete Function
	SubHPFont(const SubHPFont& _Other) = delete;
	SubHPFont(SubHPFont&& _Other) noexcept = delete;
	SubHPFont& operator=(const SubHPFont& _Other) = delete;
	SubHPFont& operator=(SubHPFont&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;

private:
	Font* SubHPFont_;
	
public:
	void SetPosition(float4 _Pos);
};

