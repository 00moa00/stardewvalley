#include "Bat.h"
#include "Player.h"

Bat::Bat() 
{

}

Bat::~Bat() 
{
}

void Bat::Start()
{
	MonsterRenderer_ = CreateRenderer("LavaBat.bmp");
	MonsterRenderer_->SetIndex(0);

	MonsterCollider_ = CreateCollision("Monster", { 48.f, 36.f });
	MonsterCollider_->SetPivot({ 0, 18.f });

	MonsterRenderer_->CreateAnimation("LavaBat.bmp", "RIGHT_WALK", static_cast<int>(BAT_INDEX::FRONT_WALK00), static_cast<int>(BAT_INDEX::FRONT_WALK03), 0.120f, true);
	MonsterRenderer_->CreateAnimation("LavaBat.bmp", "LEFT_WALK", static_cast<int>(BAT_INDEX::FRONT_WALK00), static_cast<int>(BAT_INDEX::FRONT_WALK03), 0.120f, true);
	MonsterRenderer_->CreateAnimation("LavaBat.bmp", "FRONT_WALK", static_cast<int>(BAT_INDEX::FRONT_WALK00), static_cast<int>(BAT_INDEX::FRONT_WALK03), 0.120f, true);
	MonsterRenderer_->CreateAnimation("LavaBat.bmp", "BACK_WALK", static_cast<int>(BAT_INDEX::FRONT_WALK00), static_cast<int>(BAT_INDEX::FRONT_WALK03), 0.120f, true);
	
	MonsterRenderer_->CreateAnimation("LavaBat.bmp", "RIGHT_WAIT", static_cast<int>(BAT_INDEX::INIT), static_cast<int>(BAT_INDEX::INIT), 0.120f, true);
	MonsterRenderer_->CreateAnimation("LavaBat.bmp", "LEFT_WAIT", static_cast<int>(BAT_INDEX::INIT), static_cast<int>(BAT_INDEX::INIT), 0.120f, true);
	MonsterRenderer_->CreateAnimation("LavaBat.bmp", "FRONT_WAIT", static_cast<int>(BAT_INDEX::INIT), static_cast<int>(BAT_INDEX::INIT), 0.120f, true);
	MonsterRenderer_->CreateAnimation("LavaBat.bmp", "BACK_WAIT", static_cast<int>(BAT_INDEX::INIT), static_cast<int>(BAT_INDEX::INIT), 0.120f, true);



	MonsterRenderer_->CreateAnimation("LavaBat.bmp", "RIGHT_DEATH", static_cast<int>(BAT_INDEX::DEATH), static_cast<int>(BAT_INDEX::DEATH), 0.120f, false);

	MonsterRenderer_->ChangeAnimation("FRONT_WALK");

	Damage_ = 2;
	HP_ = 10;
	Speed_ = 60.f;

	MonsterState_ = MONSTER_STATE::WAIT;
	MonsterType_ = MONSTER_TYPE::BAT;
	MoveDir_ = float4::DOWN;

	SetScale({ 48, 50 });
}

void Bat::Update()
{

	Dir = Player::MainPlayer->GetPosition() - this->GetPosition();

	//범위 체크
	Check_ = Dir.Len2D();
	Dir.Normal2D();

	if (isDeath_ == true)
	{
		MonsterState_ = MONSTER_STATE::DEATH;
	}

	switch (MonsterState_)
	{
	case MONSTER_STATE::WAIT:
		invincibility_ = true;
		MonsterRenderer_->ChangeAnimation("FRONT_WAIT");

		if (Check_ <= 300)
		{
			HP_ = 20;
			invincibility_ = false;
			MonsterState_ = MONSTER_STATE::WALK;
		}

		break;

	case MONSTER_STATE::CHECK:

		//몬스터 랜덤 방향으로 이동
		//만약 랜덤 체크한 곳에 오브젝트가 있다면 다시 돌아온다.

		RamdomDirResult_ = RandomDir_.RandomInt(0, 3);

		switch (RamdomDirResult_)
		{
		case 0:

			MoveDir_ = float4::RIGHT;
			MonsterState_ = MONSTER_STATE::WALK;
			
			break;
		case 1:

			MoveDir_ = float4::LEFT;
			MonsterState_ = MONSTER_STATE::WALK;

			break;
		case 2:
			MoveDir_ = float4::UP;
			MonsterState_ = MONSTER_STATE::WALK;

			break;
		case 3:


			MoveDir_ = float4::DOWN;
			MonsterState_ = MONSTER_STATE::WALK;
			
			break;

		}

		break;


	case MONSTER_STATE::WALK:


		Timer_ += GameEngineTime::GetDeltaTime();
		if (Timer_ > 1.0f)
		{
			Timer_ = 0.f;
			MonsterState_ = MONSTER_STATE::MOVE_TO_PLAYER;
		}
		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * 10.f);



		break;


	case MONSTER_STATE::MOVE_TO_PLAYER:
		MoveDir_ += Dir;

		Timer_ += GameEngineTime::GetDeltaTime();
		if (Timer_ > 3.0f)
		{
			Timer_ = 0.f;
			MonsterState_ = MONSTER_STATE::CHECK;
		}

		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * 10.f);
		MonsterRenderer_->ChangeAnimation("FRONT_WALK");

		break;
	case MONSTER_STATE::BACK:

		BackMove();
		break;
	case MONSTER_STATE::DEATH:
		MonsterRenderer_->ChangeAnimation("FRONT_DEATH");

		if (MonsterRenderer_->IsEndAnimation())
		{
			this->Death();
		}

		break;
	}

}
