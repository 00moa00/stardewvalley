#include "Pierre.h"
#include "Player.h"

//Pierre* Pierre::MainPierre = nullptr;
//DialogueBox* Pierre::MainDialogueBox_ = nullptr;


Pierre::Pierre() 
	:
	MainDialogueBox_(nullptr)

{
}

Pierre::~Pierre() 
{
}

void Pierre::Start()
{
	NpcRenderer_ = CreateRenderer("Pierre.bmp");
	NpcRenderer_->SetIndex(0);

	NpcCollider_ = CreateCollision("NPC", { 48.f, 20.f });
	NpcCollider_->SetPivot({ 0, 40.f });

	MainDialogueBox_ = GetLevel()->CreateActor<DialogueBox>(static_cast<int>(PLAYLEVEL::DIALOGUEBOX));
	MainDialogueBox_-> DialogueOff();

	NpcRenderer_->CreateAnimation("Pierre.bmp", "RIGHT_INIT", static_cast<int>(NPC_INDEX::RIGHT_WALK00), static_cast<int>(NPC_INDEX::RIGHT_WALK00), 0.0f, false);
	NpcRenderer_->CreateAnimation("Pierre.bmp", "LEFT_INIT", static_cast<int>(NPC_INDEX::LEFT_WALK00), static_cast<int>(NPC_INDEX::LEFT_WALK00), 0.0f, false);
	NpcRenderer_->CreateAnimation("Pierre.bmp", "FRONT_INIT", static_cast<int>(NPC_INDEX::FRONT_WALK00), static_cast<int>(NPC_INDEX::FRONT_WALK00), 0.0f, false);
	NpcRenderer_->CreateAnimation("Pierre.bmp", "BACK_INIT", static_cast<int>(NPC_INDEX::BACK_WALK00), static_cast<int>(NPC_INDEX::BACK_WALK00), 0.0f, false);

	NpcRenderer_->ChangeAnimation("FRONT_INIT");
	SetScale({ 100,150 });

}

void Pierre::Update()
{
	MoveUpdate();
	NPCDayOver();
}

void Pierre::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	//MainPierre = this;
	//MainDialogueBox_ = MainDialogueBox_;
}

void Pierre::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	//MainDialogueBox_->NextLevelOn();
}

void Pierre::OpenDialogue()
{
	if (TalkingLimit_ == false)
	{
		DialogueUpdate_ = !DialogueUpdate_;

		if (DialogueUpdate_ == true)
		{
			Inventory::MainInventory->AllUpdateOff();

			MainDialogueBox_->DialogueOn();
			MainDialogueBox_->SetPierre();

			//현재 방향 저장하고 플레이어의 방향으로 고개 돌림
			PrevDir_ = MoveDir_;
			MoveDir_ = -Player::MainPlayer->GetMoveDir();
			NpcUpdateState_ = NPC_STATE::DIALOGUE_IDLE;
		}


		if (DialogueUpdate_ == false)
		{
			Inventory::MainInventory->AllUpdateOn();
			Inventory::MainInventory->SetPopUpStateMini();

			MainDialogueBox_->DialogueOff();
			WaitTimer_ = 2.0f;
			TalkingLimit_ = true;
			NpcUpdateState_ = NPC_STATE::DIALOGUE_WAIT;
		}
	}

}

