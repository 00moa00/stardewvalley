#include "Weeds.h"
#include <GameEngineBase/GameEngineWindow.h>

Weeds::Weeds() :
	Weeds_(nullptr)
{
}

Weeds::~Weeds() 
{
}

void Weeds::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());

	Weeds_ = CreateRenderer("springobjects.bmp");
	Weeds_->SetIndex(39);
}

void Weeds::Update()
{
}

void Weeds::Render()
{
}
