#include "BackGround.h"
#include "GameData.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

BackGround::BackGround() 
	: DirtTileMap_(this),
	WetTileMap_(this)
{
}

BackGround::~BackGround() 
{
}

void BackGround::Start()
{
	//MapColImage_ = GameEngineImageManager::GetInst()->Find("FarmBack_Coll.bmp");
	Renderer = CreateRenderer();

}

