#include "Player.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>

#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

#include <GameEngine/GameEngineLevel.h> // 레벨을 통해서

#include "PlayerShirts.h"
#include "PlayerEnum.h"


Player::Player()
	: Speed_(100.0f),
	Energy_(42.f * 1.8f),
	PlayerBody_(nullptr),
	PlayerHand_(nullptr),
	state_(0)
{
}

Player::~Player() 
{
}

void Player::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	//PlayerBody_->SetIndex(0);
	//PlayerBody_ = CreateRenderer("farmer_Body.bmp");

	//플레이어 몸

	PlayerBody_ = CreateRenderer();

	PlayerBody_->CreateAnimation("farmer_Body.bmp", "BODY_INIT", PLAYER::INIT, PLAYER::FRONTWALK1, 0.3f, false);
	PlayerBody_->CreateAnimation("farmer_Body.bmp", "BODY_FRONT_WALK", PLAYER::FRONTWALK0, PLAYER::FRONTWALK1, 0.3f, true);
	PlayerBody_->CreateAnimation("farmer_Body.bmp", "BODY_RIGHT_WALK", PLAYER::RIGHT_INIT, PLAYER::RIGHTWALK1, 0.3f, true);
	PlayerBody_->CreateAnimation("farmer_Body.bmp", "BODY_BACK_WALK", PLAYER::BACK_INIT, PLAYER::WALK_BACK2, 0.3f, true);
	
	PlayerBody_->ChangeAnimation("BODY_INIT");

	//플레이어 팔

	PlayerHand_ = CreateRenderer();

	PlayerHand_->CreateAnimation("farmer_hand.bmp", "HAND_INIT", PLAYER::INIT, PLAYER::FRONTWALK1, 0.3f, false);
	PlayerHand_->CreateAnimation("farmer_hand.bmp", "HAND_FRONT_WALK", PLAYER::FRONTWALK0, PLAYER::FRONTWALK1, 0.3f, true);
	PlayerHand_->CreateAnimation("farmer_hand.bmp", "HAND_RIGHT_WALK", PLAYER::RIGHT_INIT, PLAYER::RIGHTWALK1, 0.3f, true);
	PlayerHand_->CreateAnimation("farmer_hand.bmp", "HAND_BACK_WALK", PLAYER::BACK_INIT, PLAYER::WALK_BACK2, 0.3f, true);

	PlayerHand_->ChangeAnimation("HAND_INIT");


	if (false == GameEngineInput::GetInst()->IsKey("MoveUp"))
	{
		//GameEngineInput::GetInst()->CreateKey("MoveLeft", 'A');
		//GameEngineInput::GetInst()->CreateKey("MoveRight", 'D');
		GameEngineInput::GetInst()->CreateKey("MoveUp", 'W');
		GameEngineInput::GetInst()->CreateKey("MoveDown", 'S');
	}


}




void Player::Update()
{
	moveX();
	moveY();

	if (isStop())
	{
		PlayerBody_->ChangeAnimation("BODY_INIT");
		PlayerHand_->ChangeAnimation("HAND_INIT");
	}
	else {
		SubEnergy();
	}

	
}


void Player::moveX()
{
	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * Speed_);
		PlayerBody_->ChangeAnimation("BODY_RIGHT_WALK");
		PlayerHand_->ChangeAnimation("HAND_RIGHT_WALK");

	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		SetMove(float4::LEFT * GameEngineTime::GetDeltaTime() * Speed_);
		PlayerBody_->ChangeAnimation("BODY_RIGHT_WALK");
		PlayerHand_->ChangeAnimation("HAND_RIGHT_WALK");

	}
}


void Player::moveY()
{

	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		SetMove(float4::UP * GameEngineTime::GetDeltaTime() * Speed_);
		PlayerBody_->ChangeAnimation("BODY_BACK_WALK");
		PlayerHand_->ChangeAnimation("HAND_BACK_WALK");

	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_);
		PlayerBody_->ChangeAnimation("BODY_FRONT_WALK");
		PlayerHand_->ChangeAnimation("HAND_FRONT_WALK");

	}

}


bool Player::isStop()
{
	return (true == GameEngineInput::GetInst()->IsFree("MoveRight")
		&& true == GameEngineInput::GetInst()->IsFree("MoveLeft")
		&& true == GameEngineInput::GetInst()->IsFree("MoveDown")
		&& true == GameEngineInput::GetInst()->IsFree("MoveUp"));
}


void Player::Render() 
{
	//GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find("Idle.bmp");
	//if (nullptr == FindImage)
	//{
	//	MsgBoxAssert("CCCCC!");
	//}
	//GameEngine::BackBufferImage()->BitCopyBot(FindImage, GetPosition());

}