#include "PlayerShirts.h"

#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>

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
	PlayerShirts_ = CreateRenderer("shirts2.bmp");

	PlayerShirts_->SetIndex(0);
}

void PlayerShirts::Update()
{
	unsigned int index = CustomData::GetInst().GetShirtsIndex();

	PlayerShirts_->SetIndex(index);
}

void PlayerShirts::Render()
{
}
