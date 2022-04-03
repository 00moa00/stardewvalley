#include "Player.h"

#include "CustomData.h"

#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineLevel.h> 
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>




Player::Player() 
	:
	PlayerState_(PLAYER_STATE::INIT),
	WalkAnimationFrame_(0.15f),
	Speed_(120.0f),
	Energy_(128.F),
	PlayerMove_{},
	MoveEffectTimer_(0),
	MoveEffectState_(0),
	PivotY_(),
	PivotYSpeed_(15.f),
	PlayerShirts_(nullptr),
	PlayerHair_(nullptr),
	PlayerPants_(nullptr),
	PlayerBody_(nullptr),
	ShirtIndex_(0),
	PantsIndex_(0),
	HairIndex_(0)
{
}

Player::~Player() 
{
}

void Player::Start()
{

	SetInit();
	PlayerActorSetPos();


	PlayerHair_->Renderer()->SetIndex(HairIndex_);
	PlayerShirts_->Renderer()->SetIndex(ShirtIndex_);
	PlayerPants_-> Renderer()->SetIndex(PantsIndex_);

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
	//PlayerShirts_->Renderer()->SetIndex(ShirtIndex_);


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
		PlayerActorSetPos();
		SubEnergy();

		if (!GameEngineInput::GetInst()->IsPress("MoveUP")) SetMoveEffect();



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

		PlayerBody_->Renderer()->ChangeAnimation("BODY_RIGHT_WALK");
		PlayerHand_->Renderer()->ChangeAnimation("HAND_RIGHT_WALK");
		PlayerShirts_->Renderer()->SetIndex(ShirtIndex_ + 16);
		PlayerHair_->Renderer()->SetIndex(HairIndex_ + 8);


		PlayerMove_.setRightWalk(true);
	}


	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		SetMove(float4::LEFT * GameEngineTime::GetDeltaTime() * Speed_);

		PlayerBody_->Renderer()->ChangeAnimation("BODY_LEFT_WALK");
		PlayerHand_->Renderer()->ChangeAnimation("HAND_LEFT_WALK");
		PlayerShirts_->Renderer()->SetIndex(ShirtIndex_ + 32);
		PlayerHair_->Renderer()->SetIndex(HairIndex_ + 16);

		PlayerMove_.SetLeftWalk(true);
	}

}

void Player::moveY()
{

	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		SetMove(float4::UP * GameEngineTime::GetDeltaTime() * Speed_);

		PlayerBody_->Renderer()->ChangeAnimation("BODY_BACK_WALK");
		PlayerHand_->Renderer()->ChangeAnimation("HAND_BACK_WALK");
		PlayerShirts_->Renderer()->SetIndex(ShirtIndex_ + 48);
		PlayerHair_->Renderer()->SetIndex(HairIndex_ + 24);

		PlayerMove_.SetBackWalk(true);

	}


	if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_);

		PlayerBody_->Renderer()->ChangeAnimation("BODY_FRONT_WALK");
		PlayerHand_->Renderer()->ChangeAnimation("HAND_FRONT_WALK");
		PlayerShirts_->Renderer()->SetIndex(ShirtIndex_);
		PlayerHair_->Renderer()->SetIndex(HairIndex_ );

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
		PlayerBody_-> Renderer()->ChangeAnimation("BODY_RIGHT_INIT");
		PlayerHand_->Renderer()->ChangeAnimation("HAND_RIGHT_INIT");
	}

	if (PlayerMove_.isFrontWalk_) {
		PlayerBody_->Renderer()->ChangeAnimation("BODY_FRONT_INIT");
		PlayerHand_->Renderer()->ChangeAnimation("HAND_FRONT_INIT");

	}

	if (PlayerMove_.isBackWalk_) {
		PlayerBody_->Renderer()->ChangeAnimation("BODY_BACK_INIT");
		PlayerHand_->Renderer()->ChangeAnimation("HAND_BACK_INIT");

	}

	if (PlayerMove_.isLeftWalk_) {
		PlayerBody_->Renderer()->ChangeAnimation("BODY_LEFT_INIT");
		PlayerHand_->Renderer()->ChangeAnimation("HAND_LEFT_INIT");

	}

}

void Player::SetAllPivot(float _MovePosY)
{
	PlayerBody_->Renderer()->SetPivot({ 0, _MovePosY });
	PlayerHair_->Renderer()->SetPivot({ 0, _MovePosY });
	PlayerHand_->Renderer()->SetPivot({ 0, _MovePosY });
	PlayerPants_->Renderer()->SetPivot({ 0, _MovePosY });
	PlayerShirts_->Renderer()->SetPivot({ 0, _MovePosY });

}

void Player::SetMoveEffect()
{
	if (isMove()) {
		switch (MoveEffectState_) {

		case 0:

			MoveEffectTimer_++;

			if (MoveEffectTimer_ > 200)
			{
				PivotY_ -= PivotYSpeed_ * GameEngineTime::GetDeltaTime();
				SetAllPivot(PivotY_);

				if (MoveEffectTimer_ > 400) MoveEffectState_ = 1;
			}

			break;

		case 1:

			PivotY_ += PivotYSpeed_ * GameEngineTime::GetDeltaTime();
			SetAllPivot(PivotY_);
			MoveEffectState_ = 0;
			PivotY_ = 0;
			MoveEffectTimer_ = 0;
		}

	}

	
}

void Player::PlayerActorSetPos()
{
	PlayerPants_->SetPosition({ this->GetPosition().x, this->GetPosition().y });
	PlayerHair_->SetPosition({ this->GetPosition().x, this->GetPosition().y+6.f });
	PlayerHand_->SetPosition({ this->GetPosition().x, this->GetPosition().y });
	PlayerBody_->SetPosition({ this->GetPosition().x, this->GetPosition().y });
	PlayerShirts_->SetPosition({ this->GetPosition().x, this->GetPosition().y + 11.f });
}

void Player::SetInit()
{

	ShirtIndex_ = CustomData::GetInst().GetShirtsIndex();
	PantsIndex_ = CustomData::GetInst().GetShirtsIndex();
	HairIndex_ = CustomData::GetInst().GetShirtsIndex();


	SetPosition(GameEngineWindow::GetScale().Half());

	PlayerBody_ = GetLevel()->CreateActor<PlayerBody>((int)PlayLevel::PLAYERBODY);
	PlayerHand_ = GetLevel()->CreateActor<PlayerHand>((int)PlayLevel::PLAYERHAND);
	PlayerHair_ = GetLevel()->CreateActor<PlayerHair>((int)PlayLevel::PLAYERHAIR);
	PlayerPants_ = GetLevel()->CreateActor<PlayerPants>((int)PlayLevel::PLAYERPANTS);
	PlayerShirts_ = GetLevel()->CreateActor<PlayerShirts>((int)PlayLevel::PLAYERSHIRTS);
}
