#include  "Player.h"
#include "MainUI.h"
#include "NpcData.h"
#include "PlayerEnergyFrame.h"

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
		for (int Count = Money_; Count >= Money_-_Money; --Count)
		{
			MainUI* MainUI_ = GetLevel()->FindActor<MainUI>("MainUI");
			MainUI_->SetMainUIMoney(Count);

			Shop::MainShop->SetShopMoney(Count);
		}
			Money_ -= _Money;

		return true;
	}

	else
	{
		return false;
	}

}

void Player::AddMoney(int _Money)
{
	for (int Count = Money_; Count <= Money_+_Money; ++Count)
	{

		MainUI* MainUI_ = GetLevel()->FindActor<MainUI>("MainUI");
		MainUI_->SetMainUIMoney(Count);

		//Shop* MainShop = GetLevel()->FindActor<Shop>("Shop");
		Shop::MainShop->SetShopMoney(Count);
	}
		Money_ += _Money;
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

void Player::SetisEvent(bool _Flag)
{
	isEvent_ = _Flag;
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

		Shop::MainShop->ShopOn();
		isShopping_ = true;
		isEvent_ = true;
		PlayerShoppingState_ = PLAYER_SHOPPING::SHOPPING;

		break;

	case PLAYER_SHOPPING::SHOP_OFF:

		Shop::MainShop->ShopOff();
		isEvent_ = false;
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
	if (MoveFarmCollision())
	{
		GameEngine::GetInst().ChangeLevel("MyFarmLevel");
	}

	if (MoveHouseCollision() && GameEngineInput::GetInst()->IsDown("LeftClick"))
	{
		GameEngine::GetInst().ChangeLevel("MyHouseLevel");
	}

	if (MoveBusStopCollision())
	{
		GameEngine::GetInst().ChangeLevel("BusStopLevel");
	}

	if (MoveTownCollision())
	{
		GameEngine::GetInst().ChangeLevel("TownLevel");
	}

	if (MoveShopCollision() && GameEngineInput::GetInst()->IsDown("LeftClick"))
	{
		GameEngine::GetInst().ChangeLevel("ShopLevel");
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

	else
	{
		PlayerState_ = PLAYER_UPDATE::INIT;
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
				&& MainMouse_->isMouseClick() == true)
			{
				isEvent_ = !isEvent_;

				NpcIter->second->OpenDialogue();

			}

		}
	}


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

	int Color = MapColImage_->GetImagePixel(CheckPos);

	if ((RGB(0, 0, 0) != Color))
	{
		SetMove(Move * GameEngineTime::GetDeltaTime() * Speed_);
	}

	if ((RGB(0, 0, 255) == Color))
	{
		FarmingArea_ = true;
	}

	else
	{
		FarmingArea_ = false;

	}
}

void Player::PlayerDirCheck()
{
	if (isEvent_ == false)
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
		DirAnimationChange();

}


void Player::SetPlayerHandItemPos()
{
	PlayerHandItem_->SetPosition({ this->GetPosition().x, this->GetPosition().y - 92.f });

}

void Player::SubEnergy(int _Energy)
{

	Energy_ -= _Energy;
	PlayerEnergyFrame::MainPlayerEnergyBar->GetRenderer()->SetScale({18, static_cast<float>(Energy_) });

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

bool Player::MoveBackForestCollision()
{

	return (PlayerCollider_->CollisionResult("MoveForest", ColList, CollisionType::Rect, CollisionType::Rect));
}

bool Player::MouseClickAndColl()
{
	return ((PlayerCollider_->CollisionResult("ShopFlag", ColList, CollisionType::Rect, CollisionType::Rect))
		&& (MainMouse_->isMouseClick()));
}

