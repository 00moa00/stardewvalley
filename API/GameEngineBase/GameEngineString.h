#pragma once
#include <string>
#include <algorithm>

//TODO : std::transform
//		 first1부터 last1 전까지 범위의 원소들을 unary_op를 수행하고, 그 결과를 d_first부터 차례로 저장한다
//		 first1, last1 : transform 함수를 적용할 첫 번째 원소들을 가리키는 범위
//		 first2: transform 함수를 적용할 두 번째 원소들의 시작점
//		 d_first : 결과를 저장할 범위. (first1, first2와 동일해도 됨.이 경우, 기존 데이터를 덮어쓰게 됨)
//		 binary_op : 원소들을 변환할 함수. 2 개의 parameter를 가짐.
// 

class GameEngineString
{
public:
	static void ToUpper(std::string& _Text)
	{
		for (size_t i = 0; i < _Text.size(); i++)
		{
			_Text[i] = std::toupper(_Text[i]);
		}

		// std::transform(_Text.begin(), _Text.end(), _Text.begin(), std::toupper);
	}

	static std::string ToUpperReturn(const std::string& _Text)
	{
		std::string NewText = _Text;
		for (size_t i = 0; i < _Text.size(); i++)
		{
			NewText[i] = std::toupper(NewText[i]);
		}
		return NewText;
	}

	static void AnsiToUnicode(const std::string& Text, std::wstring& _Out);
	static void UniCodeToUTF8(const std::wstring& _Text, std::string& _Out);
	static void AnsiToUTF8(const std::string& Text, std::string& _Out);
	static std::string AnsiToUTF8Return(const std::string& Text);
	static std::wstring StringToWStringReturn(const std::string& Text);

protected:

private:
	// constrcuter destructer
	GameEngineString();
	~GameEngineString();

	// delete Function
	GameEngineString(const GameEngineString& _Other) = delete;
	GameEngineString(GameEngineString&& _Other) noexcept = delete;
	GameEngineString& operator=(const GameEngineString& _Other) = delete;
	GameEngineString& operator=(GameEngineString&& _Other) noexcept = delete;


};



