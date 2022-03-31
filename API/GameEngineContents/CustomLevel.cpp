#include "CustomLevel.h"

#include "GameEngine/GameEngine.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>

#include "CustomData.h"

enum class ORDER
{
	//BACKGROUND,
	BACKGROUND,
	BOARD,
	PLAYERBACKGROUND,
	PLAYER,
	PLAYERHAIR,
	PLAYERPANTS,
	PLAYERSHIRTS,

	RIGHTARROWHAIR,
	RIGHTARROWSHIRTS,
	RIGHTARROWPANTS,

	LEFTARROWHAIR,
	LEFTARROWSHIRTS,
	LEFTARROWPANTS,

};


CustomLevel::CustomLevel()
	:
	BackGround_(nullptr),
	PlayerBackGround_(nullptr),
	PlayerCustomBoard_(nullptr),
	PlayerBody_(nullptr),
	PlayerHair_(nullptr),
	PlayerShirts_(nullptr),
	PlayerPants_(nullptr),
	RightArrow_(),
	LeftArrow_()
{
}

CustomLevel::~CustomLevel()
{
}

void CustomLevel::LevelChangeStart()
{


}
void CustomLevel::Loading()
{
	//CustomData::GetInst().SetMoveFlag(true);

//Player_->Set

	BackGround_ = CreateActor<TitleBackGround>((int)ORDER::BACKGROUND);
	PlayerCustomBoard_ = CreateActor<PlayerCustomBoard>((int)ORDER::BOARD);
	PlayerBackGround_ = CreateActor<PlayerBackGround>((int)ORDER::PLAYERBACKGROUND);

	PlayerBody_ = CreateActor<PlayerBody>((int)ORDER::PLAYER);
	PlayerBody_->SetPosition({ GameEngineWindow::GetScale().Half().x,  GameEngineWindow::GetScale().Half().y - 120.f });
	PlayerBody_->SetPlayerSpeed(0.f);

	PlayerHair_ = CreateActor<PlayerHair>((int)ORDER::PLAYERHAIR);
	PlayerHair_->SetPosition(PlayerBody_->GetPosition());

	PlayerPants_ = CreateActor<PlayerPants>((int)ORDER::PLAYERPANTS);
	PlayerPants_->SetPosition(PlayerBody_->GetPosition());

	PlayerShirts_ = CreateActor<PlayerShirts>((int)ORDER::PLAYERSHIRTS);
	PlayerShirts_->SetPosition({ PlayerBody_->GetPosition().x, PlayerBody_->GetPosition().y + 6.f }); // (16/2)-2

	for (int i = 0; i < 3; i++) {
		RightArrow_[i] = CreateActor<RightArrow>(((int)ORDER::RIGHTARROWHAIR) + i);
		RightArrow_[i]->SetPosition({ GameEngineWindow::GetScale().Half().x + 50.f,
									  GameEngineWindow::GetScale().Half().y + (50.f * i) });
	}

	for (int i = 0; i < 3; i++) {
		LeftArrow_[i] = CreateActor<LeftArrow>(((int)ORDER::LEFTARROWHAIR) + i);
		LeftArrow_[i]->SetPosition({ GameEngineWindow::GetScale().Half().x - 50.f,
									  GameEngineWindow::GetScale().Half().y + (50.f * i) });
	}
}

void CustomLevel::Update()
{
	//TODO : 테스트용 일괄 인덱스 이동
	if (true == GameEngineInput::GetInst()->IsDown("MoveRight")) {
		CustomData::GetInst().AddHairIndex();
		CustomData::GetInst().AddShirtsIndex();
		CustomData::GetInst().AddPantsIndex();
	}

	if (true == GameEngineInput::GetInst()->IsDown("MoveLeft")) {
		CustomData::GetInst().SubHairIndex();
		CustomData::GetInst().SubShirtsIndex();
		CustomData::GetInst().SubPantsIndex();
	}

	if (true == GameEngineInput::GetInst()->IsDown("Enter"))
	{
		GameEngine::GlobalEngine().ChangeLevel("Play");
	}

}

