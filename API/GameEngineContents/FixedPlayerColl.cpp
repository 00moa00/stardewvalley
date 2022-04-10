#include "FixedPlayerColl.h"


#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineLevel.h> 
#include "GameData.h"
FixedPlayerColl::FixedPlayerColl() :
	CursorPos_({}),
	MousePoint_(nullptr)
{
}

FixedPlayerColl::~FixedPlayerColl()
{
}

void FixedPlayerColl::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	//CreateRenderer();
	MousePoint_ = CreateRenderer("MouseCursor.bmp");

	MouseCollision_ = CreateCollision("FixedPlayerColl", { 144, 96 });
	MousePoint_->CameraEffectOff();

}

void FixedPlayerColl::Update()
{

	//

	//ShowCursor(FALSE);
	//GetCursorPos(&pt);

	//ScreenToClient(GameEngineWindow::GetHWND(), &pt);
	//CursorPos_.x = static_cast<float>(pt.x);
	//CursorPos_.y = static_cast<float>(pt.y);

	//MousePoint_->GetActor()->SetPosition(CursorPos_);
	//MouseCollision_->SetPivot({GetPosition()});
	//MouseCollision_->SetPivot({ CursorPos_.x + 640.f , CursorPos_.y + 360});

	////MouseCollision_->Set

}

void FixedPlayerColl::Render()
{
}
//
//bool FixedPlayerColl::isMouseClick()
//{
//	return (GameEngineInput::GetInst()->IsDown("LeftClick"));
//}
//
//bool FixedPlayerColl::isMouseHold()
//{
//	return (GameEngineInput::GetInst()->IsPress("LeftClick"));
//
//}
//
//bool FixedPlayerColl::isMouseFree()
//{
//	return (GameEngineInput::GetInst()->IsUp("LeftClick"));
//
//}
