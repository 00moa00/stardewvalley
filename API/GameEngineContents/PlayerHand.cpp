#include "PlayerHand.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>

#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

#include <GameEngine/GameEngineLevel.h> // 레벨을 통해서

#include "PlayerShirts.h"
#include "PlayerEnum.h"


PlayerHand::PlayerHand()
	: PlayerHand_(nullptr),
	WalkAnimationFrame_(0.15f)

{
}

PlayerHand::PlayerHand(float _WalkAnimationFrame)
	: PlayerHand_(nullptr),
	WalkAnimationFrame_(_WalkAnimationFrame)
{
}

PlayerHand::~PlayerHand()
{
}

void PlayerHand::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());

	PlayerHand_ = CreateRenderer();


	//================================
	//      플레이어 팔 대기상태
	//================================

	PlayerHand_->CreateAnimation("farmer_hand.bmp", "HAND_FRONT_INIT", PLAYER::FRONT_INIT, PLAYER::FRONT_INIT, 0.0f, false);
	PlayerHand_->CreateAnimation("farmer_hand.bmp", "HAND_RIGHT_INIT", PLAYER::RIGHT_INIT, PLAYER::RIGHT_INIT, 0.0f, false);
	PlayerHand_->CreateAnimation("farmer_hand.bmp", "HAND_LEFT_INIT", PLAYER::LEFT_INIT, PLAYER::LEFT_INIT, 0.0f, false);

	PlayerHand_->CreateAnimation("farmer_hand.bmp", "HAND_BACK_INIT", PLAYER::BACK_INIT, PLAYER::BACK_INIT, 0.0f, false);


	//================================
	//      플레이어 팔 이동
	//================================

	PlayerHand_->CreateAnimation("farmer_hand.bmp", "HAND_FRONT_WALK", PLAYER::FRONT_WALK0, PLAYER::FRONT_WALK1, WalkAnimationFrame_, true);
	PlayerHand_->CreateAnimation("farmer_hand.bmp", "HAND_RIGHT_WALK", PLAYER::RIGHT_INIT, PLAYER::RIGHT_WALK1, WalkAnimationFrame_, true);
	PlayerHand_->CreateAnimation("farmer_hand.bmp", "HAND_LEFT_WALK", PLAYER::LEFT_INIT, PLAYER::LEFT_WALK1, WalkAnimationFrame_, true);

	PlayerHand_->CreateAnimation("farmer_hand.bmp", "HAND_BACK_WALK", PLAYER::BACK_INIT, PLAYER::WALK_BACK2, WalkAnimationFrame_, true);


	//------< 애니메이션 초기화 >------------------------------------------------------------------

	PlayerHand_->ChangeAnimation("HAND_FRONT_INIT");


}




void PlayerHand::Update()
{


}



void PlayerHand::Render()
{
	//GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find("Idle.bmp");
	//if (nullptr == FindImage)
	//{
	//	MsgBoxAssert("CCCCC!");
	//}
	//GameEngine::BackBufferImage()->BitCopyBot(FindImage, GetPosition());

}