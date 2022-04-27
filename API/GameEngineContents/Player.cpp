#include "Player.h"

#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineLevel.h> 
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>

#include "PlayerSpriteData.h"
#include "TileData.h"

std::string Player::CurrentLevel_ = "TitleLevel";
std::string Player::PrevLevel_ = "";

Player* Player::MainPlayer = nullptr;
PlayerHandItem* Player::PlayerHandItem_ = nullptr;
Mouse* Player::MainMouse_ = nullptr;

Player::Player()
	:
	Money_(1000),

	AnimationFrame_(0.120f),
	Speed_(180.f),
	Energy_(126),
	MapSizeX_(0.f),
	MapSizeY_(0.f),

	PlayerBodyRenderer_(nullptr),
	PlayerPantsRenderer_(nullptr),
	PlayerShirtsRenderer_(nullptr),
	PlayerHairRenderer_(nullptr),
	PlayerHandRenderer_(nullptr),

	ToolRenderer_(nullptr),
	PlayerCollider_(nullptr),
	MapColImage_(nullptr),

	ObjectColl_(false),
	FarmingArea_(false),
	isShopping_(false),
	isEvent_(false),

	WetTileMap_(nullptr),
	DirtTileMap_(nullptr),
	MoveDir_(float4::DOWN),

	CurrentItemType_(TOOLTYPE::OTHER),
	UseToolState_(USE_TOOL::INIT),
	TileState_(TILE_COLL::INIT),
	PlayerState_(PLAYER_UPDATE::INIT),
	PlayerShoppingState_(PLAYER_SHOPPING::INT)



{
	ArrAnimationName[static_cast<int>(PLAYER_UPDATE::INIT)] = "INIT";
	ArrAnimationName[static_cast<int>(PLAYER_UPDATE::WALK)] = "WALK";
	ArrAnimationName[static_cast<int>(PLAYER_UPDATE::WATER)] = "WATER";
	ArrAnimationName[static_cast<int>(PLAYER_UPDATE::HOE)] = "HOE";
	ArrAnimationName[static_cast<int>(PLAYER_UPDATE::AXE)] = "HOE";
	ArrAnimationName[static_cast<int>(PLAYER_UPDATE::PICKAXE)] = "HOE";
	ArrAnimationName[static_cast<int>(PLAYER_UPDATE::HANDITEM)] = "HANDITEM";
	ArrAnimationName[static_cast<int>(PLAYER_UPDATE::HANDITEMWALK)] = "HANDITEMWALK";



	ArrAnimationToolName[static_cast<int>(PLAYER_UPDATE::INIT)] = "INIT";
	ArrAnimationToolName[static_cast<int>(PLAYER_UPDATE::WALK)] = "INIT";
	ArrAnimationToolName[static_cast<int>(PLAYER_UPDATE::HANDITEM)] = "INIT";
	ArrAnimationToolName[static_cast<int>(PLAYER_UPDATE::HANDITEMWALK)] = "INIT";
	ArrAnimationToolName[static_cast<int>(PLAYER_UPDATE::WATER)] = "WATER";
	ArrAnimationToolName[static_cast<int>(PLAYER_UPDATE::HOE)] = "HOE";
	ArrAnimationToolName[static_cast<int>(PLAYER_UPDATE::AXE)] = "AXE";
	ArrAnimationToolName[static_cast<int>(PLAYER_UPDATE::PICKAXE)] = "PICKAXE";



}


Player::~Player() 
{
	CurrentLevel_ = "";


}

void Player::Start()
{
	//------< 액터 등록 >------------------------------------------------------------------

	//	Shop_ = GetLevel()->CreateActor<Shop>((int)PLAYLEVEL::SHOP);

	PlayerHandItem_ = GetLevel()->CreateActor<PlayerHandItem>((int)PLAYLEVEL::HAND_ITEM);
	MainMouse_ = GetLevel()->CreateActor<Mouse>((int)PLAYLEVEL::MOUSE);

	//------< 초기화 >------------------------------------------------------------------
	MapColImage_ = GameEngineImageManager::GetInst()->Find("PlayerHouse_Coll.bmp");
	
	PlayerBodyRenderer_ = CreateRenderer();


	PlayerPantsRenderer_ = CreateRenderer();
	PlayerShirtsRenderer_ = CreateRenderer();
	PlayerHairRenderer_ = CreateRenderer();
	PlayerHandRenderer_ = CreateRenderer();

	PlayerBodyRenderer_->SetPivotType(RenderPivot::BOT);
	PlayerPantsRenderer_->SetPivotType(RenderPivot::BOT);
	PlayerShirtsRenderer_->SetPivotType(RenderPivot::BOT);
	PlayerHairRenderer_->SetPivotType(RenderPivot::BOT);
	PlayerHandRenderer_->SetPivotType(RenderPivot::BOT);

	PlayerBodyRenderer_->SetOrder(static_cast<int>(PLAYLEVEL::PLAYER_BODY));
	PlayerPantsRenderer_->SetOrder(static_cast<int>(PLAYLEVEL::PLAYER_PANTS));
	PlayerShirtsRenderer_->SetOrder(static_cast<int>(PLAYLEVEL::PLAYER_SHIRTS));
	PlayerHairRenderer_->SetOrder(static_cast<int>(PLAYLEVEL::PLAYER_HAIR));
	PlayerHandRenderer_->SetOrder(static_cast<int>(PLAYLEVEL::PLAYER_HAND));


	ToolRenderer_ = CreateRenderer();
	ToolRenderer_->SetPivotType(RenderPivot::BOT);
	ToolRenderer_->SetOrder(static_cast<int>(PLAYLEVEL::USE_TOOL));

	PlayerCollider_ = CreateCollision("Player", { 40.f, 30 });
	//PlayerCollider_->SetPivot({0, 20});
	SetScale({ 40.f, 40.f });

	CameraPos_ = GetPosition() - GameEngineWindow::GetInst().GetScale().Half();


	//------< 애니메이션 생성 >------------------------------------------------------------------

	//================================
	//     플레이어 대기
	//================================
	PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "RIGHT_INIT", static_cast<int>(PLAYER::RIGHT_INIT), static_cast<int>(PLAYER::RIGHT_INIT), 0.0f, false);
	PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "LEFT_INIT", static_cast<int>(PLAYER::LEFT_INIT),  static_cast<int>(PLAYER::LEFT_INIT), 0.0f, false);
	PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "FRONT_INIT", static_cast<int>(PLAYER::FRONT_INIT), static_cast<int>(PLAYER::FRONT_INIT), 0.0f, false);
	PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "BACK_INIT", static_cast<int>(PLAYER::BACK_INIT),  static_cast<int>(PLAYER::BACK_INIT), 0.0f, false);

	PlayerPantsRenderer_->CreateAnimation("PlayerPants0.bmp", "RIGHT_INIT", static_cast<int>(PLAYER::RIGHT_INIT), static_cast<int>(PLAYER::RIGHT_INIT), 0.0f, false);
	PlayerPantsRenderer_->CreateAnimation("PlayerPants0.bmp", "LEFT_INIT", static_cast<int>(PLAYER::LEFT_INIT), static_cast<int>(PLAYER::LEFT_INIT), 0.0f, false);
	PlayerPantsRenderer_->CreateAnimation("PlayerPants0.bmp", "FRONT_INIT", static_cast<int>(PLAYER::FRONT_INIT), static_cast<int>(PLAYER::FRONT_INIT), 0.0f, false);
	PlayerPantsRenderer_->CreateAnimation("PlayerPants0.bmp", "BACK_INIT", static_cast<int>(PLAYER::BACK_INIT), static_cast<int>(PLAYER::BACK_INIT), 0.0f, false);

	PlayerShirtsRenderer_->CreateAnimation("PlayerShirt0.bmp", "RIGHT_INIT", static_cast<int>(PLAYER::RIGHT_INIT), static_cast<int>(PLAYER::RIGHT_INIT), 0.0f, false);
	PlayerShirtsRenderer_->CreateAnimation("PlayerShirt0.bmp", "LEFT_INIT", static_cast<int>(PLAYER::LEFT_INIT), static_cast<int>(PLAYER::LEFT_INIT), 0.0f, false);
	PlayerShirtsRenderer_->CreateAnimation("PlayerShirt0.bmp", "FRONT_INIT", static_cast<int>(PLAYER::FRONT_INIT), static_cast<int>(PLAYER::FRONT_INIT), 0.0f, false);
	PlayerShirtsRenderer_->CreateAnimation("PlayerShirt0.bmp", "BACK_INIT", static_cast<int>(PLAYER::BACK_INIT), static_cast<int>(PLAYER::BACK_INIT), 0.0f, false);

	PlayerHairRenderer_->CreateAnimation("PlayerHair0.bmp", "RIGHT_INIT", static_cast<int>(PLAYER::RIGHT_INIT), static_cast<int>(PLAYER::RIGHT_INIT), 0.0f, false);
	PlayerHairRenderer_->CreateAnimation("PlayerHair0.bmp", "LEFT_INIT", static_cast<int>(PLAYER::LEFT_INIT), static_cast<int>(PLAYER::LEFT_INIT), 0.0f, false);
	PlayerHairRenderer_->CreateAnimation("PlayerHair0.bmp", "FRONT_INIT", static_cast<int>(PLAYER::FRONT_INIT), static_cast<int>(PLAYER::FRONT_INIT), 0.0f, false);
	PlayerHairRenderer_->CreateAnimation("PlayerHair0.bmp", "BACK_INIT", static_cast<int>(PLAYER::BACK_INIT), static_cast<int>(PLAYER::BACK_INIT), 0.0f, false);

	PlayerHandRenderer_->CreateAnimation("PlayerHand0.bmp", "RIGHT_INIT", static_cast<int>(PLAYER::RIGHT_INIT), static_cast<int>(PLAYER::RIGHT_INIT), 0.0f, false);
	PlayerHandRenderer_->CreateAnimation("PlayerHand0.bmp", "LEFT_INIT", static_cast<int>(PLAYER::LEFT_INIT), static_cast<int>(PLAYER::LEFT_INIT), 0.0f, false);
	PlayerHandRenderer_->CreateAnimation("PlayerHand0.bmp", "FRONT_INIT", static_cast<int>(PLAYER::FRONT_INIT), static_cast<int>(PLAYER::FRONT_INIT), 0.0f, false);
	PlayerHandRenderer_->CreateAnimation("PlayerHand0.bmp", "BACK_INIT", static_cast<int>(PLAYER::BACK_INIT), static_cast<int>(PLAYER::BACK_INIT), 0.0f, false);




	//================================
	//     플레이어 이동 
	//================================
	PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "RIGHT_WALK",  static_cast<int>(PLAYER::RIGHT_WALK0),  static_cast<int>(PLAYER::RIGHT_WALK5), AnimationFrame_, true);
	PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "LEFT_WALK",   static_cast<int>(PLAYER::LEFT_WALK0),  static_cast<int>(PLAYER::LEFT_WALK5), AnimationFrame_, true);
	PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "FRONT_WALK",  static_cast<int>(PLAYER::FRONT_WALK0),  static_cast<int>(PLAYER::FRONT_WALK3), AnimationFrame_, true);
	PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "BACK_WALK",   static_cast<int>(PLAYER::BACK_WALK0),  static_cast<int>(PLAYER::BACK_WALK3), AnimationFrame_, true);

	PlayerPantsRenderer_->CreateAnimation("PlayerPants0.bmp", "RIGHT_WALK", static_cast<int>(PLAYER::RIGHT_WALK0), static_cast<int>(PLAYER::RIGHT_WALK5), AnimationFrame_, true);
	PlayerPantsRenderer_->CreateAnimation("PlayerPants0.bmp", "LEFT_WALK", static_cast<int>(PLAYER::LEFT_WALK0), static_cast<int>(PLAYER::LEFT_WALK5), AnimationFrame_, true);
	PlayerPantsRenderer_->CreateAnimation("PlayerPants0.bmp", "FRONT_WALK", static_cast<int>(PLAYER::FRONT_WALK0), static_cast<int>(PLAYER::FRONT_WALK3), AnimationFrame_, true);
	PlayerPantsRenderer_->CreateAnimation("PlayerPants0.bmp", "BACK_WALK", static_cast<int>(PLAYER::BACK_WALK0), static_cast<int>(PLAYER::BACK_WALK3), AnimationFrame_, true);

	PlayerShirtsRenderer_->CreateAnimation("PlayerShirt0.bmp", "RIGHT_WALK", static_cast<int>(PLAYER::RIGHT_WALK0), static_cast<int>(PLAYER::RIGHT_WALK5), AnimationFrame_, true);
	PlayerShirtsRenderer_->CreateAnimation("PlayerShirt0.bmp", "LEFT_WALK", static_cast<int>(PLAYER::LEFT_WALK0), static_cast<int>(PLAYER::LEFT_WALK5), AnimationFrame_, true);
	PlayerShirtsRenderer_->CreateAnimation("PlayerShirt0.bmp", "FRONT_WALK", static_cast<int>(PLAYER::FRONT_WALK0), static_cast<int>(PLAYER::FRONT_WALK3), AnimationFrame_, true);
	PlayerShirtsRenderer_->CreateAnimation("PlayerShirt0.bmp", "BACK_WALK", static_cast<int>(PLAYER::BACK_WALK0), static_cast<int>(PLAYER::BACK_WALK3), AnimationFrame_, true);

	PlayerHairRenderer_->CreateAnimation("PlayerHair0.bmp", "RIGHT_WALK", static_cast<int>(PLAYER::RIGHT_WALK0), static_cast<int>(PLAYER::RIGHT_WALK5), AnimationFrame_, true);
	PlayerHairRenderer_->CreateAnimation("PlayerHair0.bmp", "LEFT_WALK", static_cast<int>(PLAYER::LEFT_WALK0), static_cast<int>(PLAYER::LEFT_WALK5), AnimationFrame_, true);
	PlayerHairRenderer_->CreateAnimation("PlayerHair0.bmp", "FRONT_WALK", static_cast<int>(PLAYER::FRONT_WALK0), static_cast<int>(PLAYER::FRONT_WALK3), AnimationFrame_, true);
	PlayerHairRenderer_->CreateAnimation("PlayerHair0.bmp", "BACK_WALK", static_cast<int>(PLAYER::BACK_WALK0), static_cast<int>(PLAYER::BACK_WALK3), AnimationFrame_, true);

	PlayerHandRenderer_->CreateAnimation("PlayerHand0.bmp", "RIGHT_WALK", static_cast<int>(PLAYER::RIGHT_WALK0), static_cast<int>(PLAYER::RIGHT_WALK5), AnimationFrame_, true);
	PlayerHandRenderer_->CreateAnimation("PlayerHand0.bmp", "LEFT_WALK", static_cast<int>(PLAYER::LEFT_WALK0), static_cast<int>(PLAYER::LEFT_WALK5), AnimationFrame_, true);
	PlayerHandRenderer_->CreateAnimation("PlayerHand0.bmp", "FRONT_WALK", static_cast<int>(PLAYER::FRONT_WALK0), static_cast<int>(PLAYER::FRONT_WALK3), AnimationFrame_, true);
	PlayerHandRenderer_->CreateAnimation("PlayerHand0.bmp", "BACK_WALK", static_cast<int>(PLAYER::BACK_WALK0), static_cast<int>(PLAYER::BACK_WALK3), AnimationFrame_, true);


	//================================
	//     플레이어 손 번쩍! 대기
	//================================
	PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "RIGHT_HANDITEM",  static_cast<int>(PLAYER::RIGHT_HAND_INIT), static_cast<int>(PLAYER::RIGHT_HAND_INIT), 0.0f, false);
	PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "LEFT_HANDITEM",  static_cast<int>(PLAYER::LEFT_HAND_INIT), static_cast<int>(PLAYER::LEFT_HAND_INIT), 0.0f, false);
	PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "FRONT_HANDITEM", static_cast<int>(PLAYER::FRONT_HAND_INIT), static_cast<int>(PLAYER::FRONT_HAND_INIT), 0.0f, false);
	PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "BACK_HANDITEM", static_cast<int>(PLAYER::BACK_HAND_INIT), static_cast<int>(PLAYER::BACK_HAND_INIT), 0.0f, false);

	PlayerPantsRenderer_->CreateAnimation("PlayerPants0.bmp", "RIGHT_HANDITEM", static_cast<int>(PLAYER::RIGHT_HAND_INIT), static_cast<int>(PLAYER::RIGHT_HAND_INIT), 0.0f, false);
	PlayerPantsRenderer_->CreateAnimation("PlayerPants0.bmp", "LEFT_HANDITEM", static_cast<int>(PLAYER::LEFT_HAND_INIT), static_cast<int>(PLAYER::LEFT_HAND_INIT), 0.0f, false);
	PlayerPantsRenderer_->CreateAnimation("PlayerPants0.bmp", "FRONT_HANDITEM", static_cast<int>(PLAYER::FRONT_HAND_INIT), static_cast<int>(PLAYER::FRONT_HAND_INIT), 0.0f, false);
	PlayerPantsRenderer_->CreateAnimation("PlayerPants0.bmp", "BACK_HANDITEM", static_cast<int>(PLAYER::BACK_HAND_INIT), static_cast<int>(PLAYER::BACK_HAND_INIT), 0.0f, false);

	PlayerShirtsRenderer_->CreateAnimation("PlayerShirt0.bmp", "RIGHT_HANDITEM", static_cast<int>(PLAYER::RIGHT_HAND_INIT), static_cast<int>(PLAYER::RIGHT_HAND_INIT), 0.0f, false);
	PlayerShirtsRenderer_->CreateAnimation("PlayerShirt0.bmp", "LEFT_HANDITEM", static_cast<int>(PLAYER::LEFT_HAND_INIT), static_cast<int>(PLAYER::LEFT_HAND_INIT), 0.0f, false);
	PlayerShirtsRenderer_->CreateAnimation("PlayerShirt0.bmp", "FRONT_HANDITEM", static_cast<int>(PLAYER::FRONT_HAND_INIT), static_cast<int>(PLAYER::FRONT_HAND_INIT), 0.0f, false);
	PlayerShirtsRenderer_->CreateAnimation("PlayerShirt0.bmp", "BACK_HANDITEM", static_cast<int>(PLAYER::BACK_HAND_INIT), static_cast<int>(PLAYER::BACK_HAND_INIT), 0.0f, false);

	PlayerHairRenderer_->CreateAnimation("PlayerHair0.bmp", "RIGHT_HANDITEM", static_cast<int>(PLAYER::RIGHT_HAND_INIT), static_cast<int>(PLAYER::RIGHT_HAND_INIT), 0.0f, false);
	PlayerHairRenderer_->CreateAnimation("PlayerHair0.bmp", "LEFT_HANDITEM", static_cast<int>(PLAYER::LEFT_HAND_INIT), static_cast<int>(PLAYER::LEFT_HAND_INIT), 0.0f, false);
	PlayerHairRenderer_->CreateAnimation("PlayerHair0.bmp", "FRONT_HANDITEM", static_cast<int>(PLAYER::FRONT_HAND_INIT), static_cast<int>(PLAYER::FRONT_HAND_INIT), 0.0f, false);
	PlayerHairRenderer_->CreateAnimation("PlayerHair0.bmp", "BACK_HANDITEM", static_cast<int>(PLAYER::BACK_HAND_INIT), static_cast<int>(PLAYER::BACK_HAND_INIT), 0.0f, false);

	PlayerHandRenderer_->CreateAnimation("PlayerHand0.bmp", "RIGHT_HANDITEM", static_cast<int>(PLAYER::RIGHT_HAND_INIT), static_cast<int>(PLAYER::RIGHT_HAND_INIT), 0.0f, false);
	PlayerHandRenderer_->CreateAnimation("PlayerHand0.bmp", "LEFT_HANDITEM", static_cast<int>(PLAYER::LEFT_HAND_INIT), static_cast<int>(PLAYER::LEFT_HAND_INIT), 0.0f, false);
	PlayerHandRenderer_->CreateAnimation("PlayerHand0.bmp", "FRONT_HANDITEM", static_cast<int>(PLAYER::FRONT_HAND_INIT), static_cast<int>(PLAYER::FRONT_HAND_INIT), 0.0f, false);
	PlayerHandRenderer_->CreateAnimation("PlayerHand0.bmp", "BACK_HANDITEM", static_cast<int>(PLAYER::BACK_HAND_INIT), static_cast<int>(PLAYER::BACK_HAND_INIT), 0.0f, false);

	//================================
	//     플레이어 이동 
	//================================
	PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "RIGHT_HANDITEMWALK", static_cast<int>(PLAYER::RIGHT_WALK_HAND0), static_cast<int>(PLAYER::RIGHT_WALK_HAND5), AnimationFrame_, true);
	PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "LEFT_HANDITEMWALK", static_cast<int>(PLAYER::LEFT_WALK_HAND0), static_cast<int>(PLAYER::LEFT_WALK_HAND5), AnimationFrame_, true);
	PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "FRONT_HANDITEMWALK",  static_cast<int>(PLAYER::FRONT_WALK_HAND0), static_cast<int>(PLAYER::FRONT_WALK_HAND3), AnimationFrame_, true);
	PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "BACK_HANDITEMWALK", static_cast<int>(PLAYER::BACK_WALK_HAND0), static_cast<int>(PLAYER::BACK_WALK_HAND3), AnimationFrame_, true);


	PlayerPantsRenderer_->CreateAnimation("PlayerPants0.bmp", "RIGHT_HANDITEMWALK", static_cast<int>(PLAYER::RIGHT_WALK_HAND0), static_cast<int>(PLAYER::RIGHT_WALK_HAND5), AnimationFrame_, true);
	PlayerPantsRenderer_->CreateAnimation("PlayerPants0.bmp", "LEFT_HANDITEMWALK", static_cast<int>(PLAYER::LEFT_WALK_HAND0), static_cast<int>(PLAYER::LEFT_WALK_HAND5), AnimationFrame_, true);
	PlayerPantsRenderer_->CreateAnimation("PlayerPants0.bmp", "FRONT_HANDITEMWALK", static_cast<int>(PLAYER::FRONT_WALK_HAND0), static_cast<int>(PLAYER::FRONT_WALK_HAND3), AnimationFrame_, true);
	PlayerPantsRenderer_->CreateAnimation("PlayerPants0.bmp", "BACK_HANDITEMWALK", static_cast<int>(PLAYER::BACK_WALK_HAND0), static_cast<int>(PLAYER::BACK_WALK_HAND3), AnimationFrame_, true);

	PlayerShirtsRenderer_->CreateAnimation("PlayerShirt0.bmp", "RIGHT_HANDITEMWALK", static_cast<int>(PLAYER::RIGHT_WALK_HAND0), static_cast<int>(PLAYER::RIGHT_WALK_HAND5), AnimationFrame_, true);
	PlayerShirtsRenderer_->CreateAnimation("PlayerShirt0.bmp", "LEFT_HANDITEMWALK", static_cast<int>(PLAYER::LEFT_WALK_HAND0), static_cast<int>(PLAYER::LEFT_WALK_HAND5), AnimationFrame_, true);
	PlayerShirtsRenderer_->CreateAnimation("PlayerShirt0.bmp", "FRONT_HANDITEMWALK", static_cast<int>(PLAYER::FRONT_WALK_HAND0), static_cast<int>(PLAYER::FRONT_WALK_HAND3), AnimationFrame_, true);
	PlayerShirtsRenderer_->CreateAnimation("PlayerShirt0.bmp", "BACK_HANDITEMWALK", static_cast<int>(PLAYER::BACK_WALK_HAND0), static_cast<int>(PLAYER::BACK_WALK_HAND3), AnimationFrame_, true);

	PlayerHairRenderer_->CreateAnimation("PlayerHair0.bmp", "RIGHT_HANDITEMWALK", static_cast<int>(PLAYER::RIGHT_WALK_HAND0), static_cast<int>(PLAYER::RIGHT_WALK_HAND5), AnimationFrame_, true);
	PlayerHairRenderer_->CreateAnimation("PlayerHair0.bmp", "LEFT_HANDITEMWALK", static_cast<int>(PLAYER::LEFT_WALK_HAND0), static_cast<int>(PLAYER::LEFT_WALK_HAND5), AnimationFrame_, true);
	PlayerHairRenderer_->CreateAnimation("PlayerHair0.bmp", "FRONT_HANDITEMWALK", static_cast<int>(PLAYER::FRONT_WALK_HAND0), static_cast<int>(PLAYER::FRONT_WALK_HAND3), AnimationFrame_, true);
	PlayerHairRenderer_->CreateAnimation("PlayerHair0.bmp", "BACK_HANDITEMWALK", static_cast<int>(PLAYER::BACK_WALK_HAND0), static_cast<int>(PLAYER::BACK_WALK_HAND3), AnimationFrame_, true);

	PlayerHandRenderer_->CreateAnimation("PlayerHand0.bmp", "RIGHT_HANDITEMWALK", static_cast<int>(PLAYER::RIGHT_WALK_HAND0), static_cast<int>(PLAYER::RIGHT_WALK_HAND5), AnimationFrame_, true);
	PlayerHandRenderer_->CreateAnimation("PlayerHand0.bmp", "LEFT_HANDITEMWALK", static_cast<int>(PLAYER::LEFT_WALK_HAND0), static_cast<int>(PLAYER::LEFT_WALK_HAND5), AnimationFrame_, true);
	PlayerHandRenderer_->CreateAnimation("PlayerHand0.bmp", "FRONT_HANDITEMWALK", static_cast<int>(PLAYER::FRONT_WALK_HAND0), static_cast<int>(PLAYER::FRONT_WALK_HAND3), AnimationFrame_, true);
	PlayerHandRenderer_->CreateAnimation("PlayerHand0.bmp", "BACK_HANDITEMWALK", static_cast<int>(PLAYER::BACK_WALK_HAND0), static_cast<int>(PLAYER::BACK_WALK_HAND3), AnimationFrame_, true);

	//================================
	//     플레이어 호미 사용
	//================================
	PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "FRONT_HOE", static_cast<int>(PLAYER::HOE_FRONT0), static_cast<int>(PLAYER::HOE_FRONT5), AnimationFrame_, true);
	PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "RIGHT_HOE", static_cast<int>(PLAYER::HOE_RIGHT0), static_cast<int>(PLAYER::HOE_RIGHT4), AnimationFrame_, true);
	PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "BACK_HOE", static_cast<int>(PLAYER::HOE_BACK0), static_cast<int>(PLAYER::HOE_BACK2), AnimationFrame_, true);
	PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "LEFT_HOE", static_cast<int>(PLAYER::HOE_LEFT0), static_cast<int>(PLAYER::HOE_LEFT4), AnimationFrame_, true);

	PlayerPantsRenderer_->CreateAnimation("PlayerPants0.bmp", "FRONT_HOE", static_cast<int>(PLAYER::HOE_FRONT0), static_cast<int>(PLAYER::HOE_FRONT5), AnimationFrame_, true);
	PlayerPantsRenderer_->CreateAnimation("PlayerPants0.bmp", "RIGHT_HOE", static_cast<int>(PLAYER::HOE_RIGHT0), static_cast<int>(PLAYER::HOE_RIGHT4), AnimationFrame_, true);
	PlayerPantsRenderer_->CreateAnimation("PlayerPants0.bmp", "BACK_HOE", static_cast<int>(PLAYER::HOE_BACK0), static_cast<int>(PLAYER::HOE_BACK2), AnimationFrame_, true);
	PlayerPantsRenderer_->CreateAnimation("PlayerPants0.bmp", "LEFT_HOE", static_cast<int>(PLAYER::HOE_LEFT0), static_cast<int>(PLAYER::HOE_LEFT4), AnimationFrame_, true);

	PlayerShirtsRenderer_->CreateAnimation("PlayerShirt0.bmp", "FRONT_HOE", static_cast<int>(PLAYER::HOE_FRONT0), static_cast<int>(PLAYER::HOE_FRONT5), AnimationFrame_, true);
	PlayerShirtsRenderer_->CreateAnimation("PlayerShirt0.bmp", "RIGHT_HOE", static_cast<int>(PLAYER::HOE_RIGHT0), static_cast<int>(PLAYER::HOE_RIGHT4), AnimationFrame_, true);
	PlayerShirtsRenderer_->CreateAnimation("PlayerShirt0.bmp", "BACK_HOE", static_cast<int>(PLAYER::HOE_BACK0), static_cast<int>(PLAYER::HOE_BACK2), AnimationFrame_, true);
	PlayerShirtsRenderer_->CreateAnimation("PlayerShirt0.bmp", "LEFT_HOE", static_cast<int>(PLAYER::HOE_LEFT0), static_cast<int>(PLAYER::HOE_LEFT4), AnimationFrame_, true);

	PlayerHairRenderer_->CreateAnimation("PlayerHair0.bmp", "FRONT_HOE", static_cast<int>(PLAYER::HOE_FRONT0), static_cast<int>(PLAYER::HOE_FRONT5), AnimationFrame_, true);
	PlayerHairRenderer_->CreateAnimation("PlayerHair0.bmp", "RIGHT_HOE", static_cast<int>(PLAYER::HOE_RIGHT0), static_cast<int>(PLAYER::HOE_RIGHT4), AnimationFrame_, true);
	PlayerHairRenderer_->CreateAnimation("PlayerHair0.bmp", "BACK_HOE", static_cast<int>(PLAYER::HOE_BACK0), static_cast<int>(PLAYER::HOE_BACK2), AnimationFrame_, true);
	PlayerHairRenderer_->CreateAnimation("PlayerHair0.bmp", "LEFT_HOE", static_cast<int>(PLAYER::HOE_LEFT0), static_cast<int>(PLAYER::HOE_LEFT4), AnimationFrame_, true);

	PlayerHandRenderer_->CreateAnimation("PlayerHand0.bmp", "FRONT_HOE", static_cast<int>(PLAYER::HOE_FRONT0), static_cast<int>(PLAYER::HOE_FRONT5), AnimationFrame_, true);
	PlayerHandRenderer_->CreateAnimation("PlayerHand0.bmp", "RIGHT_HOE", static_cast<int>(PLAYER::HOE_RIGHT0), static_cast<int>(PLAYER::HOE_RIGHT4), AnimationFrame_, true);
	PlayerHandRenderer_->CreateAnimation("PlayerHand0.bmp", "BACK_HOE", static_cast<int>(PLAYER::HOE_BACK0), static_cast<int>(PLAYER::HOE_BACK2), AnimationFrame_, true);
	PlayerHandRenderer_->CreateAnimation("PlayerHand0.bmp", "LEFT_HOE", static_cast<int>(PLAYER::HOE_LEFT0), static_cast<int>(PLAYER::HOE_LEFT4), AnimationFrame_, true);


	//================================
	//     플레이어 물뿌리개 사용
	//================================

	PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "FRONT_WATER", static_cast<int>(PLAYER::WATER_FRONT0), static_cast<int>(PLAYER::WATER_FRONT2), 0.200f, true);
	PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "RIGHT_WATER", static_cast<int>(PLAYER::WATER_RIGHT0), static_cast<int>(PLAYER::WATER_RIGHT2), 0.200f, true);
	PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "LEFT_WATER", static_cast<int>(PLAYER::WATER_LEFT0),  static_cast<int>(PLAYER::WATER_LEFT2), 0.200f, true);
	PlayerBodyRenderer_->CreateAnimation("PlayerBody0.bmp", "BACK_WATER", static_cast<int>(PLAYER::WATER_BACK0),  static_cast<int>(PLAYER::WATER_BACK2), 0.200f, true);

	PlayerPantsRenderer_->CreateAnimation("PlayerPants0.bmp", "FRONT_WATER", static_cast<int>(PLAYER::WATER_FRONT0), static_cast<int>(PLAYER::WATER_FRONT2), 0.200f, true);
	PlayerPantsRenderer_->CreateAnimation("PlayerPants0.bmp", "RIGHT_WATER", static_cast<int>(PLAYER::WATER_RIGHT0), static_cast<int>(PLAYER::WATER_RIGHT2), 0.200f, true);
	PlayerPantsRenderer_->CreateAnimation("PlayerPants0.bmp", "LEFT_WATER", static_cast<int>(PLAYER::WATER_LEFT0), static_cast<int>(PLAYER::WATER_LEFT2), 0.200f, true);
	PlayerPantsRenderer_->CreateAnimation("PlayerPants0.bmp", "BACK_WATER", static_cast<int>(PLAYER::WATER_BACK0), static_cast<int>(PLAYER::WATER_BACK2), 0.200f, true);

	PlayerShirtsRenderer_->CreateAnimation("PlayerShirt0.bmp", "FRONT_WATER", static_cast<int>(PLAYER::WATER_FRONT0), static_cast<int>(PLAYER::WATER_FRONT2), 0.200f, true);
	PlayerShirtsRenderer_->CreateAnimation("PlayerShirt0.bmp", "RIGHT_WATER", static_cast<int>(PLAYER::WATER_RIGHT0), static_cast<int>(PLAYER::WATER_RIGHT2), 0.200f, true);
	PlayerShirtsRenderer_->CreateAnimation("PlayerShirt0.bmp", "LEFT_WATER", static_cast<int>(PLAYER::WATER_LEFT0), static_cast<int>(PLAYER::WATER_LEFT2), 0.200f, true);
	PlayerShirtsRenderer_->CreateAnimation("PlayerShirt0.bmp", "BACK_WATER", static_cast<int>(PLAYER::WATER_BACK0), static_cast<int>(PLAYER::WATER_BACK2), 0.200f, true);

	PlayerHairRenderer_->CreateAnimation("PlayerHair0.bmp", "FRONT_WATER", static_cast<int>(PLAYER::WATER_FRONT0), static_cast<int>(PLAYER::WATER_FRONT2), 0.200f, true);
	PlayerHairRenderer_->CreateAnimation("PlayerHair0.bmp", "RIGHT_WATER", static_cast<int>(PLAYER::WATER_RIGHT0), static_cast<int>(PLAYER::WATER_RIGHT2), 0.200f, true);
	PlayerHairRenderer_->CreateAnimation("PlayerHair0.bmp", "LEFT_WATER", static_cast<int>(PLAYER::WATER_LEFT0), static_cast<int>(PLAYER::WATER_LEFT2), 0.200f, true);
	PlayerHairRenderer_->CreateAnimation("PlayerHair0.bmp", "BACK_WATER", static_cast<int>(PLAYER::WATER_BACK0), static_cast<int>(PLAYER::WATER_BACK2), 0.200f, true);

	PlayerHandRenderer_->CreateAnimation("PlayerHand0.bmp", "FRONT_WATER", static_cast<int>(PLAYER::WATER_FRONT0), static_cast<int>(PLAYER::WATER_FRONT2), 0.200f, true);
	PlayerHandRenderer_->CreateAnimation("PlayerHand0.bmp", "RIGHT_WATER", static_cast<int>(PLAYER::WATER_RIGHT0), static_cast<int>(PLAYER::WATER_RIGHT2), 0.200f, true);
	PlayerHandRenderer_->CreateAnimation("PlayerHand0.bmp", "LEFT_WATER", static_cast<int>(PLAYER::WATER_LEFT0), static_cast<int>(PLAYER::WATER_LEFT2), 0.200f, true);
	PlayerHandRenderer_->CreateAnimation("PlayerHand0.bmp", "BACK_WATER", static_cast<int>(PLAYER::WATER_BACK0), static_cast<int>(PLAYER::WATER_BACK2), 0.200f, true);



	//------< 툴 애니메이션 >------------------------------------------------------------------

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
	ToolRenderer_->CreateAnimation("wateringcan_left.bmp", "LEFT_WATER",  static_cast<int>(WATERINGCAN_LEFT::WATERINGCAN_LEFT0), static_cast<int>(WATERINGCAN_LEFT::WATERINGCAN_LEFT2), 0.200f, false);
	ToolRenderer_->CreateAnimation("wateringcan_front.bmp", "FRONT_WATER",  static_cast<int>(WATERINGCAN_FRONT::WATERINGCAN_FRONT0), static_cast<int>(WATERINGCAN_FRONT::WATERINGCAN_FRONT2), 0.200f, false);
	ToolRenderer_->CreateAnimation("wateringcan_back.bmp", "BACK_WATER", static_cast<int>(WATERINGCAN_BACK::WATERINGCAN_BACK0), static_cast<int>(WATERINGCAN_BACK::WATERINGCAN_BACK2), 0.200f, false);


	//------< 애니메이션 초기화 >------------------------------------------------------------------

	PlayerBodyRenderer_->ChangeAnimation("FRONT_INIT");
	PlayerPantsRenderer_->ChangeAnimation("FRONT_INIT");
	PlayerShirtsRenderer_->ChangeAnimation("FRONT_INIT");
	PlayerHairRenderer_->ChangeAnimation("FRONT_INIT");
	PlayerHandRenderer_->ChangeAnimation("FRONT_INIT");

	ToolRenderer_->ChangeAnimation("LEFT_INIT");
	//PlayerMove_.SetFrontDir(true);
	LevelRegist("MainPlayer");
}



void Player::Update()
{
	if (CurrentLevel_ != "TitleLevel")
	{
		SetCamera();
		PlayerUpdate();
		PlayerDirCheck();
		SetPlayerHandItemPos();
		ClearWetDirtTile();
		ChangeLevel();
		NpcCollCheck();
		CheckShippingBox();
	}

	if (CurrentLevel_ == "ShopLevel")
	{
		PlayerShopping();
	}
	

	if (true == GameEngineInput::GetInst()->IsDown("DebugRendereChange"))
	{
		GetLevel()->IsDebugModeSwitch();
	}

}

void Player::Render()
{

}

void Player::LevelChangeStart(GameEngineLevel* _PrevLevel)
{

	MainPlayer = this;
	PlayerHandItem_ = PlayerHandItem_;
	MainMouse_ = MainMouse_;
	LevelInit();
}

void Player::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	MainMouse_->NextLevelOn();
	PlayerHandItem_->NextLevelOn();
	PrevLevel_ = CurrentLevel_;

	//std::map<int, Items*>::iterator StartIter = MapObject_.begin();
	//std::map<int, Items*>::iterator EndIter = MapObject_.end();

	//for (; StartIter != EndIter; ++StartIter)
	//{
	//	StartIter->second->NextLevelOn();
	//}
}


void Player::PlayerUpdate()
{

	switch (PlayerState_)
	{

	case PLAYER_UPDATE::INIT:

		GetItem();
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

		isEvent_ = true;
		if (PlayerBodyRenderer_->IsEndAnimation())
		{
			if (FarmingArea_ == true)
			{
				CreateDirtTile();
				ChangeDirtTile();
				SubEnergy(2);
			}
			isEvent_ = false;
			PlayerState_ = PLAYER_UPDATE::INIT;
		}

		break;

	case PLAYER_UPDATE::WATER:

		isEvent_ = true;
		if (PlayerBodyRenderer_->IsEndAnimation())
		{
			CreateWaterEffet();
			CreateWaterTile();
			ChangeWetDirtTile();
			SubEnergy(2);

			isEvent_ = false;
			PlayerState_ = PLAYER_UPDATE::INIT;
		}

		break;

	case PLAYER_UPDATE::AXE:

		isEvent_ = true;
		if (PlayerBodyRenderer_->IsEndAnimation())
		{
			CrushTree();
			CrushWood();

			isEvent_ = false;
			PlayerState_ = PLAYER_UPDATE::INIT;
		}


		break;

	case PLAYER_UPDATE::PICKAXE:

		isEvent_ = true;
		if (PlayerBodyRenderer_->IsEndAnimation())
		{
			CrushStone();

			isEvent_ = false;
			PlayerState_ = PLAYER_UPDATE::INIT;
		}


		break;

	case PLAYER_UPDATE::HANDITEM:

		ChangeLevel();
		ChangeHandItem();

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

		PlayerWalk();
		harvestingCrops();


		if (isStop() || isEvent_ == true)
		{
			PlayerState_ = PLAYER_UPDATE::INIT;
		}

		break;

	case PLAYER_UPDATE::HANDITEMWALK:

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

	default:
		break;
	}

}

void Player::LevelInit()
{

	MainMouse_->Renderer()->CameraEffectOff();
	CurrentLevel_ = GetCurrentLevel();

	if (CurrentLevel_ == "TitleLevel")
	{
		MapColImage_ = GameEngineImageManager::GetInst()->Find("PlayerHouse_Coll.bmp");
		ToolRenderer_->CameraEffectOff();

		PlayerBodyRenderer_->CameraEffectOff();
		PlayerPantsRenderer_->CameraEffectOff();
		PlayerShirtsRenderer_->CameraEffectOff();
		PlayerHairRenderer_->CameraEffectOff();
		PlayerHandRenderer_->CameraEffectOff();
	}

	if (CurrentLevel_ == "MyHouseLevel")
	{
		MapColImage_ = GameEngineImageManager::GetInst()->Find("PlayerHouse_Coll.bmp");
		ToolRenderer_->CameraEffectOff();

		PlayerBodyRenderer_->CameraEffectOff();
		PlayerPantsRenderer_->CameraEffectOff();
		PlayerShirtsRenderer_->CameraEffectOff();
		PlayerHairRenderer_->CameraEffectOff();
		PlayerHandRenderer_->CameraEffectOff();
	}

	if (CurrentLevel_ == "MyFarmLevel")
	{
		MapSizeX_ = FARM_SIZE_WEIGHT;
		MapSizeY_ = FARM_SIZE_HEIGHT;

		MapColImage_ = GameEngineImageManager::GetInst()->Find("FarmBack_Coll.bmp");
		ToolRenderer_->CameraEffectOn();

		PlayerBodyRenderer_->CameraEffectOn();
		PlayerPantsRenderer_->CameraEffectOn();
		PlayerShirtsRenderer_->CameraEffectOn();
		PlayerHairRenderer_->CameraEffectOn();
		PlayerHandRenderer_->CameraEffectOn();
	}


	if (CurrentLevel_ == "BusStopLevel")
	{
		MapSizeX_ = BUSSTOP_SIZE_WEIGHT;
		MapSizeY_ = BUSSTOP_SIZE_HEIGHT;

		MapColImage_ = GameEngineImageManager::GetInst()->Find("BusStop_Coll.bmp");
		ToolRenderer_->CameraEffectOn();

		PlayerBodyRenderer_->CameraEffectOn();
		PlayerPantsRenderer_->CameraEffectOn();
		PlayerShirtsRenderer_->CameraEffectOn();
		PlayerHairRenderer_->CameraEffectOn();
		PlayerHandRenderer_->CameraEffectOn();
	}


	if (CurrentLevel_ == "TownLevel")
	{
		MapSizeX_ = TOWN_SIZE_WEIGHT;
		MapSizeY_ = TOWN_SIZE_HEIGHT;

		MapColImage_ = GameEngineImageManager::GetInst()->Find("Town_Col.bmp");
		ToolRenderer_->CameraEffectOn();

		PlayerBodyRenderer_->CameraEffectOn();
		PlayerPantsRenderer_->CameraEffectOn();
		PlayerShirtsRenderer_->CameraEffectOn();
		PlayerHairRenderer_->CameraEffectOn();
		PlayerHandRenderer_->CameraEffectOn();
	}

	if (CurrentLevel_ == "ShopLevel")
	{
		MapSizeX_ = SHOP_SIZE_WEIGHT;
		MapSizeY_ = SHOP_SIZE_HEIGHT;

		MapColImage_ = GameEngineImageManager::GetInst()->Find("Shop_Coll.bmp");
		ToolRenderer_->CameraEffectOn();

		PlayerBodyRenderer_->CameraEffectOn();
		PlayerPantsRenderer_->CameraEffectOn();
		PlayerShirtsRenderer_->CameraEffectOn();
		PlayerHairRenderer_->CameraEffectOn();
		PlayerHandRenderer_->CameraEffectOn();
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
		SetPosition({ 520.f, 500.f });
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
	if (CurrentLevel_ == "TownLevel" && PrevLevel_ == "ShopLevel")
	{
		SetPosition({ 2100.f, 2780.f });
	} 

	// 마을 -> 상점
	if (CurrentLevel_ == "ShopLevel" && PrevLevel_ == "TownLevel")
	{
		SetPosition({ 310.f, 1320.f });
	}

	
}

