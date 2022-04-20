#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>

#include <vector>


// Ό³Έν :
class Font : public GameEngineActor
{
	//static Font* MainFont;

public:
	// constrcuter destructer
	Font();
	~Font();

	// delete Function
	Font(const Font& _Other) = delete;
	Font(Font&& _Other) noexcept = delete;
	Font& operator=(const Font& _Other) = delete;
	Font& operator=(Font&& _Other) noexcept = delete;


private:

	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

private:

	std::vector<GameEngineRenderer*> FontRenderer;
	int Num_;
	std::string StrNum_;

public:

	void ChangeNumStr(std::string _Num);
	void ChangeNumUI(int _Num);
	void ChangeNumItem(int _Num);
	void ChangeWhiteColor();

	//================================
	//    Setter
	//================================

	void SetPositionUI(float4 _Pos);
	void SetPositionItem(float4 _Pos);
};

