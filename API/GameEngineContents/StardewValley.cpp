#include "StardewValley.h"
#include "PlayLevel.h"
#include "EndingLevel.h"
#include "TitleLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>

StardewValley::StardewValley() 
{
}

StardewValley::~StardewValley() 
{
}

void StardewValley::GameInit() 
{
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 100 }, {1280, 720});

	// 리소스를 다 로드하지 못하는 상황이 올수가 없다.

	GameEngineImageManager::GetInst()->Load("D:\\portfolio\\APIResource\\sprite\\bmp\\CharacterAPI\\Bouncer.bmp", "Bouncer.bmp");
	//GameEngineImageManager::GetInst()->Load("D:\\Project\\AR40\\API\\Resources\\Image\\HPBAR.Bmp", "HPBAR.Bmp");


	CreateLevel<TitleLevel>("Title");
	CreateLevel<PlayLevel>("Play");
	CreateLevel<EndingLevel>("Ending");
	ChangeLevel("Play");
}

void StardewValley::GameLoop() 
{

}
void StardewValley::GameEnd() 
{

}