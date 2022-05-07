#include "Player.h"

#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineLevel.h> 
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>

#include "PlayerSpriteData.h"
#include "TileData.h"
#include "CustomData.h"

std::string Player::CurrentLevel_ = "TitleLevel";
std::string Player::PrevLevel_ = "";

Player* Player::MainPlayer = nullptr;
PlayerHandItem* Player::PlayerHandItem_ = nullptr;
Mouse* Player::MainMouse_ = nullptr;

Player::Player()
	:
	Money_(1000),
	TotalMoney_(0),
	PrevMoney_(0),
	DelaySpeed_(0),
	HP_(126),
	Energy_(126),

	AnimationFrame_(0.120f),
	Speed_(220.f),
	MapSizeX_(0.f),
	MapSizeY_(0.f),

	DelaySpeedTimer_(0.f),
	AnimationWaitTimer_(0.f),
	InvincibilityTimer_(0.f),
	IsNotInvincibilityTimer_(0.f),
	SubHPTimer_(0.f),

	PlayerBodyRenderer_(nullptr),
	PlayerPantsRenderer_(nullptr),
	PlayerShirtsRenderer_(nullptr),
	PlayerHairRenderer_(nullptr),
	PlayerHandRenderer_(nullptr),

	ToolRenderer_(nullptr),
	PlayerCollider_(nullptr),
	MapColImage_(nullptr),

	FadeInOut_(nullptr),

	isEvent_(false),
	ObjectColl_(false),
	FarmingArea_(false),
	isShopping_(false),
	isDelaySpeed_(false),
	invincibility_(false),
	isNotInvincibility_(false),
	isSubTime_(false),

	WetTileMap_(nullptr),
	DirtTileMap_(nullptr),

	MoveDir_(float4::DOWN),

	LevelList_(LEVEL_LIST::TITLE_LEVEL),

	LevelChagne_(LEVEL_CHANGE_STATE::CHECK),
	CurrentItemType_(TOOLTYPE::OTHER),
	UseToolState_(USE_TOOL::INIT),
	TileState_(TILE_COLL::INIT),
	PlayerState_(PLAYER_UPDATE::INIT),
	PlayerShoppingState_(PLAYER_SHOPPING::INT),
	AddMoneyCount_(MONEY_UPDATE::WAIT),
	SubMoneyCount_(MONEY_UPDATE::WAIT)

{
	ArrAnimationName[static_cast<int>(PLAYER_UPDATE::INIT)] = "INIT";
	ArrAnimationName[static_cast<int>(PLAYER_UPDATE::WALK)] = "WALK";
	ArrAnimationName[static_cast<int>(PLAYER_UPDATE::WATER)] = "WATER";
	ArrAnimationName[static_cast<int>(PLAYER_UPDATE::HOE)] = "HOE";
	ArrAnimationName[static_cast<int>(PLAYER_UPDATE::AXE)] = "HOE";
	ArrAnimationName[static_cast<int>(PLAYER_UPDATE::PICKAXE)] = "HOE";
	ArrAnimationName[static_cast<int>(PLAYER_UPDATE::SWOARD)] = "SWOARD";

	ArrAnimationName[static_cast<int>(PLAYER_UPDATE::HANDITEM)] = "HANDITEM";
	ArrAnimationName[static_cast<int>(PLAYER_UPDATE::HANDITEMWALK)] = "HANDITEMWALK";
	ArrAnimationName[static_cast<int>(PLAYER_UPDATE::FAINT)] = "FAINT";
	ArrAnimationName[static_cast<int>(PLAYER_UPDATE::EAT_WAIT)] = "EAT_WAIT";
	ArrAnimationName[static_cast<int>(PLAYER_UPDATE::EAT)] = "EAT";
	ArrAnimationName[static_cast<int>(PLAYER_UPDATE::DRINK)] = "DRINK";
	ArrAnimationName[static_cast<int>(PLAYER_UPDATE::SHOPPING)] = "INIT";
	ArrAnimationName[static_cast<int>(PLAYER_UPDATE::GETITEM)] = "INIT";
	ArrAnimationName[static_cast<int>(PLAYER_UPDATE::TALKING)] = "INIT";


	ArrAnimationToolName[static_cast<int>(PLAYER_UPDATE::INIT)] = "INIT";
	ArrAnimationToolName[static_cast<int>(PLAYER_UPDATE::WALK)] = "INIT";
	ArrAnimationToolName[static_cast<int>(PLAYER_UPDATE::HANDITEM)] = "INIT";
	ArrAnimationToolName[static_cast<int>(PLAYER_UPDATE::HANDITEMWALK)] = "INIT";
	ArrAnimationToolName[static_cast<int>(PLAYER_UPDATE::WATER)] = "WATER";
	ArrAnimationToolName[static_cast<int>(PLAYER_UPDATE::HOE)] = "HOE";
	ArrAnimationToolName[static_cast<int>(PLAYER_UPDATE::AXE)] = "AXE";
	ArrAnimationToolName[static_cast<int>(PLAYER_UPDATE::PICKAXE)] = "PICKAXE";
	ArrAnimationToolName[static_cast<int>(PLAYER_UPDATE::SWOARD)] = "SWOARD";

	ArrAnimationToolName[static_cast<int>(PLAYER_UPDATE::FAINT)] = "INIT";
	ArrAnimationToolName[static_cast<int>(PLAYER_UPDATE::EAT_WAIT)] = "INIT";
	ArrAnimationToolName[static_cast<int>(PLAYER_UPDATE::EAT)] = "INIT";
	ArrAnimationToolName[static_cast<int>(PLAYER_UPDATE::DRINK)] = "INIT";
	ArrAnimationToolName[static_cast<int>(PLAYER_UPDATE::SHOPPING)] = "INIT";
	ArrAnimationToolName[static_cast<int>(PLAYER_UPDATE::GETITEM)] = "INIT";
	ArrAnimationToolName[static_cast<int>(PLAYER_UPDATE::TALKING)] = "INIT";


}	


Player::~Player() 
{
	CurrentLevel_ = "";


	//DirtList_.erase(DirtList_.begin(), DirtList_.end());

	if (WetDirtList_.empty() == false)
	{
		WetDirtList_.clear();
	}

	if (DirtList_.empty() == false)
	{
		DirtList_.clear();
	}

	if (SeedList_.empty() == false)
	{
		SeedList_.clear();
	}

}

void Player::Start()
{
	//------< 액터 등록 >------------------------------------------------------------------
	PlayerHandItem_ = GetLevel()->CreateActor<PlayerHandItem>((int)PLAYLEVEL::HAND_ITEM);
	MainMouse_ = GetLevel()->CreateActor<Mouse>((int)PLAYLEVEL::MOUSE);

	//------< 초기화 >------------------------------------------------------------------
	MapColImage_ = GameEngineImageManager::GetInst()->Find("PlayerHouse_Coll.bmp");
	PlayerCollider_ = CreateCollision("Player", { 40, 47 });
	PlayerCollider_->SetPivot({ 0, -24 });
	SetScale({ 40.f, 40.f });
	CameraPos_ = GetPosition() - GameEngineWindow::GetInst().GetScale().Half();
}

void Player::LevelChangeStart(GameEngineLevel* _PrevLevel)
{

	//------< 플레이어 렌더러 >------------------------------------------------------------------
	if (PlayerBodyRenderer_ == nullptr)
	{
		//------< 초기화 >------------------------------------------------------------------

		PlayerBodyRenderer_ = CreateRenderer();
		PlayerPantsRenderer_ = CreateRenderer();
		PlayerShirtsRenderer_ = CreateRenderer();
		PlayerHairRenderer_ = CreateRenderer();
		PlayerHandRenderer_ = CreateRenderer();


		PlayerBodyRenderer_->SetSortingPivot({ 0, -40 });
		PlayerPantsRenderer_->SetSortingPivot({ 0, -40 });
		PlayerShirtsRenderer_->SetSortingPivot({ 0, -40 });
		PlayerHairRenderer_->SetSortingPivot({ 0, -40 });
		PlayerHandRenderer_->SetSortingPivot({ 0, -40 });

		PlayerBodyRenderer_->SetPivotType(RenderPivot::BOT);
		PlayerPantsRenderer_->SetPivotType(RenderPivot::BOT);
		PlayerShirtsRenderer_->SetPivotType(RenderPivot::BOT);
		PlayerHairRenderer_->SetPivotType(RenderPivot::BOT);
		PlayerHandRenderer_->SetPivotType(RenderPivot::BOT);

		//------< 애니메이션 생성 >------------------------------------------------------------------
		//================================
		//     플레이어 대기
		//================================
		PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "RIGHT_INIT", static_cast<int>(PLAYER::RIGHT_INIT), static_cast<int>(PLAYER::RIGHT_INIT), 0.0f, false);
		PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "LEFT_INIT", static_cast<int>(PLAYER::LEFT_INIT), static_cast<int>(PLAYER::LEFT_INIT), 0.0f, false);
		PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "FRONT_INIT", static_cast<int>(PLAYER::FRONT_INIT), static_cast<int>(PLAYER::FRONT_INIT), 0.0f, false);
		PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "BACK_INIT", static_cast<int>(PLAYER::BACK_INIT), static_cast<int>(PLAYER::BACK_INIT), 0.0f, false);

		PlayerPantsRenderer_->CreateAnimation(CustomData::GetInst()->GetPantsFileName(), "RIGHT_INIT", static_cast<int>(PLAYER::RIGHT_INIT), static_cast<int>(PLAYER::RIGHT_INIT), 0.0f, false);
		PlayerPantsRenderer_->CreateAnimation(CustomData::GetInst()->GetPantsFileName(), "LEFT_INIT", static_cast<int>(PLAYER::LEFT_INIT), static_cast<int>(PLAYER::LEFT_INIT), 0.0f, false);
		PlayerPantsRenderer_->CreateAnimation(CustomData::GetInst()->GetPantsFileName(), "FRONT_INIT", static_cast<int>(PLAYER::FRONT_INIT), static_cast<int>(PLAYER::FRONT_INIT), 0.0f, false);
		PlayerPantsRenderer_->CreateAnimation(CustomData::GetInst()->GetPantsFileName(), "BACK_INIT", static_cast<int>(PLAYER::BACK_INIT), static_cast<int>(PLAYER::BACK_INIT), 0.0f, false);

		PlayerShirtsRenderer_->CreateAnimation(CustomData::GetInst()->GetShirtsFileName(), "RIGHT_INIT", static_cast<int>(PLAYER::RIGHT_INIT), static_cast<int>(PLAYER::RIGHT_INIT), 0.0f, false);
		PlayerShirtsRenderer_->CreateAnimation(CustomData::GetInst()->GetShirtsFileName(), "LEFT_INIT", static_cast<int>(PLAYER::LEFT_INIT), static_cast<int>(PLAYER::LEFT_INIT), 0.0f, false);
		PlayerShirtsRenderer_->CreateAnimation(CustomData::GetInst()->GetShirtsFileName(), "FRONT_INIT", static_cast<int>(PLAYER::FRONT_INIT), static_cast<int>(PLAYER::FRONT_INIT), 0.0f, false);
		PlayerShirtsRenderer_->CreateAnimation(CustomData::GetInst()->GetShirtsFileName(), "BACK_INIT", static_cast<int>(PLAYER::BACK_INIT), static_cast<int>(PLAYER::BACK_INIT), 0.0f, false);

		PlayerHairRenderer_->CreateAnimation(CustomData::GetInst()->GetHairFileName(), "RIGHT_INIT", static_cast<int>(PLAYER::RIGHT_INIT), static_cast<int>(PLAYER::RIGHT_INIT), 0.0f, false);
		PlayerHairRenderer_->CreateAnimation(CustomData::GetInst()->GetHairFileName(), "LEFT_INIT", static_cast<int>(PLAYER::LEFT_INIT), static_cast<int>(PLAYER::LEFT_INIT), 0.0f, false);
		PlayerHairRenderer_->CreateAnimation(CustomData::GetInst()->GetHairFileName(), "FRONT_INIT", static_cast<int>(PLAYER::FRONT_INIT), static_cast<int>(PLAYER::FRONT_INIT), 0.0f, false);
		PlayerHairRenderer_->CreateAnimation(CustomData::GetInst()->GetHairFileName(), "BACK_INIT", static_cast<int>(PLAYER::BACK_INIT), static_cast<int>(PLAYER::BACK_INIT), 0.0f, false);

		PlayerHandRenderer_->CreateAnimation(CustomData::GetInst()->GetHandFileName(), "RIGHT_INIT", static_cast<int>(PLAYER::RIGHT_INIT), static_cast<int>(PLAYER::RIGHT_INIT), 0.0f, false);
		PlayerHandRenderer_->CreateAnimation(CustomData::GetInst()->GetHandFileName(), "LEFT_INIT", static_cast<int>(PLAYER::LEFT_INIT), static_cast<int>(PLAYER::LEFT_INIT), 0.0f, false);
		PlayerHandRenderer_->CreateAnimation(CustomData::GetInst()->GetHandFileName(), "FRONT_INIT", static_cast<int>(PLAYER::FRONT_INIT), static_cast<int>(PLAYER::FRONT_INIT), 0.0f, false);
		PlayerHandRenderer_->CreateAnimation(CustomData::GetInst()->GetHandFileName(), "BACK_INIT", static_cast<int>(PLAYER::BACK_INIT), static_cast<int>(PLAYER::BACK_INIT), 0.0f, false);

		//================================
		//     플레이어 이동 
		//================================
		PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "RIGHT_WALK", static_cast<int>(PLAYER::RIGHT_WALK0), static_cast<int>(PLAYER::RIGHT_WALK5), AnimationFrame_, true);
		PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "LEFT_WALK", static_cast<int>(PLAYER::LEFT_WALK0), static_cast<int>(PLAYER::LEFT_WALK5), AnimationFrame_, true);
		PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "FRONT_WALK", static_cast<int>(PLAYER::FRONT_WALK0), static_cast<int>(PLAYER::FRONT_WALK3), AnimationFrame_, true);
		PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "BACK_WALK", static_cast<int>(PLAYER::BACK_WALK0), static_cast<int>(PLAYER::BACK_WALK3), AnimationFrame_, true);

		PlayerPantsRenderer_->CreateAnimation(CustomData::GetInst()->GetPantsFileName(), "RIGHT_WALK", static_cast<int>(PLAYER::RIGHT_WALK0), static_cast<int>(PLAYER::RIGHT_WALK5), AnimationFrame_, true);
		PlayerPantsRenderer_->CreateAnimation(CustomData::GetInst()->GetPantsFileName(), "LEFT_WALK", static_cast<int>(PLAYER::LEFT_WALK0), static_cast<int>(PLAYER::LEFT_WALK5), AnimationFrame_, true);
		PlayerPantsRenderer_->CreateAnimation(CustomData::GetInst()->GetPantsFileName(), "FRONT_WALK", static_cast<int>(PLAYER::FRONT_WALK0), static_cast<int>(PLAYER::FRONT_WALK3), AnimationFrame_, true);
		PlayerPantsRenderer_->CreateAnimation(CustomData::GetInst()->GetPantsFileName(), "BACK_WALK", static_cast<int>(PLAYER::BACK_WALK0), static_cast<int>(PLAYER::BACK_WALK3), AnimationFrame_, true);

		PlayerShirtsRenderer_->CreateAnimation(CustomData::GetInst()->GetShirtsFileName(), "RIGHT_WALK", static_cast<int>(PLAYER::RIGHT_WALK0), static_cast<int>(PLAYER::RIGHT_WALK5), AnimationFrame_, true);
		PlayerShirtsRenderer_->CreateAnimation(CustomData::GetInst()->GetShirtsFileName(), "LEFT_WALK", static_cast<int>(PLAYER::LEFT_WALK0), static_cast<int>(PLAYER::LEFT_WALK5), AnimationFrame_, true);
		PlayerShirtsRenderer_->CreateAnimation(CustomData::GetInst()->GetShirtsFileName(), "FRONT_WALK", static_cast<int>(PLAYER::FRONT_WALK0), static_cast<int>(PLAYER::FRONT_WALK3), AnimationFrame_, true);
		PlayerShirtsRenderer_->CreateAnimation(CustomData::GetInst()->GetShirtsFileName(), "BACK_WALK", static_cast<int>(PLAYER::BACK_WALK0), static_cast<int>(PLAYER::BACK_WALK3), AnimationFrame_, true);

		PlayerHairRenderer_->CreateAnimation(CustomData::GetInst()->GetHairFileName(), "RIGHT_WALK", static_cast<int>(PLAYER::RIGHT_WALK0), static_cast<int>(PLAYER::RIGHT_WALK5), AnimationFrame_, true);
		PlayerHairRenderer_->CreateAnimation(CustomData::GetInst()->GetHairFileName(), "LEFT_WALK", static_cast<int>(PLAYER::LEFT_WALK0), static_cast<int>(PLAYER::LEFT_WALK5), AnimationFrame_, true);
		PlayerHairRenderer_->CreateAnimation(CustomData::GetInst()->GetHairFileName(), "FRONT_WALK", static_cast<int>(PLAYER::FRONT_WALK0), static_cast<int>(PLAYER::FRONT_WALK3), AnimationFrame_, true);
		PlayerHairRenderer_->CreateAnimation(CustomData::GetInst()->GetHairFileName(), "BACK_WALK", static_cast<int>(PLAYER::BACK_WALK0), static_cast<int>(PLAYER::BACK_WALK3), AnimationFrame_, true);

		PlayerHandRenderer_->CreateAnimation(CustomData::GetInst()->GetHandFileName(), "RIGHT_WALK", static_cast<int>(PLAYER::RIGHT_WALK0), static_cast<int>(PLAYER::RIGHT_WALK5), AnimationFrame_, true);
		PlayerHandRenderer_->CreateAnimation(CustomData::GetInst()->GetHandFileName(), "LEFT_WALK", static_cast<int>(PLAYER::LEFT_WALK0), static_cast<int>(PLAYER::LEFT_WALK5), AnimationFrame_, true);
		PlayerHandRenderer_->CreateAnimation(CustomData::GetInst()->GetHandFileName(), "FRONT_WALK", static_cast<int>(PLAYER::FRONT_WALK0), static_cast<int>(PLAYER::FRONT_WALK3), AnimationFrame_, true);
		PlayerHandRenderer_->CreateAnimation(CustomData::GetInst()->GetHandFileName(), "BACK_WALK", static_cast<int>(PLAYER::BACK_WALK0), static_cast<int>(PLAYER::BACK_WALK3), AnimationFrame_, true);

		//================================
		//     플레이어 손 번쩍! 대기
		//================================
		PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "RIGHT_HANDITEM", static_cast<int>(PLAYER::RIGHT_HAND_INIT), static_cast<int>(PLAYER::RIGHT_HAND_INIT), 0.0f, false);
		PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "LEFT_HANDITEM", static_cast<int>(PLAYER::LEFT_HAND_INIT), static_cast<int>(PLAYER::LEFT_HAND_INIT), 0.0f, false);
		PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "FRONT_HANDITEM", static_cast<int>(PLAYER::FRONT_HAND_INIT), static_cast<int>(PLAYER::FRONT_HAND_INIT), 0.0f, false);
		PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "BACK_HANDITEM", static_cast<int>(PLAYER::BACK_HAND_INIT), static_cast<int>(PLAYER::BACK_HAND_INIT), 0.0f, false);

		PlayerPantsRenderer_->CreateAnimation(CustomData::GetInst()->GetPantsFileName(), "RIGHT_HANDITEM", static_cast<int>(PLAYER::RIGHT_HAND_INIT), static_cast<int>(PLAYER::RIGHT_HAND_INIT), 0.0f, false);
		PlayerPantsRenderer_->CreateAnimation(CustomData::GetInst()->GetPantsFileName(), "LEFT_HANDITEM", static_cast<int>(PLAYER::LEFT_HAND_INIT), static_cast<int>(PLAYER::LEFT_HAND_INIT), 0.0f, false);
		PlayerPantsRenderer_->CreateAnimation(CustomData::GetInst()->GetPantsFileName(), "FRONT_HANDITEM", static_cast<int>(PLAYER::FRONT_HAND_INIT), static_cast<int>(PLAYER::FRONT_HAND_INIT), 0.0f, false);
		PlayerPantsRenderer_->CreateAnimation(CustomData::GetInst()->GetPantsFileName(), "BACK_HANDITEM", static_cast<int>(PLAYER::BACK_HAND_INIT), static_cast<int>(PLAYER::BACK_HAND_INIT), 0.0f, false);

		PlayerShirtsRenderer_->CreateAnimation(CustomData::GetInst()->GetShirtsFileName(), "RIGHT_HANDITEM", static_cast<int>(PLAYER::RIGHT_HAND_INIT), static_cast<int>(PLAYER::RIGHT_HAND_INIT), 0.0f, false);
		PlayerShirtsRenderer_->CreateAnimation(CustomData::GetInst()->GetShirtsFileName(), "LEFT_HANDITEM", static_cast<int>(PLAYER::LEFT_HAND_INIT), static_cast<int>(PLAYER::LEFT_HAND_INIT), 0.0f, false);
		PlayerShirtsRenderer_->CreateAnimation(CustomData::GetInst()->GetShirtsFileName(), "FRONT_HANDITEM", static_cast<int>(PLAYER::FRONT_HAND_INIT), static_cast<int>(PLAYER::FRONT_HAND_INIT), 0.0f, false);
		PlayerShirtsRenderer_->CreateAnimation(CustomData::GetInst()->GetShirtsFileName(), "BACK_HANDITEM", static_cast<int>(PLAYER::BACK_HAND_INIT), static_cast<int>(PLAYER::BACK_HAND_INIT), 0.0f, false);

		PlayerHairRenderer_->CreateAnimation(CustomData::GetInst()->GetHairFileName(), "RIGHT_HANDITEM", static_cast<int>(PLAYER::RIGHT_HAND_INIT), static_cast<int>(PLAYER::RIGHT_HAND_INIT), 0.0f, false);
		PlayerHairRenderer_->CreateAnimation(CustomData::GetInst()->GetHairFileName(), "LEFT_HANDITEM", static_cast<int>(PLAYER::LEFT_HAND_INIT), static_cast<int>(PLAYER::LEFT_HAND_INIT), 0.0f, false);
		PlayerHairRenderer_->CreateAnimation(CustomData::GetInst()->GetHairFileName(), "FRONT_HANDITEM", static_cast<int>(PLAYER::FRONT_HAND_INIT), static_cast<int>(PLAYER::FRONT_HAND_INIT), 0.0f, false);
		PlayerHairRenderer_->CreateAnimation(CustomData::GetInst()->GetHairFileName(), "BACK_HANDITEM", static_cast<int>(PLAYER::BACK_HAND_INIT), static_cast<int>(PLAYER::BACK_HAND_INIT), 0.0f, false);

		PlayerHandRenderer_->CreateAnimation(CustomData::GetInst()->GetHandFileName(), "RIGHT_HANDITEM", static_cast<int>(PLAYER::RIGHT_HAND_INIT), static_cast<int>(PLAYER::RIGHT_HAND_INIT), 0.0f, false);
		PlayerHandRenderer_->CreateAnimation(CustomData::GetInst()->GetHandFileName(), "LEFT_HANDITEM", static_cast<int>(PLAYER::LEFT_HAND_INIT), static_cast<int>(PLAYER::LEFT_HAND_INIT), 0.0f, false);
		PlayerHandRenderer_->CreateAnimation(CustomData::GetInst()->GetHandFileName(), "FRONT_HANDITEM", static_cast<int>(PLAYER::FRONT_HAND_INIT), static_cast<int>(PLAYER::FRONT_HAND_INIT), 0.0f, false);
		PlayerHandRenderer_->CreateAnimation(CustomData::GetInst()->GetHandFileName(), "BACK_HANDITEM", static_cast<int>(PLAYER::BACK_HAND_INIT), static_cast<int>(PLAYER::BACK_HAND_INIT), 0.0f, false);

		//================================
		//     플레이어 이동 
		//================================
		PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "RIGHT_HANDITEMWALK", static_cast<int>(PLAYER::RIGHT_WALK_HAND0), static_cast<int>(PLAYER::RIGHT_WALK_HAND5), AnimationFrame_, true);
		PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "LEFT_HANDITEMWALK", static_cast<int>(PLAYER::LEFT_WALK_HAND0), static_cast<int>(PLAYER::LEFT_WALK_HAND5), AnimationFrame_, true);
		PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "FRONT_HANDITEMWALK", static_cast<int>(PLAYER::FRONT_WALK_HAND0), static_cast<int>(PLAYER::FRONT_WALK_HAND3), AnimationFrame_, true);
		PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "BACK_HANDITEMWALK", static_cast<int>(PLAYER::BACK_WALK_HAND0), static_cast<int>(PLAYER::BACK_WALK_HAND3), AnimationFrame_, true);

		PlayerPantsRenderer_->CreateAnimation(CustomData::GetInst()->GetPantsFileName(), "RIGHT_HANDITEMWALK", static_cast<int>(PLAYER::RIGHT_WALK_HAND0), static_cast<int>(PLAYER::RIGHT_WALK_HAND5), AnimationFrame_, true);
		PlayerPantsRenderer_->CreateAnimation(CustomData::GetInst()->GetPantsFileName(), "LEFT_HANDITEMWALK", static_cast<int>(PLAYER::LEFT_WALK_HAND0), static_cast<int>(PLAYER::LEFT_WALK_HAND5), AnimationFrame_, true);
		PlayerPantsRenderer_->CreateAnimation(CustomData::GetInst()->GetPantsFileName(), "FRONT_HANDITEMWALK", static_cast<int>(PLAYER::FRONT_WALK_HAND0), static_cast<int>(PLAYER::FRONT_WALK_HAND3), AnimationFrame_, true);
		PlayerPantsRenderer_->CreateAnimation(CustomData::GetInst()->GetPantsFileName(), "BACK_HANDITEMWALK", static_cast<int>(PLAYER::BACK_WALK_HAND0), static_cast<int>(PLAYER::BACK_WALK_HAND3), AnimationFrame_, true);

		PlayerShirtsRenderer_->CreateAnimation(CustomData::GetInst()->GetShirtsFileName(), "RIGHT_HANDITEMWALK", static_cast<int>(PLAYER::RIGHT_WALK_HAND0), static_cast<int>(PLAYER::RIGHT_WALK_HAND5), AnimationFrame_, true);
		PlayerShirtsRenderer_->CreateAnimation(CustomData::GetInst()->GetShirtsFileName(), "LEFT_HANDITEMWALK", static_cast<int>(PLAYER::LEFT_WALK_HAND0), static_cast<int>(PLAYER::LEFT_WALK_HAND5), AnimationFrame_, true);
		PlayerShirtsRenderer_->CreateAnimation(CustomData::GetInst()->GetShirtsFileName(), "FRONT_HANDITEMWALK", static_cast<int>(PLAYER::FRONT_WALK_HAND0), static_cast<int>(PLAYER::FRONT_WALK_HAND3), AnimationFrame_, true);
		PlayerShirtsRenderer_->CreateAnimation(CustomData::GetInst()->GetShirtsFileName(), "BACK_HANDITEMWALK", static_cast<int>(PLAYER::BACK_WALK_HAND0), static_cast<int>(PLAYER::BACK_WALK_HAND3), AnimationFrame_, true);

		PlayerHairRenderer_->CreateAnimation(CustomData::GetInst()->GetHairFileName(), "RIGHT_HANDITEMWALK", static_cast<int>(PLAYER::RIGHT_WALK_HAND0), static_cast<int>(PLAYER::RIGHT_WALK_HAND5), AnimationFrame_, true);
		PlayerHairRenderer_->CreateAnimation(CustomData::GetInst()->GetHairFileName(), "LEFT_HANDITEMWALK", static_cast<int>(PLAYER::LEFT_WALK_HAND0), static_cast<int>(PLAYER::LEFT_WALK_HAND5), AnimationFrame_, true);
		PlayerHairRenderer_->CreateAnimation(CustomData::GetInst()->GetHairFileName(), "FRONT_HANDITEMWALK", static_cast<int>(PLAYER::FRONT_WALK_HAND0), static_cast<int>(PLAYER::FRONT_WALK_HAND3), AnimationFrame_, true);
		PlayerHairRenderer_->CreateAnimation(CustomData::GetInst()->GetHairFileName(), "BACK_HANDITEMWALK", static_cast<int>(PLAYER::BACK_WALK_HAND0), static_cast<int>(PLAYER::BACK_WALK_HAND3), AnimationFrame_, true);

		PlayerHandRenderer_->CreateAnimation(CustomData::GetInst()->GetHandFileName(), "RIGHT_HANDITEMWALK", static_cast<int>(PLAYER::RIGHT_WALK_HAND0), static_cast<int>(PLAYER::RIGHT_WALK_HAND5), AnimationFrame_, true);
		PlayerHandRenderer_->CreateAnimation(CustomData::GetInst()->GetHandFileName(), "LEFT_HANDITEMWALK", static_cast<int>(PLAYER::LEFT_WALK_HAND0), static_cast<int>(PLAYER::LEFT_WALK_HAND5), AnimationFrame_, true);
		PlayerHandRenderer_->CreateAnimation(CustomData::GetInst()->GetHandFileName(), "FRONT_HANDITEMWALK", static_cast<int>(PLAYER::FRONT_WALK_HAND0), static_cast<int>(PLAYER::FRONT_WALK_HAND3), AnimationFrame_, true);
		PlayerHandRenderer_->CreateAnimation(CustomData::GetInst()->GetHandFileName(), "BACK_HANDITEMWALK", static_cast<int>(PLAYER::BACK_WALK_HAND0), static_cast<int>(PLAYER::BACK_WALK_HAND3), AnimationFrame_, true);

		//================================
		//     플레이어 호미 사용
		//================================
		PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "FRONT_HOE", static_cast<int>(PLAYER::HOE_FRONT0), static_cast<int>(PLAYER::HOE_FRONT5), AnimationFrame_, false);
		PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "RIGHT_HOE", static_cast<int>(PLAYER::HOE_RIGHT0), static_cast<int>(PLAYER::HOE_RIGHT4), AnimationFrame_, false);
		PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "BACK_HOE", static_cast<int>(PLAYER::HOE_BACK0), static_cast<int>(PLAYER::HOE_BACK2), AnimationFrame_, false);
		PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "LEFT_HOE", static_cast<int>(PLAYER::HOE_LEFT0), static_cast<int>(PLAYER::HOE_LEFT4), AnimationFrame_, false);

		PlayerPantsRenderer_->CreateAnimation(CustomData::GetInst()->GetPantsFileName(), "FRONT_HOE", static_cast<int>(PLAYER::HOE_FRONT0), static_cast<int>(PLAYER::HOE_FRONT5), AnimationFrame_, false);
		PlayerPantsRenderer_->CreateAnimation(CustomData::GetInst()->GetPantsFileName(), "RIGHT_HOE", static_cast<int>(PLAYER::HOE_RIGHT0), static_cast<int>(PLAYER::HOE_RIGHT4), AnimationFrame_, false);
		PlayerPantsRenderer_->CreateAnimation(CustomData::GetInst()->GetPantsFileName(), "BACK_HOE", static_cast<int>(PLAYER::HOE_BACK0), static_cast<int>(PLAYER::HOE_BACK2), AnimationFrame_, false);
		PlayerPantsRenderer_->CreateAnimation(CustomData::GetInst()->GetPantsFileName(), "LEFT_HOE", static_cast<int>(PLAYER::HOE_LEFT0), static_cast<int>(PLAYER::HOE_LEFT4), AnimationFrame_, false);

		PlayerShirtsRenderer_->CreateAnimation(CustomData::GetInst()->GetShirtsFileName(), "FRONT_HOE", static_cast<int>(PLAYER::HOE_FRONT0), static_cast<int>(PLAYER::HOE_FRONT5), AnimationFrame_, false);
		PlayerShirtsRenderer_->CreateAnimation(CustomData::GetInst()->GetShirtsFileName(), "RIGHT_HOE", static_cast<int>(PLAYER::HOE_RIGHT0), static_cast<int>(PLAYER::HOE_RIGHT4), AnimationFrame_, false);
		PlayerShirtsRenderer_->CreateAnimation(CustomData::GetInst()->GetShirtsFileName(), "BACK_HOE", static_cast<int>(PLAYER::HOE_BACK0), static_cast<int>(PLAYER::HOE_BACK2), AnimationFrame_, false);
		PlayerShirtsRenderer_->CreateAnimation(CustomData::GetInst()->GetShirtsFileName(), "LEFT_HOE", static_cast<int>(PLAYER::HOE_LEFT0), static_cast<int>(PLAYER::HOE_LEFT4), AnimationFrame_, false);

		PlayerHairRenderer_->CreateAnimation(CustomData::GetInst()->GetHairFileName(), "FRONT_HOE", static_cast<int>(PLAYER::HOE_FRONT0), static_cast<int>(PLAYER::HOE_FRONT5), AnimationFrame_, false);
		PlayerHairRenderer_->CreateAnimation(CustomData::GetInst()->GetHairFileName(), "RIGHT_HOE", static_cast<int>(PLAYER::HOE_RIGHT0), static_cast<int>(PLAYER::HOE_RIGHT4), AnimationFrame_, false);
		PlayerHairRenderer_->CreateAnimation(CustomData::GetInst()->GetHairFileName(), "BACK_HOE", static_cast<int>(PLAYER::HOE_BACK0), static_cast<int>(PLAYER::HOE_BACK2), AnimationFrame_, false);
		PlayerHairRenderer_->CreateAnimation(CustomData::GetInst()->GetHairFileName(), "LEFT_HOE", static_cast<int>(PLAYER::HOE_LEFT0), static_cast<int>(PLAYER::HOE_LEFT4), AnimationFrame_, false);

		PlayerHandRenderer_->CreateAnimation(CustomData::GetInst()->GetHandFileName(), "FRONT_HOE", static_cast<int>(PLAYER::HOE_FRONT0), static_cast<int>(PLAYER::HOE_FRONT5), AnimationFrame_, false);
		PlayerHandRenderer_->CreateAnimation(CustomData::GetInst()->GetHandFileName(), "RIGHT_HOE", static_cast<int>(PLAYER::HOE_RIGHT0), static_cast<int>(PLAYER::HOE_RIGHT4), AnimationFrame_, false);
		PlayerHandRenderer_->CreateAnimation(CustomData::GetInst()->GetHandFileName(), "BACK_HOE", static_cast<int>(PLAYER::HOE_BACK0), static_cast<int>(PLAYER::HOE_BACK2), AnimationFrame_, false);
		PlayerHandRenderer_->CreateAnimation(CustomData::GetInst()->GetHandFileName(), "LEFT_HOE", static_cast<int>(PLAYER::HOE_LEFT0), static_cast<int>(PLAYER::HOE_LEFT4), AnimationFrame_, false);


		//================================
		//     플레이어 물뿌리개 사용
		//================================
		PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "FRONT_WATER", static_cast<int>(PLAYER::WATER_FRONT0), static_cast<int>(PLAYER::WATER_FRONT2), 0.200f, true);
		PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "RIGHT_WATER", static_cast<int>(PLAYER::WATER_RIGHT0), static_cast<int>(PLAYER::WATER_RIGHT2), 0.200f, true);
		PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "LEFT_WATER", static_cast<int>(PLAYER::WATER_LEFT0), static_cast<int>(PLAYER::WATER_LEFT2), 0.200f, true);
		PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "BACK_WATER", static_cast<int>(PLAYER::WATER_BACK0), static_cast<int>(PLAYER::WATER_BACK2), 0.200f, true);

		PlayerPantsRenderer_->CreateAnimation(CustomData::GetInst()->GetPantsFileName(), "FRONT_WATER", static_cast<int>(PLAYER::WATER_FRONT0), static_cast<int>(PLAYER::WATER_FRONT2), 0.200f, true);
		PlayerPantsRenderer_->CreateAnimation(CustomData::GetInst()->GetPantsFileName(), "RIGHT_WATER", static_cast<int>(PLAYER::WATER_RIGHT0), static_cast<int>(PLAYER::WATER_RIGHT2), 0.200f, true);
		PlayerPantsRenderer_->CreateAnimation(CustomData::GetInst()->GetPantsFileName(), "LEFT_WATER", static_cast<int>(PLAYER::WATER_LEFT0), static_cast<int>(PLAYER::WATER_LEFT2), 0.200f, true);
		PlayerPantsRenderer_->CreateAnimation(CustomData::GetInst()->GetPantsFileName(), "BACK_WATER", static_cast<int>(PLAYER::WATER_BACK0), static_cast<int>(PLAYER::WATER_BACK2), 0.200f, true);

		PlayerShirtsRenderer_->CreateAnimation(CustomData::GetInst()->GetShirtsFileName(), "FRONT_WATER", static_cast<int>(PLAYER::WATER_FRONT0), static_cast<int>(PLAYER::WATER_FRONT2), 0.200f, true);
		PlayerShirtsRenderer_->CreateAnimation(CustomData::GetInst()->GetShirtsFileName(), "RIGHT_WATER", static_cast<int>(PLAYER::WATER_RIGHT0), static_cast<int>(PLAYER::WATER_RIGHT2), 0.200f, true);
		PlayerShirtsRenderer_->CreateAnimation(CustomData::GetInst()->GetShirtsFileName(), "LEFT_WATER", static_cast<int>(PLAYER::WATER_LEFT0), static_cast<int>(PLAYER::WATER_LEFT2), 0.200f, true);
		PlayerShirtsRenderer_->CreateAnimation(CustomData::GetInst()->GetShirtsFileName(), "BACK_WATER", static_cast<int>(PLAYER::WATER_BACK0), static_cast<int>(PLAYER::WATER_BACK2), 0.200f, true);

		PlayerHairRenderer_->CreateAnimation(CustomData::GetInst()->GetHairFileName(), "FRONT_WATER", static_cast<int>(PLAYER::WATER_FRONT0), static_cast<int>(PLAYER::WATER_FRONT2), 0.200f, true);
		PlayerHairRenderer_->CreateAnimation(CustomData::GetInst()->GetHairFileName(), "RIGHT_WATER", static_cast<int>(PLAYER::WATER_RIGHT0), static_cast<int>(PLAYER::WATER_RIGHT2), 0.200f, true);
		PlayerHairRenderer_->CreateAnimation(CustomData::GetInst()->GetHairFileName(), "LEFT_WATER", static_cast<int>(PLAYER::WATER_LEFT0), static_cast<int>(PLAYER::WATER_LEFT2), 0.200f, true);
		PlayerHairRenderer_->CreateAnimation(CustomData::GetInst()->GetHairFileName(), "BACK_WATER", static_cast<int>(PLAYER::WATER_BACK0), static_cast<int>(PLAYER::WATER_BACK2), 0.200f, true);

		PlayerHandRenderer_->CreateAnimation(CustomData::GetInst()->GetHandFileName(), "FRONT_WATER", static_cast<int>(PLAYER::WATER_FRONT0), static_cast<int>(PLAYER::WATER_FRONT2), 0.200f, true);
		PlayerHandRenderer_->CreateAnimation(CustomData::GetInst()->GetHandFileName(), "RIGHT_WATER", static_cast<int>(PLAYER::WATER_RIGHT0), static_cast<int>(PLAYER::WATER_RIGHT2), 0.200f, true);
		PlayerHandRenderer_->CreateAnimation(CustomData::GetInst()->GetHandFileName(), "LEFT_WATER", static_cast<int>(PLAYER::WATER_LEFT0), static_cast<int>(PLAYER::WATER_LEFT2), 0.200f, true);
		PlayerHandRenderer_->CreateAnimation(CustomData::GetInst()->GetHandFileName(), "BACK_WATER", static_cast<int>(PLAYER::WATER_BACK0), static_cast<int>(PLAYER::WATER_BACK2), 0.200f, true);


		//================================
		//     플레이어 칼 사용
		//================================
		PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "FRONT_SWOARD", static_cast<int>(PLAYER::SWAORD_FRONT0), static_cast<int>(PLAYER::SWAORD_FRONT4), 0.040f, false);
		PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "RIGHT_SWOARD", static_cast<int>(PLAYER::SWAORD_RIGHT2), static_cast<int>(PLAYER::SWAORD_RIGHT4), 0.040f, false);
		PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "BACK_SWOARD", static_cast<int>(PLAYER::SWAORD_BACK0), static_cast<int>(PLAYER::SWAORD_BACK3), 0.040f, false);
		PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "LEFT_SWOARD", static_cast<int>(PLAYER::SWAORD_LEFT1), static_cast<int>(PLAYER::SWAORD_LEFT3), 0.040f, false);

		PlayerPantsRenderer_->CreateAnimation(CustomData::GetInst()->GetPantsFileName(), "FRONT_SWOARD", static_cast<int>(PLAYER::SWAORD_FRONT0), static_cast<int>(PLAYER::SWAORD_FRONT4), 0.040f, false);
		PlayerPantsRenderer_->CreateAnimation(CustomData::GetInst()->GetPantsFileName(), "RIGHT_SWOARD", static_cast<int>(PLAYER::SWAORD_RIGHT2), static_cast<int>(PLAYER::SWAORD_RIGHT4), 0.040f, false);
		PlayerPantsRenderer_->CreateAnimation(CustomData::GetInst()->GetPantsFileName(), "BACK_SWOARD", static_cast<int>(PLAYER::SWAORD_BACK0), static_cast<int>(PLAYER::SWAORD_BACK3), 0.040f, false);
		PlayerPantsRenderer_->CreateAnimation(CustomData::GetInst()->GetPantsFileName(), "LEFT_SWOARD", static_cast<int>(PLAYER::SWAORD_LEFT1), static_cast<int>(PLAYER::SWAORD_LEFT3), 0.040f, false);

		PlayerShirtsRenderer_->CreateAnimation(CustomData::GetInst()->GetShirtsFileName(), "FRONT_SWOARD", static_cast<int>(PLAYER::SWAORD_FRONT0), static_cast<int>(PLAYER::SWAORD_FRONT4), 0.040f, false);
		PlayerShirtsRenderer_->CreateAnimation(CustomData::GetInst()->GetShirtsFileName(), "RIGHT_SWOARD", static_cast<int>(PLAYER::SWAORD_RIGHT2), static_cast<int>(PLAYER::SWAORD_RIGHT4), 0.040f, false);
		PlayerShirtsRenderer_->CreateAnimation(CustomData::GetInst()->GetShirtsFileName(), "BACK_SWOARD", static_cast<int>(PLAYER::SWAORD_BACK0), static_cast<int>(PLAYER::SWAORD_BACK3), 0.040f, false);
		PlayerShirtsRenderer_->CreateAnimation(CustomData::GetInst()->GetShirtsFileName(), "LEFT_SWOARD", static_cast<int>(PLAYER::SWAORD_LEFT1), static_cast<int>(PLAYER::SWAORD_LEFT3), 0.040f, false);

		PlayerHairRenderer_->CreateAnimation(CustomData::GetInst()->GetHairFileName(), "FRONT_SWOARD", static_cast<int>(PLAYER::SWAORD_FRONT0), static_cast<int>(PLAYER::SWAORD_FRONT4), 0.040f, false);
		PlayerHairRenderer_->CreateAnimation(CustomData::GetInst()->GetHairFileName(), "RIGHT_SWOARD", static_cast<int>(PLAYER::SWAORD_RIGHT2), static_cast<int>(PLAYER::SWAORD_RIGHT4), 0.040f, false);
		PlayerHairRenderer_->CreateAnimation(CustomData::GetInst()->GetHairFileName(), "BACK_SWOARD", static_cast<int>(PLAYER::SWAORD_BACK0), static_cast<int>(PLAYER::SWAORD_BACK3), 0.040f, false);
		PlayerHairRenderer_->CreateAnimation(CustomData::GetInst()->GetHairFileName(), "LEFT_SWOARD", static_cast<int>(PLAYER::SWAORD_LEFT1), static_cast<int>(PLAYER::SWAORD_LEFT3), 0.040f, false);

		PlayerHandRenderer_->CreateAnimation(CustomData::GetInst()->GetHandFileName(), "FRONT_SWOARD", static_cast<int>(PLAYER::SWAORD_FRONT0), static_cast<int>(PLAYER::SWAORD_FRONT4), 0.040f, false);
		PlayerHandRenderer_->CreateAnimation(CustomData::GetInst()->GetHandFileName(), "RIGHT_SWOARD", static_cast<int>(PLAYER::SWAORD_RIGHT2), static_cast<int>(PLAYER::SWAORD_RIGHT4), 0.040f, false);
		PlayerHandRenderer_->CreateAnimation(CustomData::GetInst()->GetHandFileName(), "BACK_SWOARD", static_cast<int>(PLAYER::SWAORD_BACK0), static_cast<int>(PLAYER::SWAORD_BACK3), 0.040f, false);
		PlayerHandRenderer_->CreateAnimation(CustomData::GetInst()->GetHandFileName(), "LEFT_SWOARD", static_cast<int>(PLAYER::SWAORD_LEFT1), static_cast<int>(PLAYER::SWAORD_LEFT3), 0.040f, false);


		//================================
		//     플레이어 기절
		//================================
		PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "FRONT_FAINT", static_cast<int>(PLAYER::FAINT0), static_cast<int>(PLAYER::FAINT1), 0.350f, false);
		PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "RIGHT_FAINT", static_cast<int>(PLAYER::FAINT0), static_cast<int>(PLAYER::FAINT1), 0.350f, false);
		PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "LEFT_FAINT", static_cast<int>(PLAYER::FAINT0), static_cast<int>(PLAYER::FAINT1), 0.350f, false);
		PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "BACK_FAINT", static_cast<int>(PLAYER::FAINT0), static_cast<int>(PLAYER::FAINT1), 0.350f, false);

		PlayerPantsRenderer_->CreateAnimation(CustomData::GetInst()->GetPantsFileName(), "FRONT_FAINT", static_cast<int>(PLAYER::FAINT0), static_cast<int>(PLAYER::FAINT1), 0.350f, false);
		PlayerPantsRenderer_->CreateAnimation(CustomData::GetInst()->GetPantsFileName(), "RIGHT_FAINT", static_cast<int>(PLAYER::FAINT0), static_cast<int>(PLAYER::FAINT1), 0.350f, false);
		PlayerPantsRenderer_->CreateAnimation(CustomData::GetInst()->GetPantsFileName(), "LEFT_FAINT", static_cast<int>(PLAYER::FAINT0), static_cast<int>(PLAYER::FAINT1), 0.350f, false);
		PlayerPantsRenderer_->CreateAnimation(CustomData::GetInst()->GetPantsFileName(), "BACK_FAINT", static_cast<int>(PLAYER::FAINT0), static_cast<int>(PLAYER::FAINT1), 0.350f, false);

		PlayerShirtsRenderer_->CreateAnimation(CustomData::GetInst()->GetShirtsFileName(), "FRONT_FAINT", static_cast<int>(PLAYER::FAINT0), static_cast<int>(PLAYER::FAINT1), 0.350f, false);
		PlayerShirtsRenderer_->CreateAnimation(CustomData::GetInst()->GetShirtsFileName(), "RIGHT_FAINT", static_cast<int>(PLAYER::FAINT0), static_cast<int>(PLAYER::FAINT1), 0.350f, false);
		PlayerShirtsRenderer_->CreateAnimation(CustomData::GetInst()->GetShirtsFileName(), "LEFT_FAINT", static_cast<int>(PLAYER::FAINT0), static_cast<int>(PLAYER::FAINT1), 0.350f, false);
		PlayerShirtsRenderer_->CreateAnimation(CustomData::GetInst()->GetShirtsFileName(), "BACK_FAINT", static_cast<int>(PLAYER::FAINT0), static_cast<int>(PLAYER::FAINT1), 0.350f, false);

		PlayerHairRenderer_->CreateAnimation(CustomData::GetInst()->GetHairFileName(), "FRONT_FAINT", static_cast<int>(PLAYER::FAINT0), static_cast<int>(PLAYER::FAINT1), 0.350f, false);
		PlayerHairRenderer_->CreateAnimation(CustomData::GetInst()->GetHairFileName(), "RIGHT_FAINT", static_cast<int>(PLAYER::FAINT0), static_cast<int>(PLAYER::FAINT1), 0.350f, false);
		PlayerHairRenderer_->CreateAnimation(CustomData::GetInst()->GetHairFileName(), "LEFT_FAINT", static_cast<int>(PLAYER::FAINT0), static_cast<int>(PLAYER::FAINT1), 0.350f, false);
		PlayerHairRenderer_->CreateAnimation(CustomData::GetInst()->GetHairFileName(), "BACK_FAINT", static_cast<int>(PLAYER::FAINT0), static_cast<int>(PLAYER::FAINT1), 0.350f, false);

		PlayerHandRenderer_->CreateAnimation(CustomData::GetInst()->GetHandFileName(), "FRONT_FAINT", static_cast<int>(PLAYER::FAINT0), static_cast<int>(PLAYER::FAINT1), 0.350f, false);
		PlayerHandRenderer_->CreateAnimation(CustomData::GetInst()->GetHandFileName(), "RIGHT_FAINT", static_cast<int>(PLAYER::FAINT0), static_cast<int>(PLAYER::FAINT1), 0.350f, false);
		PlayerHandRenderer_->CreateAnimation(CustomData::GetInst()->GetHandFileName(), "LEFT_FAINT", static_cast<int>(PLAYER::FAINT0), static_cast<int>(PLAYER::FAINT1), 0.350f, false);
		PlayerHandRenderer_->CreateAnimation(CustomData::GetInst()->GetHandFileName(), "BACK_FAINT", static_cast<int>(PLAYER::FAINT0), static_cast<int>(PLAYER::FAINT1), 0.350f, false);

		//================================
		//     음식 대기
		//================================

		PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "FRONT_EAT_WAIT", static_cast<int>(PLAYER::EAT0), static_cast<int>(PLAYER::EAT0), 0.350f, false);
		PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "RIGHT_EAT_WAIT", static_cast<int>(PLAYER::EAT0), static_cast<int>(PLAYER::EAT0), 0.350f, false);
		PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "LEFT_EAT_WAIT", static_cast<int>(PLAYER::EAT0), static_cast<int>(PLAYER::EAT0), 0.350f, false);
		PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "BACK_EAT_WAIT", static_cast<int>(PLAYER::EAT0), static_cast<int>(PLAYER::EAT0), 0.350f, false);

		PlayerPantsRenderer_->CreateAnimation(CustomData::GetInst()->GetPantsFileName(), "FRONT_EAT_WAIT", static_cast<int>(PLAYER::EAT0), static_cast<int>(PLAYER::EAT0), 0.350f, false);
		PlayerPantsRenderer_->CreateAnimation(CustomData::GetInst()->GetPantsFileName(), "RIGHT_EAT_WAIT", static_cast<int>(PLAYER::EAT0), static_cast<int>(PLAYER::EAT0), 0.350f, false);
		PlayerPantsRenderer_->CreateAnimation(CustomData::GetInst()->GetPantsFileName(), "LEFT_EA_WAITT", static_cast<int>(PLAYER::EAT0), static_cast<int>(PLAYER::EAT0), 0.350f, false);
		PlayerPantsRenderer_->CreateAnimation(CustomData::GetInst()->GetPantsFileName(), "BACK_EAT_WAIT", static_cast<int>(PLAYER::EAT0), static_cast<int>(PLAYER::EAT0), 0.350f, false);

		PlayerShirtsRenderer_->CreateAnimation(CustomData::GetInst()->GetShirtsFileName(), "FRONT_EAT_WAIT", static_cast<int>(PLAYER::EAT0), static_cast<int>(PLAYER::EAT0), 0.350f, false);
		PlayerShirtsRenderer_->CreateAnimation(CustomData::GetInst()->GetShirtsFileName(), "RIGHT_EAT_WAIT", static_cast<int>(PLAYER::EAT0), static_cast<int>(PLAYER::EAT0), 0.350f, false);
		PlayerShirtsRenderer_->CreateAnimation(CustomData::GetInst()->GetShirtsFileName(), "LEFT_EAT_WAIT", static_cast<int>(PLAYER::EAT0), static_cast<int>(PLAYER::EAT0), 0.350f, false);
		PlayerShirtsRenderer_->CreateAnimation(CustomData::GetInst()->GetShirtsFileName(), "BACK_EAT_WAIT", static_cast<int>(PLAYER::EAT0), static_cast<int>(PLAYER::EAT0), 0.350f, false);

		PlayerHairRenderer_->CreateAnimation(CustomData::GetInst()->GetHairFileName(), "FRONT_EAT_WAIT", static_cast<int>(PLAYER::EAT0), static_cast<int>(PLAYER::EAT0), 0.350f, false);
		PlayerHairRenderer_->CreateAnimation(CustomData::GetInst()->GetHairFileName(), "RIGHT_EAT_WAIT", static_cast<int>(PLAYER::EAT0), static_cast<int>(PLAYER::EAT0), 0.350f, false);
		PlayerHairRenderer_->CreateAnimation(CustomData::GetInst()->GetHairFileName(), "LEFT_EAT_WAIT", static_cast<int>(PLAYER::EAT0), static_cast<int>(PLAYER::EAT0), 0.350f, false);
		PlayerHairRenderer_->CreateAnimation(CustomData::GetInst()->GetHairFileName(), "BACK_EAT_WAIT", static_cast<int>(PLAYER::EAT0), static_cast<int>(PLAYER::EAT0), 0.350f, false);

		PlayerHandRenderer_->CreateAnimation(CustomData::GetInst()->GetHandFileName(), "FRONT_EAT_WAIT", static_cast<int>(PLAYER::EAT0), static_cast<int>(PLAYER::EAT0), 0.350f, false);
		PlayerHandRenderer_->CreateAnimation(CustomData::GetInst()->GetHandFileName(), "RIGHT_EAT_WAIT", static_cast<int>(PLAYER::EAT0), static_cast<int>(PLAYER::EAT0), 0.350f, false);
		PlayerHandRenderer_->CreateAnimation(CustomData::GetInst()->GetHandFileName(), "LEFT_EAT_WAIT", static_cast<int>(PLAYER::EAT0), static_cast<int>(PLAYER::EAT0), 0.350f, false);
		PlayerHandRenderer_->CreateAnimation(CustomData::GetInst()->GetHandFileName(), "BACK_EAT_WAIT", static_cast<int>(PLAYER::EAT0), static_cast<int>(PLAYER::EAT0), 0.350f, false);



		//================================
		//     음식 먹기
		//================================
		PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "FRONT_EAT", static_cast<int>(PLAYER::EAT1), static_cast<int>(PLAYER::EAT2), 0.350f, true);
		PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "RIGHT_EAT", static_cast<int>(PLAYER::EAT1), static_cast<int>(PLAYER::EAT2), 0.350f, true);
		PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "LEFT_EAT", static_cast<int>(PLAYER::EAT1), static_cast<int>(PLAYER::EAT2), 0.350f, true);
		PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "BACK_EAT", static_cast<int>(PLAYER::EAT1), static_cast<int>(PLAYER::EAT2), 0.350f, true);

		PlayerPantsRenderer_->CreateAnimation(CustomData::GetInst()->GetPantsFileName(), "FRONT_EAT", static_cast<int>(PLAYER::EAT1), static_cast<int>(PLAYER::EAT2), 0.350f, true);
		PlayerPantsRenderer_->CreateAnimation(CustomData::GetInst()->GetPantsFileName(), "RIGHT_EAT", static_cast<int>(PLAYER::EAT1), static_cast<int>(PLAYER::EAT2), 0.350f, true);
		PlayerPantsRenderer_->CreateAnimation(CustomData::GetInst()->GetPantsFileName(), "LEFT_EAT", static_cast<int>(PLAYER::EAT1), static_cast<int>(PLAYER::EAT2), 0.350f, true);
		PlayerPantsRenderer_->CreateAnimation(CustomData::GetInst()->GetPantsFileName(), "BACK_EAT", static_cast<int>(PLAYER::EAT1), static_cast<int>(PLAYER::EAT2), 0.350f, true);

		PlayerShirtsRenderer_->CreateAnimation(CustomData::GetInst()->GetShirtsFileName(), "FRONT_EAT", static_cast<int>(PLAYER::EAT1), static_cast<int>(PLAYER::EAT2), 0.350f, true);
		PlayerShirtsRenderer_->CreateAnimation(CustomData::GetInst()->GetShirtsFileName(), "RIGHT_EAT", static_cast<int>(PLAYER::EAT1), static_cast<int>(PLAYER::EAT2), 0.350f, true);
		PlayerShirtsRenderer_->CreateAnimation(CustomData::GetInst()->GetShirtsFileName(), "LEFT_EAT", static_cast<int>(PLAYER::EAT1), static_cast<int>(PLAYER::EAT2), 0.350f, true);
		PlayerShirtsRenderer_->CreateAnimation(CustomData::GetInst()->GetShirtsFileName(), "BACK_EAT", static_cast<int>(PLAYER::EAT1), static_cast<int>(PLAYER::EAT2), 0.350f, true);

		PlayerHairRenderer_->CreateAnimation(CustomData::GetInst()->GetHairFileName(), "FRONT_EAT", static_cast<int>(PLAYER::EAT1), static_cast<int>(PLAYER::EAT2), 0.350f, true);
		PlayerHairRenderer_->CreateAnimation(CustomData::GetInst()->GetHairFileName(), "RIGHT_EAT", static_cast<int>(PLAYER::EAT1), static_cast<int>(PLAYER::EAT2), 0.350f, true);
		PlayerHairRenderer_->CreateAnimation(CustomData::GetInst()->GetHairFileName(), "LEFT_EAT", static_cast<int>(PLAYER::EAT1), static_cast<int>(PLAYER::EAT2), 0.350f, true);
		PlayerHairRenderer_->CreateAnimation(CustomData::GetInst()->GetHairFileName(), "BACK_EAT", static_cast<int>(PLAYER::EAT1), static_cast<int>(PLAYER::EAT2), 0.350f, true);

		PlayerHandRenderer_->CreateAnimation(CustomData::GetInst()->GetHandFileName(), "FRONT_EAT", static_cast<int>(PLAYER::EAT1), static_cast<int>(PLAYER::EAT2), 0.350f, true);
		PlayerHandRenderer_->CreateAnimation(CustomData::GetInst()->GetHandFileName(), "RIGHT_EAT", static_cast<int>(PLAYER::EAT1), static_cast<int>(PLAYER::EAT2), 0.350f, true);
		PlayerHandRenderer_->CreateAnimation(CustomData::GetInst()->GetHandFileName(), "LEFT_EAT", static_cast<int>(PLAYER::EAT1), static_cast<int>(PLAYER::EAT2), 0.350f, true);
		PlayerHandRenderer_->CreateAnimation(CustomData::GetInst()->GetHandFileName(), "BACK_EAT", static_cast<int>(PLAYER::EAT1), static_cast<int>(PLAYER::EAT2), 0.350f, true);

		//================================
		//     드링크
		//================================
		PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "FRONT_DRINK", static_cast<int>(PLAYER::DRINK1), static_cast<int>(PLAYER::DRINK3), 0.350f, false);
		PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "RIGHT_DRINK", static_cast<int>(PLAYER::DRINK1), static_cast<int>(PLAYER::DRINK3), 0.350f, false);
		PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "LEFT_DRINK", static_cast<int>(PLAYER::DRINK1), static_cast<int>(PLAYER::DRINK3), 0.350f, false);
		PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "BACK_DRINK", static_cast<int>(PLAYER::DRINK1), static_cast<int>(PLAYER::DRINK3), 0.350f, false);

		PlayerPantsRenderer_->CreateAnimation(CustomData::GetInst()->GetPantsFileName(), "FRONT_DRINK", static_cast<int>(PLAYER::DRINK1), static_cast<int>(PLAYER::DRINK3), 0.350f, false);
		PlayerPantsRenderer_->CreateAnimation(CustomData::GetInst()->GetPantsFileName(), "RIGHT_DRINK", static_cast<int>(PLAYER::DRINK1), static_cast<int>(PLAYER::DRINK3), 0.350f, false);
		PlayerPantsRenderer_->CreateAnimation(CustomData::GetInst()->GetPantsFileName(), "LEFT_DRINK", static_cast<int>(PLAYER::DRINK1), static_cast<int>(PLAYER::DRINK3), 0.350f, false);
		PlayerPantsRenderer_->CreateAnimation(CustomData::GetInst()->GetPantsFileName(), "BACK_DRINK", static_cast<int>(PLAYER::DRINK1), static_cast<int>(PLAYER::DRINK3), 0.350f, false);

		PlayerShirtsRenderer_->CreateAnimation(CustomData::GetInst()->GetShirtsFileName(), "FRONT_DRINK", static_cast<int>(PLAYER::DRINK1), static_cast<int>(PLAYER::DRINK3), 0.350f, false);
		PlayerShirtsRenderer_->CreateAnimation(CustomData::GetInst()->GetShirtsFileName(), "RIGHT_DRINK", static_cast<int>(PLAYER::DRINK1), static_cast<int>(PLAYER::DRINK3), 0.350f, false);
		PlayerShirtsRenderer_->CreateAnimation(CustomData::GetInst()->GetShirtsFileName(), "LEFT_DRINK", static_cast<int>(PLAYER::DRINK1), static_cast<int>(PLAYER::DRINK3), 0.350f, false);
		PlayerShirtsRenderer_->CreateAnimation(CustomData::GetInst()->GetShirtsFileName(), "BACK_DRINK", static_cast<int>(PLAYER::DRINK1), static_cast<int>(PLAYER::DRINK3), 0.350f, false);

		PlayerHairRenderer_->CreateAnimation(CustomData::GetInst()->GetHairFileName(), "FRONT_DRINK", static_cast<int>(PLAYER::DRINK1), static_cast<int>(PLAYER::DRINK3), 0.350f, false);
		PlayerHairRenderer_->CreateAnimation(CustomData::GetInst()->GetHairFileName(), "RIGHT_DRINK", static_cast<int>(PLAYER::DRINK1), static_cast<int>(PLAYER::DRINK3), 0.350f, false);
		PlayerHairRenderer_->CreateAnimation(CustomData::GetInst()->GetHairFileName(), "LEFT_DRINK", static_cast<int>(PLAYER::DRINK1), static_cast<int>(PLAYER::DRINK3), 0.350f, false);
		PlayerHairRenderer_->CreateAnimation(CustomData::GetInst()->GetHairFileName(), "BACK_DRINK", static_cast<int>(PLAYER::DRINK1), static_cast<int>(PLAYER::DRINK3), 0.350f, false);

		PlayerHandRenderer_->CreateAnimation(CustomData::GetInst()->GetHandFileName(), "FRONT_DRINK", static_cast<int>(PLAYER::DRINK1), static_cast<int>(PLAYER::DRINK3), 0.350f, false);
		PlayerHandRenderer_->CreateAnimation(CustomData::GetInst()->GetHandFileName(), "RIGHT_DRINK", static_cast<int>(PLAYER::DRINK1), static_cast<int>(PLAYER::DRINK3), 0.350f, false);
		PlayerHandRenderer_->CreateAnimation(CustomData::GetInst()->GetHandFileName(), "LEFT_DRINK", static_cast<int>(PLAYER::DRINK1), static_cast<int>(PLAYER::DRINK3), 0.350f, false);
		PlayerHandRenderer_->CreateAnimation(CustomData::GetInst()->GetHandFileName(), "BACK_DRINK", static_cast<int>(PLAYER::DRINK1), static_cast<int>(PLAYER::DRINK3), 0.350f, false);


		//------< 애니메이션 초기화 >------------------------------------------------------------------

		PlayerBodyRenderer_->ChangeAnimation("FRONT_INIT");
		PlayerPantsRenderer_->ChangeAnimation("FRONT_INIT");
		PlayerShirtsRenderer_->ChangeAnimation("FRONT_INIT");
		PlayerHairRenderer_->ChangeAnimation("FRONT_INIT");
		PlayerHandRenderer_->ChangeAnimation("FRONT_INIT");

	}

	//------< 플레이어 툴 렌더러 >------------------------------------------------------------------

	if (ToolRenderer_ == nullptr)
	{

		//------< 초기화 >------------------------------------------------------------------

		ToolRenderer_ = CreateRenderer();
		ToolRenderer_->SetPivotType(RenderPivot::BOT);
		ToolRenderer_->SetOrder(static_cast<int>(PLAYLEVEL::USE_TOOL));



		//------< 애니메이션 생성 >------------------------------------------------------------------
		//================================
		//     플레이어 툴 대기
		//================================
		ToolRenderer_->CreateAnimation("axe_back.bmp", "LEFT_INIT", static_cast<int>(HOE_BACK::HOE_BACK2), static_cast<int>(HOE_BACK::HOE_BACK2), AnimationFrame_, false);
		ToolRenderer_->CreateAnimation("axe_back.bmp", "RIGHT_INIT", static_cast<int>(HOE_BACK::HOE_BACK2), static_cast<int>(HOE_BACK::HOE_BACK2), AnimationFrame_, false);
		ToolRenderer_->CreateAnimation("axe_back.bmp", "FRONT_INIT", static_cast<int>(HOE_BACK::HOE_BACK2), static_cast<int>(HOE_BACK::HOE_BACK2), AnimationFrame_, false);
		ToolRenderer_->CreateAnimation("axe_back.bmp", "BACK_INIT", static_cast<int>(HOE_BACK::HOE_BACK2), static_cast<int>(HOE_BACK::HOE_BACK2), AnimationFrame_, false);



		//================================
		//     플레이어 호미 사용
		//================================
		ToolRenderer_->CreateAnimation("hoe_left.bmp", "LEFT_HOE", static_cast<int>(HOE_LEFT::HOE_LEFT0), static_cast<int>(HOE_LEFT::HOE_LEFT4), AnimationFrame_, false);
		ToolRenderer_->CreateAnimation("hoe_right.bmp", "RIGHT_HOE", static_cast<int>(HOE_RIGHT::HOE_RIGHT0), static_cast<int>(HOE_RIGHT::HOE_RIGHT4), AnimationFrame_, false);
		ToolRenderer_->CreateAnimation("hoe_front.bmp", "FRONT_HOE", static_cast<int>(HOE_FRONT::HOE_FRONT0), static_cast<int>(HOE_FRONT::HOE_FRONT4), AnimationFrame_, false);
		ToolRenderer_->CreateAnimation("hoe_back.bmp", "BACK_HOE", static_cast<int>(HOE_BACK::HOE_BACK0), static_cast<int>(HOE_BACK::HOE_BACK2), AnimationFrame_, false);

		//================================
		//     플레이어 도끼 사용
		//================================
		ToolRenderer_->CreateAnimation("axe_left.bmp", "LEFT_AXE", static_cast<int>(AXE_LEFT::AXE_LEFT0), static_cast<int>(AXE_LEFT::AXE_LEFT4), AnimationFrame_, false);
		ToolRenderer_->CreateAnimation("axe_right.bmp", "RIGHT_AXE", static_cast<int>(AXE_RIGHT::AXE_RIGHT0), static_cast<int>(AXE_RIGHT::AXE_RIGHT4), AnimationFrame_, false);
		ToolRenderer_->CreateAnimation("axe_front.bmp", "FRONT_AXE", static_cast<int>(AXE_FRONT::AXE_FRONT0), static_cast<int>(AXE_FRONT::AXE_FRONT4), AnimationFrame_, false);
		ToolRenderer_->CreateAnimation("axe_back.bmp", "BACK_AXE", static_cast<int>(AXE_BACK::AXE_BACK0), static_cast<int>(AXE_BACK::AXE_BACK2), AnimationFrame_, false);


		//================================
		//     플레이어 곡괭이 사용
		//================================
		ToolRenderer_->CreateAnimation("pickaxe_left.bmp", "LEFT_PICKAXE", static_cast<int>(PICKAXE_LEFT::PICKAXE_LEFT0), static_cast<int>(PICKAXE_LEFT::PICKAXE_LEFT4), AnimationFrame_, false);
		ToolRenderer_->CreateAnimation("pickaxe_right.bmp", "RIGHT_PICKAXE", static_cast<int>(PICKAXE_RIGHT::PICKAXE_RIGHT0), static_cast<int>(PICKAXE_RIGHT::PICKAXE_RIGHT4), AnimationFrame_, false);
		ToolRenderer_->CreateAnimation("pickaxe_front.bmp", "FRONT_PICKAXE", static_cast<int>(PICKAXE_FRONT::PICKAXE_FRONT0), static_cast<int>(PICKAXE_FRONT::PICKAXE_FRONT4), AnimationFrame_, false);
		ToolRenderer_->CreateAnimation("pickaxe_back.bmp", "BACK_PICKAXE", static_cast<int>(PICKAXE_BACK::PICKAXE_BACK0), static_cast<int>(PICKAXE_BACK::PICKAXE_BACK2), AnimationFrame_, false);


		//================================
		//     플레이어 물뿌리개 사용
		//================================

		ToolRenderer_->CreateAnimation("wateringcan_right.bmp", "RIGHT_WATER", static_cast<int>(WATERINGCAN_RIGHT::WATERINGCAN_RIGHT0), static_cast<int>(WATERINGCAN_RIGHT::WATERINGCAN_RIGHT2), 0.200f, false);
		ToolRenderer_->CreateAnimation("wateringcan_left.bmp", "LEFT_WATER", static_cast<int>(WATERINGCAN_LEFT::WATERINGCAN_LEFT0), static_cast<int>(WATERINGCAN_LEFT::WATERINGCAN_LEFT2), 0.200f, false);
		ToolRenderer_->CreateAnimation("wateringcan_front.bmp", "FRONT_WATER", static_cast<int>(WATERINGCAN_FRONT::WATERINGCAN_FRONT0), static_cast<int>(WATERINGCAN_FRONT::WATERINGCAN_FRONT2), 0.200f, false);
		ToolRenderer_->CreateAnimation("wateringcan_back.bmp", "BACK_WATER", static_cast<int>(WATERINGCAN_BACK::WATERINGCAN_BACK0), static_cast<int>(WATERINGCAN_BACK::WATERINGCAN_BACK2), 0.200f, false);
		

		//================================
		//     플레이어 칼 사용
		//================================
		
		ToolRenderer_->CreateAnimation("Swoard_right.bmp", "RIGHT_SWOARD", static_cast<int>(SWAORD_RIGHT::SWAORD_RIGHT1), static_cast<int>(SWAORD_RIGHT::SWAORD_RIGHT3), 0.040f, false);
		ToolRenderer_->CreateAnimation("Swoard_Left.bmp", "LEFT_SWOARD", static_cast<int>(SWAORD_LEFT::SWAORD_LEFT1), static_cast<int>(SWAORD_LEFT::SWAORD_LEFT3), 0.040f, false);
		ToolRenderer_->CreateAnimation("Swoard_front.bmp", "FRONT_SWOARD", static_cast<int>(SWAORD_FRONT::SWAORD_FRONT0), static_cast<int>(SWAORD_FRONT::SWAORD_FRONT4), 0.040f, false);
		ToolRenderer_->CreateAnimation("Swoard_back.bmp", "BACK_SWOARD", static_cast<int>(SWAORD_BACK::SWAORD_BACK0), static_cast<int>(SWAORD_BACK::SWAORD_BACK3), 0.040f, false);



		//------< 애니메이션 초기화 >------------------------------------------------------------------
		
		ToolRenderer_->ChangeAnimation("LEFT_INIT");
	}

	LevelChagne_ = LEVEL_CHANGE_STATE::CHECK;

	MainPlayer = this;
	PlayerHandItem_ = PlayerHandItem_;
	MainMouse_ = MainMouse_;

	LevelInit();
}


void Player::LevelChangeEnd(GameEngineLevel* _NextLevel)
{

	if (FadeInOut_ != nullptr)
	{
		FadeInOut_->Death();
	}
	//MapObject_.erase(MapObject_.begin(), MapObject_.end());

	MainMouse_->NextLevelOn();
	PlayerHandItem_->NextLevelOn();

	PrevLevel_ = CurrentLevel_;


	if (CurrentLevel_ == "Mine1" || CurrentLevel_ == "Mine2" || CurrentLevel_ == "Mine3" || CurrentLevel_ == "Mine4" )
	{

		std::map<int, Items*> ::iterator StartIter = MapObject_.begin();
		std::map<int, Items*> ::iterator EndIter = MapObject_.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			StartIter->second->Death();
		}

		std::map<std::string, Monster*>::iterator StarMonstertIter= MonsterList_.begin();
		std::map<std::string, Monster*>::iterator EndMonstertIter = MonsterList_.end();

		for (; StarMonstertIter != EndMonstertIter; ++StarMonstertIter)
		{
			StarMonstertIter->second->Death();
		}

		//MapObject_.erase(MapObject_.begin(), MapObject_.end());
		MapObject_.clear();
	}

	//if (CurrentLevel_ == "TownLevel")
	//{
 //
	//	std::map<std::string, Npc*>::iterator StarNPCtIter = NpcList_.begin();
	//	std::map<std::string, Npc*>::iterator EndMonstertIter = NpcList_.end();

	//	for (; StarNPCtIter != EndMonstertIter; ++StarNPCtIter)
	//	{
	//		StarNPCtIter->second->Death();
	//	}
	//			MapObject_.clear();


	//	std::map<int, Items*> ::iterator StartIter = MapObject_.begin();
	//	std::map<int, Items*> ::iterator EndIter = MapObject_.end();

	//	for (; StartIter != EndIter; ++StartIter)
	//	{
	//		StartIter->second->Death();
	//	}
	//	MapObject_.clear();

	//}


}



void Player::Update()
{
	switch (LevelList_)
	{
	case LEVEL_LIST::DAYOFF_LEVEL:

		break;

	case LEVEL_LIST::TITLE_LEVEL:
		break;
	case LEVEL_LIST::MYHOUSE_LEVEL:

		GetItem();
		SetCamera();
		PlayerUpdate();
		SetPlayerHandItemPos();
		ChangeLevel();
	//	NpcCollCheck();
		DelaySpeed();
		DirAnimationChange();

		break;
	case LEVEL_LIST::MYFARM_LEVEL:



		SetCamera();
		PlayerUpdate();
		SetPlayerHandItemPos();
		ChangeLevel();
		//NpcCollCheck();
		harvestingCrops();
		DelaySpeed();
		CheckShippingBox();
		DirAnimationChange();

		break;
	case LEVEL_LIST::BUSSTOP_LEVEL:

		SetCamera();
		PlayerUpdate();
		SetPlayerHandItemPos();
		ChangeLevel();
		DelaySpeed();
		DirAnimationChange();

		break;
	case LEVEL_LIST::TOWN_LEVEL:

		SetCamera();
		NpcCollCheck();
		PlayerUpdate();
		SetPlayerHandItemPos();
		ChangeLevel();
		DelaySpeed();
		DirAnimationChange();

		break;
	case LEVEL_LIST::SALOON_LEVEL:

		SetCamera();
		NpcCollCheck();
		PlayerUpdate();
		SetPlayerHandItemPos();
		ChangeLevel();
		DelaySpeed();
		PlayerShopping();
		AddMoneyAnimation();
		SubMoneyAnimation();
		DirAnimationChange();

		break;
	case LEVEL_LIST::SEEDSHOP_LEVEL:

		SetCamera();
		NpcCollCheck();
		PlayerUpdate();
		SetPlayerHandItemPos();
		ChangeLevel();
		DelaySpeed();
		PlayerShopping();
		AddMoneyAnimation();
		SubMoneyAnimation();
		DirAnimationChange();

		break;
	case LEVEL_LIST::BACKFOREST_LEVEL:

		SetCamera();
		PlayerUpdate();
		PlayerDirCheck();
		SetPlayerHandItemPos();
		ChangeLevel();
		DelaySpeed();
		DirAnimationChange();

		break;
	case LEVEL_LIST::MINE_LEVEL:

		SetCamera();
		PlayerUpdate();
		SetPlayerHandItemPos();
		ChangeLevel();
		DelaySpeed();
		DirAnimationChange();
		UpdateInvincibilityTime();
		UpdateIsNotInvincibilityTime();
		MonsterAndPlayerColl();

		break;
	case LEVEL_LIST::MINEPOINT_LEVEL:

		SetCamera();
		PlayerUpdate();
		SetPlayerHandItemPos();
		ChangeLevel();
		DelaySpeed();
		DirAnimationChange();

		break;
	case LEVEL_LIST::MINEFLOOR_LEVEL:

		SetCamera();
		PlayerUpdate();
		SetPlayerHandItemPos();
		ChangeLevel();
		DelaySpeed();
		DirAnimationChange();

		break;
	default:
		break;
	}

	if (true == GameEngineInput::GetInst()->IsDown("MoveShopLevel"))
	{
		GameEngine::GetInst().ChangeLevel("Mine1");

	}

	if (true == GameEngineInput::GetInst()->IsDown("MoveTown"))
	{
		GameEngine::GetInst().ChangeLevel("SeedShopLevel");
	}

	if (true == GameEngineInput::GetInst()->IsDown("DebugRendereChange"))
	{
		GetLevel()->IsDebugModeSwitch();
	}

}

void Player::Render()
{

}


//------< 메인 업데이트 >------------------------------------------------------------------

void Player::PlayerUpdate()
{

	switch (PlayerState_)
	{

	case PLAYER_UPDATE::INIT:

		ChangeHandItem();
		harvestingCrops();

		//손에 들 수 있는 아이템이라면 
		if (Inventory::MainInventory->GetCurrentItem() != nullptr && Inventory::MainInventory->GetCurrentItem()->GetisPossibleHand() == true)
		{
			PlayerState_ = PLAYER_UPDATE::HANDITEM;

		}

		//인벤토리 밖 && 농사 가능한 지역이라면 툴 사용 
		if (MainMouse_->MouseClickInventoryOut())
		{
			CheckTool();//툴에 맞게 스테이트 이동
		}


		//이동키를 눌렀다면 이동스테이트로 변경
		if (isMove() && isEvent_ == false)
		{
			PlayerState_ = PLAYER_UPDATE::WALK;
		}


		break;

	case PLAYER_UPDATE::HOE:

		if (PlayerBodyRenderer_->IsEndAnimation())
		{		AttackMonster();

			if (FarmingArea_ == true)
			{
				CreateDirtTile();
				ChangeDirtTile();

				SubEnergy(2);
			}

			PlayerState_ = PLAYER_UPDATE::INIT;
		}

		break;

	case PLAYER_UPDATE::WATER:

		if (PlayerBodyRenderer_->IsEndAnimation())
		{
			CreateWaterEffet();
			CreateWaterTile();
			ChangeWetDirtTile();

			SubEnergy(2);

			PlayerState_ = PLAYER_UPDATE::INIT;
		}

		break;

	case PLAYER_UPDATE::AXE:

		if (PlayerBodyRenderer_->IsEndAnimation())
		{
			CrushTree();
			CrushWood();
			SubEnergy(2);

			PlayerState_ = PLAYER_UPDATE::INIT;
		}


		break;

	case PLAYER_UPDATE::PICKAXE:

		if (PlayerBodyRenderer_->IsEndAnimation())
		{
			CrushStone();
			AttackMonster();

			PlayerState_ = PLAYER_UPDATE::INIT;
		}


		break;
	case PLAYER_UPDATE::SWOARD:

		ToolRenderer_->SetPivot({ 0, 38 });
		if (GetDirString() == "BACK_")
		{
			ToolRenderer_->SetOrder({ static_cast<int>(PLAYLEVEL::BOTTOM_EFFECT) });
			PlayerHandRenderer_->SetOrder({ static_cast<int>(PLAYLEVEL::BOTTOM_EFFECT) });

		}

		if (PlayerBodyRenderer_->IsEndAnimation())
		{
			SubEnergy(2);

			ToolRenderer_->SetPivot({0, 0});
			PlayerHandRenderer_->SetOrder({ static_cast<int>(PLAYLEVEL::PLAYER) });
			ToolRenderer_->SetOrder({ static_cast<int>(PLAYLEVEL::USE_TOOL) });
			PlayerState_ = PLAYER_UPDATE::INIT;
		}

		break;

	case PLAYER_UPDATE::HANDITEM:

		PlayerDirCheck();
		ChangeLevel();
		ChangeHandItem();
		CheckDrink();
		CheckEat();

		if (MainMouse_->MouseClickInventoryOut())
		{
			CreateSeed();
		}

		//손에 들 수 없는 아이템을 선택했다면 기본 상태로 돌아간다.
		if (Inventory::MainInventory->GetCurrentItem() != nullptr && Inventory::MainInventory->GetCurrentItem()->GetisPossibleHand() == false)
		{
			PlayerState_ = PLAYER_UPDATE::INIT;

		}

		if (isMove()
			&& Inventory::MainInventory->GetCurrentItem()->GetisPossibleHand() == true)
		{
			PlayerState_ = PLAYER_UPDATE::HANDITEMWALK;
		}


		break;


	case PLAYER_UPDATE::WALK:
		PlayerDirCheck();
		PlayerWalk();
		harvestingCrops();
		CheckDrink();
		CheckEat();


		if (isStop())
		{
			PlayerState_ = PLAYER_UPDATE::INIT;
		}

		break;

	case PLAYER_UPDATE::HANDITEMWALK:
		PlayerDirCheck();
		PlayerWalk();


		if (MainMouse_->MouseClickInventoryOut())
		{
			CreateSeed();
		}

		if (isStop())
		{
			PlayerState_ = PLAYER_UPDATE::INIT;
		}

		break;


	case PLAYER_UPDATE::FAINT:
		PlayerState_ = PLAYER_UPDATE::FAINT;

		//플레이어에서 체크해도 괜찮지만 매번 돌리기엔 부담..

		PlayerBodyRenderer_->ChangeAnimation(GetDirString() + ArrAnimationName[static_cast<int>(PlayerState_)]);
		PlayerPantsRenderer_->ChangeAnimation(GetDirString() + ArrAnimationName[static_cast<int>(PlayerState_)]);
		PlayerShirtsRenderer_->ChangeAnimation(GetDirString() + ArrAnimationName[static_cast<int>(PlayerState_)]);
		PlayerHairRenderer_->ChangeAnimation(GetDirString() + ArrAnimationName[static_cast<int>(PlayerState_)]);
		PlayerHandRenderer_->ChangeAnimation(GetDirString() + ArrAnimationName[static_cast<int>(PlayerState_)]);

		if (PlayerBodyRenderer_->IsEndAnimation())
		{
			FadeInOut_ = GetLevel()->CreateActor<FadeInOut>(static_cast<int>(PLAYLEVEL::FADE));

			ChangeLevelName_ = "DayOffLevel";
			FadeInOut_->SetFadeOut();
			LevelChagne_ = LEVEL_CHANGE_STATE::FADE_OUT;
			PlayerState_ = PLAYER_UPDATE::INIT;

		}


		break;
	case PLAYER_UPDATE::EAT_WAIT:

		AnimationWaitTimer_ += GameEngineTime::GetDeltaTime() ;
		if (AnimationWaitTimer_ > 0.5f)
		{
			AnimationWaitTimer_ = 0.f;
			PlayerState_ = PLAYER_UPDATE::EAT;

		}

		break;

	case PLAYER_UPDATE::EAT:

		if (PlayerBodyRenderer_->IsEndAnimation())
		{
			GetCurrentItem()->SubItemCount();
			AddEnergy(GetCurrentItem()->GetAddHP());
			PlayerState_ = PLAYER_UPDATE::INIT;
		}

		break;
	case PLAYER_UPDATE::DRINK:

		if (PlayerBodyRenderer_->IsEndAnimation())
		{
			GetCurrentItem()->SubItemCount();
			AddEnergy(GetCurrentItem()->GetAddHP());
			isDelaySpeed_ = true;
			DelaySpeed_ = GetCurrentItem()->GetDrinkChangeSpeed();
			Speed_ += DelaySpeed_;
			DelaySpeedTimer_ = GetCurrentItem()->GetChangeSpeedTime();
			PlayerState_ = PLAYER_UPDATE::INIT;
		}

		break;
	case PLAYER_UPDATE::SHOPPING:
		MoveDir_ = float4::UP;

		break;
	case PLAYER_UPDATE::GETITEM:

		MoveDir_ = float4::DOWN;
		break;

	case PLAYER_UPDATE::TALKING:


		break;
	default:
		break;
	}

}

void Player::LevelInit()
{
	//------< 기본 세팅 >------------------------------------------------------------------

	MainMouse_->Renderer()->CameraEffectOff();
	CurrentLevel_ = GetCurrentLevel();

	if (CurrentLevel_ == "DayOffLevel")
	{
		LevelList_ = LEVEL_LIST::TITLE_LEVEL;

		MapColImage_ = nullptr;
		ToolRenderer_->CameraEffectOff();

		PlayerHandItem_->GetRenderer()->CameraEffectOn();

		PlayerBodyRenderer_->CameraEffectOff();
		PlayerPantsRenderer_->CameraEffectOff();
		PlayerShirtsRenderer_->CameraEffectOff();
		PlayerHairRenderer_->CameraEffectOff();
		PlayerHandRenderer_->CameraEffectOff();

		//MainPlayer->Off();
		//Inventory::MainInventory->AllUpdateOff();
	}



	if (CurrentLevel_ == "TitleLevel")
	{
		LevelList_ = LEVEL_LIST::TITLE_LEVEL;

		MapColImage_ = nullptr;
		ToolRenderer_->CameraEffectOff();

		PlayerHandItem_->GetRenderer()->CameraEffectOn();

		PlayerBodyRenderer_->CameraEffectOff();
		PlayerPantsRenderer_->CameraEffectOff();
		PlayerShirtsRenderer_->CameraEffectOff();
		PlayerHairRenderer_->CameraEffectOff();
		PlayerHandRenderer_->CameraEffectOff();
	}

	if (CurrentLevel_ == "MyHouseLevel")
	{
		LevelList_ = LEVEL_LIST::MYHOUSE_LEVEL;

		MapColImage_ = GameEngineImageManager::GetInst()->Find("PlayerHouse_Coll.bmp");
		ToolRenderer_->CameraEffectOff();

		PlayerHandItem_->GetRenderer()->CameraEffectOff();

		PlayerBodyRenderer_->CameraEffectOff();
		PlayerPantsRenderer_->CameraEffectOff();
		PlayerShirtsRenderer_->CameraEffectOff();
		PlayerHairRenderer_->CameraEffectOff();
		PlayerHandRenderer_->CameraEffectOff();

		//MainPlayer->On();
	}

	if (CurrentLevel_ == "MyFarmLevel")
	{
		LevelList_ = LEVEL_LIST::MYFARM_LEVEL;

		MapSizeX_ = FARM_SIZE_WEIGHT;
		MapSizeY_ = FARM_SIZE_HEIGHT;

		MapColImage_ = GameEngineImageManager::GetInst()->Find("FarmBack_Coll.bmp");
		ToolRenderer_->CameraEffectOn();

		PlayerHandItem_->GetRenderer()->CameraEffectOn();

		PlayerBodyRenderer_->CameraEffectOn();
		PlayerPantsRenderer_->CameraEffectOn();
		PlayerShirtsRenderer_->CameraEffectOn();
		PlayerHairRenderer_->CameraEffectOn();
		PlayerHandRenderer_->CameraEffectOn();
	}


	if (CurrentLevel_ == "BusStopLevel")
	{
		LevelList_ = LEVEL_LIST::BUSSTOP_LEVEL;

		MapSizeX_ = BUSSTOP_SIZE_WEIGHT;
		MapSizeY_ = BUSSTOP_SIZE_HEIGHT;

		MapColImage_ = nullptr;
		ToolRenderer_->CameraEffectOn();

		PlayerHandItem_->GetRenderer()->CameraEffectOn();

		PlayerBodyRenderer_->CameraEffectOn();
		PlayerPantsRenderer_->CameraEffectOn();
		PlayerShirtsRenderer_->CameraEffectOn();
		PlayerHairRenderer_->CameraEffectOn();
		PlayerHandRenderer_->CameraEffectOn();
	}


	if (CurrentLevel_ == "TownLevel")
	{
		LevelList_ = LEVEL_LIST::TOWN_LEVEL;

		MapSizeX_ = TOWN_SIZE_WEIGHT;
		MapSizeY_ = TOWN_SIZE_HEIGHT;

		MapColImage_ = nullptr;
		ToolRenderer_->CameraEffectOn();

		PlayerHandItem_->GetRenderer()->CameraEffectOn();

		PlayerBodyRenderer_->CameraEffectOn();
		PlayerPantsRenderer_->CameraEffectOn();
		PlayerShirtsRenderer_->CameraEffectOn();
		PlayerHairRenderer_->CameraEffectOn();
		PlayerHandRenderer_->CameraEffectOn();
	}

	if (CurrentLevel_ == "SeedShopLevel")
	{
		LevelList_ = LEVEL_LIST::SEEDSHOP_LEVEL;

		MapSizeX_ = SHOP_SIZE_WEIGHT;
		MapSizeY_ = SHOP_SIZE_HEIGHT;

		MapColImage_ = nullptr;
		ToolRenderer_->CameraEffectOn();

		PlayerHandItem_->GetRenderer()->CameraEffectOn();

		PlayerBodyRenderer_->CameraEffectOn();
		PlayerPantsRenderer_->CameraEffectOn();
		PlayerShirtsRenderer_->CameraEffectOn();
		PlayerHairRenderer_->CameraEffectOn();
		PlayerHandRenderer_->CameraEffectOn();
	}


	if (CurrentLevel_ == "SaloonLevel")
	{
		LevelList_ = LEVEL_LIST::SALOON_LEVEL;

		MapSizeX_ = SALOON_SIZE_WEIGHT;
		MapSizeY_ = SALOON_SIZE_HEIGHT;

		MapColImage_ = nullptr;
		ToolRenderer_->CameraEffectOn();

		PlayerHandItem_->GetRenderer()->CameraEffectOn();

		PlayerBodyRenderer_->CameraEffectOn();
		PlayerPantsRenderer_->CameraEffectOn();
		PlayerShirtsRenderer_->CameraEffectOn();
		PlayerHairRenderer_->CameraEffectOn();
		PlayerHandRenderer_->CameraEffectOn();
	}


	if (CurrentLevel_ == "BackForestLevel")
	{
		LevelList_ = LEVEL_LIST::BACKFOREST_LEVEL;

		MapSizeX_ = FOREST_SIZE_WEIGHT;
		MapSizeY_ = FOREST_SIZE_HEIGHT;

		MapColImage_ = nullptr;
		ToolRenderer_->CameraEffectOn();

		PlayerHandItem_->GetRenderer()->CameraEffectOn();

		PlayerBodyRenderer_->CameraEffectOn();
		PlayerPantsRenderer_->CameraEffectOn();
		PlayerShirtsRenderer_->CameraEffectOn();
		PlayerHairRenderer_->CameraEffectOn();
		PlayerHandRenderer_->CameraEffectOn();
	}

	if (CurrentLevel_ == "MineLevel")
	{
		LevelList_ = LEVEL_LIST::MINE_LEVEL;

		MapSizeX_ = MINE_SIZE_WEIGHT;
		MapSizeY_ = MINE_SIZE_HEIGHT;

		MapColImage_ = GameEngineImageManager::GetInst()->Find("MineStartColl.bmp");
		ToolRenderer_->CameraEffectOn();

		PlayerHandItem_->GetRenderer()->CameraEffectOn();

		PlayerBodyRenderer_->CameraEffectOn();
		PlayerPantsRenderer_->CameraEffectOn();
		PlayerShirtsRenderer_->CameraEffectOn();
		PlayerHairRenderer_->CameraEffectOn();
		PlayerHandRenderer_->CameraEffectOn();
	}


	if (CurrentLevel_ == "MinePoint")
	{
		LevelList_ = LEVEL_LIST::MINEPOINT_LEVEL;

		MapSizeX_ = MINEPOINT_SIZE_WEIGHT;
		MapSizeY_ = MINEPOINT_SIZE_HEIGHT;

		MapColImage_ = GameEngineImageManager::GetInst()->Find("Empty.bmp");
		ToolRenderer_->CameraEffectOn();

		PlayerHandItem_->GetRenderer()->CameraEffectOn();

		PlayerBodyRenderer_->CameraEffectOn();
		PlayerPantsRenderer_->CameraEffectOn();
		PlayerShirtsRenderer_->CameraEffectOn();
		PlayerHairRenderer_->CameraEffectOn();
		PlayerHandRenderer_->CameraEffectOn();
	}


	if (CurrentLevel_ == "Mine1" 
		|| CurrentLevel_ == "Mine2"
		|| CurrentLevel_ == "Mine3"
		|| CurrentLevel_ == "Mine4")
	{
		LevelList_ = LEVEL_LIST::MINE_LEVEL;

		MapSizeX_ = MINEFLOOR_SIZE_WEIGHT;
		MapSizeY_ = MINEFLOOR_SIZE_HEIGHT;

		MapColImage_ = GameEngineImageManager::GetInst()->Find("Empty.bmp");
		ToolRenderer_->CameraEffectOn();

		PlayerHandItem_->GetRenderer()->CameraEffectOn();

		PlayerBodyRenderer_->CameraEffectOn();
		PlayerPantsRenderer_->CameraEffectOn();
		PlayerShirtsRenderer_->CameraEffectOn();
		PlayerHairRenderer_->CameraEffectOn();
		PlayerHandRenderer_->CameraEffectOn();
	}


	//------< 위치 초기화 >------------------------------------------------------------------

	//쓰러지고 집

	if (CurrentLevel_ == "MyHouseLevel" && PrevLevel_ == "DayOffLevel")
	{
		SetPosition({ 790.f, 490.f });
	}
	// 집 -> 마인
	if (CurrentLevel_ == "Mine1" && PrevLevel_ == "MyHouseLevel")
	{
		SetPosition({ 250.f , 500.f });
	}


	// 타이틀 -> 집
	if (CurrentLevel_ == "TownLevel" && PrevLevel_ == "")
	{
		SetPosition({ 110.f, 2620.f });
	}

	// 타이틀 -> 집
	if (CurrentLevel_ == "MyHouseLevel" && PrevLevel_ == "")
	{
		SetPosition({ 790.f, 490.f });
	}

	// 집 -> 농장
	if (CurrentLevel_ == "MyFarmLevel" && PrevLevel_ == "MyHouseLevel")
	{
		SetPosition({ 3100.f, 760.f });
	}

	// 농장 -> 집
	if (CurrentLevel_ == "MyHouseLevel" && PrevLevel_ == "MyFarmLevel")
	{
		SetPosition({ 540.f, 550.f });
	}

	// 농장 -> 뒷산
	if (CurrentLevel_ == "BackForestLevel" && PrevLevel_ == "MyFarmLevel")
	{
		SetPosition({ 695.f, 1830.f });
	}


	// 뒷산 -> 농장
	if (CurrentLevel_ == "MyFarmLevel" && PrevLevel_ == "BackForestLevel")
	{
		SetPosition({ 1965.f, 110.f });
	}

	// 뒷산 -> 광산
	if (CurrentLevel_ == "MineLevel" && PrevLevel_ == "BackForestLevel")
	{
		SetPosition({ 890.f, 685.f });
	}

	// 광산 -> 광산포인트
	if (CurrentLevel_ == "MinePoint" && PrevLevel_ == "MineLevel")
	{
		SetPosition({ 845.f, 300.f });
	}

	// 광산포인트 -> 광산1
	if (CurrentLevel_ == "Mine1" && PrevLevel_ == "MinePoint")
	{
		SetPosition({ 215.f, 300.f });
	}

	// 광산1 -> 광산2
	if (CurrentLevel_ == "Mine2" && PrevLevel_ == "Mine1")
	{
		SetPosition({ 335.f, 1550.f });
	}

	// 광산2 -> 광산3
	if (CurrentLevel_ == "Mine3" && PrevLevel_ == "Mine2")
	{
		SetPosition({ 887.f, 200.f });
	}

	// 광산3 -> 광산4
	if (CurrentLevel_ == "Mine4" && PrevLevel_ == "Mine3")
	{
		SetPosition({ 600.f, 295.f });
	}


	// 광산4 -> 광산
	if (CurrentLevel_ == "MineLevel" && PrevLevel_ == "Mine4")
	{
		SetPosition({ 1127.f, 510.f });
	}


	// 광산3 -> 광산
	if (CurrentLevel_ == "MineLevel" && PrevLevel_ == "Mine3")
	{
		SetPosition({ 1127.f, 510.f });
	}


	// 광산2 -> 광산
	if (CurrentLevel_ == "MineLevel" && PrevLevel_ == "Mine2")
	{
		SetPosition({ 1127.f, 510.f });
	}

	// 광산1 -> 광산
	if (CurrentLevel_ == "MineLevel" && PrevLevel_ == "Mine1")
	{
		SetPosition({ 1127.f, 510.f });
	}

	// 광산포인트 -> 광산
	if (CurrentLevel_ == "MineLevel" && PrevLevel_ == "MinePoint")
	{
		SetPosition({ 1127.f, 510.f });
	}


	// 버스정류장 -> 농장
	if (CurrentLevel_ == "MyFarmLevel" && PrevLevel_ == "BusStopLevel")
	{
		SetPosition({ 3740.f, 780.f });
	}

	// 농장 -> 버스정류장
	if (CurrentLevel_ == "BusStopLevel" && PrevLevel_ == "MyFarmLevel")
	{
		SetPosition({ 120.f, 1120.f });
	}

	// 마을 -> 버스정류장
	if (CurrentLevel_ == "BusStopLevel" && PrevLevel_ == "TownLevel")
	{
		SetPosition({ 1580.f, 1120.f });
	}

	// 버스정류장 -> 마을
	if (CurrentLevel_ == "TownLevel" && PrevLevel_ == "BusStopLevel")
	{
		SetPosition({ 110.f, 2620.f });
	}

	// 상점 -> 마을
	if (CurrentLevel_ == "TownLevel" && PrevLevel_ == "SeedShopLevel")
	{
		SetPosition({ 2100.f, 2780.f });
	} 

	// 마을 -> 상점
	if (CurrentLevel_ == "SeedShopLevel" && PrevLevel_ == "TownLevel")
	{
		SetPosition({ 310.f, 1320.f });
	}

	// 마을 -> 주점
	if (CurrentLevel_ == "SaloonLevel" && PrevLevel_ == "TownLevel")
	{
		SetPosition({ 695.f, 1140.f });
	}

	// 주점 -> 마을
	if (CurrentLevel_ == "TownLevel" && PrevLevel_ == "SaloonLevel")
	{
		SetPosition({ 1185.f, 3480.f });
	}

	// 집 -> 주점
	if (CurrentLevel_ == "SaloonLevel" && PrevLevel_ == "MyHouseLevel")
	{
		SetPosition({ 695.f, 1140.f });
	}

	DayOffFarming_ = 0;
	DayOffFForaging_ = 0;
	DayOffFishing_ = 0;
	DayOffMining_ = 0;
	DayOffOther_ = 0;



}

