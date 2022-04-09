#include "BackGround.h"
#include "GameData.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

BackGround::BackGround() 
{
}

BackGround::~BackGround() 
{
}

void BackGround::Start()
{

	Image_ = CreateRenderer();

}

