#include "Player.h"

#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineLevel.h> 
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>

#include "PlayerSpriteData.h"
#include "TileData.h"

std::string Player::CurrentLevel_ = "";
std::string Player::PrevLevel_ = "";


//PLAYERSTATE Player::PlayerState_ = PLAYERSTATE::INIT;
//GameEngineRenderer* Player::PlayerRenderer_ = nullptr;
//GameEngineCollision* Player::PlayerCollider_ = nullptr;
//Inventory* Player::Inventory_ = nullptr;
//Mouse* Player::Mouse_ = nullptr;
//FixedPlayerColl* Player::FixedPlayerColl_ = nullptr;

Player::Player()
	:
	PlayerState_(PLAYERSTATE::COLLINIT),
	AnimationFrame_(0.120f),
	Speed_(150.f),
	Energy_(150.f),
	PlayerRenderer_(nullptr),
	PlayerCollider_(nullptr),
	//Inventory_(nullptr),
	Mouse_(nullptr),
	ObjectColl_(false),
	FarmingArea_(false),
	MoveDir_(float4::DOWN)

{
	ArrAnimationName[static_cast<int>(PLAYERSTATE::INIT)] = "INIT";
	ArrAnimationName[static_cast<int>(PLAYERSTATE::WALK)] = "WALK";
	ArrAnimationName[static_cast<int>(PLAYERSTATE::HOE)] = "HOE";

}


Player::~Player() 
{
	CurrentLevel_ = "";

	std::map<int, FarmTile*>::iterator StartIter = TileList_.begin();
	std::map<int, FarmTile*>::iterator EndIter = TileList_.end();


	for (; StartIter != EndIter; ++StartIter)
	{
		delete StartIter->second->GetTile();
	}
	//TileList_.clear();
}

void Player::Start()
{
	//------< 초기화 >------------------------------------------------------------------

	Inventory_ = GetLevel()->CreateActor<Inventory>((int)PLAYLEVEL::INVENTORY);
	Mouse_ = GetLevel()->CreateActor<Mouse>((int)PLAYLEVEL::MOUSE);

	MapColImage_ = GameEngineImageManager::GetInst()->Find("PlayerHouse_Coll.bmp");

	PlayerRenderer_ = CreateRenderer();
	PlayerRenderer_->SetPivotType(RenderPivot::BOT);

	PlayerCollider_ = CreateCollision("Player", { 48, 96 });

	Mouse_->Renderer()->CameraEffectOff();

	Hoe_ = Inventory_->NewItem<Hoe>(float4{ 0, 24.f });

	CameraPos_ = GetPosition() - GameEngineWindow::GetInst().GetScale().Half();

	SetPlayerStartPos();
	SetScale({ 40, 20 });


	//------< 애니메이션 생성 >------------------------------------------------------------------

	//================================
	//     플레이어 대기
	//================================
	PlayerRenderer_->CreateAnimation("Player.bmp", "FRONT_INIT", PLAYER::FRONT_INIT, PLAYER::FRONT_INIT, 0.0f, false);
	PlayerRenderer_->CreateAnimation("Player.bmp", "RIGHT_INIT", PLAYER::RIGHT_INIT, PLAYER::RIGHT_INIT, 0.0f, false);
	PlayerRenderer_->CreateAnimation("Player.bmp", "LEFT_INIT", PLAYER::LEFT_INIT, PLAYER::LEFT_INIT, 0.0f, false);
	PlayerRenderer_->CreateAnimation("Player.bmp", "BACK_INIT", PLAYER::BACK_INIT, PLAYER::BACK_INIT, 0.0f, false);

	//================================
	//     플레이어 이동 
	//================================
	PlayerRenderer_->CreateAnimation("Player.bmp", "FRONT_WALK", PLAYER::FRONT_WALK0, PLAYER::FRONT_WALK3, AnimationFrame_, true);
	PlayerRenderer_->CreateAnimation("Player.bmp", "RIGHT_WALK", PLAYER::RIGHT_WALK0, PLAYER::RIGHT_WALK5, AnimationFrame_, true);
	PlayerRenderer_->CreateAnimation("Player.bmp", "LEFT_WALK", PLAYER::LEFT_WALK0, PLAYER::LEFT_WALK5, AnimationFrame_, true);
	PlayerRenderer_->CreateAnimation("Player.bmp", "BACK_WALK", PLAYER::BACK_WALK0, PLAYER::BACK_WALK3, AnimationFrame_, true);

	//================================
	//     플레이어 툴 사용
	//================================
	PlayerRenderer_->CreateAnimation("Player.bmp", "FRONT_HOE", PLAYER::HOE_FRONT0, PLAYER::HOE_FRONT5, AnimationFrame_, true);
	PlayerRenderer_->CreateAnimation("Player.bmp", "RIGHT_HOE", PLAYER::HOE_RIGHT0, PLAYER::HOE_RIGHT4, AnimationFrame_, true);
	PlayerRenderer_->CreateAnimation("Player.bmp", "LEFT_HOE", PLAYER::HOE_LEFT0, PLAYER::HOE_LEFT4, AnimationFrame_, true);
	PlayerRenderer_->CreateAnimation("Player.bmp", "BACK_HOE", PLAYER::HOE_BACK0, PLAYER::HOE_BACK2, AnimationFrame_, true);


	//------< 애니메이션 초기화 >------------------------------------------------------------------

	PlayerRenderer_->ChangeAnimation("FRONT_INIT");
	//PlayerMove_.SetFrontDir(true);
}


void Player::Update()
{
	PlayerDirCheck();
	SetCamera();
	ChangeTile();

	switch (PlayerState_)
	{
	case PLAYERSTATE::COLLINIT:
		
		CurrentLevel_ = GetCurrentLevel();
		Speed_ = 150.f;

		if (CurrentLevel_ == "MyFarmLevel") 
		{
			MapColImage_ = GameEngineImageManager::GetInst()->Find("FarmBack_Coll.bmp");
		}

		if (CurrentLevel_ == "MyHouseLevel") 
		{
			MapColImage_ = GameEngineImageManager::GetInst()->Find("PlayerHouse_Coll.bmp");
		}

		PlayerState_ = PLAYERSTATE::INIT;
		break;

	case PLAYERSTATE::INIT:

		ChangeLevelAndColl();


		if (Mouse_->MouseClickInventoryOut() && FarmingArea_ == true)
		{
			PlayerState_ = PLAYERSTATE::HOE;
		}

		if (isMove())
		{
			PlayerState_ = PLAYERSTATE::WALK;
		}

		break;

	case PLAYERSTATE::HOE:

		//PlayerRenderer_->ChangeAnimation("LEFT_HOE");


		if (PlayerRenderer_->IsEndAnimation())
		{
			CreateDirtTile();

			PlayerState_ = PLAYERSTATE::INIT;
		}

		break;

	case PLAYERSTATE::WALK:

		PlayerWalk();
		SubEnergy();


		if (isStop())
		{
			PlayerState_ = PLAYERSTATE::INIT;
		}

		break;


	default:
		break;
	}



}

void Player::Render()
{
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

	

	int Color = MapColImage_->GetImagePixel(CheckPos);





	if ((RGB(0, 0, 0) != Color ) )
	{
		SetMove(Move * GameEngineTime::GetDeltaTime() * Speed_);
	}


	
	// if ((RGB(0, 255, 255) == Color))
	//{
	//	GameEngine::GetInst().ChangeLevel("MyHouseLevel");
	//}

	if ((RGB(0, 0, 255) == Color) )
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

void Player::SetDirAnimation()
{

	if (MoveDir_.CompareInt2D(float4::RIGHT) ) 
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
		float MapSizeX = FARM_SIZE_WEIGHT;
		float MapSizeY = FARM_SIZE_HEIGHT;


		CameraPos_ = GetPosition() - GameEngineWindow::GetInst().GetScale().Half();

		if (CameraPos_.x <= 0)
		{
			CameraPos_.x = 0;
		}
		if (CameraPos_.x >= MapSizeX - GameEngineWindow::GetInst().GetScale().ix())
		{
			CameraPos_.x = MapSizeX - GameEngineWindow::GetInst().GetScale().ix();
		}
		if (CameraPos_.y <= 0)
		{
			CameraPos_.y = 0;
		}
		if (CameraPos_.y >= MapSizeY - GameEngineWindow::GetInst().GetScale().iy())
		{
			CameraPos_.y = MapSizeY - GameEngineWindow::GetInst().GetScale().iy();
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

void Player::PlayerCollCheck()
{
	float4 CheckPos ;

	float4 NextPos = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);


	//if (float4::DOWN.CompareInt2D(MoveDir_))
	//{
	//	NextPos += float4(0.0f, 24.0f);
	//}
	//if (float4::RIGHT.CompareInt2D(MoveDir_))
	//{
	//	NextPos += float4(24.0f, 0.0f);
	//}
	//if (float4::LEFT.CompareInt2D(MoveDir_))
	//{
	//	NextPos += float4(-24.0f, 0.0f);
	//}
	//if (float4::UP.CompareInt2D(MoveDir_))
	//{
	//	NextPos += float4(0.0f, 24.0f);
	//}

	CheckPos = NextPos;

	int Color = MapColImage_->GetImagePixel(CheckPos);


}

void Player::ChangeLevelAndColl()
{
	if (MoveFarmCollision()) 
	{
		PlayerState_ = PLAYERSTATE::COLLINIT;
		GameEngine::GetInst().ChangeLevel("MyFarmLevel");
	}

	if (MoveHouseCollision())
	{
		PlayerState_ = PLAYERSTATE::COLLINIT;

		GameEngine::GetInst().ChangeLevel("MyHouseLevel");
	}
}

void Player::SetPlayerStartPos()
{



}

void Player::CreateDirtTile()
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



	TileIndex Index = TileMap_->GetTileIndex({ Pos.x , Pos.y });
	int ChangeIndex = Index.X + (Index.Y * FARM_CHIP_NUM_Y);

	std::map<int, FarmTile*>::iterator FindIter = TileList_.find(ChangeIndex);
	std::map<int, FarmTile*>::iterator EndIter = TileList_.end();

	//찾아서 타일맵이 이미 형성되어 있다면 + 그게 그냥 판 땅이라면, 새로운 타일맵을 생성하지 않음

	if (FindIter != EndIter)
	{
		if (FindIter->second->GetTileState() == TILE_STATE::HOE_DIRT_CREATE)
		{
			return;
		}
	}

	else {
		FarmTile* Tile = TileMap_->CreateTile<FarmTile>(static_cast<int>(Pos.x / CHIP_SIZE), static_cast<int>(Pos.y / CHIP_SIZE)
			, "hoeDirt.bmp", 0, (int)PLAYLEVEL::OBJECT);
		Tile->TileState_ = TILE_STATE::HOE_DIRT_CREATE;

		Index = TileMap_->GetTileIndex({ Pos.x , Pos.y });
		ChangeIndex = Index.X + (Index.Y * FARM_CHIP_NUM_Y);

		TileList_.insert(std::make_pair(ChangeIndex, Tile));
	}
	//delete Tile;
}


void Player::DirAnimationChange()
{

	//if (PlayerState_ == PLAYERSTATE::INVENTROY_MINI_INIT) { return ; }
	//if (PlayerState_ == PLAYERSTATE::INVENTROY_POPUP_INIT) { return; }
	//if (PlayerState_ == PLAYERSTATE::INVENTROY_POPUP) { return; }

	if (PlayerState_ == PLAYERSTATE::COLLINIT) 
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


void Player::ChangeTile()
{

	//위치 초기화
	//std::map<int, FarmTile*>::iterator StartIter = TileList_.begin();
	std::map<int, FarmTile*>::iterator EndIter = TileList_.end();



	for (int i = 0; i < FARM_CHIP_NUM_X * FARM_CHIP_NUM_Y; ++i)
	{

		std::map<int, FarmTile*>::iterator FindLeftIter = TileList_.find(i - 1);
		std::map<int, FarmTile*>::iterator FindThisIter = TileList_.find(i);
		std::map<int, FarmTile*>::iterator FindRightIter = TileList_.find(i + 1);
		std::map<int, FarmTile*>::iterator FindTopIter = TileList_.find(i - FARM_CHIP_NUM_Y);
		std::map<int, FarmTile*>::iterator FindBottomIter = TileList_.find(i + FARM_CHIP_NUM_Y);


		//현재 찾으려는 타일이 없으면 패스
		if (FindThisIter == EndIter) continue;

		//------< 위 아래 아무것도 없을때 x축, 원라인 >------------------------------------------------------------------

		if (FindTopIter == EndIter && FindBottomIter == EndIter)
		{
			//===================================================
			//   case 1 왼쪽 타일은 없는데 오른쪽 타일은 있는경우
			//===================================================

			if (FindLeftIter == EndIter && FindRightIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::W_LINE_LEFT));

			}

			//===================================================
			//   case 2 왼쪽타일은 있는데 오른쪽 타일은 없는경우
			//===================================================

			if (FindLeftIter != EndIter && FindRightIter == EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::W_LINE_RIGHT));

			}

			//===================================================
			//   case 3 왼쪽 오른쪽 둘 다 있는 경우
			//===================================================

			if (FindLeftIter != EndIter && FindRightIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::W_LINE_MIDDLE));

			}


		}

		//------< 양 옆 아무것도 없을때 y축, 원라인 >------------------------------------------------------------------

		if (FindLeftIter == EndIter && FindRightIter == EndIter)
		{

			//===================================================
			//   case 1 위쪽 타일은 없는데 아래쪽 타일은 있는경우
			//===================================================

			if (FindTopIter == EndIter && FindBottomIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::H_LINE_TOP));

			}


			//===================================================
			//   case 2 위쪽타일은 있는데 아래쪽 타일은 없는경우
			//===================================================

			if (FindTopIter != EndIter && FindBottomIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::H_LINE_MIDDLE));

			}


			//===================================================
			//   case 3 위쪽 아래쪽 둘 다 있는 경우
			//===================================================

			if (FindTopIter != EndIter && FindBottomIter == EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::H_LINE_BOTTOM));

			}


		}



		//------< 아래는 있는데 위가 없을경우 >------------------------------------------------------------------


		if (FindTopIter == EndIter && FindBottomIter != EndIter)
		{

			//===================================================
			//   case 1 왼쪽 타일은 없는데 오른쪽 타일은 있는경우
			//===================================================
			if (FindLeftIter == EndIter && FindRightIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::LEFT_TOP));

			}


			//===================================================
			//   case 2 왼쪽타일은 있는데 오른쪽 타일은 없는경우
			//===================================================

			if (FindLeftIter != EndIter && FindRightIter == EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::RIGHT_TOP));

			}


			//===================================================
			//   case 3 왼쪽 오른쪽 둘 다 있는 경우
			//===================================================
			if (FindLeftIter != EndIter && FindRightIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::MIDDLE_TOP));

			}


		}

		//------< 위는 있는데 아래는 없는 경우 >------------------------------------------------------------------

		if (FindTopIter != EndIter && FindBottomIter == EndIter)
		{

			//===================================================
			//   case 1 왼쪽 타일은 없는데 오른쪽 타일은 있는경우
			//===================================================
			if (FindLeftIter == EndIter && FindRightIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::LEFT_BOTTOM));

			}


			//===================================================
			//   case 2 왼쪽타일은 있는데 오른쪽 타일은 없는경우
			//===================================================

			if (FindLeftIter != EndIter && FindRightIter == EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::RIGHT_BOTTOM));

			}


			//===================================================
			//   case 3 왼쪽 오른쪽 둘 다 있는 경우
			//===================================================
			if (FindLeftIter != EndIter && FindRightIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::MIDDLE_BOTTOM));

			}

		}


		//------< 위아래 둘다 있는 경우 >------------------------------------------------------------------

		if (FindTopIter != EndIter && FindBottomIter != EndIter)
		{

			//===================================================
			//   case 1 왼쪽 타일은 없는데 오른쪽 타일은 있는경우
			//===================================================
			if (FindLeftIter == EndIter && FindRightIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::LEFT_MIDDLE));

			}


			//===================================================
			//   case 2 왼쪽타일은 있는데 오른쪽 타일은 없는경우
			//===================================================

			if (FindLeftIter != EndIter && FindRightIter == EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::RIGHT_MIDDLE));

			}


			//===================================================
			//   case 3 왼쪽 오른쪽 둘 다 있는 경우
			//===================================================
			if (FindLeftIter != EndIter && FindRightIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::MIDDLE_MIDDLE));

			}

		}

		//------< 위의 모든 경우에 속하지 않는다 >------------------------------------------------------------------

		if (FindLeftIter == EndIter || FindRightIter == EndIter || FindTopIter == EndIter || FindBottomIter == EndIter)
		{
			continue;
		}

	}


}

