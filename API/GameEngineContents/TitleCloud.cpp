#include "TitleCloud.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

TitleCloud::TitleCloud()
{
	// Level_ = nullptr;
}

TitleCloud::~TitleCloud()
{
}

void TitleCloud::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale(GameEngineWindow::GetScale());



}

void TitleCloud::Render()
{


	//DebugRectRender();
}

void TitleCloud::Update()
{

}
