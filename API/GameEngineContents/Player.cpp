#include "Player.h"

#include "CustomData.h"

#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineLevel.h> 
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>

enum class ORDER
{
	//BACKGROUND,
	PLAYERBODY,
	PLAYERHAIR,
	PLAYERPANTS,
	PLAYERSHIRTS,
	PLAYERHAND,

};


Player::Player() 
	:
	PlayerState_(PLAYER_STATE::INIT),
	WalkAnimationFrame_(0.15f),
	Speed_(120.0f),
	Energy_(128.F),
	PlayerShirts_(nullptr),
	PlayerHair_(nullptr),
	PlayerPants_(nullptr),
	PlayerBody_(nullptr),
	isFrontWalk_(false),
	isBackWalk_(false),
	isRightWalk_(false),
	isLeftWalk_(false),
	isInit_(false)
{
}

Player::~Player() 
{
}



void Player::Start()
{
	ShirtIndex_ = CustomData::GetInst().GetShirtsIndex();
	PantsIndex_ = CustomData::GetInst().GetShirtsIndex();
	HairIndex_ = CustomData::GetInst().GetShirtsIndex();


	SetPosition(GameEngineWindow::GetScale().Half());

	PlayerBody_ = GetLevel()->CreateActor<PlayerBody>((int)ORDER::PLAYERBODY);
	PlayerHand_ = GetLevel()->CreateActor<PlayerHand>((int)ORDER::PLAYERHAND);
	PlayerHair_ = GetLevel()->CreateActor<PlayerHair>((int)ORDER::PLAYERHAIR);
	PlayerPants_ = GetLevel()->CreateActor<PlayerPants>((int)ORDER::PLAYERPANTS);
	PlayerShirts_ = GetLevel()->CreateActor<PlayerShirts>((int)ORDER::PLAYERSHIRTS);



	PlayerPants_->SetPosition({ this->GetPosition().x, this->GetPosition().y });
	PlayerHair_->SetPosition({ this->GetPosition().x, this->GetPosition().y });
	PlayerHand_->SetPosition({ this->GetPosition().x, this->GetPosition().y });
	PlayerBody_->SetPosition({ this->GetPosition().x, this->GetPosition().y });
	PlayerShirts_->SetPosition({ this->GetPosition().x, this->GetPosition().y + 11.f });


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
	PlayerShirts_->Renderer()->SetIndex(ShirtIndex_);


	switch (PlayerState_)
	{
	case PLAYER_STATE::INIT:
		SetInit();
		SetWalkInit(true);

		if (isMove()) PlayerState_ = PLAYER_STATE::MOVE;

		break;

	case PLAYER_STATE::MOVE:
		PlayerBody_->SetPosition(this->GetPosition());		
		PlayerHair_->SetPosition(this->GetPosition());
		PlayerPants_->SetPosition(this->GetPosition());
		PlayerHand_->SetPosition(this->GetPosition());
		PlayerShirts_->SetPosition({ this->GetPosition().x, this->GetPosition().y+11.f});

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


		setRightWalk(true);
	}


	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		SetMove(float4::LEFT * GameEngineTime::GetDeltaTime() * Speed_);

		PlayerBody_->Renderer()->ChangeAnimation("BODY_LEFT_WALK");
		PlayerHand_->Renderer()->ChangeAnimation("HAND_LEFT_WALK");
		PlayerShirts_->Renderer()->SetIndex(ShirtIndex_ + 32);

		SetLeftWalk(true);
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

		SetBackWalk(true);

	}


	if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_);

		PlayerBody_->Renderer()->ChangeAnimation("BODY_FRONT_WALK");
		PlayerHand_->Renderer()->ChangeAnimation("HAND_FRONT_WALK");
		PlayerShirts_->Renderer()->SetIndex(ShirtIndex_);

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

	if (isRightWalk_) {
		PlayerBody_-> Renderer()->ChangeAnimation("BODY_RIGHT_INIT");
		PlayerHand_->Renderer()->ChangeAnimation("HAND_RIGHT_INIT");
	}

	if (isFrontWalk_) {
		PlayerBody_->Renderer()->ChangeAnimation("BODY_FRONT_INIT");
		PlayerHand_->Renderer()->ChangeAnimation("HAND_FRONT_INIT");

	}

	if (isBackWalk_) {
		PlayerBody_->Renderer()->ChangeAnimation("BODY_BACK_INIT");
		PlayerHand_->Renderer()->ChangeAnimation("HAND_BACK_INIT");

	}

	if (isLeftWalk_) {
		PlayerBody_->Renderer()->ChangeAnimation("BODY_LEFT_INIT");
		PlayerHand_->Renderer()->ChangeAnimation("HAND_LEFT_INIT");

	}

}
