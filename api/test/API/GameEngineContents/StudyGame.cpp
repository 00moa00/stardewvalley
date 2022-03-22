#include "StudyGame.h"
#include "PlayLevel.h"
#include "EndingLevel.h"
#include "TitleLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>

StudyGame::StudyGame() 
{
}

StudyGame::~StudyGame() 
{
}

void StudyGame::GameInit() 
{
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 100 }, {1280, 720});

	// 리소스를 다 로드하지 못하는 상황이 올수가 없다.

	GameEngineImageManager::GetInst()->Load("D:\\Project\\AR33\\API\\Project\\ApiFrameWork\\Res\\Texture\\Idle.bmp", "Idle.bmp");


	CreateLevel<TitleLevel>("Title");
	CreateLevel<PlayLevel>("Play");
	CreateLevel<EndingLevel>("Ending");
	ChangeLevel("Play");
}

void StudyGame::GameLoop() 
{

}
void StudyGame::GameEnd() 
{

}