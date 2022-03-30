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
	PlayerState_(PLAYER_STATE::INIT)

{
}

Player::~Player() 
{
}

void Player::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());

	PlayerBody_ = CreateRenderer();
	PlayerHand_ = CreateRenderer();



	//================================
	//     플레이어 바디 대기상태
	//================================

	PlayerBody_->CreateAnimation("farmer_Body.bmp", "BODY_FRONT_INIT", PLAYER::FRONT_INIT, PLAYER::FRONT_INIT, 0.0f, false);
	PlayerBody_->CreateAnimation("farmer_Body.bmp", "BODY_RIGHT_INIT", PLAYER::RIGHT_INIT, PLAYER::RIGHT_INIT, 0.0f, false);
	PlayerBody_->CreateAnimation("farmer_Body.bmp", "BODY_BACK_INIT", PLAYER::BACK_INIT, PLAYER::BACK_INIT, 0.0f, false);


	//================================
	//     플레이어 바디 이동 
	//================================

	PlayerBody_->CreateAnimation("farmer_Body.bmp", "BODY_FRONT_WALK", PLAYER::FRONT_WALK0, PLAYER::FRONT_WALK1, 0.3f, true);
	PlayerBody_->CreateAnimation("farmer_Body.bmp", "BODY_RIGHT_WALK", PLAYER::RIGHT_INIT, PLAYER::RIGHT_WALK1, 0.3f, true);
	PlayerBody_->CreateAnimation("farmer_Body.bmp", "BODY_BACK_WALK", PLAYER::BACK_INIT, PLAYER::WALK_BACK2, 0.3f, true);
	


	//================================
	//      플레이어 팔 대기상태
	//================================

	PlayerHand_->CreateAnimation("farmer_hand.bmp", "HAND_FRONT_INIT", PLAYER::FRONT_INIT, PLAYER::FRONT_INIT, 0.0f, false);
	PlayerHand_->CreateAnimation("farmer_hand.bmp", "HAND_RIGHT_INIT", PLAYER::RIGHT_INIT, PLAYER::RIGHT_INIT, 0.0f, false);
	PlayerHand_->CreateAnimation("farmer_hand.bmp", "HAND_BACK_INIT", PLAYER::BACK_INIT, PLAYER::BACK_INIT, 0.0f, false);


	//================================
	//      플레이어 팔 이동
	//================================

	PlayerHand_->CreateAnimation("farmer_hand.bmp", "HAND_FRONT_WALK", PLAYER::FRONT_WALK0, PLAYER::FRONT_WALK1, 0.3f, true);
	PlayerHand_->CreateAnimation("farmer_hand.bmp", "HAND_RIGHT_WALK", PLAYER::RIGHT_INIT, PLAYER::RIGHT_WALK1, 0.3f, true);
	PlayerHand_->CreateAnimation("farmer_hand.bmp", "HAND_BACK_WALK", PLAYER::BACK_INIT, PLAYER::WALK_BACK2, 0.3f, true);


	//------< 애니메이션 초기화 >------------------------------------------------------------------

	PlayerBody_->ChangeAnimation("BODY_FRONT_INIT");
	PlayerHand_->ChangeAnimation("HAND_FRONT_INIT");


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
	switch (PlayerState_)
	{
	case PLAYER_STATE::INIT:
		SetInit();

		if (isMove()) PlayerState_ = PLAYER_STATE::MOVE;

		break;

	case PLAYER_STATE::MOVE:

		moveX();
		moveY();
		SubEnergy();


		if (isStop()) PlayerState_ = PLAYER_STATE::INIT;

		break;

	default:
		break;
	}

}


void Player::moveX()
{
	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * Speed_);
		PlayerBody_->ChangeAnimation("BODY_RIGHT_WALK");
		PlayerHand_->ChangeAnimation("HAND_RIGHT_WALK");

		setRightWalk(true);
	}


	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		SetMove(float4::LEFT * GameEngineTime::GetDeltaTime() * Speed_);
		PlayerBody_->ChangeAnimation("BODY_RIGHT_WALK");
		PlayerHand_->ChangeAnimation("HAND_RIGHT_WALK");

		SetLeftWalk(true);
	}

}


void Player::moveY()
{

	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		SetMove(float4::UP * GameEngineTime::GetDeltaTime() * Speed_);
		PlayerBody_->ChangeAnimation("BODY_BACK_WALK");
		PlayerHand_->ChangeAnimation("HAND_BACK_WALK");

		SetBackWalk(true);

	}


	if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_);
		PlayerBody_->ChangeAnimation("BODY_FRONT_WALK");
		PlayerHand_->ChangeAnimation("HAND_FRONT_WALK");

		SetFrontWalk(true);

	}

}


bool Player::isStop()
{
	return (true == GameEngineInput::GetInst()->IsFree("MoveRight")
		&& true == GameEngineInput::GetInst()->IsFree("MoveLeft")
		&& true == GameEngineInput::GetInst()->IsFree("MoveDown")
		&& true == GameEngineInput::GetInst()->IsFree("MoveUp"));
}

bool Player::isMove()
{
	return (true == GameEngineInput::GetInst()->IsPress("MoveRight")
		|| true == GameEngineInput::GetInst()->IsPress("MoveLeft")
		|| true == GameEngineInput::GetInst()->IsPress("MoveDown")
		|| true == GameEngineInput::GetInst()->IsPress("MoveUp"));
}

void Player::SetInit()
{
	if (GetIsRightWalk()) {
		PlayerBody_->ChangeAnimation("BODY_RIGHT_INIT");
		PlayerHand_->ChangeAnimation("HAND_RIGHT_INIT");
	}

	if (GetIsFrontWalk()) {
		PlayerBody_->ChangeAnimation("BODY_FRONT_INIT");
		PlayerHand_->ChangeAnimation("HAND_FRONT_INIT");

	}

	if (GetIsBackWalk()) {
		PlayerBody_->ChangeAnimation("BODY_BACK_INIT");
		PlayerHand_->ChangeAnimation("HAND_BACK_INIT");

	}


	if (GetIsLeftWalk()) {
		PlayerBody_->ChangeAnimation("BODY_RIGHT_INIT");
		PlayerHand_->ChangeAnimation("HAND_RIGHT_INIT");

	}

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