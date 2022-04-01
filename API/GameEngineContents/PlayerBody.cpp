#include "PlayerBody.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>

#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

#include <GameEngine/GameEngineLevel.h> // 레벨을 통해서

#include "PlayerShirts.h"
#include "PlayerEnum.h"


PlayerBody::PlayerBody()
	: 
	PlayerBody_(nullptr),
	WalkAnimationFrame_(0.15f)
{
}

PlayerBody::PlayerBody(float _WalkAnimationFrame)
	:
	PlayerBody_(nullptr),
	WalkAnimationFrame_(_WalkAnimationFrame)
{
}

PlayerBody::~PlayerBody()
{
}

void PlayerBody::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());

	PlayerBody_ = CreateRenderer();



	//================================
	//     플레이어 바디 대기상태
	//================================

	PlayerBody_->CreateAnimation("farmer_Body.bmp", "BODY_FRONT_INIT", PLAYER::FRONT_INIT, PLAYER::FRONT_INIT, 0.0f, false);
	PlayerBody_->CreateAnimation("farmer_Body.bmp", "BODY_RIGHT_INIT", PLAYER::RIGHT_INIT, PLAYER::RIGHT_INIT, 0.0f, false);
	PlayerBody_->CreateAnimation("farmer_Body.bmp", "BODY_LEFT_INIT", PLAYER::LEFT_INIT, PLAYER::LEFT_INIT, 0.0f, false);

	PlayerBody_->CreateAnimation("farmer_Body.bmp", "BODY_BACK_INIT", PLAYER::BACK_INIT, PLAYER::BACK_INIT, 0.0f, false);


	//================================
	//     플레이어 바디 이동 
	//================================

	PlayerBody_->CreateAnimation("farmer_Body.bmp", "BODY_FRONT_WALK", PLAYER::FRONT_WALK0, PLAYER::FRONT_WALK1, WalkAnimationFrame_, true);
	PlayerBody_->CreateAnimation("farmer_Body.bmp", "BODY_RIGHT_WALK", PLAYER::RIGHT_INIT, PLAYER::RIGHT_WALK1, WalkAnimationFrame_, true);
	PlayerBody_->CreateAnimation("farmer_Body.bmp", "BODY_LEFT_WALK", PLAYER::LEFT_INIT, PLAYER::LEFT_WALK1, WalkAnimationFrame_, true);

	PlayerBody_->CreateAnimation("farmer_Body.bmp", "BODY_BACK_WALK", PLAYER::BACK_INIT, PLAYER::WALK_BACK2, WalkAnimationFrame_, true);



	//------< 애니메이션 초기화 >------------------------------------------------------------------

	PlayerBody_->ChangeAnimation("BODY_FRONT_INIT");



}




void PlayerBody::Update()
{

	//GetLevel()->SetCameraPos(GetPosition() - GameEngineWindow::GetInst().GetScale().Half());



}


void PlayerBody::Render()
{
	//GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find("Idle.bmp");
	//if (nullptr == FindImage)
	//{
	//	MsgBoxAssert("CCCCC!");
	//}
	//GameEngine::BackBufferImage()->BitCopyBot(FindImage, GetPosition());

}