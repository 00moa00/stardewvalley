#include "DayOffLevel.h"
#include "GameData.h"
#include "TileData.h"
#include <GameEngineBase/GameEngineTime.h>
#include <sstream>

DayOffLevel::DayOffLevel() 
	:

	DayOffFarming_(0),
	DayOffFForaging_(0),
	DayOffFishing_(0),
	DayOffMining_(0),
	DayOffOther_(0),
	DayOffTotal_(0),

	PrevFarmingMoney_(0),
	PrevForagingMoney_(0),
	PrevFishingMoney_(0),
	PrevMiningMoney_(0),
	PrevOtherMoney_(0),
	PrevTotalMoney_(0),


	FarmingState_(MONEY_UPDATE::WAIT),
	ForagingState_(MONEY_UPDATE::WAIT),
	FishingState_(MONEY_UPDATE::WAIT),
	MiningState_(MONEY_UPDATE::WAIT),
	OtherState_(MONEY_UPDATE::WAIT),
	TotalState_(MONEY_UPDATE::WAIT),

	UpdateState_(DAYOFF_STATE::MONEY_UPDATE),

	DayOffFarmingFont_(nullptr),
	DayOffFForagingFont_(nullptr),
	DayOffFishingFont_(nullptr),
	DayOffMiningFont_(nullptr),
	DayOffOtherFont_(nullptr),
	DayOffTotalFont_(nullptr),

	DayFont_(nullptr)

{
	SetName("DayOffLevel");
	BackGround_ = CreateActor<BackGround>((int)PLAYLEVEL::DAY_OFF);
}

DayOffLevel::~DayOffLevel() 
{
}

void DayOffLevel::Loading()
{
	OKButton_ = CreateActor<MenuButton>(static_cast<int>(PLAYLEVEL::DAY_OFF));
	OKButton_->CreateButtonRenderer("OkButton.bmp");
	OKButton_->CreateButtonCollision("OkButton", { 50,47 });
	OKButton_->SetPosition({ 900.f, 600.f });
	OKButton_->GetRenderer()->CameraEffectOff();

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

	DayOffTotal_ = DayOffFarming_ + DayOffFForaging_ + DayOffFishing_ + DayOffMining_ + DayOffOther_;

	DayOffFarmingFont_ = CreateActor<Font>(static_cast<int>(PLAYLEVEL::DAY_OFF_FONT));
	DayOffFarmingFont_->SetPosition({ 817.f, 178.f });

	DayOffFForagingFont_ = CreateActor<Font>(static_cast<int>(PLAYLEVEL::DAY_OFF_FONT));
	DayOffFForagingFont_->SetPosition({ 817.f, 260.f });

	DayOffFishingFont_ = CreateActor<Font>(static_cast<int>(PLAYLEVEL::DAY_OFF_FONT));
	DayOffFishingFont_->SetPosition({ 817.f, 345.f });

	DayOffMiningFont_ = CreateActor<Font>(static_cast<int>(PLAYLEVEL::DAY_OFF_FONT));
	DayOffMiningFont_->SetPosition({ 817.f, 428.f });

	DayOffOtherFont_ = CreateActor<Font>(static_cast<int>(PLAYLEVEL::DAY_OFF_FONT));
	DayOffOtherFont_->SetPosition({ 817.f, 515.f });

	DayOffTotalFont_ = CreateActor<Font>(static_cast<int>(PLAYLEVEL::DAY_OFF_FONT));
	DayOffTotalFont_->SetPosition({ 817.f, 598.f });

	DayFont_ = CreateActor<Font>(static_cast<int>(PLAYLEVEL::DAY_OFF_FONT));
	DayFont_->SetPosition({ 470.f, 73.f });


	int Day = MainUI::MainMainUI->GetDay() -1;
	std::stringstream ssDay;

	ssDay << Day;


	DayFont_->ChangeFont({ "Day " + ssDay.str() + " of Spring, Year 1" }, {0, 0});

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

	UpdateState_ = DAYOFF_STATE::MONEY_UPDATE;
	Player::MainPlayer->AddMoney(DayOffTotal_);
	MainUI::MainMainUI->SetMainUIMoney(Player::MainPlayer->GetMoney());

}


void DayOffLevel::Update()
{


	if (OKButton_->ButtonMouseOverAndLeftClick())
	{
		GameEngine::GetInst().ChangeLevel("MyHouseLevel");
	}

	AddFarmingAnimation();
	AddForagingAnimation();
	AddFisingAnimation();
	AddMiningAnimation();
	AddOtherAnimation();
	AddTotalAnimation();

}

void DayOffLevel::AddFarmingAnimation()
{
	switch (FarmingState_)
	{
	case MONEY_UPDATE::WAIT:

		FarmingState_ = MONEY_UPDATE::CHANGE_FONT;

		break;
	case MONEY_UPDATE::ADD_TIME:

		PrevFarmingMoney_ += 20;
		FarmingState_ = MONEY_UPDATE::CHANGE_FONT;

		break;
	case MONEY_UPDATE::CHANGE_FONT:

		if (PrevFarmingMoney_ >= DayOffFarming_)
		{
			DayOffFarmingFont_->ChangeNumMoneyLeftSort(DayOffFarming_, { 0 ,0 });
			FarmingState_ = MONEY_UPDATE::WAIT;
		}

		else
		{
			DayOffFarmingFont_->ChangeNumMoneyLeftSort(PrevFarmingMoney_, { 0 ,0 });
			FarmingState_ = MONEY_UPDATE::ADD_TIME;
		}

		break;
	default:
		break;
	}
}


void DayOffLevel::AddForagingAnimation()
{
	switch (ForagingState_)
	{
	case MONEY_UPDATE::WAIT:

		ForagingState_ = MONEY_UPDATE::CHANGE_FONT;

		break;
	case MONEY_UPDATE::ADD_TIME:

		PrevForagingMoney_ += 20;
		ForagingState_ = MONEY_UPDATE::CHANGE_FONT;

		break;
	case MONEY_UPDATE::CHANGE_FONT:

		if (PrevForagingMoney_ >= DayOffFForaging_)
		{
			DayOffFForagingFont_->ChangeNumMoneyLeftSort(DayOffFForaging_, { 0 ,0 });
			ForagingState_ = MONEY_UPDATE::WAIT;
		}

		else
		{
			DayOffFForagingFont_->ChangeNumMoneyLeftSort(PrevForagingMoney_, { 0 ,0 });
			ForagingState_ = MONEY_UPDATE::ADD_TIME;
		}

		break;
	default:
		break;
	}
}


void DayOffLevel::AddFisingAnimation()
{
	switch (FishingState_)
	{
	case MONEY_UPDATE::WAIT:

		FishingState_ = MONEY_UPDATE::CHANGE_FONT;

		break;
	case MONEY_UPDATE::ADD_TIME:

		PrevFishingMoney_ += 20;
		FishingState_ = MONEY_UPDATE::CHANGE_FONT;

		break;
	case MONEY_UPDATE::CHANGE_FONT:

		if (PrevFishingMoney_ >= DayOffFishing_)
		{
			DayOffFishingFont_->ChangeNumMoneyLeftSort(DayOffFishing_, { 0 ,0 });
			FishingState_ = MONEY_UPDATE::WAIT;
		}

		else
		{
			DayOffFishingFont_->ChangeNumMoneyLeftSort(PrevFishingMoney_, { 0 ,0 });
			FishingState_ = MONEY_UPDATE::ADD_TIME;
		}

		break;
	default:
		break;
	}
}


void DayOffLevel::AddMiningAnimation()
{
	switch (MiningState_)
	{
	case MONEY_UPDATE::WAIT:

		MiningState_ = MONEY_UPDATE::CHANGE_FONT;

		break;
	case MONEY_UPDATE::ADD_TIME:

		PrevMiningMoney_ += 20;
		MiningState_ = MONEY_UPDATE::CHANGE_FONT;

		break;
	case MONEY_UPDATE::CHANGE_FONT:

		if (PrevMiningMoney_ >= DayOffMining_)
		{
			DayOffMiningFont_->ChangeNumMoneyLeftSort(DayOffMining_, { 0 ,0 });
			MiningState_ = MONEY_UPDATE::WAIT;
		}

		else
		{
			DayOffMiningFont_->ChangeNumMoneyLeftSort(PrevMiningMoney_, { 0 ,0 });
			MiningState_ = MONEY_UPDATE::ADD_TIME;
		}

		break;
	default:
		break;
	}
}


void DayOffLevel::AddOtherAnimation()
{
	switch (OtherState_)
	{
	case MONEY_UPDATE::WAIT:

		OtherState_ = MONEY_UPDATE::CHANGE_FONT;

		break;
	case MONEY_UPDATE::ADD_TIME:

		PrevOtherMoney_ += 20;
		OtherState_ = MONEY_UPDATE::CHANGE_FONT;

		break;
	case MONEY_UPDATE::CHANGE_FONT:

		if (PrevOtherMoney_ >= DayOffOther_)
		{
			DayOffOtherFont_->ChangeNumMoneyLeftSort(DayOffOther_, { 0 ,0 });
			OtherState_ = MONEY_UPDATE::WAIT;
		}

		else
		{
			DayOffOtherFont_->ChangeNumMoneyLeftSort(PrevOtherMoney_, { 0 ,0 });
			OtherState_ = MONEY_UPDATE::ADD_TIME;
		}

		break;
	default:
		break;
	}
}


void DayOffLevel::AddTotalAnimation()
{
	switch (TotalState_)
	{
	case MONEY_UPDATE::WAIT:

		TotalState_ = MONEY_UPDATE::CHANGE_FONT;

		break;
	case MONEY_UPDATE::ADD_TIME:

		PrevTotalMoney_ += 20;
		TotalState_ = MONEY_UPDATE::CHANGE_FONT;

		break;
	case MONEY_UPDATE::CHANGE_FONT:

		if (PrevTotalMoney_ >= DayOffTotal_)
		{
			DayOffTotalFont_->ChangeNumMoneyLeftSort(DayOffTotal_, { 0 ,0 });
			TotalState_ = MONEY_UPDATE::WAIT;
		}

		else
		{
			DayOffTotalFont_->ChangeNumMoneyLeftSort(PrevTotalMoney_, { 0 ,0 });
			TotalState_ = MONEY_UPDATE::ADD_TIME;
		}

		break;
	default:
		break;
	}
}
