#include "PlayerHair.h"

//#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>

#include <GameEngine/GameEngineRenderer.h>

#include <GameEngine/GameEngineLevel.h>
#include "CustomData.h"

PlayerHair::PlayerHair() 
	:
	PlayerHair_(nullptr)
{
}

PlayerHair::~PlayerHair() 
{
}

void PlayerHair::Start()
{
	SetPosition({ GetPosition().x, GetPosition().y});
	PlayerHair_ = CreateRenderer("hairstyles.bmp");
	PlayerHair_->SetIndex(0);

}

void PlayerHair::Update()
{
	unsigned int index = CustomData::GetInst().GetHairIndex();
	PlayerHair_->SetIndex(index);
}

void PlayerHair::Render()
{
}
