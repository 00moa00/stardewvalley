#include "MenuButton.h"
#include <GameEngineBase/GameEngineInput.h>

MenuButton::MenuButton() 
	:
	Index_(0),

	ButtonRenderer_(nullptr),
	ButtonCollision_(nullptr)
{
}

MenuButton::~MenuButton() 
{
}

void MenuButton::Start()
{
	ButtonRenderer_ = CreateRenderer();
	ButtonRenderer_->CameraEffectOff();
}

void MenuButton::Update()
{


}

void MenuButton::CreateButtonRenderer(std::string _FileName, int _Index)
{
	Index_ = _Index;
	ButtonRenderer_->SetImage(_FileName);
	ButtonRenderer_->SetIndex(_Index);
}

void MenuButton::CreateButtonRenderer(std::string _FileName)
{
	ButtonRenderer_->SetImage(_FileName);
}

void MenuButton::CreateButtonCollision(std::string _CollName, float4 _CollSize)
{
	ButtonCollision_ = CreateCollision(_CollName, _CollSize);

}

void MenuButton::MouseOverChangeIndex()
{
	if (ButtonCollision_ != nullptr && ButtomMouseOver())
	{
		ButtonRenderer_->SetIndex(Index_ + 4);
	}

	else
	{
		ButtonRenderer_->SetIndex(Index_);
	}
}

bool MenuButton::ButtomMouseOver()
{
	return (ButtonCollision_->CollisionResult("MouseCursor", ColList, CollisionType::Rect, CollisionType::Rect));

}

bool MenuButton::ButtonMouseOverAndLeftClick()
{
	return (ButtonCollision_->CollisionResult("MouseCursor", ColList, CollisionType::Rect, CollisionType::Rect))
		&&(true == GameEngineInput::GetInst()->IsDown("LeftClick"));
}
