#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class BotUI : public GameEngineActor
{
public:
	BotUI();
	~BotUI();

	BotUI(const BotUI& _Other) = delete;
	BotUI(BotUI&& _Other) noexcept = delete;
	BotUI& operator=(const BotUI& _Other) = delete;
	BotUI& operator=(BotUI&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Render() override;
};

