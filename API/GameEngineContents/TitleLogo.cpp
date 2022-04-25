#include "TitleLogo.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>

#include <GameEngine/GameEngineLevel.h>

#include "MenuNewGame.h"
#include "MenuLoad.h"
#include "MenuExit.h"

GameEngineLevel* MenuNewGame_ = nullptr;
GameEngineLevel* MenuLoad_ = nullptr;
GameEngineLevel* MenuExit_ = nullptr;


TitleLogo::TitleLogo()
	:	
		DelayTIme_(0),

		RamdomAnimation_(),
		RamdomInitFrame_(),

		Logo_(nullptr)
{
}

TitleLogo::~TitleLogo() 
{
}



void TitleLogo::Start() 
{

	Logo_ = CreateRenderer("logo_Sheet.bmp");
	Logo_->SetIndex(0);


	Logo_->CreateAnimation("logo_Sheet.bmp", "LOGO_INIT", 0, 0, 0.200f, false);
	Logo_->CreateAnimation("logo_Sheet.bmp", "LOGO_RIGHT", 1, 3, 0.120f, false);
	Logo_->CreateAnimation("logo_Sheet.bmp", "LOGO_LEFT", 4, 6, 0.120f, false);

	Logo_->ChangeAnimation("LOGO_INIT");

}

void TitleLogo::Render() 
{
}

void TitleLogo::Update()
{
	
	switch (UpdateState_)
	{
	case ANIMATION_UPDATE::RAMDOM:

		ReSetAccTime();
	

		if (RamdomAnimation_.RandomInt(0, 5) == 0)
		{
			UpdateState_ = ANIMATION_UPDATE::INIT;
			break;
		}

		if (RamdomAnimation_.RandomInt(0, 1) == 0)
		{
			UpdateState_ = ANIMATION_UPDATE::RIGHT;
			break;
		}

		if (RamdomAnimation_.RandomInt(0, 1) == 0)
		{
			UpdateState_ = ANIMATION_UPDATE::LEFT;
			break;
		}

		break;
	case ANIMATION_UPDATE::INIT:

		Logo_->ChangeAnimation("LOGO_INIT");
		if (Logo_->IsEndAnimation())
		{
			DelayTIme_ = GetAccTime() + RamdomInitFrame_.RandomInt(2, 8);

			if (DelayTIme_ > 10)
			{
				UpdateState_ = ANIMATION_UPDATE::RAMDOM;
			}
			break;
		}

		break;
	case ANIMATION_UPDATE::RIGHT:

		Logo_->ChangeAnimation("LOGO_RIGHT");
		if (Logo_->IsEndAnimation())
		{
			UpdateState_ = ANIMATION_UPDATE::RAMDOM;
			break;
		}

		break;
	case ANIMATION_UPDATE::LEFT:

		Logo_->ChangeAnimation("LOGO_LEFT");
		if (Logo_->IsEndAnimation())
		{
			UpdateState_ = ANIMATION_UPDATE::RAMDOM;
			break;
		}
		break;

	default:
		break;
	}

}
