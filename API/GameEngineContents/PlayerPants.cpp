#include "PlayerPants.h"

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>

#include <GameEngine/GameEngineRenderer.h>

//#include <GameEngine/GameEngineLevel.h> // 레벨을 통해서

#include "CustomData.h"
#include "PlayerEnum.h"


PlayerPants::PlayerPants() 
	:
	PlayerPants_(nullptr)
{
}

PlayerPants::~PlayerPants() 
{
}

void PlayerPants::Start()
{
	SetPosition({ GetPosition().x, GetPosition().y });

	//PlayerPants_ = CreateRenderer();
	//PlayerPants_->CreateAnimation("farmer_Body.bmp", "BODY_INIT", PLAYER::INIT, PLAYER::FRONTWALK1, 0.3f, false);
	//
	//PlayerPants_->ChangeAnimation("BODY_INIT");


	PlayerPants_ = CreateRenderer("pants.bmp");


}

void PlayerPants::Update()
{

}

void PlayerPants::Render()
{
}
