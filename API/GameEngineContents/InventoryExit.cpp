#include "InventoryExit.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <vector>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineInput.h>

InventoryExit::InventoryExit() 
{
}

InventoryExit::~InventoryExit() 
{
}

void InventoryExit::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	Exit_ = CreateRenderer("exit.bmp");
	ExitCollision_ = CreateCollision("Exit", { 64, 64 });
	
	Exit_->CameraEffectOff();
	//ExitCollision_->GetCollisionPos();
	//ExitCollision_->GetCollisionPos
}

void InventoryExit::Update()
{
}

void InventoryExit::Render()
{
}

bool InventoryExit::MouseClick()
{
	std::vector<GameEngineCollision*> ColList;

	return (ExitCollision_->CollisionResult("MouseCursor", ColList, CollisionType::Rect, CollisionType::Rect)
		&&  (true == GameEngineInput::GetInst()->IsDown("LeftClick")));
}
