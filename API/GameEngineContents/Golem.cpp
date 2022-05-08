#include "Golem.h"
#include "Player.h"

Golem::Golem() 
	:
	CheckTimer_(0.f),
	Check_(0.f),

	CheckTime_(false),
	SubCollision_(nullptr)


{
	ArrAnimationName[static_cast<int>(MONSTER_STATE::REVIVAL)] = "REVIVAL";
	ArrAnimationName[static_cast<int>(MONSTER_STATE::WAIT)] = "WAIT";
	ArrAnimationName[static_cast<int>(MONSTER_STATE::WALK)] = "WALK";

	ArrAnimationName[static_cast<int>(MONSTER_STATE::RE_CHECK)] = "CHECKWAIT";
	ArrAnimationName[static_cast<int>(MONSTER_STATE::CHECK)] = "CHECKWAIT";
	ArrAnimationName[static_cast<int>(MONSTER_STATE::BACK)] = "CHECKWAIT";
	ArrAnimationName[static_cast<int>(MONSTER_STATE::COLL)] = "CHECKWAIT";

	ArrAnimationName[static_cast<int>(MONSTER_STATE::MOVE_TO_PLAYER)] = "CHECKWAIT";

	ArrAnimationName[static_cast<int>(MONSTER_STATE::DEATH)] = "DEATH";
}

Golem::~Golem() 
{
}

void Golem::Start()
{
	MonsterRenderer_ = CreateRenderer("StoneGolem.bmp");
	MonsterRenderer_->SetIndex(0);

	MonsterCollider_ = CreateCollision("Monster", { 48.f, 36.f });
	MonsterCollider_->SetPivot({ 0, 18.f });

	MonsterRenderer_->CreateAnimation("StoneGolem.bmp", "RIGHT_WALK", static_cast<int>(STONE_GOLEM::RIGHT_WALK00), static_cast<int>(STONE_GOLEM::RIGHT_WALK03), 0.120f, true);
	MonsterRenderer_->CreateAnimation("StoneGolem.bmp", "LEFT_WALK", static_cast<int>(STONE_GOLEM::LEFT_WALK00), static_cast<int>(STONE_GOLEM::LEFT_WALK03), 0.120f, true);
	MonsterRenderer_->CreateAnimation("StoneGolem.bmp", "FRONT_WALK", static_cast<int>(STONE_GOLEM::FRONT_WALK00), static_cast<int>(STONE_GOLEM::FRONT_WALK03), 0.120f, true);
	MonsterRenderer_->CreateAnimation("StoneGolem.bmp", "BACK_WALK", static_cast<int>(STONE_GOLEM::BACK_WALK00), static_cast<int>(STONE_GOLEM::BACK_WALK03), 0.120f, true);

	MonsterRenderer_->CreateAnimation("StoneGolem.bmp", "RIGHT_REVIVAL", static_cast<int>(STONE_GOLEM::REVIVAL00), static_cast<int>(STONE_GOLEM::REVIVAL_K07), 0.200f, false);
	MonsterRenderer_->CreateAnimation("StoneGolem.bmp", "LEFT_REVIVAL", static_cast<int>(STONE_GOLEM::REVIVAL00), static_cast<int>(STONE_GOLEM::REVIVAL_K07), 0.200f, false);
	MonsterRenderer_->CreateAnimation("StoneGolem.bmp", "FRONT_REVIVAL", static_cast<int>(STONE_GOLEM::REVIVAL00), static_cast<int>(STONE_GOLEM::REVIVAL_K07), 0.200f, false);
	MonsterRenderer_->CreateAnimation("StoneGolem.bmp", "BACK_REVIVAL", static_cast<int>(STONE_GOLEM::REVIVAL00), static_cast<int>(STONE_GOLEM::REVIVAL_K07), 0.200f, false);

	MonsterRenderer_->CreateAnimation("StoneGolem.bmp", "RIGHT_DEATH", static_cast<int>(STONE_GOLEM::DEATH), static_cast<int>(STONE_GOLEM::DEATH), 0.200f, false);
	MonsterRenderer_->CreateAnimation("StoneGolem.bmp", "LEFT_DEATH", static_cast<int>(STONE_GOLEM::DEATH), static_cast<int>(STONE_GOLEM::DEATH), 0.200f, false);
	MonsterRenderer_->CreateAnimation("StoneGolem.bmp", "FRONT_DEATH", static_cast<int>(STONE_GOLEM::DEATH), static_cast<int>(STONE_GOLEM::DEATH), 0.200f, false);
	MonsterRenderer_->CreateAnimation("StoneGolem.bmp", "BACK_DEATH", static_cast<int>(STONE_GOLEM::DEATH), static_cast<int>(STONE_GOLEM::DEATH), 0.200f, false);

	MonsterRenderer_->CreateAnimation("StoneGolem.bmp", "RIGHT_CHECKWAIT", static_cast<int>(STONE_GOLEM::RIGHT_WALK00), static_cast<int>(STONE_GOLEM::RIGHT_WALK03), 0.120f, true);
	MonsterRenderer_->CreateAnimation("StoneGolem.bmp", "LEFT_CHECKWAIT", static_cast<int>(STONE_GOLEM::LEFT_WALK00), static_cast<int>(STONE_GOLEM::LEFT_WALK03), 0.120f, true);
	MonsterRenderer_->CreateAnimation("StoneGolem.bmp", "FRONT_CHECKWAIT", static_cast<int>(STONE_GOLEM::FRONT_WALK00), static_cast<int>(STONE_GOLEM::FRONT_WALK03), 0.120f, true);
	MonsterRenderer_->CreateAnimation("StoneGolem.bmp", "BACK_CHECKWAIT", static_cast<int>(STONE_GOLEM::BACK_WALK00), static_cast<int>(STONE_GOLEM::BACK_WALK03), 0.120f, true);

	MonsterRenderer_->CreateAnimation("StoneGolem.bmp", "RIGHT_WAIT", static_cast<int>(STONE_GOLEM::DEATH), static_cast<int>(STONE_GOLEM::DEATH), 0.120f, false);
	MonsterRenderer_->CreateAnimation("StoneGolem.bmp", "LEFT_WAIT", static_cast<int>(STONE_GOLEM::DEATH), static_cast<int>(STONE_GOLEM::DEATH), 0.120f, false);
	MonsterRenderer_->CreateAnimation("StoneGolem.bmp", "FRONT_WAIT", static_cast<int>(STONE_GOLEM::DEATH), static_cast<int>(STONE_GOLEM::DEATH), 0.120f, false);
	MonsterRenderer_->CreateAnimation("StoneGolem.bmp", "BACK_WAIT", static_cast<int>(STONE_GOLEM::DEATH), static_cast<int>(STONE_GOLEM::DEATH), 0.120f, false);

	MonsterRenderer_->ChangeAnimation("FRONT_WALK");

	Damage_ = 2;
	HP_ = 22;
	Speed_ = 60.f;

	MonsterState_ = MONSTER_STATE::WAIT;
	MonsterType_ = MONSTER_TYPE::GOLEM;

	SetScale({ 48, 50 });
}

void Golem::Update()
{
	//몬스터 방향 체크
	DirAnimation(); 

	Dir = Player::MainPlayer->GetPosition() - this->GetPosition();

	//범위 체크
	Check_ = Dir.Len2D();
	Dir.Normal2D();

	if (isDeath_ == true || HP_ <= 0)
	{
		MonsterState_ = MONSTER_STATE::DEATH;

	}

	switch (MonsterState_)
	{
	case MONSTER_STATE::WAIT:
		invincibility_ = true;

		if (Check_ <= 150)
		{
			GameEngineSound::SoundPlayOneShot("skeletonDie.wav");
			invincibility_ = false;
			MonsterState_ = MONSTER_STATE::REVIVAL;
		}
		break;

	case MONSTER_STATE::REVIVAL:


		if (MonsterRenderer_->IsEndAnimation())
		{

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

		//랜덤한 방향을 정하고 벽이 있다면 다시 돌아온다
		MonsterState_ = MONSTER_STATE::CHECK;

		break;


	case MONSTER_STATE::MOVE_TO_PLAYER :

		//x가 더 짧다
		if (Dir.x < Dir.y)
		{
			if (Dir.x > 0)
			{
				MoveDir_ = float4::RIGHT;
				MonsterState_ = MONSTER_STATE::WALK;
				break;
			}
			else
			{
				MoveDir_ = float4::LEFT;
				MonsterState_ = MONSTER_STATE::WALK;
				break;
			}
		}

		//y가 더 짧다
		else 
		{
			if (Dir.y < 0)
			{
				MoveDir_ = float4::UP;
				MonsterState_ = MONSTER_STATE::WALK;
				break;
			}

			else 
			{
				MoveDir_ = float4::DOWN;
				MonsterState_ = MONSTER_STATE::WALK;
				break;
			}
		}

		break;
	case MONSTER_STATE::WALK:

		//가다가 일정 시간이 지나면 방향을 튼다.
		Timer_ += GameEngineTime::GetDeltaTime();
		if (Timer_ > 1.0f && Check_ > 300)
		{
			Timer_ = 0.f;
			MonsterState_ = MONSTER_STATE::CHECK;
		}
		//플레이어로 향하는 방향 체크

		//플레이어에게 향하는 길을 찾는다. && 플레이어와 닿았을때 방향전향플러그가 true일때만
		//플레이어를 향해 간다.

		CheckTimer_ += GameEngineTime::GetDeltaTime();

		if (Check_ <= 150)
		{
			if (CheckTimer_ > 1.0f)
			{
				CheckTimer_ = 0.f;
				MonsterState_ = MONSTER_STATE::MOVE_TO_PLAYER;

				break;
			}

		}

		//오브젝트가 있으면 랜덤한 방향으로 머리를 튼다.
		if (CheckMapObject() == true)
		{
			MonsterState_ = MONSTER_STATE::CHECK;
			break;
		}


		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);

		break;
	case MONSTER_STATE::BACK:
		BackMove();

		break;
	case MONSTER_STATE::DEATH:

		//MonsterRenderer_->SetPivot({ 0 , 12 });
		if (MonsterRenderer_->IsEndAnimation())
		{
			GameEngineSound::SoundPlayOneShot("shadowDie.wav");
			this->Death();
		}

		break;
	}

}


void Golem::DirAnimation()
{
	MonsterRenderer_->ChangeAnimation(GetDirString() + ArrAnimationName[static_cast<int>(MonsterState_)]);
}

