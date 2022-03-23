#include "StardewValley.h"
#include "PlayLevel.h"
#include "EndingLevel.h"
#include "TitleLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngine/GameEngineImageManager.h>
#include <vector>


StardewValley::StardewValley() 
{
}

StardewValley::~StardewValley() 
{
}

void StardewValley::GameInit() 
{
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 100 }, {1920, 1080});

	// 현재 디렉토리
	GameEngineDirectory ResourcesDir;
	ResourcesDir.MoveParent("API");
	ResourcesDir.MoveParent("portfolio");
	ResourcesDir.Move("APIResource");
	ResourcesDir.Move("sprite");
	ResourcesDir.Move("bmp");
	ResourcesDir.Move("All");

	// 폴더안에 모든 이미지 파일을 찾는다.
	std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

	for (size_t i = 0; i < AllImageFileList.size(); i++)
	{
		GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
	}

	//GameEngineImageManager::GetInst()->Load("D:\\portfolio\\APIResource\\sprite\\bmp\\CharacterAPI\\Bouncer.bmp", "Bouncer.bmp");
	//GameEngineImageManager::GetInst()->Load("D:\\Project\\AR40\\API\\Resources\\Image\\HPBAR.Bmp", "HPBAR.Bmp");


	CreateLevel<TitleLevel>("Title");
	CreateLevel<PlayLevel>("Play");
	CreateLevel<EndingLevel>("Ending");
	ChangeLevel("Title");
}

void StardewValley::GameLoop() 
{

}
void StardewValley::GameEnd() 
{

}