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
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 100 }, {960, 540});

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

	//GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("Bouncer.bmp");
	//GameEngineImageManager::GetInst()->Load("D:\\portfolio\\APIResource\\sprite\\bmp\\CharacterAPI\\Bouncer.bmp", "Bouncer.bmp");
	//GameEngineImageManager::GetInst()->Load("D:\\Project\\AR40\\API\\Resources\\Image\\HPBAR.Bmp", "HPBAR.Bmp");

	GameEngineImage* TitleImage = GameEngineImageManager::GetInst()->Find("TitleButtons.ko-KR.bmp");
	TitleImage->Cut({ 400, 187 }, { 0,0 }); //0



	for (int j = 0; j < 2; j++) {
		for (int i = 0; i < 4; i++) {
			if (i == 2) continue; // 협동플레이 버튼 스킵
			TitleImage->Cut({ 74.f, 58.f }, { 74.f * (float)i, 187.f + (58.f * j)});//1 2 3
		}
	}

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