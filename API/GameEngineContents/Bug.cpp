#include "Bug.h"

Bug::Bug() 
{
	ArrAnimationName[static_cast<int>(MONSTER_STATE::MOVE_UP)] = "WALK";

	ArrAnimationName[static_cast<int>(MONSTER_STATE::MOVE_DOWN)] = "WALK";


}

Bug::~Bug() 
{
}

void Bug::Start()
{
	MonsterRenderer_ = CreateRenderer("ArmoredBug.bmp");
	MonsterRenderer_->SetIndex(0);

	MonsterCollider_ = CreateCollision("Monster", { 48.f, 36.f });
	MonsterCollider_->SetPivot({ 0, 18.f });

	MonsterRenderer_->CreateAnimation("ArmoredBug.bmp", "RIGHT_WALK", static_cast<int>(BUG_INDEX::RIGHT_WALK00), static_cast<int>(BUG_INDEX::RIGHT_WALK03), 0.120f, true);
	MonsterRenderer_->CreateAnimation("ArmoredBug.bmp", "LEFT_WALK", static_cast<int>(BUG_INDEX::LEFT_WALK00), static_cast<int>(BUG_INDEX::LEFT_WALK03), 0.120f, true);
	MonsterRenderer_->CreateAnimation("ArmoredBug.bmp", "FRONT_WALK", static_cast<int>(BUG_INDEX::FRONT_WALK00), static_cast<int>(BUG_INDEX::FRONT_WALK03), 0.120f, true);
	MonsterRenderer_->CreateAnimation("ArmoredBug.bmp", "BACK_WALK", static_cast<int>(BUG_INDEX::BACK_WALK00), static_cast<int>(BUG_INDEX::BACK_WALK03), 0.120f, true);

	MonsterRenderer_->ChangeAnimation("FRONT_WALK");

	Damage_ = 2;
	HP_ = 10;
	Speed_ = 30.f;


	MonsterState_ = MONSTER_STATE::MOVE_UP;

	SetScale({ 48, 60 });
}

void Bug::Update()
{
	switch (MonsterState_)
	{

	case MONSTER_STATE::MOVE_UP:
		MoveDir_ = float4::UP;
		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);


		if (CheckMapObject() == true)
		{
			MonsterState_ = MONSTER_STATE::MOVE_DOWN;
		}

		break;

	case MONSTER_STATE::MOVE_DOWN:
		MoveDir_ = float4::DOWN;
		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);

		if (CheckMapObject() == true)
		{
			MonsterState_ = MONSTER_STATE::MOVE_UP;
		}

		break;
	default:
		break;
	}
}

void Bug::DirAnimation()
{
	MonsterRenderer_->ChangeAnimation(GetDirString() + ArrAnimationName[static_cast<int>(MonsterState_)]);

}
