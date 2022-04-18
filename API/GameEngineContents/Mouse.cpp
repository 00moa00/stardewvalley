#include "Mouse.h"


#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineLevel.h> 

#include "GameData.h"
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
	//SetPosition({ FARM_SIZE_WEIGHT / 2, FARM_SIZE_WEIGHT / 2 });

	CursorPos_ = { FARM_SIZE_WEIGHT / 2, FARM_SIZE_WEIGHT / 2 };
	MousePoint_ = CreateRenderer("MouseCursor.bmp");
	//MousePoint_->SetScale({ 600, 330 }); 
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

	

	//MouseCollision_->Set
	
}

void Mouse::Render()
{
}

