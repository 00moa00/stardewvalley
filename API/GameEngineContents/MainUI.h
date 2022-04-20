#pragma once
#include <GameEngine/GameEngineActor.h>
#include "Font.h"

// Ό³Έν :
class MainUI : public GameEngineActor
{
public:
	static MainUI* MainMainUI;
	// constrcuter destructer
	MainUI();
	~MainUI();

	// delete Function
	MainUI(const MainUI& _Other) = delete;
	MainUI(MainUI&& _Other) noexcept = delete;
	MainUI& operator=(const MainUI& _Other) = delete;
	MainUI& operator=(MainUI&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update() override;
	void Render() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:

	int Money_;

	GameEngineRenderer* MainUI_;
	static Font* Font_;


public:
	void SetMainUIMoney(int _Money);

};

