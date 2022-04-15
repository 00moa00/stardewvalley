#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>

#include <vector>
// Ό³Έν :
class Font : public GameEngineActor
{
public:
	// constrcuter destructer
	Font();
	~Font();

	// delete Function
	Font(const Font& _Other) = delete;
	Font(Font&& _Other) noexcept = delete;
	Font& operator=(const Font& _Other) = delete;
	Font& operator=(Font&& _Other) noexcept = delete;

protected:

private:

	void Start() override;
	void Update() override;

private:

	std::vector<GameEngineRenderer*> FontRenderer;
	int Num_;
	int Count_;
	std::string StrNum_;

public:
	void ChangeNum(int _Num);
	void ChangeWhiteColor();

	void SetPositionUI(float4 _Pos);
	void SetPositionItem(float4 _Pos);
};

