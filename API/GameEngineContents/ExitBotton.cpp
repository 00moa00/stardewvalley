#include "ExitBotton.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <vector>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineInput.h>

ExitBotton::ExitBotton() 
{
}

ExitBotton::~ExitBotton() 
{
}

void ExitBotton::Start()
{
	//SetPosition(GameEngineWindow::GetScale().Half());
	Exit_ = CreateRenderer("exit.bmp");
	ExitCollision_ = CreateCollision("Exit", {24, 24 });
	Exit_->CameraEffectOff();
	//ExitCollision_->GetCollisionPos();
	//ExitCollision_->GetCollisionPos
}

void ExitBotton::Update()
{
}

void ExitBotton::Render()
{
}

bool ExitBotton::MouseClick()
{
	std::vector<GameEngineCollision*> ColList;

	return (ExitCollision_->CollisionResult("MouseCursor", ColList, CollisionType::Rect, CollisionType::Rect)
		&&  (true == GameEngineInput::GetInst()->IsDown("LeftClick")));
}
