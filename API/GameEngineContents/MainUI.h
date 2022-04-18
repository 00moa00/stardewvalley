#pragma once
#include <GameEngine/GameEngineActor.h>
#include "Font.h"

// Ό³Έν :
class MainUI : public GameEngineActor
{
public:
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

private:
	GameEngineRenderer* MainUI_;
	Font* Font_;

	int Money_;

public:
	void SetMainUIMoney(int _Money);

};

