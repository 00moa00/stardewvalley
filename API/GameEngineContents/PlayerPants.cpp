#include "PlayerPants.h"

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>

#include <GameEngine/GameEngineRenderer.h>

//#include <GameEngine/GameEngineLevel.h> // 레벨을 통해서

#include "CustomData.h"


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
	PlayerPants_ = CreateRenderer("pants.bmp");

	PlayerPants_->SetIndex(0);
}

void PlayerPants::Update()
{
	unsigned int index = CustomData::GetInst().GetPantsIndex();

	PlayerPants_->SetIndex(index);
}

void PlayerPants::Render()
{
}
