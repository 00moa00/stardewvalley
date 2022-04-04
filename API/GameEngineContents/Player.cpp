#include "Player.h"

#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineLevel.h> 
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>

#include "PlayerEnum.h"





Player::Player() 
	:
	PlayerState_(PLAYER_STATE::INIT),
	WalkAnimationFrame_(0.125f),
	Speed_(150.0f),
	Energy_(128.F),
	PlayerMove_{},
	Player_(nullptr)

{
}

Player::~Player() 
{
}

void Player::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());

	Player_ = CreateRenderer();

	//================================
	//     플레이어 대기상태
	//================================

	Player_->CreateAnimation("Player.bmp", "FRONT_INIT", PLAYER::FRONT_INIT, PLAYER::FRONT_INIT, 0.0f, false);
	Player_->CreateAnimation("Player.bmp", "RIGHT_INIT", PLAYER::RIGHT_INIT, PLAYER::RIGHT_INIT, 0.0f, false);
	Player_->CreateAnimation("Player.bmp", "LEFT_INIT", PLAYER::LEFT_INIT, PLAYER::LEFT_INIT, 0.0f, false);

	Player_->CreateAnimation("Player.bmp", "BACK_INIT", PLAYER::BACK_INIT, PLAYER::BACK_INIT, 0.0f, false);


	//================================
	//     플레이어 이동 
	//================================

	Player_->CreateAnimation("Player.bmp", "FRONT_WALK", PLAYER::FRONT_WALK0, PLAYER::FRONT_WALK3, 0.1f, true);
	Player_->CreateAnimation("Player.bmp", "RIGHT_WALK", PLAYER::RIGHT_WALK0, PLAYER::RIGHT_WALK5, 0.1f, true);
	Player_->CreateAnimation("Player.bmp", "LEFT_WALK", PLAYER::LEFT_WALK0, PLAYER::LEFT_WALK5, WalkAnimationFrame_, true);

	Player_->CreateAnimation("Player.bmp", "BACK_WALK", PLAYER::BACK_WALK0, PLAYER::BACK_WALK3, WalkAnimationFrame_, true);



	//------< 애니메이션 초기화 >------------------------------------------------------------------

	Player_->ChangeAnimation("FRONT_INIT");


	SetInit();

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

		SetDir();

		PlayerMove_.SetWalkInit(true);
		if (isMove()) PlayerState_ = PLAYER_STATE::MOVE;

		break;

	case PLAYER_STATE::MOVEEFFECT:

	case PLAYER_STATE::MOVE:

		moveX();
		moveY();
		SubEnergy();





		PlayerMove_.SetWalkInit(false);

		if (isStop()) PlayerState_ = PLAYER_STATE::INIT;

		break;

	default:
		break;
	}

}

void Player::Render()
{
}


void Player::moveX()
{


	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * Speed_);

		Player_->ChangeAnimation("RIGHT_WALK");


		PlayerMove_.setRightWalk(true);
	}


	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		SetMove(float4::LEFT * GameEngineTime::GetDeltaTime() * Speed_);

		Player_->ChangeAnimation("LEFT_WALK");

		PlayerMove_.SetLeftWalk(true);
	}

}

void Player::moveY()
{

	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		SetMove(float4::UP * GameEngineTime::GetDeltaTime() * Speed_);

		Player_->ChangeAnimation("BACK_WALK");


		PlayerMove_.SetBackWalk(true);

	}


	if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_);

		Player_->ChangeAnimation("FRONT_WALK");


		PlayerMove_.SetFrontWalk(true);

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

void Player::SetDir()
{

	if (PlayerMove_.isRightWalk_) {
		Player_->ChangeAnimation("RIGHT_INIT");
	}

	if (PlayerMove_.isFrontWalk_) {
		Player_->ChangeAnimation("FRONT_INIT");

	}

	if (PlayerMove_.isBackWalk_) {
		Player_->ChangeAnimation("BACK_INIT");
	}

	if (PlayerMove_.isLeftWalk_) {
		Player_->ChangeAnimation("LEFT_INIT");

	}

}




void Player::SetInit()
{


	SetPosition(GameEngineWindow::GetScale().Half());


}
