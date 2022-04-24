#include "Title.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>


Title::Title() 
{
}

Title::~Title() 
{
}




void Title::Start()
{
	SetPosition({ 1280.f/2, 1500.f });
}

void Title::Render()
{
}

void Title::Update()
{
	SetCamera();
	float4 Move = float4::UP;
	SetMove((Move * GameEngineTime::GetDeltaTime() * 150.f));
}

void Title::SetCamera()
{
	GetLevel()->SetCameraPos(GetPosition() - GameEngineWindow::GetInst().GetScale().Half());

	if (0 > GetLevel()->GetCameraPos().x)
	{
		float4 CurCameraPos = GetLevel()->GetCameraPos();
		CurCameraPos.x = 0;
		GetLevel()->SetCameraPos(CurCameraPos);
	}

	if (0 > GetLevel()->GetCameraPos().y)
	{
		float4 CurCameraPos = GetLevel()->GetCameraPos();
		CurCameraPos.y = 0;
		GetLevel()->SetCameraPos(CurCameraPos);
	}

	{
		CameraPos_ = GetPosition() - GameEngineWindow::GetInst().GetScale().Half();

		if (CameraPos_.x <= 0)
		{
			CameraPos_.x = 0;
		}

		if (CameraPos_.x >= 1280.f - GameEngineWindow::GetInst().GetScale().ix())
		{
			CameraPos_.x = 1280.f - GameEngineWindow::GetInst().GetScale().ix();
		}

		if (CameraPos_.y <= 0)
		{
			CameraPos_.y = 0;
		}

		if (CameraPos_.y >= 1500.f - GameEngineWindow::GetInst().GetScale().iy())
		{
			CameraPos_.y = 1500.f - GameEngineWindow::GetInst().GetScale().iy();
		}

		GetLevel()->SetCameraPos(CameraPos_);
	}
}
