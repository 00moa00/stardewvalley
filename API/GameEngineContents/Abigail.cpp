#include "Abigail.h"
#include "Player.h"
#include "MainUI.h"

Abigail::Abigail() 
    :
    MainDialogueBox_(nullptr)
{
}

Abigail::~Abigail() 
{
}

void Abigail::Start()
{
	NpcRenderer_ = CreateRenderer("Abigail.bmp");
	NpcRenderer_->SetIndex(0);
	NpcCollider_ = CreateCollision("NPC", { 48.f, 20.f });
	NpcCollider_->SetPivot({ 0, 40.f });

	MainDialogueBox_ = GetLevel()->CreateActor<DialogueBox>(static_cast<int>(PLAYLEVEL::DIALOGUEBOX));
	MainDialogueBox_->DialogueOff();

	NpcRenderer_->CreateAnimation("Abigail.bmp", "RIGHT_INIT", static_cast<int>(NPC_INDEX::RIGHT_WALK00), static_cast<int>(NPC_INDEX::RIGHT_WALK00), 0.0f, false);
	NpcRenderer_->CreateAnimation("Abigail.bmp", "LEFT_INIT", static_cast<int>(NPC_INDEX::LEFT_WALK00), static_cast<int>(NPC_INDEX::LEFT_WALK00), 0.0f, false);
	NpcRenderer_->CreateAnimation("Abigail.bmp", "FRONT_INIT", static_cast<int>(NPC_INDEX::FRONT_WALK00), static_cast<int>(NPC_INDEX::FRONT_WALK00), 0.0f, false);
	NpcRenderer_->CreateAnimation("Abigail.bmp", "BACK_INIT", static_cast<int>(NPC_INDEX::BACK_WALK00), static_cast<int>(NPC_INDEX::BACK_WALK00), 0.0f, false);

	NpcRenderer_->CreateAnimation("Abigail.bmp", "RIGHT_WALK", static_cast<int>(NPC_INDEX::RIGHT_WALK00), static_cast<int>(NPC_INDEX::RIGHT_WALK03), 0.150f, true);
	NpcRenderer_->CreateAnimation("Abigail.bmp", "LEFT_WALK", static_cast<int>(NPC_INDEX::LEFT_WALK00), static_cast<int>(NPC_INDEX::LEFT_WALK03), 0.150f, true);
	NpcRenderer_->CreateAnimation("Abigail.bmp", "FRONT_WALK", static_cast<int>(NPC_INDEX::FRONT_WALK00), static_cast<int>(NPC_INDEX::FRONT_WALK03), 0.150f, true);
	NpcRenderer_->CreateAnimation("Abigail.bmp", "BACK_WALK", static_cast<int>(NPC_INDEX::BACK_WALK00), static_cast<int>(NPC_INDEX::BACK_WALK03), 0.150f, true);

	NpcRenderer_->ChangeAnimation("FRONT_INIT");
	SetScale({ 50,100 });

	LoadAbigailMoveFlag();
}

void Abigail::Update()
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

void Abigail::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
}

void Abigail::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}

void Abigail::OpenDialogue()
{

	if (TalkingLimit_ == false)
	{
		DialogueUpdate_ = !DialogueUpdate_;


		if (DialogueUpdate_ == true)
		{
			Inventory::MainInventory->AllUpdateOff();

			MainDialogueBox_->DialogueOn();
			MainDialogueBox_->SetAbigail();

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

bool Abigail::MoveRight()
{
	return (NpcCollider_->CollisionResult("AbigailRight", ColList, CollisionType::Rect, CollisionType::Rect));
}

bool Abigail::MoveLeft()
{
	return (NpcCollider_->CollisionResult("AbigailLeft", ColList, CollisionType::Rect, CollisionType::Rect));
}

bool Abigail::MoveDown()
{
	return (NpcCollider_->CollisionResult("AbigailDown", ColList, CollisionType::Rect, CollisionType::Rect));
}

bool Abigail::MoveUp()
{
	return (NpcCollider_->CollisionResult("AbigailUp", ColList, CollisionType::Rect, CollisionType::Rect));
}

bool Abigail::MoveWait()
{
	if (NpcCollider_->CollisionResult("AbigailWait", ColList, CollisionType::Rect, CollisionType::Rect))
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
