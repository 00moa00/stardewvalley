#include "Mouse.h"


#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineLevel.h> 

Mouse::Mouse() :
	CursorPos_({}),
	MousePoint_(nullptr)
{
}

Mouse::~Mouse() 
{
}

void Mouse::Start()
{

	CursorPos_ = GameEngineWindow::GetScale().Half();
	MousePoint_ = CreateRenderer("MouseCursor.bmp");
	//MousePoint_->SetScale({ 600, 330 }); 	//800, 440  로고 원본 크기

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

bool Mouse::isMouseClick()
{
	return (GameEngineInput::GetInst()->IsDown("LeftClick"));
}

bool Mouse::isMouseHold()
{
	return (GameEngineInput::GetInst()->IsPress("LeftClick"));

}

bool Mouse::isMouseFree()
{
	return (GameEngineInput::GetInst()->IsUp("LeftClick"));

}
