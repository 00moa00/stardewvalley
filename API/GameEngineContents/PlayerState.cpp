#include  "Player.h"


//******************************************************************************
//
//
//		플레이어 관련 함수 구현부
//
//
//******************************************************************************






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

TOOLTYPE Player::CurrentItemType()
{
	CurrentItemType_ = Player::Inventory_->CurrentItem()->GetToolType();

	return CurrentItemType_;

}

void Player::SetDirAnimation()
{

	if (MoveDir_.CompareInt2D(float4::RIGHT))
	{
		PlayerRenderer_->ChangeAnimation("RIGHT_INIT");
	}

	if (MoveDir_.CompareInt2D(float4::DOWN))
	{
		PlayerRenderer_->ChangeAnimation("FRONT_INIT");

	}

	if (MoveDir_.CompareInt2D(float4::UP))
	{
		PlayerRenderer_->ChangeAnimation("BACK_INIT");
	}

	if (MoveDir_.CompareInt2D(float4::LEFT))
	{
		PlayerRenderer_->ChangeAnimation("LEFT_INIT");
	}

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

	MovePrevDir_ = MoveDir_;
	DirAnimationChange();

}


float4 Player::PlayerCollCheckPos()
{
	float4 Length = MoveDir_;

	if (float4::DOWN.CompareInt2D(MoveDir_))
	{
		Length += float4(0.0f, 24.0f);
	}
	if (float4::RIGHT.CompareInt2D(MoveDir_))
	{
		Length += float4(24.0f, 0.0f);
	}
	if (float4::LEFT.CompareInt2D(MoveDir_))
	{
		Length += float4(-24.0f, 0.0f);
	}
	if (float4::UP.CompareInt2D(MoveDir_))
	{
		Length += float4(0.0f, -24.0f);
	}

	float4 Pos = { GetPosition().x + Length.x, GetPosition().y + Length.y };

	return Pos;

}

void Player::ChangeLevel()
{
	if (MoveFarmCollision())
	{
		PlayerState_ = PLAYER_UPDATE::LEVELINIT;
		GameEngine::GetInst().ChangeLevel("MyFarmLevel");
	}

	if (MoveHouseCollision())
	{
		PlayerState_ = PLAYER_UPDATE::LEVELINIT;
		GameEngine::GetInst().ChangeLevel("MyHouseLevel");
	}

	if (MoveBusStopCollision())
	{
		PlayerState_ = PLAYER_UPDATE::LEVELINIT;
		GameEngine::GetInst().ChangeLevel("BusStopLevel");
	}

	if (MoveTownCollision())
	{
		PlayerState_ = PLAYER_UPDATE::LEVELINIT;
		GameEngine::GetInst().ChangeLevel("TownLevel");
	}

	if (MoveShopCollision())
	{
		PlayerState_ = PLAYER_UPDATE::LEVELINIT;
		GameEngine::GetInst().ChangeLevel("ShopLevel");
	}

}


void Player::SetPlayerStartPos()
{



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


	PlayerRenderer_->ChangeAnimation(GetDirString() + ArrAnimationName[static_cast<int>(PlayerState_)]);


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


void Player::CollInit()
{
	if (CurrentLevel_ == "MyFarmLevel")
	{
		MapSizeX_ = FARM_SIZE_WEIGHT;
		MapSizeY_ = FARM_SIZE_HEIGHT;

		MapColImage_ = GameEngineImageManager::GetInst()->Find("FarmBack_Coll.bmp");
	}


	if (CurrentLevel_ == "MyHouseLevel")
	{
		MapColImage_ = GameEngineImageManager::GetInst()->Find("PlayerHouse_Coll.bmp");
	}


	if (CurrentLevel_ == "BusStopLevel")
	{
		MapSizeX_ = BUSSTOP_SIZE_WEIGHT;
		MapSizeY_ = BUSSTOP_SIZE_HEIGHT;

		MapColImage_ = GameEngineImageManager::GetInst()->Find("BusStop_Coll.bmp");
	}


	if (CurrentLevel_ == "TownLevel")
	{
		MapSizeX_ = TOWN_SIZE_WEIGHT;
		MapSizeY_ = TOWN_SIZE_HEIGHT;

		MapColImage_ = GameEngineImageManager::GetInst()->Find("Town_Col.bmp");
	}

	if (CurrentLevel_ == "ShopLevel")
	{
		MapSizeX_ = SHOP_SIZE_WEIGHT;
		MapSizeY_ = SHOP_SIZE_HEIGHT;

		MapColImage_ = GameEngineImageManager::GetInst()->Find("Shop_Coll.bmp");
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

	else
	{
		PlayerState_ = PLAYER_UPDATE::INIT;
	}



}


void  Player::SetObjectColl(bool b)
{
	ObjectColl_ = b;
}


bool  Player::GetObjectColl()
{
	return ObjectColl_;
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

PLAYER_UPDATE Player::GetPlayerState()
{
	return PlayerState_;
}

Inventory* Player::GetInventroy()
{
	return Inventory_;
}


GameEngineRenderer* Player::Renderer() {
	return PlayerRenderer_;
}

GameEngineImage* Player::CollImage() {
	return MapColImage_;
}


std::string  Player::GetCurrentLevel()
{
	return GetLevel()->GetNameConstRef();
}


float  Player::GetEnergy()
{
	return Energy_;
}

int Player::GetMoney()
{
	return Money_;
}



void  Player::CopyList(std::map<int, Items*> _OtherList)
{
	std::copy(_OtherList.begin(), _OtherList.end(), std::inserter(MapObject_, MapObject_.begin()));
}


void Player::SubEnergy() {
	Energy_ -= 3.0f * GameEngineTime::GetDeltaTime();
}

void Player::SetPlayerHandItemPos()
{
	PlayerHandItem_->SetPosition({ this->GetPosition().x, this->GetPosition().y - 92.f });

}


bool Player::PlayerMouseClickCollision() {

	return (PlayerCollider_->CollisionResult("MouseCursor", ColList, CollisionType::Rect, CollisionType::Rect))
		&& (Mouse_->isMouseClick());
}

bool Player::MoveFarmCollision() {

	return (PlayerCollider_->CollisionResult("MoveFarm", ColList, CollisionType::Rect, CollisionType::Rect));
}

bool Player::MoveHouseCollision() {

	return (PlayerCollider_->CollisionResult("MoveHouse", ColList, CollisionType::Rect, CollisionType::Rect));
}


bool Player::MoveBusStopCollision() {

	return (PlayerCollider_->CollisionResult("MoveBusStop", ColList, CollisionType::Rect, CollisionType::Rect));
}


bool Player::MoveTownCollision() {

	return (PlayerCollider_->CollisionResult("MoveTown", ColList, CollisionType::Rect, CollisionType::Rect));
}

bool Player::MoveShopCollision()
{
	return (PlayerCollider_->CollisionResult("MoveShop", ColList, CollisionType::Rect, CollisionType::Rect));
}


bool Player::MoveBackForestCollision() {

	return (PlayerCollider_->CollisionResult("MoveForest", ColList, CollisionType::Rect, CollisionType::Rect));
}

