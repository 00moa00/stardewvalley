#include "Pierre.h"
#include "Player.h"

Pierre* Pierre::MainPierre = nullptr;

Pierre::Pierre() 
{
}

Pierre::~Pierre() 
{
}

void Pierre::Start()
{
	NpcRenderer_ = CreateRenderer("Pierre.bmp");
	NpcRenderer_->SetIndex(0);

	PersonalCollider_ = CreateCollision("Pierre", { 48.f, 96.f });
	NpcCollider_ = CreateCollision("NPC", { 48.f, 96.f });

	DialogueBox_ = GetLevel()->CreateActor<DialogueBox>(static_cast<int>(PLAYLEVEL::DIALOGUEBOX));
	DialogueBox_ -> DialogueOff();

	NpcRenderer_->CreateAnimation("Pierre.bmp", "RIGHT_INIT", static_cast<int>(NPC_INDEX::RIGHT_WALK00), static_cast<int>(NPC_INDEX::RIGHT_WALK00), 0.0f, false);
	NpcRenderer_->CreateAnimation("Pierre.bmp", "LEFT_INIT", static_cast<int>(NPC_INDEX::LEFT_WALK00), static_cast<int>(NPC_INDEX::LEFT_WALK00), 0.0f, false);
	NpcRenderer_->CreateAnimation("Pierre.bmp", "FRONT_INIT", static_cast<int>(NPC_INDEX::FRONT_WALK00), static_cast<int>(NPC_INDEX::FRONT_WALK00), 0.0f, false);
	NpcRenderer_->CreateAnimation("Pierre.bmp", "BACK_INIT", static_cast<int>(NPC_INDEX::BACK_WALK00), static_cast<int>(NPC_INDEX::BACK_WALK00), 0.0f, false);

	NpcRenderer_->ChangeAnimation("FRONT_INIT");

}

void Pierre::Update()
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

void Pierre::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainPierre = this;
}

void Pierre::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}

void Pierre::OpenDialogue()
{
	DialogueUpdate_ = !DialogueUpdate_;


	if (DialogueUpdate_ == true)
	{
		DialogueBox_ ->DialogueOn();
		DialogueBox_->SetPierre();
		MoveDir_ = - Player::MainPlayer->GetMoveDir();
	}


	if (DialogueUpdate_ == false)
	{
		DialogueBox_->DialogueOff();
	}
}

