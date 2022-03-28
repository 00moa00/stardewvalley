#include "RightArrow.h"


#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>


#include <GameEngine/GameEngineRenderer.h>

#include <GameEngine/GameEngineLevel.h> 

RightArrow::RightArrow() 
	:
	RightArrow_(nullptr)
{
}

RightArrow::~RightArrow() 
{
}

void RightArrow::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	RightArrow_ = CreateRenderer("RightArrow.bmp");
}

void RightArrow::Update()
{
}

void RightArrow::Render()
{
}
