#include "DialogueBox.h"

DialogueBox::DialogueBox() 
{
}

DialogueBox::~DialogueBox() 
{
}

void DialogueBox::Start()
{
	DialogueRenderer_ = CreateRenderer("DialogueBox.bmp");
	DialogueRenderer_->CameraEffectOff();

	PortraitRenderer_ = CreateRenderer("Pierre_Portrait.bmp");
	PortraitRenderer_->SetIndex(0);
		
	DialogueFont_1.Load("Stardew_Valley.ttf");
	Dialogue_1 = "";

}

void DialogueBox::Update()
{
}

void DialogueBox::Render()
{


	DialogueFont_1.Draw(Dialogue_1, { 100.0f, 100.0f }, 100, 50);
}

void DialogueBox::SetDialogue(std::string _Text)
{
	Dialogue_1 = _Text;
}

void DialogueBox::SetPierre()
{
	PortraitRenderer_->SetImage("Pierre_Portrait.bmp");
	PortraitRenderer_->SetIndex(0);
	Dialogue_1 = " * sigh* ... I've got those behind-the-counter- blues...";
}

void DialogueBox::SetLewis()
{
	PortraitRenderer_->SetImage("Lewis_Portrait.bmp");
	PortraitRenderer_->SetIndex(0);
}

