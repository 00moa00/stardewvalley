#include "Font.h"
#include <string.h>
#include <sstream>

//Font* Font::MainFont = nullptr;

Font::Font() 
	:
	Num_(0)
{
}

Font::~Font() 
{
}

void Font::Start()
{
	NumberRenderer.reserve(10);

	for (int i = 0; i < 11; ++i)
	{
		NumberRenderer.push_back(CreateRenderer("font_colored.bmp"));
		std::vector<GameEngineRenderer*>::iterator This = --NumberRenderer.end();
		(*This)->SetIndex(10);
		(*This)->CameraEffectOff();
	}

	FontRenderer.reserve(300);

	for (int i = 0; i < 300; ++i)
	{
		FontRenderer.push_back(CreateRenderer("Font.bmp"));
		std::vector<GameEngineRenderer*>::iterator This = --FontRenderer.end();
		(*This)->SetIndex(48);
		(*This)->CameraEffectOff();
	}

}

void Font::Update()
{


}

void Font::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	//MainFont = nullptr;
}

void Font::ChangeNumStr(std::string _Num)
{
	int Count_ = 0;

	StrNum_ = _Num;

	for (Count_ = 0; Count_ < StrNum_.size(); ++Count_)
	{
		//숫자의 앞에서부터 접근
		char String = StrNum_.at(Count_);

		//int로 변환
		int Index = String - '0';

		//인덱스를 바꿈
		NumberRenderer.at(Count_)->SetIndex(Index);
	}


	//그 외의 숫자는 공백으로 함
	for (; Count_ < 11; ++Count_)
	{
		NumberRenderer.at(Count_)->SetIndex(10);
	}
}

void Font::ChangeNumRightSort(int _Num)
{
	int Count_ = 0 ;
	Num_ = _Num;

	//0 이라면
	if (Num_ == 0)
	{
		std::vector<GameEngineRenderer*>::iterator Iter = NumberRenderer.begin();
		for (; Iter != NumberRenderer.end(); ++Iter) {

			(*Iter)->SetIndex(10);

		}
		return;

	}


	std::stringstream IntToString;
	IntToString << Num_;
	StrNum_ = IntToString.str();

	for (Count_ = 0; Count_ < StrNum_.size(); ++Count_)
	{
		//숫자의 앞에서부터 접근
		char String = StrNum_.at(Count_);

		//int로 변환
		int Index = String - '0';

		//인덱스를 바꿈
		NumberRenderer.at(Count_)->SetIndex(Index);
	}


	//그 외의 숫자는 공백으로 함
	for (; Count_ < 11; ++Count_)
	{
		NumberRenderer.at(Count_)->SetIndex(10);
	}
}

void Font::ChangeNumItemLeftSort(int _Num, float4 _Pos)
{
	int Count_ = 0;

	Num_ = _Num;
	//1개는 표시 안함
	if (Num_ == 1)
	{
		std::vector<GameEngineRenderer*>::iterator Iter = NumberRenderer.begin();
		for (; Iter != NumberRenderer.end(); ++Iter) {

			(*Iter)->SetIndex(10);

		}

		return;
	}


	std::stringstream IntToString;
	IntToString << Num_;
	StrNum_ = IntToString.str();

	for (Count_ = 0; Count_ < StrNum_.size(); ++Count_)
	{
		//숫자의 앞에서부터 접근
		char String = StrNum_.at(Count_);

		//int로 변환
		int Index = String - '0';

		//인덱스를 바꿈
		NumberRenderer.at(Count_)->SetIndex(Index);

	}


	float MarginX = 0;
	for (int ChangePivotCount = Count_; ChangePivotCount > -1; --ChangePivotCount)
	{
		NumberRenderer.at(ChangePivotCount)->SetPivot({ _Pos.x - MarginX, _Pos.y + 12.f });
		MarginX += 17.f;

	}


	//그 외의 숫자는 공백으로 함
	for (; Count_ < 11; ++Count_)
	{
		NumberRenderer.at(Count_)->SetIndex(10);
	}

}

void Font::ChangeNumMoneyLeftSort(int _Num, float4 _Pos)
{
	int Count_ = 0;
	Num_ = _Num;

	//0 이라면
	if (Num_ == 0)
	{
		std::vector<GameEngineRenderer*>::iterator Iter = NumberRenderer.begin();
		for (; Iter != NumberRenderer.end(); ++Iter) {

			(*Iter)->SetIndex(10);

		}
		return;

	}


	std::stringstream IntToString;
	IntToString << Num_;
	StrNum_ = IntToString.str();

	for (Count_ = 0; Count_ < StrNum_.size(); ++Count_)
	{
		//숫자의 앞에서부터 접근
		char String = StrNum_.at(Count_);

		//int로 변환
		int Index = String - '0';

		//인덱스를 바꿈
		NumberRenderer.at(Count_)->SetIndex(Index);
	}

	float MarginX = 0;
	for (int ChangePivotCount = Count_; ChangePivotCount > -1; --ChangePivotCount)
	{
		NumberRenderer.at(ChangePivotCount)->SetPivot({ _Pos.x - MarginX, _Pos.y  });
		MarginX += 18.f;

	}

	//그 외의 숫자는 공백으로 함
	for (; Count_ < 11; ++Count_)
	{
		NumberRenderer.at(Count_)->SetIndex(10);
	}
}

void Font::ChangeNumLeftSort(int _Num , float4 _Pos)
{
	int Count_ = 0;
	Num_ = _Num;

	//0 이라면
	if (Num_ == 0)
	{
		std::vector<GameEngineRenderer*>::iterator Iter = NumberRenderer.begin();
		for (; Iter != NumberRenderer.end(); ++Iter) {

			(*Iter)->SetIndex(10);

		}
		return;

	}


	std::stringstream IntToString;
	IntToString << Num_;
	StrNum_ = IntToString.str();

	for (Count_ = 0; Count_ < StrNum_.size(); ++Count_)
	{
		//숫자의 앞에서부터 접근
		char String = StrNum_.at(Count_);

		//int로 변환
		int Index = String - '0';

		//인덱스를 바꿈
		NumberRenderer.at(Count_)->SetIndex(Index);
	}

	float MarginX =0;
	for (int ChangePivotCount = Count_; ChangePivotCount > -1; --ChangePivotCount)
	{
		NumberRenderer.at(ChangePivotCount)->SetPivot({ _Pos.x - MarginX, _Pos.y + 12.f });
		MarginX += 11.f;

	}

	//그 외의 숫자는 공백으로 함
	for (; Count_ < 11; ++Count_)
	{
		NumberRenderer.at(Count_)->SetIndex(10);
	}
}





void Font::SetPositionRightSort(float4 _Pos)
{
	std::vector<GameEngineRenderer*>::iterator Iter = NumberRenderer.begin();
	for (int i = 0; Iter != NumberRenderer.end(); ++Iter)
	{

		(*Iter)->SetPivot({ _Pos.x + (18 * i), _Pos.y });
		++i;

	}
}

void Font::SetPositionItem(float4 _Pos)
{

	std::vector<GameEngineRenderer*>::iterator ItemPosIter = NumberRenderer.begin();
	for (int i = 0; ItemPosIter != NumberRenderer.end(); ++ItemPosIter)
	{

		(*ItemPosIter)->SetPivot({ _Pos.x + (20.f) + (8.f * i), _Pos.y+(22.f)});
		++i;

	}

}

void Font::ChangeWhiteColor()
{

	std::vector<GameEngineRenderer*>::iterator Iter = NumberRenderer.begin();
	for (; Iter != NumberRenderer.end(); ++Iter) {

		(*Iter)->SetImage("font_colored_White.bmp");

	}
}

void Font::ChangeFont(std::string _Font, float4 _Pos)
{
	int Count_ = 0;
	float MarginX = 0;
	float MarginY = 0;

	char Font_[300];
	strcpy_s(Font_, _Font.c_str());

	for (Count_ = 0; Count_ < _Font.size(); ++Count_)
	{
		switch (Font_[Count_])
		{
		case 'A':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::A));
			break;
		case 'B':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::B));
			break;
		case 'C':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::C));
			break;
		case 'D':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::D));
			break;
		case 'E':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::E));
			break;
		case 'F':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::F));
			break;
		case 'G':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::G));
			break;
		case 'H':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::H));
			break;
		case 'I':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::I));
			break;
		case 'J':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::J));
			break;
		case 'K':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::K));
			break;
		case 'L':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::L));
			break;
		case 'M':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::M));
			break;
		case 'N':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::N));
			break;
		case 'O':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::O));
			break;
		case 'P':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::P));
			break;
		case 'Q':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::Q));
			break;
		case 'R':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::R));
			break;
		case 'S':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::S));
			break;
		case 'T':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::T));
			break;
		case 'U':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::U));
			break;
		case 'V':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::V));
			break;
		case 'W':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::W));
			break;
		case 'X':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::X));
			break;
		case 'Y':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::Y));
			break;
		case 'Z':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::Z));
			break;
		case 'a':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::a));
			break;
		case 'b':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::b));
			break;
		case 'c':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::c));
			break;
		case 'd':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::d));
			break;
		case 'e':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::e));
			break;
		case 'f':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::f));
			break;
		case 'g':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::g));
			break;
		case 'h':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::h));
			break;
		case 'i':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::i));
			break;
		case 'j':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::j));
			break;
		case 'k':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::k));
			break;
		case 'l':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::l));
			break;
		case 'm':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::m));
			break;
		case 'n':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::n));
			break;
		case 'o':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::o));
			break;
		case 'p':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::p));
			break;
		case 'q':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::q));
			break;
		case 'r':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::r));
			break;
		case 's':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::s));
			break;
		case 't':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::t));
			break;
		case 'u':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::u));
			break;
		case 'v':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::v));
			break;
		case 'w':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::w));
			break;
		case 'x':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::x));
			break;
		case 'y':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::y));
			break;
		case 'z':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::z));
			break;
		case '?':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::Question));
			break;
		case '*':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::Astrerrisk));
			break;
		case ')':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::Square_Bracket_Right));
			break;
		case '(':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::Square_Bracket_Left));
			break;
		case '"':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::Big_Question_Mark));
			break;
		case '!':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::Exclamaion_Mark));
			break;
		case '-':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::_));
			break;
		case '.':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::DecimalPoint));
			break;
		case '/':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::EMPTY));
			MarginY += 40.f;
			MarginX = 0;
			break;
		case ' ':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::EMPTY));
			break;

		default:
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::EMPTY));
		}


		FontRenderer.at(Count_)->SetPivot({ _Pos.x + MarginX, _Pos.y + MarginY });
		if (Font_[Count_] != '/')
		{
			MarginX += 17.f;
		}


	}



	//그 외는공백으로 함
	for (; Count_ < 300; ++Count_)
	{
		FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT::EMPTY));
	}

}

