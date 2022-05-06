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
		FontRenderer.push_back(CreateRenderer("font_ver2.bmp"));
		std::vector<GameEngineRenderer*>::iterator This = --FontRenderer.end();
		(*This)->SetIndex(static_cast<int>(FONT_VER2::EMPTY));
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

void Font::InitFont()
{
	for (int Count_ = 0; Count_ < 300; ++Count_)
	{
		FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::EMPTY));
	}
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


	//그 외의 숫자는 공백으로 함. 일단 세자리만 설정
	for (; Count_ < 3; ++Count_)
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

void Font::SetFontCameraEffectOn()
{
	std::vector<GameEngineRenderer*>::iterator Iter = NumberRenderer.begin();
	for (; Iter != NumberRenderer.end(); ++Iter) {

		(*Iter)->CameraEffectOn();
	}
}

void Font::ChangeWhiteColor()
{
	std::vector<GameEngineRenderer*>::iterator Iter = NumberRenderer.begin();
	for (; Iter != NumberRenderer.end(); ++Iter) {

		(*Iter)->SetImage("font_colored_White.bmp");
	}
}

void Font::ChangeRedColor()
{
	std::vector<GameEngineRenderer*>::iterator Iter = NumberRenderer.begin();
	for (; Iter != NumberRenderer.end(); ++Iter) {

		(*Iter)->SetImage("font_colored_Red.bmp");
	}
}

void Font::ChangeGrayColor()
{
	std::vector<GameEngineRenderer*>::iterator Iter = NumberRenderer.begin();
	for (; Iter != NumberRenderer.end(); ++Iter) {

		(*Iter)->SetImage("font_colored_Gray.bmp");
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
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::A));
			break;
		case 'B':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::B));
			break;
		case 'C':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::C));
			break;
		case 'D':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::D));
			break;
		case 'E':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::E));
			break;
		case 'F':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::F));
			break;
		case 'G':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::G));
			break;
		case 'H':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::H));
			break;
		case 'I':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::I));
			break;
		case 'J':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::J));
			break;
		case 'K':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::K));
			break;
		case 'L':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::L));
			break;
		case 'M':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::M));
			break;
		case 'N':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::N));
			break;
		case 'O':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::O));
			break;
		case 'P':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::P));
			break;
		case 'Q':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::Q));
			break;
		case 'R':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::R));
			break;
		case 'S':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::S));
			break;
		case 'T':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::T));
			break;
		case 'U':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::U));
			break;
		case 'V':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::V));
			break;
		case 'W':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::W));
			break;
		case 'X':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::X));
			break;
		case 'Y':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::Y));
			break;
		case 'Z':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::Z));
			break;
		case 'a':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::a));
			break;
		case 'b':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::b));
			break;
		case 'c':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::c));
			break;
		case 'd':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::d));
			break;
		case 'e':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::e));
			break;
		case 'f':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::f));
			break;
		case 'g':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::g));
			break;
		case 'h':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::h));
			break;
		case 'i':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::i));
			break;
		case 'j':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::j));
			break;
		case 'k':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::k));
			break;
		case 'l':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::l));
			break;
		case 'm':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::m));
			break;
		case 'n':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::n));
			break;
		case 'o':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::o));
			break;
		case 'p':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::p));
			break;
		case 'q':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::q));
			break;
		case 'r':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::r));
			break;
		case 's':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::s));
			break;
		case 't':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::t));
			break;
		case 'u':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::u));
			break;
		case 'v':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::v));
			break;
		case 'w':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::w));
			break;
		case 'x':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::x));
			break;
		case 'y':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::y));
			break;
		case 'z':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::z));
			break;
		case '0':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::Zero));
			break;
		case '1':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::One));
			break;
		case '2':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::Two));
			break;
		case '3':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::Three));
			break;
		case '4':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::Four));
			break;
		case '5':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::Five));
			break;
		case '6':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::Six));
			break;
		case '7':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::Seven));
			break;
		case '8':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::Eight));
			break;
		case '9':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::Nine));
			break;

		case '?':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::Question));
			break;
		case '*':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::Astrerrisk));
			break;
		case ')':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::Square_Bracket_Right));
			break;
		case '(':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::Square_Bracket_Left));
			break;
		case '"':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::Big_Question_Mark));
			break;
		case '!':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::Exclamaion_Mark));
			break;
		case '-':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::_));
			break;
		case '.':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::DecimalPoint));
			break;
		case ' ':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::EMPTY));
			break;
		case ',':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::Period));
			break;
		case '`':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::Small_Question_Mark));
			break;
		case '/':
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::EMPTY));
			MarginY += 40.f;
			MarginX = 0;
			break;


		default:
			FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::EMPTY));
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
		FontRenderer.at(Count_)->SetIndex(static_cast<int>(FONT_VER2::EMPTY));
	}

}

void Font::CreateFontInit(std::string _Font, float4 _Pos)
{
}

