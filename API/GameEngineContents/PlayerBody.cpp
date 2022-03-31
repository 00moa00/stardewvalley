#include "PlayerBody.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>

#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

#include <GameEngine/GameEngineLevel.h> // 레벨을 통해서

#include "PlayerShirts.h"
#include "PlayerEnum.h"


PlayerBody::PlayerBody()
	: Speed_(120.0f),
	Energy_(128.F),
	PlayerBody_(nullptr),
	PlayerState_(PLAYER_STATE::INIT),
	WalkAnimationFrame_(0.2f)

{
}

PlayerBody::~PlayerBody()
{
}

void PlayerBody::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());

	PlayerBody_ = CreateRenderer();



	//================================
	//     플레이어 바디 대기상태
	//================================

	PlayerBody_->CreateAnimation("farmer_Body.bmp", "BODY_FRONT_INIT", PLAYER::FRONT_INIT, PLAYER::FRONT_INIT, 0.0f, false);
	PlayerBody_->CreateAnimation("farmer_Body.bmp", "BODY_RIGHT_INIT", PLAYER::RIGHT_INIT, PLAYER::RIGHT_INIT, 0.0f, false);
	PlayerBody_->CreateAnimation("farmer_Body.bmp", "BODY_LEFT_INIT", PLAYER::LEFT_INIT, PLAYER::LEFT_INIT, 0.0f, false);

	PlayerBody_->CreateAnimation("farmer_Body.bmp", "BODY_BACK_INIT", PLAYER::BACK_INIT, PLAYER::BACK_INIT, 0.0f, false);


	//================================
	//     플레이어 바디 이동 
	//================================

	PlayerBody_->CreateAnimation("farmer_Body.bmp", "BODY_FRONT_WALK", PLAYER::FRONT_WALK0, PLAYER::FRONT_WALK1, WalkAnimationFrame_, true);
	PlayerBody_->CreateAnimation("farmer_Body.bmp", "BODY_RIGHT_WALK", PLAYER::RIGHT_INIT, PLAYER::RIGHT_WALK1, WalkAnimationFrame_, true);
	PlayerBody_->CreateAnimation("farmer_Body.bmp", "BODY_LEFT_WALK", PLAYER::LEFT_INIT, PLAYER::LEFT_WALK1, WalkAnimationFrame_, true);

	PlayerBody_->CreateAnimation("farmer_Body.bmp", "BODY_BACK_WALK", PLAYER::BACK_INIT, PLAYER::WALK_BACK2, WalkAnimationFrame_, true);



	//------< 애니메이션 초기화 >------------------------------------------------------------------

	PlayerBody_->ChangeAnimation("BODY_FRONT_INIT");


	if (false == GameEngineInput::GetInst()->IsKey("MoveUp"))
	{
		//GameEngineInput::GetInst()->CreateKey("MoveLeft", 'A');
		//GameEngineInput::GetInst()->CreateKey("MoveRight", 'D');
		GameEngineInput::GetInst()->CreateKey("MoveUp", 'W');
		GameEngineInput::GetInst()->CreateKey("MoveDown", 'S');
	}


}




void PlayerBody::Update()
{

	//GetLevel()->SetCameraPos(GetPosition() - GameEngineWindow::GetInst().GetScale().Half());

	switch (PlayerState_)
	{
	case PLAYER_STATE::INIT:
		SetInit();
		SetWalkInit(true);

		if (isMove()) PlayerState_ = PLAYER_STATE::MOVE;

		break;

	case PLAYER_STATE::MOVE:

		moveX();
		moveY();
		SubEnergy();

		SetWalkInit(false);


		if (isStop()) PlayerState_ = PLAYER_STATE::INIT;

		break;

	default:
		break;
	}

}


void PlayerBody::moveX()
{
	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * Speed_);
		PlayerBody_->ChangeAnimation("BODY_RIGHT_WALK");

		setRightWalk(true);
	}


	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		SetMove(float4::LEFT * GameEngineTime::GetDeltaTime() * Speed_);
		PlayerBody_->ChangeAnimation("BODY_LEFT_WALK");

		SetLeftWalk(true);
	}

}


void PlayerBody::moveY()
{

	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		SetMove(float4::UP * GameEngineTime::GetDeltaTime() * Speed_);
		PlayerBody_->ChangeAnimation("BODY_BACK_WALK");

		SetBackWalk(true);

	}


	if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_);
		PlayerBody_->ChangeAnimation("BODY_FRONT_WALK");

		SetFrontWalk(true);

	}

}


bool PlayerBody::isStop()
{
	return (true == GameEngineInput::GetInst()->IsFree("MoveRight")
		&& true == GameEngineInput::GetInst()->IsFree("MoveLeft")
		&& true == GameEngineInput::GetInst()->IsFree("MoveDown")
		&& true == GameEngineInput::GetInst()->IsFree("MoveUp"));
}

bool PlayerBody::isMove()
{
	return (true == GameEngineInput::GetInst()->IsPress("MoveRight")
		|| true == GameEngineInput::GetInst()->IsPress("MoveLeft")
		|| true == GameEngineInput::GetInst()->IsPress("MoveDown")
		|| true == GameEngineInput::GetInst()->IsPress("MoveUp"));
}

void PlayerBody::SetInit()
{
	if (GetIsRightWalk()) {
		PlayerBody_->ChangeAnimation("BODY_RIGHT_INIT");
	}

	if (GetIsFrontWalk()) {
		PlayerBody_->ChangeAnimation("BODY_FRONT_INIT");

	}

	if (GetIsBackWalk()) {
		PlayerBody_->ChangeAnimation("BODY_BACK_INIT");

	}


	if (GetIsLeftWalk()) {
		PlayerBody_->ChangeAnimation("BODY_LEFT_INIT");

	}

}


void PlayerBody::Render()
{
	//GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find("Idle.bmp");
	//if (nullptr == FindImage)
	//{
	//	MsgBoxAssert("CCCCC!");
	//}
	//GameEngine::BackBufferImage()->BitCopyBot(FindImage, GetPosition());

}