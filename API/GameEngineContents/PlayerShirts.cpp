#include "PlayerShirts.h"

#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include "PlayerEnum.h"
#include "CustomData.h"

//#include <GameEngine/GameEngineLevel.h> // 레벨을 통해서


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

	//PlayerShirts_->CreateAnimation("shirts.bmp", "BODY_INIT", SHIRT01_INIT, SHIRT01_INIT, 0.3f, false);

	//PlayerShirts_->CreateAnimation("shirts.bmp", "BODY_FRONT_WALK", PLAYER::FRONTWALK0, PLAYER::FRONTWALK1, 0.3f, false);
	//PlayerShirts_->CreateAnimation("shirts.bmp", "BODY_RIGHT_WALK", PLAYER::RIGHT_INIT, PLAYER::RIGHTWALK1, 0.3f, false);
	//PlayerShirts_->CreateAnimation("shirts.bmp", "BODY_BACK_WALK", PLAYER::BACK_INIT, PLAYER::WALK_BACK2, 0.3f, false);

}

void PlayerShirts::Update()
{

}

void PlayerShirts::Render()
{
}
