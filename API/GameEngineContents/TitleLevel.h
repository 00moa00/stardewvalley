#pragma once
#include <GameEngine/GameEngineLevel.h>
#include "TitleLogo.h"
#include "RendererData.h"
#include "MenuExit.h"
#include "MenuLoad.h"
#include "MenuNewGame.h"
#include "Mouse.h"
#include "Player.h"
#include "Title.h"
#include "BackGround.h"
#include "Bird.h"

#include "CustomBoard.h"


// 설명 :
class TitleLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	TitleLevel();
	~TitleLevel();

	// delete Function
	TitleLevel(const TitleLevel& _Other) = delete;
	TitleLevel(TitleLevel&& _Other) noexcept = delete;
	TitleLevel& operator=(const TitleLevel& _Other) = delete;
	TitleLevel& operator=(TitleLevel&& _Other) noexcept = delete;

private:

	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _NextLevel) override;

private:

	bool isPopup_;
	bool KeyFlag_; //업데이트에서 함수를 한번만 사용하기 위한 플러그
	int Timer_;

	Title* Title_;

	TitleLogo* TitleLogo_;
	MenuNewGame* MenuNewGame_;
	MenuLoad* MenuLoad_;
	MenuExit* MenuExit_;

	Mouse* Mouse_;

	BackGround* TitleBackGround_;
	BackGround* TitleRightFrontMount;
	BackGround* TitleLeftFrontMount;
	BackGround* TitleBackMountBlue;
	BackGround* TitleBackMountGreen;
	BackGround* TitleCloud_[3];

	Bird* Bird_[2];

	CustomBoard* CustomBoard_;


private:

	void MoveCloud();
	void MoveFrontMount();
	void MoveBackMount();
	void MoveTitleLogo();
	void MoveLogo();
	void PopUpMenu();
	void MoveBird();

	void SkipTitle();

	//================================
	//     Getter
	//================================


	//================================
	//     Setter
	//================================


	void AddTimer(int i) {
		Timer_ += i;
	}

	int getTimer() {
		return Timer_;
	}
};

