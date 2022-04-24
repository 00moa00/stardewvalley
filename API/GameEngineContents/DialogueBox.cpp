#include "DialogueBox.h"

DialogueBox::DialogueBox() 

	:
		DialogueBoxRenderer_(nullptr),
		PortraitRenderer_(nullptr),
		DialogueRenderer_(nullptr),
		DialogueRandom_()

{
}

DialogueBox::~DialogueBox() 
{
}

void DialogueBox::Start()
{
	SetPosition({ GameEngineWindow::GetScale().Half().x, 520.f });

	DialogueBoxRenderer_ = CreateRenderer("DialogueBox.bmp");
	DialogueBoxRenderer_->CameraEffectOff();

	PortraitRenderer_ = CreateRenderer("Pierre_Portrait.bmp");
	PortraitRenderer_->SetIndex(0);
	PortraitRenderer_->SetPivot({756.f - 478.5f, -26.f});
	PortraitRenderer_->CameraEffectOff();

	DialogueRenderer_ = CreateRenderer("Pierre_dialogue_Sheet.bmp");
	DialogueRenderer_->SetIndex(0);
	DialogueRenderer_->SetPivot({ 0,0 });
	DialogueRenderer_->CameraEffectOff();


	DialogueName_ = CreateRenderer("Name_Sheet.bmp");
	DialogueName_->SetIndex(0);
	DialogueName_->SetPivot({ 755.f - 478.5f, 110.f });
	DialogueName_->CameraEffectOff();


}

void DialogueBox::Update()
{
}

void DialogueBox::Render()
{
}

void DialogueBox::SetDialogue(std::string _Text)
{
}

void DialogueBox::SetPierre()
{
	PortraitRenderer_->SetImage("Pierre_Portrait.bmp");
	PortraitRenderer_->SetIndex(0);
	DialogueRenderer_->SetIndex(DialogueRandom_.RandomInt(0,3));
	DialogueName_->SetIndex(static_cast<int>(NPC::PIERRE));
}

void DialogueBox::SetLewis()
{
	PortraitRenderer_->SetImage("Lewis_Portrait.bmp");
	DialogueName_->SetIndex(static_cast<int>(NPC::LEWIS));

}

void DialogueBox::DialogueOn()
{
	DialogueBoxRenderer_->On();
	PortraitRenderer_->On();
	DialogueRenderer_->On();
	DialogueName_->On();

}

void DialogueBox::DialogueOff()
{
	DialogueBoxRenderer_->Off();
	PortraitRenderer_->Off();
	DialogueRenderer_->Off();
	DialogueName_->Off();
}

