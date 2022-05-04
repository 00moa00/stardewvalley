#include "Clab.h"
#include "Player.h"

Clab::Clab() 
{
	ArrAnimationName[static_cast<int>(MONSTER_STATE::WALK)] = "WALK";

	ArrAnimationName[static_cast<int>(MONSTER_STATE::WAIT)] = "WAIT";
	ArrAnimationName[static_cast<int>(MONSTER_STATE::RE_CHECK)] = "WAIT";
	ArrAnimationName[static_cast<int>(MONSTER_STATE::CHECK)] = "WAIT";

}

Clab::~Clab() 
{
}

void Clab::Start()
{
	MonsterRenderer_ = CreateRenderer("StoneGolem.bmp");
	MonsterRenderer_->SetIndex(0);

	MonsterCollider_ = CreateCollision("Monster", { 48.f, 48.f });
	MonsterCollider_->SetPivot({ 0, 24.f });

	MonsterRenderer_->CreateAnimation("StoneGolem.bmp", "RIGHT_WALK", static_cast<int>(CRAB_INDEX::RIGHT_WALK00), static_cast<int>(CRAB_INDEX::RIGHT_WALK03), 0.120f, true);
	MonsterRenderer_->CreateAnimation("StoneGolem.bmp", "LEFT_WALK", static_cast<int>(CRAB_INDEX::LEFT_WALK00), static_cast<int>(CRAB_INDEX::LEFT_WALK03), 0.120f, true);
	MonsterRenderer_->CreateAnimation("StoneGolem.bmp", "FRONT_WALK", static_cast<int>(CRAB_INDEX::FRONT_WALK00), static_cast<int>(CRAB_INDEX::FRONT_WALK03), 0.120f, true);
	MonsterRenderer_->CreateAnimation("StoneGolem.bmp", "BACK_WALK", static_cast<int>(CRAB_INDEX::BACK_WALK00), static_cast<int>(CRAB_INDEX::BACK_WALK03), 0.120f, true);

	MonsterRenderer_->CreateAnimation("StoneGolem.bmp", "DEATH", static_cast<int>(CRAB_INDEX::DEATH), static_cast<int>(CRAB_INDEX::DEATH), 0.0f, false);

	MonsterRenderer_->CreateAnimation("StoneGolem.bmp", "RIGHT_WAIT", static_cast<int>(CRAB_INDEX::RIGHT_WALK00), static_cast<int>(CRAB_INDEX::RIGHT_WALK00), 0.120f, false);
	MonsterRenderer_->CreateAnimation("StoneGolem.bmp", "LEFT_WAIT", static_cast<int>(CRAB_INDEX::LEFT_WALK00), static_cast<int>(CRAB_INDEX::LEFT_WALK00), 0.120f, false);
	MonsterRenderer_->CreateAnimation("StoneGolem.bmp", "FRONT_WAIT", static_cast<int>(CRAB_INDEX::FRONT_WALK00), static_cast<int>(CRAB_INDEX::FRONT_WALK00), 0.120f, false);
	MonsterRenderer_->CreateAnimation("StoneGolem.bmp", "BACK_WAIT", static_cast<int>(CRAB_INDEX::BACK_WALK00), static_cast<int>(CRAB_INDEX::BACK_WALK00), 0.120f, false);

	MonsterRenderer_->ChangeAnimation("RIGHT_WAIT");

	MonsterState_ = MONSTER_STATE::WAIT;
	MonsterType_ = MONSTER_TYPE::CRAB;


	Damage_ = 2;
	HP_ = 10;
	Speed_ = 60.f;

	SetScale({ 48, 48 });
}

void Clab::Update()
{
	switch (MonsterState_)
	{
	case MONSTER_STATE::WAIT:
		if (isHit_ == true) 
		{
			MonsterState_ = MONSTER_STATE::WALK;
		}

		break;
	case MONSTER_STATE::CHECK:
		RamdomDirResult_ = RandomDir_.RandomInt(0, 3);

		switch (RamdomDirResult_)
		{
		case 0:
			if (CheckRightObject() == true)
			{
				MonsterState_ = MONSTER_STATE::RE_CHECK;
			}
			else
			{
				MoveDir_ = float4::RIGHT;
				MonsterState_ = MONSTER_STATE::WALK;
			}

			break;
		case 1:

			if (CheckLeftObject() == true)
			{
				MonsterState_ = MONSTER_STATE::RE_CHECK;
			}
			else
			{
				MoveDir_ = float4::LEFT;
				MonsterState_ = MONSTER_STATE::WALK;
			}

			break;
		case 2:

			if (CheckUpObject() == true)
			{
				MonsterState_ = MONSTER_STATE::RE_CHECK;
			}
			else
			{
				MoveDir_ = float4::UP;
				MonsterState_ = MONSTER_STATE::WALK;
			}

			break;
		case 3:

			if (CheckDownObject() == true)
			{
				MonsterState_ = MONSTER_STATE::RE_CHECK;
			}
			else
			{
				MoveDir_ = float4::DOWN;
				MonsterState_ = MONSTER_STATE::WALK;
			}

			break;
		default:
			break;
		}

		break;

	case MONSTER_STATE::RE_CHECK:
		MonsterState_ = MONSTER_STATE::CHECK;

		break;
	case MONSTER_STATE::WALK:

		Dir = Player::MainPlayer->GetPosition() - this->GetPosition();
		Check = Dir.Len2D();

		Timer_ += GameEngineTime::GetDeltaTime();
		if (Timer_ > 3.0f && Check > 150)
		{
			Timer_ = 0.f;
			MonsterState_ = MONSTER_STATE::CHECK;
		}

		Dir.Normal2D();

		if (Check <= 150)
		{

			//플레이어가 오른쪽, 아래에 있다
			if (Dir.x > 0 && Dir.y > 0)
			{
				MoveDir_ = float4::ZERO;
				MoveDir_ = float4::RIGHT;
			}

			//플레이어가 오른쪽, 위에 있다
			if (Dir.x > 0 && Dir.y < 0)
			{
				MoveDir_ = float4::ZERO;
				MoveDir_ = float4::RIGHT;
			}

			//플레이어가 왼쪽, 위에 있다
			if (Dir.x < 0 && Dir.y < 0)
			{
				MoveDir_ = float4::ZERO;
				MoveDir_ = float4::LEFT;
			}

			//플레이어가 왼쪽, 아래에 있다
			if (Dir.x < 0 && Dir.y > 0)
			{
				MoveDir_ = float4::ZERO;
				MoveDir_ = float4::LEFT;
			}

			if (Player::MainPlayer->GetPosition().ix() == this->GetPosition().ix())
			{


				if (Dir.y > 0)
				{
					MoveDir_ = float4::ZERO;
					MoveDir_ = float4::DOWN;
				}

				if (Dir.y < 0)
				{
					MoveDir_ = float4::ZERO;
					MoveDir_ = float4::UP;
				}
			}
		}

		if (CheckMapObject() == true)
		{
			MonsterState_ = MONSTER_STATE::CHECK;
		}

		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);



		break;
	default:
		break;
	}
}

void Clab::DirAnimation()
{
}
