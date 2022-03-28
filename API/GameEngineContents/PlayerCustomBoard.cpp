#include "PlayerCustomBoard.h"

//#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>



#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineLevel.h>

PlayerCustomBoard::PlayerCustomBoard()
	:
	PlayerCustomBoard_(nullptr)
{
}

PlayerCustomBoard::~PlayerCustomBoard()
{
}

void PlayerCustomBoard::Start()
{
	SetPosition({ GameEngineWindow::GetScale().Half() });
	PlayerCustomBoard_ = CreateRenderer("Customboard.bmp");
	PlayerCustomBoard_->SetScale({580 * 0.7f ,696 * 0.7f });

}

void PlayerCustomBoard::Update()
{
}

void PlayerCustomBoard::Render()
{
}
