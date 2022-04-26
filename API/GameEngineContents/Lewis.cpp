#include "Lewis.h"
#include "Player.h"

Lewis* Lewis::MainLewis = nullptr;

Lewis::Lewis() 
{
}

Lewis::~Lewis() 
{
}

void Lewis::Start()
{
	NpcRenderer_ = CreateRenderer("Lewis.bmp");
	NpcRenderer_->SetIndex(0);

	PersonalCollider_ = CreateCollision("Lewis", { 48.f, 96.f });
	NpcCollider_ = CreateCollision("NPC", { 48.f, 96.f });

	DialogueBox_ = GetLevel()->CreateActor<DialogueBox>(static_cast<int>(PLAYLEVEL::DIALOGUEBOX));
	DialogueBox_->DialogueOff();

	NpcRenderer_->CreateAnimation("Lewis.bmp", "RIGHT_INIT", static_cast<int>(NPC_INDEX::RIGHT_WALK00), static_cast<int>(NPC_INDEX::RIGHT_WALK00), 0.0f, false);
	NpcRenderer_->CreateAnimation("Lewis.bmp", "LEFT_INIT", static_cast<int>(NPC_INDEX::LEFT_WALK00), static_cast<int>(NPC_INDEX::LEFT_WALK00), 0.0f, false);
	NpcRenderer_->CreateAnimation("Lewis.bmp", "FRONT_INIT", static_cast<int>(NPC_INDEX::FRONT_WALK00), static_cast<int>(NPC_INDEX::FRONT_WALK00), 0.0f, false);
	NpcRenderer_->CreateAnimation("Lewis.bmp", "BACK_INIT", static_cast<int>(NPC_INDEX::BACK_WALK00), static_cast<int>(NPC_INDEX::BACK_WALK00), 0.0f, false);

	NpcRenderer_->ChangeAnimation("FRONT_INIT");
}

void Lewis::Update()
{
	switch (NpcUpdateState_)
	{
	case NPC_STATE::INIT:

		//플레이어와 멀어지면 원래 방향으로 리셋
		if (ForAwayPlayer() == true)
		{
			MoveDir_ = float4::DOWN;
		}

		break;
	case NPC_STATE::WALK:

		break;
	default:
		break;
	}

	DirAnimationChange();
}

void Lewis::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
}

void Lewis::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}

void Lewis::OpenDialogue()
{
	DialogueUpdate_ = !DialogueUpdate_;


	if (DialogueUpdate_ == true)
	{
		DialogueBox_->DialogueOn();
		DialogueBox_->SetPierre();
		MoveDir_ = -Player::MainPlayer->GetMoveDir();
	}


	if (DialogueUpdate_ == false)
	{
		DialogueBox_->DialogueOff();
	}
}

