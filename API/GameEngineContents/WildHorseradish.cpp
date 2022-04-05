#include "WildHorseradish.h"
#include <GameEngineBase/GameEngineWindow.h>

WildHorseradish::WildHorseradish() :
	WildHorseradish_(nullptr)
{
}

WildHorseradish::~WildHorseradish()
{
}

void WildHorseradish::thisCreateActor()
{
	GetLevel()->CreateActor<WildHorseradish>(11);
}

void WildHorseradish::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());

	WildHorseradish_ = CreateRenderer("springobjects.bmp");
	WildHorseradish_->SetIndex(39);
}

void WildHorseradish::Update()
{
}

void WildHorseradish::Render()
{
}
