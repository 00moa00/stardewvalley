#include "BackForestLevel.h"
#include "MoveFlag.h"
#include "GameData.h"
#include "TileData.h"
#include <GameEngineBase/GameEngineTime.h>

BackForestLevel::BackForestLevel() 
{
	SetName("BackForestLevel");
	BackGround_ = CreateActor<BackGround>((int)PLAYLEVEL::BACKGROUND);
	BackGroundFront_ = CreateActor<BackGround>((int)PLAYLEVEL::BACKGROUND_FRONT);
}

BackForestLevel::~BackForestLevel() 
{
}

void BackForestLevel::Loading()
{
}

void BackForestLevel::Update()
{
}

void BackForestLevel::LevelChangeStart(GameEngineLevel* _NextLevel)
{
}

void BackForestLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}
