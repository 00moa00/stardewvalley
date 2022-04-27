#include "CustomBoard.h"
#include <GameEngineBase/GameEngineWindow.h>

#include "RendererData.h"

CustomBoard::CustomBoard() 
	:
	ArrowButton_(),

	CustomBoardRenderer_(nullptr)
{
}

CustomBoard::~CustomBoard() 
{
}

void CustomBoard::Start()
{
	CustomBoardRenderer_ = CreateRenderer("Customboard.bmp");

	ArrowButton_[0] = GetLevel()->CreateActor<ArrowButton>(static_cast<int>(TITLELEVEL::CUSTROM_ARROW));
	ArrowButton_[0]->CreateLeftArrow();
	ArrowButton_[0]->SetPosition({ GameEngineWindow::GetInst().GetScale().Half().x - 100.f, 410.f});
	ArrowButton_[0]->GetRenderer()->CameraEffectOff();

	ArrowButton_[1] = GetLevel()->CreateActor<ArrowButton>(static_cast<int>(TITLELEVEL::CUSTROM_ARROW));
	ArrowButton_[1]->CreateLeftArrow();
	ArrowButton_[1]->SetPosition({ GameEngineWindow::GetInst().GetScale().Half().x - 100.f, 480.f });
	ArrowButton_[1]->GetRenderer()->CameraEffectOff();

	ArrowButton_[2] = GetLevel()->CreateActor<ArrowButton>(static_cast<int>(TITLELEVEL::CUSTROM_ARROW));
	ArrowButton_[2]->CreateLeftArrow();
	ArrowButton_[2]->SetPosition({ GameEngineWindow::GetInst().GetScale().Half().x - 100.f, 550.f });
	ArrowButton_[2]->GetRenderer()->CameraEffectOff();

	ArrowButton_[3] = GetLevel()->CreateActor<ArrowButton>(static_cast<int>(TITLELEVEL::CUSTROM_ARROW));
	ArrowButton_[3]->CreateRightArrow();
	ArrowButton_[3]->SetPosition({ GameEngineWindow::GetInst().GetScale().Half().x + 100.f, 410.f });
	ArrowButton_[3]->GetRenderer()->CameraEffectOff();

	ArrowButton_[4] = GetLevel()->CreateActor<ArrowButton>(static_cast<int>(TITLELEVEL::CUSTROM_ARROW));
	ArrowButton_[4]->CreateRightArrow();
	ArrowButton_[4]->SetPosition({ GameEngineWindow::GetInst().GetScale().Half().x + 100.f, 480.f });
	ArrowButton_[4]->GetRenderer()->CameraEffectOff();

	ArrowButton_[5] = GetLevel()->CreateActor<ArrowButton>(static_cast<int>(TITLELEVEL::CUSTROM_ARROW));
	ArrowButton_[5]->CreateRightArrow();
	ArrowButton_[5]->SetPosition({ GameEngineWindow::GetInst().GetScale().Half().x + 100.f, 550.f });
	ArrowButton_[5]->GetRenderer()->CameraEffectOff();

}

void CustomBoard::Update()
{
}

void CustomBoard::CustomBoardOff()
{
	CustomBoardRenderer_->Off();

	for (int i = 0; i < 6; ++i)
	{
		ArrowButton_[i]->Off();
	}

}

void CustomBoard::CustomBoardOn()
{
	CustomBoardRenderer_->On();

	for (int i = 0; i < 6; ++i)
	{
		ArrowButton_[i]->On();
	}

}

