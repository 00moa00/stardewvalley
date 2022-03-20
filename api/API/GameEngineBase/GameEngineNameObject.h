#pragma once
#include <string>

class GameEngineNameObject
{
public:
	GameEngineNameObject();
	virtual ~GameEngineNameObject();

	GameEngineNameObject(const GameEngineNameObject& _Other) = delete;
	GameEngineNameObject(GameEngineNameObject&& _Other) noexcept = delete;
	GameEngineNameObject& operator=(const GameEngineNameObject& _Other) = delete;
	GameEngineNameObject& operator=(GameEngineNameObject&& _Other) noexcept = delete;

	// 그냥 std::string으로 하면 값이 복사가 되면서 문제가 많아진다.
	inline void SetName(const std::string& _Name) 
	{
		Name_ = _Name;
	}


	std::string GetNameCopy()
	{
		return Name_;
	}

	const std::string& GetNameConstRef()
	{
		return Name_;
	}

	const char* GetNameConstPtr()
	{
		return Name_.c_str();
	}


protected:

private:
	std::string Name_;

};

