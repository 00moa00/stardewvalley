#include "PlayerShirts.h"

#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include "PlayerEnum.h"

//#include <GameEngine/GameEngineLevel.h> // 레벨을 통해서

#include "CustomData.h"

PlayerShirts::PlayerShirts()
	:
	PlayerShirts_(nullptr)
{
}

PlayerShirts::~PlayerShirts()
{
}

void PlayerShirts::Start()
{
	SetPosition({ GetPosition().x, GetPosition().y });

	PlayerShirts_ = CreateRenderer("shirts.bmp");

	//PlayerShirts_ = CreateRenderer();

	//PlayerShirts_->CreateAnimation("shirts.bmp", "BODY_INIT", PLAYER::INIT, PLAYER::FRONTWALK1, 0.3f, false);
	//PlayerShirts_->CreateAnimation("shirts.bmp", "BODY_FRONT_WALK", PLAYER::FRONTWALK0, PLAYER::FRONTWALK1, 0.3f, false);
	//PlayerShirts_->CreateAnimation("shirts.bmp", "BODY_RIGHT_WALK", PLAYER::RIGHT_INIT, PLAYER::RIGHTWALK1, 0.3f, false);
	//PlayerShirts_->CreateAnimation("shirts.bmp", "BODY_BACK_WALK", PLAYER::BACK_INIT, PLAYER::WALK_BACK2, 0.3f, false);

	PlayerShirts_->SetIndex(0);
}

void PlayerShirts::Update()
{
	unsigned int index = CustomData::GetInst().GetShirtsIndex();


	if (GetIsFrontWalk()) {
		PlayerShirts_->SetIndex(index);
		ResetAllState();

	}

	if (GetIsRightWalk()) {
		PlayerShirts_->SetIndex(index + 16);
		ResetAllState();

	}


	if (GetIsLeftWalk()) {
		PlayerShirts_->SetIndex(index + 32);
		ResetAllState();

	}

	if (GetIsBackWalk()) {
		PlayerShirts_->SetIndex(index + 48);
		ResetAllState();


	}

}

void PlayerShirts::Render()
{
}
