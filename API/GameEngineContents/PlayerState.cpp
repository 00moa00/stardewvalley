#include  "Player.h"
#include "MainUI.h"
#include "NpcData.h"
#include "PlayerEnergyFrame.h"
#include "PlayerHPFrame.h"
#include "SubHPFont.h"

#include "FadeInOut.h"


//------< 공개 함수 >------------------------------------------------------------------


//******************************************************************************
//
//
//		Getter
//
//
//******************************************************************************


bool  Player::GetObjectColl()
{
	return ObjectColl_;
}

bool Player::GetisShopping()
{
	return isShopping_;
}

int  Player::GetEnergy()
{
	return Energy_;
}

int Player::GetDayOffFarming()
{
	return DayOffFarming_;
}

int Player::GetDayOffForaging()
{
	return DayOffFForaging_;
}

int Player::GetDayOffFishing()
{
	return DayOffFishing_;
}

int Player::GetDayOffMining()
{
	return DayOffMining_;
}

int Player::GetDayOffOther()
{
	return DayOffOther_;
}

float4 Player::GetMoveDir()
{
	return MoveDir_;
}

int Player::GetMoney()
{
	return Money_;
}

std::string  Player::GetCurrentLevel()
{
	return GetLevel()->GetNameConstRef();
}

Items* Player::GetCurrentItem()
{
	return Inventory::MainInventory->GetCurrentItem();
}

TOOLTYPE Player::CurrentItemType()
{
	if (Inventory::MainInventory->GetCurrentItem() == nullptr)
	{
		return TOOLTYPE::OTHER;
	}

	CurrentItemType_ = Inventory::MainInventory->GetCurrentItem()->GetToolType();
	return CurrentItemType_;
}


PLAYER_SHOPPING Player::GetPlayerShoppingState()
{
	return PlayerShoppingState_;
}

bool Player::GetPlayerShoppingStateShopping()
{
	return (PlayerShoppingState_ == PLAYER_SHOPPING::SHOPPING);
}

PLAYER_UPDATE Player::GetPlayerState()
{
	return PlayerState_;
}

bool Player::GetMoneyAddMoneyCountWait()
{
	return AddMoneyCount_ == MONEY_UPDATE::WAIT;
}

bool Player::GetMoneySubMoneyCountWait()
{
	return SubMoneyCount_ == MONEY_UPDATE::WAIT;
}

Inventory* Player::GetInventroy()
{
	return Inventory::MainInventory;
}

GameEngineRenderer* Player::Renderer() {
	return PlayerBodyRenderer_;
}

GameEngineImage* Player::CollImage() {
	return MapColImage_;
}

bool Player::FindWetDirt(int _Index)
{
	std::map<int, FarmTile*>::iterator FindtIter = WetDirtList_.find(_Index);
	std::map<int, FarmTile*>::iterator EndIter = WetDirtList_.end();

	if (FindtIter != EndIter)
	{
		return true;
	}

	else
	{
		return false;
	}

}



//******************************************************************************
//
//
//		Setter
//
//
//******************************************************************************

void Player::SetPlayerFaint()
{
	
	PlayerState_ = PLAYER_UPDATE::FAINT;
	
}

void Player::SetisEvent(bool _Flag)
{
	isEvent_ = _Flag;
}

void Player::ChangeHair(int _Index)
{

	if (_Index == 0)
	{
		PlayerHairRenderer_->SetImage("PlayerHair0.bmp");
	}

}

void Player::ChangeShirts(int _Index)
{
}

void Player::ChangePants(int _Index)
{
}

void Player::SetResetPlayerHandItem()
{
	PlayerState_ = PLAYER_UPDATE::WALK;
	//Inventory::MainInventory->SetCurrentItemHoe();
}



bool Player::SubMoney(int _Money)
{
	if (Money_ > 0 + _Money)
	{
		PrevMoney_ = Money_;
		Money_ -= _Money;
		//TotalMoney_ = 
		SubMoneyCount_ = MONEY_UPDATE::ADD_TIME;
		return true;
	}

	else
	{
		false;
	}


}

void Player::AddMoney(int _Money)
{

	PrevMoney_ = Money_;
	Money_ += _Money;

	AddMoneyCount_ = MONEY_UPDATE::ADD_TIME;
}

void Player::SetisShopping(bool b)
{
	isShopping_ = b;
}

void  Player::SetObjectColl(bool b)
{
	ObjectColl_ = b;
}

void  Player::SetCurrentLevel(std::string s)
{
	CurrentLevel_ = s;
}

void  Player::SetPrevLevel(std::string s)
{
	PrevLevel_ = s;
}

void  Player::SetDirtTileMap(GameEngineRendererTileMap* _TileMap)
{
	DirtTileMap_ = _TileMap;

}

void  Player::SetWetTileMap(GameEngineRendererTileMap* _TileMap)
{
	WetTileMap_ = _TileMap;

}

void Player::DeleteSeedList(int _Index)
{
	SeedList_.erase(_Index);
}

void Player::SetPlayerDirDown()
{
	MoveDir_ = float4::DOWN;

}

void Player::SetUpdateStateInit()
{
	PlayerState_ = PLAYER_UPDATE::INIT;

}



//******************************************************************************
//
//
//		Etc
//
//
//******************************************************************************


void  Player::CopyList(std::map<int, Items*> _OtherList)
{
	std::copy(_OtherList.begin(), _OtherList.end(), std::inserter(MapObject_, MapObject_.begin()));
}

void Player::CopyList(std::map<std::string, Npc*> _OtherList)
{
	std::copy(_OtherList.begin(), _OtherList.end(), std::inserter(NpcList_, NpcList_.begin()));

}

void Player::CopyList(std::map<std::string, Monster*> _OtherList)
{
	std::copy(_OtherList.begin(), _OtherList.end(), std::inserter(MonsterList_, MonsterList_.begin()));

}

//------< 비공개 함수 >------------------------------------------------------------------

//******************************************************************************
//
//
//		업데이트, 체크
//
//
//******************************************************************************

void Player::PlayerShopping()
{
	//Shop* MainShop = GetLevel()->FindActor<Shop>("Shop");

	switch (PlayerShoppingState_)
	{
	case PLAYER_SHOPPING::INT:

		Shop::MainShop->ShopOff();

		if (MouseClickAndColl() == true)
		{
			PlayerState_ = PLAYER_UPDATE::SHOPPING;
			PlayerShoppingState_ = PLAYER_SHOPPING::SHOP_ON;
		}
		break;

	case PLAYER_SHOPPING::SHOPPING:

		if (isShopping_ == false)
		{
			PlayerShoppingState_ = PLAYER_SHOPPING::SHOP_OFF;

		}

		break;


	case PLAYER_SHOPPING::SHOP_ON:

		WoodStepBGMPlayer.Volume(0.0f);
		SandStepBGMPlayer.Volume(0.0f);
		WeedStepBGMPlayer.Volume(0.0f);

		Shop::MainShop->ShopOn();
		Inventory::MainInventory->SetInventoryMoveStateInit();
		isShopping_ = true;
	//	isEvent_ = true;
		PlayerShoppingState_ = PLAYER_SHOPPING::SHOPPING;

		break;

	case PLAYER_SHOPPING::SHOP_OFF:

		GameEngineSound::SoundPlayOneShot("bigDeSelect.wav");
		Shop::MainShop->ShopOff();
	//	isEvent_ = false;
		PlayerState_ = PLAYER_UPDATE::INIT;
		PlayerShoppingState_ = PLAYER_SHOPPING::INT;

		break;

	default:
		break;
	}
	//쇼핑중

	//if (MouseClickAndColl() == true && isShopping_ == false)
	//{
	//	isShopping_ = true;
	//}
	//
	//if (isShopping_ == true) Shop_->ShopOn();
	//if (isShopping_ == false) Shop_->ShopOff();

}

void Player::SetCamera()
{
	GetLevel()->SetCameraPos(GetPosition() - GameEngineWindow::GetInst().GetScale().Half());

	if (0 > GetLevel()->GetCameraPos().x)
	{
		float4 CurCameraPos = GetLevel()->GetCameraPos();
		CurCameraPos.x = 0;
		GetLevel()->SetCameraPos(CurCameraPos);
	}

	if (0 > GetLevel()->GetCameraPos().y)
	{
		float4 CurCameraPos = GetLevel()->GetCameraPos();
		CurCameraPos.y = 0;
		GetLevel()->SetCameraPos(CurCameraPos);
	}

	{
		CameraPos_ = GetPosition() - GameEngineWindow::GetInst().GetScale().Half();

		if (CameraPos_.x <= 0)
		{
			CameraPos_.x = 0;
		}

		if (CameraPos_.x >= MapSizeX_ - GameEngineWindow::GetInst().GetScale().ix())
		{
			CameraPos_.x = MapSizeX_ - GameEngineWindow::GetInst().GetScale().ix();
		}

		if (CameraPos_.y <= 0)
		{
			CameraPos_.y = 0;
		}

		if (CameraPos_.y >= MapSizeY_ - GameEngineWindow::GetInst().GetScale().iy())
		{
			CameraPos_.y = MapSizeY_ - GameEngineWindow::GetInst().GetScale().iy();
		}

		GetLevel()->SetCameraPos(CameraPos_);
	}

}

void Player::SetPlayerStartPos()
{



}

void Player::ChangeLevel()
{

	switch (LevelChagne_)
	{


	case LEVEL_CHANGE_STATE::CHECK:

		if (MoveFarmCollision())
		{

			if (CurrentLevel_ == "MyHouseLevel")
			{
				GameEngineSound::SoundPlayOneShot("doorOpen.wav");

			}

			FadeInOut_ = GetLevel()->CreateActor<FadeInOut>(static_cast<int>(PLAYLEVEL::FADE));
			FadeInOut_->SetFadeOut();
			ChangeLevelName_ = "MyFarmLevel";
			LevelChagne_ = LEVEL_CHANGE_STATE::FADE_OUT;
		}

		if (MoveHouseCollision() && GameEngineInput::GetInst()->IsDown("RightClick"))
		{
			GameEngineSound::SoundPlayOneShot("doorOpen.wav");

			FadeInOut_ = GetLevel()->CreateActor<FadeInOut>(static_cast<int>(PLAYLEVEL::FADE));
			FadeInOut_->SetFadeOut();

			ChangeLevelName_ = "MyHouseLevel";
			LevelChagne_ = LEVEL_CHANGE_STATE::FADE_OUT;

		}

		if (MoveBusStopCollision())
		{
			FadeInOut_ = GetLevel()->CreateActor<FadeInOut>(static_cast<int>(PLAYLEVEL::FADE));
			FadeInOut_->SetFadeOut();
			ChangeLevelName_ = "BusStopLevel";
			LevelChagne_ = LEVEL_CHANGE_STATE::FADE_OUT;
		}


		if (MoveTownCollision() && CurrentLevel_ != "SaloonLevel")
		{
			FadeInOut_ = GetLevel()->CreateActor<FadeInOut>(static_cast<int>(PLAYLEVEL::FADE));
			FadeInOut_->SetFadeOut();
			ChangeLevelName_ = "TownLevel";
			LevelChagne_ = LEVEL_CHANGE_STATE::FADE_OUT;
		}

		if (MoveTownCollision() && GameEngineInput::GetInst()->IsDown("RightClick") && CurrentLevel_ == "SaloonLevel")
		{
			GameEngineSound::SoundPlayOneShot("doorOpen.wav");

			FadeInOut_ = GetLevel()->CreateActor<FadeInOut>(static_cast<int>(PLAYLEVEL::FADE));
			FadeInOut_->SetFadeOut();

			ChangeLevelName_ = "TownLevel";
			LevelChagne_ = LEVEL_CHANGE_STATE::FADE_OUT;
		}



		if (MoveShopCollision() && GameEngineInput::GetInst()->IsDown("RightClick"))
		{
			GameEngineSound::SoundPlayOneShot("doorOpen.wav");

			FadeInOut_ = GetLevel()->CreateActor<FadeInOut>(static_cast<int>(PLAYLEVEL::FADE));
			FadeInOut_->SetFadeOut();
			ChangeLevelName_ = "SeedShopLevel";
			LevelChagne_ = LEVEL_CHANGE_STATE::FADE_OUT;
		}


		if (MoveSaloonCollision() && GameEngineInput::GetInst()->IsDown("RightClick"))
		{
			GameEngineSound::SoundPlayOneShot("doorOpen.wav");

			FadeInOut_ = GetLevel()->CreateActor<FadeInOut>(static_cast<int>(PLAYLEVEL::FADE));
			FadeInOut_->SetFadeOut();

			ChangeLevelName_ = "SaloonLevel";
			LevelChagne_ = LEVEL_CHANGE_STATE::FADE_OUT;
		}

		//
		if (MoveBackForestCollision())
		{
			FadeInOut_ = GetLevel()->CreateActor<FadeInOut>(static_cast<int>(PLAYLEVEL::FADE));
			FadeInOut_->SetFadeOut();
			ChangeLevelName_ = "BackForestLevel";
			LevelChagne_ = LEVEL_CHANGE_STATE::FADE_OUT;
		}

		if (MoveMineLevelCollision() && GameEngineInput::GetInst()->IsDown("RightClick"))
		{
			FadeInOut_ = GetLevel()->CreateActor<FadeInOut>(static_cast<int>(PLAYLEVEL::FADE));
			FadeInOut_->SetFadeOut();
			ChangeLevelName_ = "MineLevel";
			LevelChagne_ = LEVEL_CHANGE_STATE::FADE_OUT;
		}

		if (MoveMinePointCollision() && GameEngineInput::GetInst()->IsDown("RightClick"))
		{
			GameEngineSound::SoundPlayOneShot("stairsdown.wav");

			FadeInOut_ = GetLevel()->CreateActor<FadeInOut>(static_cast<int>(PLAYLEVEL::FADE));
			FadeInOut_->SetFadeOut();
			ChangeLevelName_ = "MinePoint";
			LevelChagne_ = LEVEL_CHANGE_STATE::FADE_OUT;
		}

		if (MoveMine1Collision() && GameEngineInput::GetInst()->IsDown("RightClick"))
		{
			GameEngineSound::SoundPlayOneShot("stairsdown.wav");

			FadeInOut_ = GetLevel()->CreateActor<FadeInOut>(static_cast<int>(PLAYLEVEL::FADE));
			FadeInOut_->SetFadeOut();
			ChangeLevelName_ = "Mine1";
			LevelChagne_ = LEVEL_CHANGE_STATE::FADE_OUT;
		}

		if (MoveMine2Collision() && GameEngineInput::GetInst()->IsDown("RightClick"))
		{
			GameEngineSound::SoundPlayOneShot("stairsdown.wav");

			FadeInOut_ = GetLevel()->CreateActor<FadeInOut>(static_cast<int>(PLAYLEVEL::FADE));
			FadeInOut_->SetFadeOut();
			ChangeLevelName_ = "Mine2";
			LevelChagne_ = LEVEL_CHANGE_STATE::FADE_OUT;
		}

		if (MoveMine3Collision() && GameEngineInput::GetInst()->IsDown("RightClick"))
		{
			GameEngineSound::SoundPlayOneShot("stairsdown.wav");

			FadeInOut_ = GetLevel()->CreateActor<FadeInOut>(static_cast<int>(PLAYLEVEL::FADE));
			FadeInOut_->SetFadeOut();
			ChangeLevelName_ = "Mine3";
			LevelChagne_ = LEVEL_CHANGE_STATE::FADE_OUT;
		}

		if (MoveMine4Collision() && GameEngineInput::GetInst()->IsDown("RightClick"))
		{
			GameEngineSound::SoundPlayOneShot("stairsdown.wav");

			FadeInOut_ = GetLevel()->CreateActor<FadeInOut>(static_cast<int>(PLAYLEVEL::FADE));
			FadeInOut_->SetFadeOut();
			ChangeLevelName_ = "Mine4";
			LevelChagne_ = LEVEL_CHANGE_STATE::FADE_OUT;
		}

		break;
	case LEVEL_CHANGE_STATE::FADE_OUT:

		if (FadeInOut_->GetFadeEnd())
		{

			GameEngine::GetInst().ChangeLevel(ChangeLevelName_);
		}

		break;
	case LEVEL_CHANGE_STATE::LEVEL_CHANGE:
		break;
	default:
		break;
	}



}

void Player::ChangeHandItem()
{
	if (Inventory::MainInventory->GetCurrentItem() != nullptr && Inventory::MainInventory->GetCurrentItem()->GetisPossibleHand() == true)
	{
		PlayerHandItem_->GetRenderer()->SetImage((Inventory::MainInventory->GetCurrentItem()->GetFileName()));
		PlayerHandItem_->GetRenderer()->SetIndex((Inventory::MainInventory->GetCurrentItem()->GetFileIndex()));
	}

	else
	{
		PlayerHandItem_->GetRenderer()->SetImage("Empty.bmp");
	}
}



void Player::CheckTool()
{

	if (CurrentItemType() == TOOLTYPE::HOE)
	{
		PlayerState_ = PLAYER_UPDATE::HOE;
	}

	else if (CurrentItemType() == TOOLTYPE::WATTERING_CAN)
	{
		PlayerState_ = PLAYER_UPDATE::WATER;
	}

	else if (CurrentItemType() == TOOLTYPE::AXE)
	{
		PlayerState_ = PLAYER_UPDATE::AXE;
	}

	else if (CurrentItemType() == TOOLTYPE::PICKAXE)
	{
		PlayerState_ = PLAYER_UPDATE::PICKAXE;
	}

	else if (CurrentItemType() == TOOLTYPE::SWOARD)
	{
		AttackMonster();

		PlayerState_ = PLAYER_UPDATE::SWOARD;
	}
	else
	{
		PlayerState_ = PLAYER_UPDATE::INIT;
	}



}

void Player::CheckDrink()
{
	if (GetCurrentItem()->GetObjectType() == OBJECTTYPE::DRINK && GameEngineInput::GetInst()->IsDown("RightClick"))
	{
		PlayerHandItem_->GetRenderer()->SetImage("Empty.bmp");
		PlayerState_ = PLAYER_UPDATE::DRINK;
	}
}

void Player::CheckEat()
{
	if (GetCurrentItem()->GetObjectType() == OBJECTTYPE::FOOD && GameEngineInput::GetInst()->IsDown("RightClick"))
	{
		GetCurrentItem()->DropItemInMap();
		PlayerHandItem_->GetRenderer()->SetImage("Empty.bmp");
		PlayerState_ = PLAYER_UPDATE::EAT_WAIT;
	}
}

void Player::NpcCollCheck()
{
	if (PlayerCollider_->NextPostCollisionCheck("NPC", MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_, CollisionType::Rect, CollisionType::Rect) == true)
	{
		std::map<std::string, Npc*>::iterator NpcIter = NpcList_.begin();
		std::map<std::string, Npc*>::iterator NpcEndIter = NpcList_.end();


		for (; NpcIter != NpcEndIter; ++NpcIter) {

			if (NpcIter->second->NPCCheck(PlayerCollCheckPos(), GetScale()) == true
				&& NpcIter->second->GetTalkingLimit() == false
				&& MainMouse_->isMouseRightClick() == true)
			{
				isEvent_ = !isEvent_;
				//if (PlayerState_ == PLAYER_UPDATE::INIT)
				//{
				//	PlayerState_ = PLAYER_UPDATE::TALKING;
				//}
				//if (PlayerState_ == PLAYER_UPDATE::TALKING)
				//{
				//	PlayerState_ = PLAYER_UPDATE::INIT;
				//}

				NpcIter->second->OpenDialogue();

			}

		}
	}


}

void Player::AddMoneyAnimation()
{

	switch (AddMoneyCount_)
	{
	case MONEY_UPDATE::WAIT:
		break;
	case MONEY_UPDATE::ADD_TIME:

		PrevMoney_ += 3;
		AddMoneyCount_ = MONEY_UPDATE::CHANGE_FONT;
	
		break;
	case MONEY_UPDATE::CHANGE_FONT:

		if (PrevMoney_ >= Money_)
		{
			MainUI::MainMainUI->SetMainUIMoney(Money_);
			Shop::MainShop->SetShopMoney(Money_);
			AddMoneyCount_ = MONEY_UPDATE::WAIT;
		}

		else
		{
			MainUI::MainMainUI->SetMainUIMoney(PrevMoney_);
			Shop::MainShop->SetShopMoney(PrevMoney_);
			AddMoneyCount_ = MONEY_UPDATE::ADD_TIME;
		}

		break;
	default:
		break;
	}
}

void Player::SubMoneyAnimation()
{
	switch (SubMoneyCount_)
	{
	case MONEY_UPDATE::WAIT:
		break;
	case MONEY_UPDATE::ADD_TIME:

		PrevMoney_ -= 3;
		SubMoneyCount_ = MONEY_UPDATE::CHANGE_FONT;

		break;
	case MONEY_UPDATE::CHANGE_FONT:

		if (PrevMoney_ <= Money_)
		{
			MainUI::MainMainUI->SetMainUIMoney(Money_);
			Shop::MainShop->SetShopMoney(Money_);
			SubMoneyCount_ = MONEY_UPDATE::WAIT;
		}

		else
		{
			MainUI::MainMainUI->SetMainUIMoney(PrevMoney_);
			Shop::MainShop->SetShopMoney(PrevMoney_);
			SubMoneyCount_ = MONEY_UPDATE::ADD_TIME;
		}

		break;
	default:
		break;
	}
}

void Player::DelaySpeed()
{
	if (isDelaySpeed_ == true)
	{
		DelaySpeedTimer_ -= GameEngineTime::GetDeltaTime();
		
		if (DelaySpeedTimer_ <= 0)
		{
			isDelaySpeed_ = false;
			Speed_ = 220.f;
			DelaySpeedTimer_ = 0;
		}
	}
}

void Player::UpdateInvincibilityTime()
{
	if (invincibility_ == true)
	{
		InvincibilityTimer_ += GameEngineTime::GetDeltaTime();

		if (InvincibilityTimer_ > 0)
		{
			SetPlayerAlpha0();
		}

		if (InvincibilityTimer_ > 0.1 )
		{
			SetPlayerAlpha255();
		}

		if (InvincibilityTimer_ > 0.2)
		{
			SetPlayerAlpha0();
		}

		if (InvincibilityTimer_ > 0.3)
		{
			SetPlayerAlpha255();
		}

		if (InvincibilityTimer_ > 0.4)
		{
			SetPlayerAlpha0();
		}

		if (InvincibilityTimer_ > 0.5f)
		{
			SetPlayerAlpha255();
			InvincibilityTimer_ = 0.f;
			isNotInvincibility_ = true;
			invincibility_ = false;
		}
	}
}

void Player::UpdateIsNotInvincibilityTime()
{
	//매 프레임 무적이 되는걸 막기 위한 함수
	//isNotInvincibility_가 false일때만 무적이 될 수 있따.

	if (isNotInvincibility_ == true)
	{
		IsNotInvincibilityTimer_ += GameEngineTime::GetDeltaTime();

		if (IsNotInvincibilityTimer_ > 2.0f)
		{
			IsNotInvincibilityTimer_ = 0.f;
			isNotInvincibility_ = false;
		}
	}
}

void Player::SetPlayerAlpha255()
{
	PlayerBodyRenderer_->SetAlpha(255);
	PlayerPantsRenderer_->SetAlpha(255);
	PlayerShirtsRenderer_->SetAlpha(255);
	PlayerHairRenderer_->SetAlpha(255);
	PlayerHandRenderer_->SetAlpha(255);
}

void Player::SetPlayerAlpha0()
{

	PlayerBodyRenderer_->SetAlpha(0);
	PlayerPantsRenderer_->SetAlpha(0);
	PlayerShirtsRenderer_->SetAlpha(0);
	PlayerHairRenderer_-> SetAlpha(0);
	PlayerHandRenderer_->SetAlpha(0);

}



//******************************************************************************
//
//
//		플레이어 기본
//
//
//******************************************************************************


bool Player::isStop()
{
	return (true == GameEngineInput::GetInst()->IsFree("MoveRight")
		&& true == GameEngineInput::GetInst()->IsFree("MoveLeft")
		&& true == GameEngineInput::GetInst()->IsFree("MoveDown")
		&& true == GameEngineInput::GetInst()->IsFree("MoveUp"));
}

bool Player::isMove()
{
	return (true == GameEngineInput::GetInst()->IsPress("MoveRight")
		|| true == GameEngineInput::GetInst()->IsPress("MoveLeft")
		|| true == GameEngineInput::GetInst()->IsPress("MoveDown")
		|| true == GameEngineInput::GetInst()->IsPress("MoveUp"));
}

void Player::PlayerWalk() {


	float4 NextPos;
	float4 CheckPos = MoveDir_;
	float4 Move = float4::ZERO;

	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		Move += float4::RIGHT;
	}
	else if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		Move += float4::LEFT;
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		Move += float4::UP;
	}

	else if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		Move += float4::DOWN;
	}

	Move.Normal2D();

	NextPos = GetPosition() + (Move * GameEngineTime::GetDeltaTime() * Speed_);
	CheckPos += NextPos;


	if (PlayerCollider_->NextPostCollisionCheck("MapObject", Move * GameEngineTime::GetDeltaTime() * Speed_, CollisionType::Rect, CollisionType::Rect) == true)
	{
		Move = float4::ZERO;
	}

	if (PlayerCollider_->NextPostCollisionCheck("NPC", Move * GameEngineTime::GetDeltaTime() * Speed_, CollisionType::Rect, CollisionType::Rect) == true)
	{
		Move = float4::ZERO;
	}


	if (MapColImage_ != nullptr)
	{
		int Color = MapColImage_->GetImagePixel(CheckPos);

		if ((RGB(0, 0, 0) == Color))
		{
			Move = float4::ZERO;

		}

		if ((RGB(0, 0, 255) == Color))
		{
			FarmingArea_ = true;
		}
		else
		{
			FarmingArea_ = false;

		}

		if ( (CurrentLevel_ != "MyHouseLevel") && (CurrentLevel_ != "SaloonLevel") && (CurrentLevel_ != "SeedShopLevel"))
		{
			if ((RGB(255, 0, 0) == Color))
			{
				//FarmingArea_ = true;
				WeedStepBGMPlayer.Volume(0.5f);
				SandStepBGMPlayer.Volume(0.0f);
			}
			else
			{
				WeedStepBGMPlayer.Volume(0.0f);

				SandStepBGMPlayer.Volume(0.6f);
			}
		}

	}


	SetMove(Move * GameEngineTime::GetDeltaTime() * Speed_);


}

void Player::PlayerDirCheck()
{

	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		MoveDir_ = float4::LEFT;
	}
	else if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir_ = float4::RIGHT;
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		MoveDir_ = float4::UP;
	}
	else if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		MoveDir_ = float4::DOWN;
	}

}


void Player::SetPlayerHandItemPos()
{
	PlayerHandItem_->SetPosition({ this->GetPosition().x, this->GetPosition().y - 92.f });

}

void Player::SubEnergy(int _Energy)
{

	Energy_ -= _Energy;
	PlayerEnergyFrame::MainPlayerEnergyBar->GetRenderer()->SetScale({18, static_cast<float>(Energy_) });
	//TODO : 에너지가 0이면 어쩔거임?

}

void Player::AddEnergy(int _Energy)
{
	Energy_ += _Energy;

	if (Energy_ > 126)
	{
		Energy_ = 126;
	}
}

void Player::SubHP(int _HP)
{
	if (invincibility_ == true)
	{
		return;
	}

	SubHPFont* SubHPFont_;
	SubHPFont_ = GetLevel()->CreateActor<SubHPFont>();
	SubHPFont_->SetPosAndNumRed(this->GetPosition(), _HP);

	HP_ -= _HP;
	PlayerHPFrame::MainPlayerHPBar->GetRenderer()->SetScale({ 18, static_cast<float>(HP_) });
	//TODO : HP가 0이면 어쩔거임?

}

void Player::AddHP(int _HP)
{
	HP_ += _HP;

	if (HP_ > _HP)
	{
		HP_ = _HP;
	}
}


//******************************************************************************
//
//
//		애니메이션
//
//
//******************************************************************************


void Player::SetDirAnimation()
{

	if (MoveDir_.CompareInt2D(float4::RIGHT))
	{
		PlayerBodyRenderer_->ChangeAnimation("RIGHT_INIT");
		PlayerPantsRenderer_->ChangeAnimation("RIGHT_INIT");
		PlayerShirtsRenderer_->ChangeAnimation("RIGHT_INIT");
		PlayerHairRenderer_->ChangeAnimation("RIGHT_INIT");
		PlayerHandRenderer_->ChangeAnimation("RIGHT_INIT");

	}

	if (MoveDir_.CompareInt2D(float4::DOWN))
	{
		PlayerBodyRenderer_->ChangeAnimation("FRONT_INIT");
		PlayerPantsRenderer_->ChangeAnimation("FRONT_INIT");
		PlayerShirtsRenderer_->ChangeAnimation("FRONT_INIT");
		PlayerHairRenderer_->ChangeAnimation("FRONT_INIT");
		PlayerHandRenderer_->ChangeAnimation("FRONT_INIT");

	}

	if (MoveDir_.CompareInt2D(float4::UP))
	{
		PlayerBodyRenderer_->ChangeAnimation("BACK_INIT");
		PlayerPantsRenderer_->ChangeAnimation("BACK_INIT");
		PlayerShirtsRenderer_->ChangeAnimation("BACK_INIT");
		PlayerHairRenderer_->ChangeAnimation("BACK_INIT");
		PlayerHandRenderer_->ChangeAnimation("BACK_INIT");

	}

	if (MoveDir_.CompareInt2D(float4::LEFT))
	{
		PlayerBodyRenderer_->ChangeAnimation("LEFT_INIT");
		PlayerPantsRenderer_->ChangeAnimation("LEFT_INIT");
		PlayerShirtsRenderer_->ChangeAnimation("LEFT_INIT");
		PlayerHairRenderer_->ChangeAnimation("LEFT_INIT");
		PlayerHandRenderer_->ChangeAnimation("LEFT_INIT");

	}

}

void Player::DirAnimationChange()
{

	//if (PlayerState_ == PLAYER_UPDATE::INVENTROY_MINI_INIT) { return ; }
	//if (PlayerState_ == PLAYER_UPDATE::INVENTROY_POPUP_INIT) { return; }
	//if (PlayerState_ == PLAYER_UPDATE::INVENTROY_POPUP) { return; }

	if (PlayerState_ == PLAYER_UPDATE::LEVELINIT)
	{
		return;
	}


	PlayerBodyRenderer_->ChangeAnimation(GetDirString() + ArrAnimationName[static_cast<int>(PlayerState_)]);
	PlayerPantsRenderer_->ChangeAnimation(GetDirString() + ArrAnimationName[static_cast<int>(PlayerState_)]);
	PlayerShirtsRenderer_->ChangeAnimation(GetDirString() + ArrAnimationName[static_cast<int>(PlayerState_)]);
	PlayerHairRenderer_->ChangeAnimation(GetDirString() + ArrAnimationName[static_cast<int>(PlayerState_)]);
	PlayerHandRenderer_->ChangeAnimation(GetDirString() + ArrAnimationName[static_cast<int>(PlayerState_)]);


	ToolRenderer_->ChangeAnimation(GetDirString() + ArrAnimationToolName[static_cast<int>(PlayerState_)]);


}

std::string Player::GetDirString()
{
	if (MoveDir_.CompareInt2D(float4::DOWN))
	{
		return "FRONT_";
	}

	else if (MoveDir_.CompareInt2D(float4::UP))
	{
		return "BACK_";
	}

	else if (MoveDir_.CompareInt2D(float4::LEFT))
	{
		return "LEFT_";
	}

	else if (MoveDir_.CompareInt2D(float4::RIGHT))
	{
		return "RIGHT_";
	}

	return "";
}


//******************************************************************************
//
//
//		마우스, 충돌 관련
//
//
//******************************************************************************



bool Player::PlayerMouseClickCollision() 
{
	return (PlayerCollider_->CollisionResult("MouseCursor", ColList, CollisionType::Rect, CollisionType::Rect))
		&& (MainMouse_->isMouseClick());
}

bool Player::MoveFarmCollision()
{

	return (PlayerCollider_->CollisionResult("MoveFarm", ColList, CollisionType::Rect, CollisionType::Rect));
}

bool Player::MoveHouseCollision() 
{

	return (PlayerCollider_->CollisionResult("MoveHouse", ColList, CollisionType::Rect, CollisionType::Rect));
}

bool Player::MoveBusStopCollision() 
{

	return (PlayerCollider_->CollisionResult("MoveBusStop", ColList, CollisionType::Rect, CollisionType::Rect));
}

bool Player::MoveTownCollision() 
{

	return (PlayerCollider_->CollisionResult("MoveTown", ColList, CollisionType::Rect, CollisionType::Rect));
}

bool Player::MoveShopCollision()
{
	return (PlayerCollider_->CollisionResult("MoveShop", ColList, CollisionType::Rect, CollisionType::Rect));
}

bool Player::MoveSaloonCollision()
{
	return (PlayerCollider_->CollisionResult("MoveSalon", ColList, CollisionType::Rect, CollisionType::Rect));
}

//
bool Player::MoveBackForestCollision()
{

	return (PlayerCollider_->CollisionResult("MoveBackForest", ColList, CollisionType::Rect, CollisionType::Rect));
}

bool Player::MoveMineLevelCollision()
{
	return (PlayerCollider_->CollisionResult("MoveMine", ColList, CollisionType::Rect, CollisionType::Rect));
}

bool Player::MoveMinePointCollision()
{
	return (PlayerCollider_->CollisionResult("MoveMinePoint", ColList, CollisionType::Rect, CollisionType::Rect));
}

bool Player::MoveMine1Collision()
{
	return (PlayerCollider_->CollisionResult("MoveMine1", ColList, CollisionType::Rect, CollisionType::Rect));
}

bool Player::MoveMine2Collision()
{
	return (PlayerCollider_->CollisionResult("MoveMine2", ColList, CollisionType::Rect, CollisionType::Rect));
}

bool Player::MoveMine3Collision()
{
	return (PlayerCollider_->CollisionResult("MoveMine3", ColList, CollisionType::Rect, CollisionType::Rect));
}

bool Player::MoveMine4Collision()
{
	return (PlayerCollider_->CollisionResult("MoveMine4", ColList, CollisionType::Rect, CollisionType::Rect));
}

bool Player::MouseClickAndColl()
{
	return ((PlayerCollider_->CollisionResult("ShopFlag", ColList, CollisionType::Rect, CollisionType::Rect))
		&& (MainMouse_->isMouseRightClick()));
}

