#include "Pierre.h"
#include "Player.h"

Pierre* Pierre::MainPierre = nullptr;
DialogueBox* Pierre::MainDialogueBox_ = nullptr;


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

	NpcCollider_ = CreateCollision("NPC", { 48.f, 60.f });
	NpcCollider_->SetPivot({ 0, 20.f });

	MainDialogueBox_ = GetLevel()->CreateActor<DialogueBox>(static_cast<int>(PLAYLEVEL::DIALOGUEBOX));
	MainDialogueBox_-> DialogueOff();

	NpcRenderer_->CreateAnimation("Pierre.bmp", "RIGHT_INIT", static_cast<int>(NPC_INDEX::RIGHT_WALK00), static_cast<int>(NPC_INDEX::RIGHT_WALK00), 0.0f, false);
	NpcRenderer_->CreateAnimation("Pierre.bmp", "LEFT_INIT", static_cast<int>(NPC_INDEX::LEFT_WALK00), static_cast<int>(NPC_INDEX::LEFT_WALK00), 0.0f, false);
	NpcRenderer_->CreateAnimation("Pierre.bmp", "FRONT_INIT", static_cast<int>(NPC_INDEX::FRONT_WALK00), static_cast<int>(NPC_INDEX::FRONT_WALK00), 0.0f, false);
	NpcRenderer_->CreateAnimation("Pierre.bmp", "BACK_INIT", static_cast<int>(NPC_INDEX::BACK_WALK00), static_cast<int>(NPC_INDEX::BACK_WALK00), 0.0f, false);

	NpcRenderer_->ChangeAnimation("FRONT_INIT");
	SetScale({ 48,96 });

}

void Pierre::Update()
{
	MoveUpdate();

}

void Pierre::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainPierre = this;
	MainDialogueBox_ = MainDialogueBox_;
}

void Pierre::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	MainDialogueBox_->NextLevelOn();
}

void Pierre::OpenDialogue()
{
	DialogueUpdate_ = !DialogueUpdate_;


	if (DialogueUpdate_ == true)
	{
		MainDialogueBox_->DialogueOn();
		MainDialogueBox_->SetPierre();
		MoveDir_ = - Player::MainPlayer->GetMoveDir();
	}


	if (DialogueUpdate_ == false)
	{
		MainDialogueBox_->DialogueOff();
	}
}

