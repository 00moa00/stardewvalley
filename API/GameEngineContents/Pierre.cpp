#include "Pierre.h"

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
}

void Pierre::Update()
{
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
	}


	if (DialogueUpdate_ == false)
	{
		DialogueBox_->DialogueOff();
	}
}


