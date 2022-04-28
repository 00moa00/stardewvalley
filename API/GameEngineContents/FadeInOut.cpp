#include "FadeInOut.h"

FadeInOut::FadeInOut() 

	:
	FadeEnd_(false),
	FadeIn_(false),
	FadeOut_(false)
{
}

FadeInOut::~FadeInOut() 
{
}

void FadeInOut::Start()
{
	FadeRenderer_ = CreateRenderer("FadeIn.bmp");
	FadeRenderer_->CameraEffectOff();
	FadeRenderer_->SetAlpha(0);
	
	SetPosition({ GameEngineWindow::GetInst().GetScale().x / 2, GameEngineWindow::GetInst().GetScale().y / 2 });

}

void FadeInOut::Update()
{
	//밝아진당
	if (FadeIn_ == true)
	{
		FadeAlpha_ -= 40.f * (GameEngineTime::GetDeltaTime() * 10);
		FadeRenderer_->SetAlpha(FadeAlpha_);

		if (FadeAlpha_ <= 0)
		{
			FadeIn_ = false;
			FadeEnd_ = true;
			FadeRenderer_->Death();
		}
	}

	//어두워진당
	if (FadeOut_ == true)
	{
		FadeAlpha_ += 40.f * (GameEngineTime::GetDeltaTime() * 10);
		FadeRenderer_->SetAlpha(FadeAlpha_);

		if (FadeAlpha_ > 255)
		{
			FadeOut_ = false;
			FadeEnd_ = true;
			//FadeAlpha_ = 0;
		}

	}

}

void FadeInOut::SetFadeIn()
{
	FadeEnd_ = false;

	FadeIn_ = true;
	FadeRenderer_->SetAlpha(255);
	FadeAlpha_ = 255;

}

void FadeInOut::SetFadeOut()
{
	FadeEnd_ = false;
	FadeOut_ = true;

	FadeRenderer_->SetAlpha(0);
	FadeAlpha_ = 0;

}

