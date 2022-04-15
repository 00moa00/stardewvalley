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

Player* Player::MainPlayer = nullptr;
Inventory* Player::MainInventory = nullptr;



//PLAYER_UPDATE Player::PlayerState_ = PLAYER_UPDATE::INIT;
//GameEngineRenderer* Player::PlayerRenderer_ = nullptr;
//GameEngineCollision* Player::PlayerCollider_ = nullptr;
//Inventory* Player::Inventory_ = nullptr;
//Mouse* Player::Mouse_ = nullptr;
//FixedPlayerColl* Player::FixedPlayerColl_ = nullptr;

Player::Player()
	:
	PlayerState_(PLAYER_UPDATE::LEVELINIT),
	AnimationFrame_(0.120f),
	Speed_(150.f),
	Energy_(150.f),
	PlayerRenderer_(nullptr),
	PlayerCollider_(nullptr),
	MapColImage_(nullptr),
	Inventory_(nullptr),
	Mouse_(nullptr),
	ObjectColl_(false),
	FarmingArea_(false),
	MoveDir_(float4::DOWN),
	MapSizeX_(0.f),
	UsingAxe_(false),
	MapSizeY_(0.f),
	UseToolState_(USE_TOOL::INIT),
	TileState_(TILE_COLL::INIT)



{
	ArrAnimationName[static_cast<int>(PLAYER_UPDATE::INIT)] = "INIT";
	ArrAnimationName[static_cast<int>(PLAYER_UPDATE::WALK)] = "WALK";
	ArrAnimationName[static_cast<int>(PLAYER_UPDATE::HOE)] = "HOE";
	ArrAnimationName[static_cast<int>(PLAYER_UPDATE::WATER)] = "WATER";
	ArrAnimationName[static_cast<int>(PLAYER_UPDATE::AXE)] = "AXE";


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
}

void Player::Start()
{
	//------< 액터 등록 >------------------------------------------------------------------

	//Font_ = GetLevel()->CreateActor<Font>((int)PLAYLEVEL::INVENTORY);
	Inventory_ = GetLevel()->CreateActor<Inventory>((int)PLAYLEVEL::INVENTORY);
	Mouse_ = GetLevel()->CreateActor<Mouse>((int)PLAYLEVEL::MOUSE);

	//------< 액터 초기화 >------------------------------------------------------------------

	//Font_->ChangeNum(10);
	//Font_->SetPosition(GameEngineWindow::GetInst().GetScale().Half());
	MapColImage_ = GameEngineImageManager::GetInst()->Find("PlayerHouse_Coll.bmp");
	PlayerRenderer_ = CreateRenderer();
	PlayerRenderer_->SetPivotType(RenderPivot::BOT);
	PlayerCollider_ = CreateCollision("Player", { 48, 96 });

	Mouse_->Renderer()->CameraEffectOff();
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
	//     플레이어 호미 사용
	//================================
	PlayerRenderer_->CreateAnimation("Player.bmp", "FRONT_HOE", PLAYER::HOE_FRONT0, PLAYER::HOE_FRONT5, AnimationFrame_, true);
	PlayerRenderer_->CreateAnimation("Player.bmp", "RIGHT_HOE", PLAYER::HOE_RIGHT0, PLAYER::HOE_RIGHT4, AnimationFrame_, true);
	PlayerRenderer_->CreateAnimation("Player.bmp", "LEFT_HOE", PLAYER::HOE_LEFT0, PLAYER::HOE_LEFT4, AnimationFrame_, true);
	PlayerRenderer_->CreateAnimation("Player.bmp", "BACK_HOE", PLAYER::HOE_BACK0, PLAYER::HOE_BACK2, AnimationFrame_, true);


	//================================
	//     플레이어 물뿌리개 사용
	//================================

	PlayerRenderer_->CreateAnimation("Player.bmp", "FRONT_WATER", PLAYER::WATER_FRONT0, PLAYER::WATER_FRONT2, 0.200f, true);
	PlayerRenderer_->CreateAnimation("Player.bmp", "RIGHT_WATER", PLAYER::WATER_RIGHT0, PLAYER::WATER_RIGHT2, 0.200f, true);
	PlayerRenderer_->CreateAnimation("Player.bmp", "LEFT_WATER", PLAYER::WATER_LEFT0, PLAYER::WATER_LEFT2, 0.200f, true);
	PlayerRenderer_->CreateAnimation("Player.bmp", "BACK_WATER", PLAYER::WATER_BACK0, PLAYER::WATER_BACK2, 0.200f, true);



	//================================
	//     플레이어 도끼 사용
	//================================
	PlayerRenderer_->CreateAnimation("Player.bmp", "FRONT_AXE", PLAYER::HOE_FRONT0, PLAYER::HOE_FRONT5, AnimationFrame_, true);
	PlayerRenderer_->CreateAnimation("Player.bmp", "RIGHT_AXE", PLAYER::HOE_RIGHT0, PLAYER::HOE_RIGHT4, AnimationFrame_, true);
	PlayerRenderer_->CreateAnimation("Player.bmp", "LEFT_AXE", PLAYER::HOE_LEFT0, PLAYER::HOE_LEFT4, AnimationFrame_, true);
	PlayerRenderer_->CreateAnimation("Player.bmp", "BACK_AXE", PLAYER::HOE_BACK0, PLAYER::HOE_BACK2, AnimationFrame_, true);




	//------< 애니메이션 초기화 >------------------------------------------------------------------

	PlayerRenderer_->ChangeAnimation("FRONT_INIT");
	//PlayerMove_.SetFrontDir(true);
	LevelRegist("MainPlayer");
}



void Player::Update()
{

	PlayerDirCheck();
	ObjectTileColl();
	SetCamera();
	ChangeTile();
	PlayerUpdate();
}

void Player::Render()
{

}

void Player::LevelChangeStart()
{

	//if(MainPlayer != nullptr) Inventory_->operator= (*MainPlayer->Inventory_);

}

void Player::LevelChangeEnd()
{
	if (MainPlayer != nullptr) Inventory_->operator= (*MainPlayer->Inventory_);
	MainPlayer = this;
}




void Player::PlayerUpdate()
{

	switch (PlayerState_)
	{
	case PLAYER_UPDATE::LEVELINIT:

		Speed_ = 150.f;
		CurrentLevel_ = GetCurrentLevel();

		CollInit();

		PlayerState_ = PLAYER_UPDATE::INIT;
		break;

	case PLAYER_UPDATE::INIT:

		ChangeLevel();
		MapObject_;

		if (Mouse_->MouseClickInventoryOut() && FarmingArea_ == true)
		{
			CheckTool();//툴에 맞게 스테이트 이동
		}

		if (isMove())
		{
			PlayerState_ = PLAYER_UPDATE::WALK;
		}

		break;

	case PLAYER_UPDATE::HOE:

		if (PlayerRenderer_->IsEndAnimation())
		{
			CreateDirtTile();
			PlayerState_ = PLAYER_UPDATE::INIT;
		}

		break;

	case PLAYER_UPDATE::WATER:

		if (PlayerRenderer_->IsEndAnimation())
		{
			CreateWaterTile();
			PlayerState_ = PLAYER_UPDATE::INIT;
		}

		break;


	case PLAYER_UPDATE::AXE:

		if (PlayerRenderer_->IsEndAnimation())
		{
			CrushWood();
		}

		break;


	case PLAYER_UPDATE::WALK:

		PlayerWalk();
		SubEnergy();


		if (isStop())
		{
			PlayerState_ = PLAYER_UPDATE::INIT;
		}

		break;

	default:
		break;
	}

}

