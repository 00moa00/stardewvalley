#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>

#include <vector>


// 설명 :
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

	std::vector<GameEngineRenderer*> NumberRenderer;
	std::vector<GameEngineRenderer*> FontRenderer;

	int Num_;
	std::string StrNum_;

public:

	// 스트링으로 받을떄
	void ChangeNumStr(std::string _Num);

	//기본 오른쪽, 왼쪽 정렬
	void ChangeNumRightSort(int _Num);
	void ChangeNumLeftSort(int _Num, float4 _Pos);

	//아이템, 소지금일때 정령 간격이 다르다
	void ChangeNumItemLeftSort(int _Num, float4 _Pos);
	void ChangeNumMoneyLeftSort(int _Num, float4 _Pos);

	void ChangeWhiteColor();

	//영문
	void ChangeFont(std::string _Font, float4 _Pos);

	//================================
	//    Setter
	//================================

	void SetPositionRightSort(float4 _Pos);
	void SetPositionItem(float4 _Pos);
};

enum class FONT
{
	Question,
	_ = 3,
	Astrerrisk = 6,
	Square_Bracket_Right,
	Square_Bracket_Left,
	Small_Question_Mark,
	Big_Question_Mark = 14,
	Exclamaion_Mark,
	z,
	y,
	x,
	w,
	v,
	u,
	t,
	s,
	r,
	q,
	p,
	o,
	n,
	m,
	l,
	k,
	j,
	i,
	h,
	g,
	f,
	e,
	d,
	c,
	b,
	a,
	Z,
	Y,
	X,
	W,
	V,
	U,
	T,
	S,
	R,
	Q,
	P,
	O,
	N,
	M,
	L,
	K,
	J,
	I,
	H,
	G,
	F,
	E,
	D,
	C,
	B,
	A,
	EMPTY,

};
