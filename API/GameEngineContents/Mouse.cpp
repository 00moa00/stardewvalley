#include "Mouse.h"

#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineLevel.h> 

#include "GameData.h"

Mouse* Mouse::MainMouse = nullptr;

Mouse::Mouse() :
	CursorPos_({}),
	pt(),
	MousePoint_(nullptr),
	MouseCollision_(nullptr),
	HoldingMouse_(false)
{
}

Mouse::~Mouse() 
{
}

void Mouse::Start()
{
	CursorPos_ = { FARM_SIZE_WEIGHT / 2, FARM_SIZE_WEIGHT / 2 };

	MousePoint_ = CreateRenderer("MouseCursor.bmp");
	MousePoint_->CameraEffectOff();

	MouseCollision_ = CreateCollision("MouseCursor", { 24, 30 });
}

void Mouse::Update()
{
	ShowCursor(FALSE);
	GetCursorPos(&pt);

	ScreenToClient(GameEngineWindow::GetHWND(), &pt);

	CursorPos_.x = static_cast<float>(pt.x);
	CursorPos_.y = static_cast<float>(pt.y);

	MousePoint_->GetActor()->SetPosition(CursorPos_);


}

void Mouse::Render()
{
}

void Mouse::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainMouse = this;
}

