#include "DayOffLevel.h"
#include "GameData.h"
#include "TileData.h"
#include <GameEngineBase/GameEngineTime.h>

DayOffLevel::DayOffLevel() 
	:
	DayOffFarming_(0),
	DayOffFForaging_(0),
	DayOffFishing_(0),
	DayOffMining_(0),
	DayOffOther_(0),
	DayOffTotal_(0)

{
	SetName("DayOffLevel");
	BackGround_ = CreateActor<BackGround>((int)PLAYLEVEL::BACKGROUND);
	BackGroundFront_ = CreateActor<BackGround>((int)PLAYLEVEL::BACKGROUND_FRONT);
}

DayOffLevel::~DayOffLevel() 
{
}

void DayOffLevel::Loading()
{
	OKButton_ = CreateActor<MenuButton>(static_cast<int>(TITLELEVEL::CUSTROM_BUTTON));
	OKButton_->CreateButtonRenderer("OkButton.bmp");
	OKButton_->CreateButtonCollision("OkButton", { 50,47 });
	OKButton_->SetPosition({ 810.f, 560.f });
	OKButton_->GetRenderer()->CameraEffectOff();

}

void DayOffLevel::Update()
{

	if (OKButton_->ButtonMouseOverAndLeftClick())
	{
		GameEngine::GetInst().ChangeLevel("MyHouseLevel");
	}

}

void DayOffLevel::LevelChangeStart(GameEngineLevel* _NextLevel)
{

	BackGround_->GetRenderer()->SetImage("DayOff.bmp");
	BackGround_->GetRenderer()->SetPivot({ HOUSE_SIZE_WEIGHT / 2,  HOUSE_SIZE_HEIGHT / 2 });

	FadeInOut* FadeInOut_ = CreateActor<FadeInOut>(static_cast<int>(PLAYLEVEL::FADE));
	FadeInOut_->SetFadeIn();

	DayOffFarming_ = Player::MainPlayer->GetDayOffFarming();
	DayOffFForaging_ = Player::MainPlayer->GetDayOffForaging();
	DayOffFishing_ = Player::MainPlayer->GetDayOffFishing();

	DayOffMining_ = Player::MainPlayer->GetDayOffMining();
	DayOffOther_ = Player::MainPlayer->GetDayOffOther();
	Player::MainPlayer->Off();
	DayOffTotal_ = DayOffFarming_ + DayOffFForaging_ + DayOffFishing_ + DayOffMining_ + DayOffOther_;


}

void DayOffLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	if (_NextLevel->GetNameCopy() != "TitleLevel")
	{
		Player::MainPlayer->NextLevelOn();
		Inventory::MainInventory->NextLevelOn();
		MainUI::MainMainUI->NextLevelOn();
		PlayerEnergyFrame::MainPlayerEnergyFrame->NextLevelOn();
		PlayerHPFrame::MainPlayerHPFrame->NextLevelOn();

	}
	Player::MainPlayer->On();

}
