#include "Penny.h"
#include "Player.h"
#include "MainUI.h"

//DialogueBox* Penny::MainDialogueBox_ = nullptr;


Penny::Penny() 
	:
	MainDialogueBox_(nullptr)

{
}

Penny::~Penny() 
{
}

void Penny::Start()
{
	NpcRenderer_ = CreateRenderer("Penny.bmp");
	NpcRenderer_->SetIndex(0);
	NpcCollider_ = CreateCollision("NPC", { 48.f, 20.f });
	NpcCollider_->SetPivot({0, 40.f});

	MainDialogueBox_ = GetLevel()->CreateActor<DialogueBox>(static_cast<int>(PLAYLEVEL::DIALOGUEBOX));
	MainDialogueBox_->DialogueOff();

	NpcRenderer_->CreateAnimation("Penny.bmp", "RIGHT_INIT", static_cast<int>(NPC_INDEX::RIGHT_WALK00), static_cast<int>(NPC_INDEX::RIGHT_WALK00), 0.0f, false);
	NpcRenderer_->CreateAnimation("Penny.bmp", "LEFT_INIT", static_cast<int>(NPC_INDEX::LEFT_WALK00), static_cast<int>(NPC_INDEX::LEFT_WALK00), 0.0f, false);
	NpcRenderer_->CreateAnimation("Penny.bmp", "FRONT_INIT", static_cast<int>(NPC_INDEX::FRONT_WALK00), static_cast<int>(NPC_INDEX::FRONT_WALK00), 0.0f, false);
	NpcRenderer_->CreateAnimation("Penny.bmp", "BACK_INIT", static_cast<int>(NPC_INDEX::BACK_WALK00), static_cast<int>(NPC_INDEX::BACK_WALK00), 0.0f, false);

	NpcRenderer_->CreateAnimation("Penny.bmp", "RIGHT_WALK", static_cast<int>(NPC_INDEX::RIGHT_WALK00), static_cast<int>(NPC_INDEX::RIGHT_WALK03), 0.150f, true);
	NpcRenderer_->CreateAnimation("Penny.bmp", "LEFT_WALK", static_cast<int>(NPC_INDEX::LEFT_WALK00), static_cast<int>(NPC_INDEX::LEFT_WALK03), 0.150f, true);
	NpcRenderer_->CreateAnimation("Penny.bmp", "FRONT_WALK", static_cast<int>(NPC_INDEX::FRONT_WALK00), static_cast<int>(NPC_INDEX::FRONT_WALK03), 0.150f, true);
	NpcRenderer_->CreateAnimation("Penny.bmp", "BACK_WALK", static_cast<int>(NPC_INDEX::BACK_WALK00), static_cast<int>(NPC_INDEX::BACK_WALK03), 0.150f, true);

	NpcRenderer_->ChangeAnimation("FRONT_INIT");
	SetScale({ 50,100 });
	MoveDir_ = float4::DOWN;
	NpcUpdateState_ = NPC_STATE::WALK;

	LoadPennyMoveFlag();
}

void Penny::Update()
{
	MoveUpdate();
	NPCDayOver();

	if (NpcUpdateState_ == NPC_STATE::WAIT)
	{
		if (MainUI::MainMainUI->GetHour() > 13 && WaitCount_ == 1)
		{
			MoveDir_ = float4::UP;
			NpcUpdateState_ = NPC_STATE::WALK;
		}
	}
}

void Penny::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	//MainDialogueBox_ = MainDialogueBox_;
}

void Penny::LevelChangeEnd(GameEngineLevel* _NextLevel)
{

}

void Penny::OpenDialogue()
{

	if (TalkingLimit_ == false)
	{
		DialogueUpdate_ = !DialogueUpdate_;


		if (DialogueUpdate_ == true)
		{
			Inventory::MainInventory->AllUpdateOff();

			MainDialogueBox_->DialogueOn();
			MainDialogueBox_->SetPenny();

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

bool Penny::MoveRight()
{
	return (NpcCollider_->CollisionResult("PennyRight", ColList, CollisionType::Rect, CollisionType::Rect));
}

bool Penny::MoveLeft()
{
	return (NpcCollider_->CollisionResult("PennyLeft", ColList, CollisionType::Rect, CollisionType::Rect));
}

bool Penny::MoveDown()
{
	return (NpcCollider_->CollisionResult("PennyDown", ColList, CollisionType::Rect, CollisionType::Rect));
}

bool Penny::MoveUp()
{
	return (NpcCollider_->CollisionResult("PennyUp", ColList, CollisionType::Rect, CollisionType::Rect));

}

bool Penny::MoveWait()
{
	if (NpcCollider_->CollisionResult("PennyWait", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		for (std::vector<NpcMove*>::iterator Start = MoveFlagList_.begin(); Start != MoveFlagList_.end(); ++Start)
		{
			if ((*Start)->CheckCollNPC())
			{
				(*Start)->Death();
				MoveFlagList_.erase(Start);
				return true;
			}
		}
	}

	else
	{
		return false;
	}
}

