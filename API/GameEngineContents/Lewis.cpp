#include "Lewis.h"
#include "Player.h"
#include "MainUI.h"

//Lewis* Lewis::MainLewis = nullptr;
//DialogueBox* Lewis::MainDialogueBox_ = nullptr;

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

	NpcCollider_ = CreateCollision("NPC", { 48.f, 20.f });
	NpcCollider_->SetPivot({ 0, 40.f });

	MainDialogueBox_ = GetLevel()->CreateActor<DialogueBox>(static_cast<int>(PLAYLEVEL::DIALOGUEBOX));
	MainDialogueBox_->DialogueOff();

	NpcRenderer_->CreateAnimation("Lewis.bmp", "RIGHT_INIT", static_cast<int>(NPC_INDEX::RIGHT_WALK00), static_cast<int>(NPC_INDEX::RIGHT_WALK00), 0.0f, false);
	NpcRenderer_->CreateAnimation("Lewis.bmp", "LEFT_INIT", static_cast<int>(NPC_INDEX::LEFT_WALK00), static_cast<int>(NPC_INDEX::LEFT_WALK00), 0.0f, false);
	NpcRenderer_->CreateAnimation("Lewis.bmp", "FRONT_INIT", static_cast<int>(NPC_INDEX::FRONT_WALK00), static_cast<int>(NPC_INDEX::FRONT_WALK00), 0.0f, false);
	NpcRenderer_->CreateAnimation("Lewis.bmp", "BACK_INIT", static_cast<int>(NPC_INDEX::BACK_WALK00), static_cast<int>(NPC_INDEX::BACK_WALK00), 0.0f, false);

	NpcRenderer_->CreateAnimation("Lewis.bmp", "RIGHT_WALK", static_cast<int>(NPC_INDEX::RIGHT_WALK00), static_cast<int>(NPC_INDEX::RIGHT_WALK03), 0.150f, true);
	NpcRenderer_->CreateAnimation("Lewis.bmp", "LEFT_WALK", static_cast<int>(NPC_INDEX::LEFT_WALK00), static_cast<int>(NPC_INDEX::LEFT_WALK03), 0.150f, true);
	NpcRenderer_->CreateAnimation("Lewis.bmp", "FRONT_WALK", static_cast<int>(NPC_INDEX::FRONT_WALK00), static_cast<int>(NPC_INDEX::FRONT_WALK03), 0.150f, true);
	NpcRenderer_->CreateAnimation("Lewis.bmp", "BACK_WALK", static_cast<int>(NPC_INDEX::BACK_WALK00), static_cast<int>(NPC_INDEX::BACK_WALK03), 0.150f, true);


	NpcRenderer_->ChangeAnimation("FRONT_INIT");
	SetScale({ 48,96 });

	LoadLewisMoveFlag();
}

void Lewis::Update()
{
	MoveUpdate();
	CheckTalkingLimit();

	if (NpcUpdateState_ == NPC_STATE::WAIT)
	{

		//오전 10시
		if (MainUI::MainMainUI->GetHour() > 10 && WaitCount_ == 0)
		{
			//MoveDir_ = float4::DOWN;
			NpcUpdateState_ = NPC_STATE::WALK;
		}

		//if (MainUI::MainMainUI->GetHour() > 18 && WaitCount_ == 1)
		//{
		//	MoveDir_ = float4::DOWN;
		//	NpcUpdateState_ = NPC_STATE::WALK;
		//}


	}


}

void Lewis::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	//MainLewis = this;
	MainDialogueBox_ = MainDialogueBox_;
}

void Lewis::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	//MainDialogueBox_->NextLevelOn();
}

void Lewis::OpenDialogue()
{
	DialogueUpdate_ = !DialogueUpdate_;


	if (DialogueUpdate_ == true)
	{
		Inventory::MainInventory->AllUpdateOff();

		MainDialogueBox_->DialogueOn();
		MainDialogueBox_->SetLewis();

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
		NpcUpdateState_ = NPC_STATE::DIALOGUE_WAIT;
	}
}

bool Lewis::MoveRight()
{
	return (NpcCollider_->CollisionResult("LewisRight", ColList, CollisionType::Rect, CollisionType::Rect));
}

bool Lewis::MoveLeft()
{
	return (NpcCollider_->CollisionResult("LewisLeft", ColList, CollisionType::Rect, CollisionType::Rect));
}

bool Lewis::MoveDown()
{
	return (NpcCollider_->CollisionResult("LewisDown", ColList, CollisionType::Rect, CollisionType::Rect));
}

bool Lewis::MoveUp()
{
	return (NpcCollider_->CollisionResult("LewisUp", ColList, CollisionType::Rect, CollisionType::Rect));
}


bool Lewis::MoveWait()
{
	if (NpcCollider_->CollisionResult("LewisWait", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		for (std::vector<NpcMove*>::iterator Start = MoveFlagList_.begin(); Start != MoveFlagList_.end(); ++Start)
		{
			if ((*Start)->CheckCollNPC())
			{
				(*Start)->Death();
				MoveFlagList_.erase(Start);
				return true;
			}

			else
			{
				false;
			}
		}
	}

	else
	{
		return false;
	}
}

