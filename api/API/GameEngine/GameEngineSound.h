#pragma once
#include <GameEngineBase/GameEngineNameObject.h>

class GameEngineSound : public GameEngineNameObject
{
public:
	GameEngineSound();
	~GameEngineSound();

	GameEngineSound(const GameEngineSound& _Other) = delete;
	GameEngineSound(GameEngineSound&& _Other) noexcept = delete;
	GameEngineSound& operator=(const GameEngineSound& _Other) = delete;
	GameEngineSound& operator=(GameEngineSound&& _Other) noexcept = delete;

protected:

private:

};

