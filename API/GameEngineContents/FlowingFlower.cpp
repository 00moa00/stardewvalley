#include "FlowingFlower.h"
#include "GameData.h"
#include "Player.h"

FlowingFlower::FlowingFlower() 
	:
	CreateFocusPlayer_(false),

	RamdomTimer_(),
	RamdomPosX_(),
	RamdomPosY_(),

	CreateTimer_(0.f),
	MaxX_(0.f),
	MinX_(0.f),
	MaxY_(0.f),
	MinY_(0.f),
	CreateMaxY_(0.f),

	CreateFlowerState_(CREATE_FLOWER::CREATE),

	FlowerParticles_(nullptr)

{
}

FlowingFlower::~FlowingFlower() 
{
}

void FlowingFlower::Start()
{
}

void FlowingFlower::Update()
{
	if (CreateFocusPlayer_ == true)
	{
		MinX_ = Player::MainPlayer->GetPosition().x - (GameEngineWindow::GetInst().GetScale().x / 2) + 1500.f;
		MaxX_ = Player::MainPlayer->GetPosition().x + (GameEngineWindow::GetInst().GetScale().x / 2 + 1500.f);

		MinY_ = Player::MainPlayer->GetPosition().y - (GameEngineWindow::GetInst().GetScale().y / 2) - 1500.f;
		MaxY_ = Player::MainPlayer->GetPosition().y + (GameEngineWindow::GetInst().GetScale().y / 2) + 1500.f;
		CreateMaxY_ = Player::MainPlayer->GetPosition().y - (GameEngineWindow::GetInst().GetScale().y / 2);
	}


	switch (CreateFlowerState_)
	{
	case CREATE_FLOWER::SET_TIMER:

		CreateTimer_ = RamdomTimer_.RandomFloat(0.3f, 0.5f);
		CreateFlowerState_ = CREATE_FLOWER::TIMER;

		break;
	case CREATE_FLOWER::TIMER:
		CreateTimer_ -= GameEngineTime::GetDeltaTime();

		if (CreateTimer_ <= 0)
		{
			CreateFlowerState_ = CREATE_FLOWER::CREATE;
		}

		break;
	case CREATE_FLOWER::CREATE:

		FlowerParticles_ = (GetLevel()->CreateActor<FlowerParticles>(static_cast<int>(PLAYLEVEL::EFFECT)));
		FlowerParticles_->SetPosition({ RamdomPosX_.RandomFloat(MinX_, MaxX_), RamdomPosY_.RandomFloat(MinY_, CreateMaxY_)});
		FlowerParticles_->SetRandomAnimation(MaxY_);

		CreateFlowerState_ = CREATE_FLOWER::SET_TIMER;
		break;
	case CREATE_FLOWER::INIT:
		break;
	default:
		break;
	}

	
}

void FlowingFlower::SetMax(float4 _Max)
{
	MinX_ = 0 - 200.f;
	MaxX_ = _Max.x + 1000.f;

	MinY_ = 0 - 200.f;
	MaxY_ = _Max.x + 50.f;

	CreateMaxY_ = 0;
}

void FlowingFlower::SetMaxFocusPlayer(bool _Flag)
{

	CreateFocusPlayer_ = _Flag;

}

