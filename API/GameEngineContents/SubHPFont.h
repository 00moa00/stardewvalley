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
	float4 PrevPos_;
	float4 MoveDir_;

	Font* SubHPFont_;
	
public:
	void SetPosAndNumRed(float4 _Pos, int _Damage);
	void SetPosAndNumGray(float4 _Pos, int _Damage);

};

