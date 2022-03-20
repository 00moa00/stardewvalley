#include "StardewValley.h"
#include "PlayLevel.h"
#include "EndingLevel.h"
#include "TitleLevel.h"
#include <GameEngineBase/GameEngineWindow.h>

StardewValley::StardewValley() 
{
}

StardewValley::~StardewValley() 
{
}

void StardewValley::GameInit() 
{
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 100 }, {1280, 720});

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