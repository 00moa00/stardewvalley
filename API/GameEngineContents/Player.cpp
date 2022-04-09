#include "Player.h"

#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineLevel.h> 
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>

#include "PlayerEnum.h"

Player::Player() 
	:
	PlayerState_(PLAYERSTATE::INIT),
	AnimationFrame_(0.120f),
	Speed_(150.f),
	Energy_(150.f),
	PlayerMove_{},
	PlayerRenderer_(nullptr),
	PlayerCollider_(nullptr),
	Inventory_(nullptr),
	Mouse_(nullptr)

{

}


Player::~Player() 
{
}

void Player::Start()
{
	//------< 초기화 >------------------------------------------------------------------


	SetPosition(GameEngineWindow::GetScale().Half());

	PlayerRenderer_ = CreateRenderer();
	PlayerCollider_ = CreateCollision("Player", { 48*4, 96 });

	Inventory_ = GetLevel()->CreateActor<Inventory>((int)PLAYLEVEL::PLAYER);
	Mouse_ = GetLevel()->CreateActor<Mouse>((int)PLAYLEVEL::MOUSE);

	Hoe_ = Inventory_->NewItem<Hoe>(float4 {0,24.f});




	//------< 애니메이션 생성 >------------------------------------------------------------------

	//================================
	//     플레이어 대기
	//================================
	PlayerRenderer_->CreateAnimation("Player.bmp", "FRONT_INIT", PLAYER::FRONT_INIT, PLAYER::FRONT_INIT, 0.0f, false);
	PlayerRenderer_->CreateAnimation("Player.bmp", "RIGHT_INIT", PLAYER::RIGHT_INIT, PLAYER::RIGHT_INIT, 0.0f, false);
	PlayerRenderer_->CreateAnimation("Player.bmp", "LEFT_INIT", PLAYER::LEFT_INIT, PLAYER::LEFT_INIT, 0.0f, false);
	PlayerRenderer_->CreateAnimation("Player.bmp", "BACK_INIT", PLAYER::BACK_INIT, PLAYER::BACK_INIT, 0.0f, false);

	//================================
	//     플레이어 이동 
	//================================
	PlayerRenderer_->CreateAnimation("Player.bmp", "FRONT_WALK", PLAYER::FRONT_WALK0, PLAYER::FRONT_WALK3, AnimationFrame_, true);
	PlayerRenderer_->CreateAnimation("Player.bmp", "RIGHT_WALK", PLAYER::RIGHT_WALK0, PLAYER::RIGHT_WALK5, AnimationFrame_, true);
	PlayerRenderer_->CreateAnimation("Player.bmp", "LEFT_WALK", PLAYER::LEFT_WALK0, PLAYER::LEFT_WALK5, AnimationFrame_, true);
	PlayerRenderer_->CreateAnimation("Player.bmp", "BACK_WALK", PLAYER::BACK_WALK0, PLAYER::BACK_WALK3, AnimationFrame_, true);

	//================================
	//     플레이어 툴 사용
	//================================
	//PlayerRenderer_->CreateAnimation("Player.bmp", "FRONT_HOE", PLAYER::HOE, PLAYER::FRONT_WALK3, DirAnimationFrame_, true);
	PlayerRenderer_->CreateAnimation("Player.bmp", "RIGHT_HOE", PLAYER::HOE_RIGHT0, PLAYER::HOE_RIGHT4, AnimationFrame_, true);
	PlayerRenderer_->CreateAnimation("Player.bmp", "LEFT_HOE", PLAYER::HOE_LEFT0, PLAYER::HOE_LEFT4, AnimationFrame_, false);
	//PlayerRenderer_->CreateAnimation("Player.bmp", "BACK_WALK", PLAYER::BACK_WALK0, PLAYER::BACK_WALK3, DirAnimationFrame_, true);


	//------< 애니메이션 초기화 >------------------------------------------------------------------

	PlayerRenderer_->ChangeAnimation("FRONT_INIT");
	PlayerMove_.SetFrontDir(true);
}


void Player::Update()
{
	switch (PlayerState_)
	{

	case PLAYERSTATE::INVENTROY_MINI_INIT:

		Inventory_->SetisMiniInven(MINIPOPUP::MINI);
		PlayerState_ = PLAYERSTATE::INIT;
		break;

	case PLAYERSTATE::INIT:
	
		SetDirAnimation();

		if (true == GameEngineInput::GetInst()->IsDown("Enter")) PlayerState_ = PLAYERSTATE::INVENTROY_POPUP_INIT;
		if(PlayerMouseCollision())  PlayerState_ = PLAYERSTATE::TOOL_USE;
		if (isMove()) PlayerState_ = PLAYERSTATE::MOVE;
		break;

	case PLAYERSTATE::TOOL_USE:

		PlayerRenderer_->ChangeAnimation("RIGHT_HOE");

		//if (Mouse_->isMouseFree()) PlayerState_ = PLAYERSTATE::INIT;

		if (PlayerRenderer_->IsEndAnimation()) {
			//Player_->SetCurrentFrame(PLAYER::HOE_RIGHT0);
			PlayerState_ = PLAYERSTATE::INIT;
		}

		//
		break;

	case PLAYERSTATE::MOVE:

		moveX();
		moveY();
		SubEnergy();

		if (isStop()) PlayerState_ = PLAYERSTATE::INIT;
		break;
	case PLAYERSTATE::INVENTROY_POPUP_INIT:

		Inventory_->SetisMiniInven(MINIPOPUP::MAIN);
		PlayerState_ = PLAYERSTATE::INVENTROY_POPUP;
		break;

	case PLAYERSTATE::INVENTROY_POPUP :

	

		if (Inventory_->InventoryExitMouseClick() ||
			true == GameEngineInput::GetInst()->IsDown("Enter")) {
			PlayerState_ = PLAYERSTATE::INVENTROY_MINI_INIT;
		}

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

		PlayerRenderer_->ChangeAnimation("RIGHT_WALK");
		PlayerMove_.setRightDir(true);
	}


	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		SetMove(float4::LEFT * GameEngineTime::GetDeltaTime() * Speed_);

		PlayerRenderer_->ChangeAnimation("LEFT_WALK");
		PlayerMove_.SetLeftDir(true);
	}

}

void Player::moveY()
{

	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		SetMove(float4::UP * GameEngineTime::GetDeltaTime() * Speed_);

		PlayerRenderer_->ChangeAnimation("BACK_WALK");
		PlayerMove_.SetBackDir(true);

	}


	if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_);

		PlayerRenderer_->ChangeAnimation("FRONT_WALK");
		PlayerMove_.SetFrontDir(true);

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

void Player::SetDirAnimation()
{

	if (PlayerMove_.isRightDir_) {
		PlayerRenderer_->ChangeAnimation("RIGHT_INIT");
	}

	if (PlayerMove_.isFrontDir_) {
		PlayerRenderer_->ChangeAnimation("FRONT_INIT");

	}

	if (PlayerMove_.isBackDir_) {
		PlayerRenderer_->ChangeAnimation("BACK_INIT");
	}

	if (PlayerMove_.isLeftDir_) {
		PlayerRenderer_->ChangeAnimation("LEFT_INIT");
	}

}


//
//void Player::SetInit()
//{
//	SetPosition(GameEngineWindow::GetScale().Half());
//}
//
