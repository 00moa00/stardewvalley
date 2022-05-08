#include "CustomBoard.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngine.h>
#include "RendererData.h"
#include "Player.h"
#include "CustomData.h"
#include <GameEngineBase/GameEngineSound.h>

CustomBoard::CustomBoard() 
	:
	HairIndex_(0),
	ShirtIndex_(0),
	PantsIndex_(0),
	DirIndex_(0),

	isCustomUpdate_(false),
	ClickBackButton_(false),

	CustomUpdate_(CUSTOM_STATE::WAIT),

	CustomBoardRenderer_(nullptr),

	OKButton_(nullptr),
	BackButton_(nullptr),

	HairFont_(nullptr),
	ShirtFont_(nullptr),
	PantsFont_(nullptr),

	DirChangeRightArrow_(nullptr),
	DirChangeLeftArrow_(nullptr)

{
	HairString[0] = "Hair1";
	HairString[1] = "Hair2";
	HairString[2] = "Hair3";

	ShirtsString[0] = "Shirt1";
	ShirtsString[1] = "Shirt2";
	ShirtsString[2] = "Shirt3";
	ShirtsString[3] = "Shirt4";
	ShirtsString[4] = "Shirt5";

	PantsString[0] = "Pants1";
	PantsString[1] = "Pants2";

}

CustomBoard::~CustomBoard() 
{
}

void CustomBoard::Start()
{
	CustomBoardRenderer_ = CreateRenderer("Customboard.bmp");

	CustomBody_ = CreateRenderer("BodySheet.bmp");
	CustomBody_->SetIndex(0);
	CustomBody_->SetPivot({0, -80.f});

	CustomHand_ = CreateRenderer("HandSheet.bmp");
	CustomHand_->SetIndex(0);
	CustomHand_->SetPivot({ 0, -80.f });

	CustomPants_ = CreateRenderer("PantsSheet.bmp");
	CustomPants_->SetIndex(0);
	CustomPants_->SetPivot({ 0, -80.f });

	CustomShirts_ = CreateRenderer("ShirtsSheet.bmp");
	CustomShirts_->SetIndex(0);
	CustomShirts_->SetPivot({ 0, -80.f });

	CustomHair_ = CreateRenderer("hairSheet.bmp");
	CustomHair_->SetIndex(0);
	CustomHair_->SetPivot({ 0, -80.f });

	HairSubButton_ = GetLevel()->CreateActor<ArrowButton>(static_cast<int>(TITLELEVEL::CUSTROM_ARROW));
	HairSubButton_->CreateLeftArrow();
	HairSubButton_->CreateArrowCollision("HairSubButton");
	HairSubButton_->SetPosition({ GameEngineWindow::GetInst().GetScale().Half().x - 100.f, 410.f});
	HairSubButton_->GetRenderer()->CameraEffectOff();

	HairAddButton_ = GetLevel()->CreateActor<ArrowButton>(static_cast<int>(TITLELEVEL::CUSTROM_ARROW));
	HairAddButton_->CreateRightArrow();
	HairAddButton_->CreateArrowCollision("HairAddButton");
	HairAddButton_->SetPosition({ GameEngineWindow::GetInst().GetScale().Half().x + 100.f, 410.f });
	HairAddButton_->GetRenderer()->CameraEffectOff();

	ShirtSubButton_ = GetLevel()->CreateActor<ArrowButton>(static_cast<int>(TITLELEVEL::CUSTROM_ARROW));
	ShirtSubButton_->CreateLeftArrow();
	ShirtSubButton_->CreateArrowCollision("ShirtSubButton");
	ShirtSubButton_->SetPosition({ GameEngineWindow::GetInst().GetScale().Half().x - 100.f, 480.f });
	ShirtSubButton_->GetRenderer()->CameraEffectOff();

	ShirtAddButton_ = GetLevel()->CreateActor<ArrowButton>(static_cast<int>(TITLELEVEL::CUSTROM_ARROW));
	ShirtAddButton_->CreateRightArrow();
	ShirtAddButton_->CreateArrowCollision("ShirtAddButton");
	ShirtAddButton_->SetPosition({ GameEngineWindow::GetInst().GetScale().Half().x + 100.f, 480.f });
	ShirtAddButton_->GetRenderer()->CameraEffectOff();

	PantsSubButton_ = GetLevel()->CreateActor<ArrowButton>(static_cast<int>(TITLELEVEL::CUSTROM_ARROW));
	PantsSubButton_->CreateLeftArrow();
	PantsSubButton_->CreateArrowCollision("PantsSubButton");
	PantsSubButton_->SetPosition({ GameEngineWindow::GetInst().GetScale().Half().x - 100.f, 550.f });
	PantsSubButton_->GetRenderer()->CameraEffectOff();

	PantsAddButton_ = GetLevel()->CreateActor<ArrowButton>(static_cast<int>(TITLELEVEL::CUSTROM_ARROW));
	PantsAddButton_->CreateRightArrow();
	PantsAddButton_->CreateArrowCollision("PantsAddButton");
	PantsAddButton_->SetPosition({ GameEngineWindow::GetInst().GetScale().Half().x + 100.f, 550.f });
	PantsAddButton_->GetRenderer()->CameraEffectOff();

	DirChangeRightArrow_ = GetLevel()->CreateActor<ArrowButton>(static_cast<int>(TITLELEVEL::CUSTROM_ARROW));
	DirChangeRightArrow_->CreateRightArrow();
	DirChangeRightArrow_->CreateArrowCollision("DirChangeRightArrow");
	DirChangeRightArrow_->SetPosition({ GameEngineWindow::GetInst().GetScale().Half().x + 70.f, 300.f });
	DirChangeRightArrow_->GetRenderer()->CameraEffectOff();

	DirChangeLeftArrow_ = GetLevel()->CreateActor<ArrowButton>(static_cast<int>(TITLELEVEL::CUSTROM_ARROW));
	DirChangeLeftArrow_->CreateLeftArrow();
	DirChangeLeftArrow_->CreateArrowCollision("DirChangeLeftArrow");
	DirChangeLeftArrow_->SetPosition({ GameEngineWindow::GetInst().GetScale().Half().x - 70.f, 300.f });
	DirChangeLeftArrow_->GetRenderer()->CameraEffectOff();

	OKButton_ = GetLevel()->CreateActor<MenuButton>(static_cast<int>(TITLELEVEL::CUSTROM_BUTTON));
	OKButton_->CreateButtonRenderer("OkButton.bmp");
	OKButton_->CreateButtonCollision("OkButton", {50,47});
	OKButton_->SetPosition({810.f, 560.f });
	OKButton_->GetRenderer()->CameraEffectOff();

	BackButton_ = GetLevel()->CreateActor<MenuButton>(static_cast<int>(TITLELEVEL::CUSTROM_BUTTON));
	BackButton_->CreateButtonRenderer("Back.bmp");
	BackButton_->GetRenderer()->SetIndex(0);
	BackButton_->CreateButtonCollision("Back", { 132, 54 });
	BackButton_->SetPosition({ 980.f, 580.f });
	BackButton_->GetRenderer()->CameraEffectOff();

	HairFont_ = GetLevel()->CreateActor<Font>(static_cast<int>(PLAYLEVEL::DIALOGUEFONT));
	HairFont_->ChangeFont(HairString[HairIndex_], { GameEngineWindow::GetInst().GetScale().Half().x - 40.f, 410.f });

	ShirtFont_ = GetLevel()->CreateActor<Font>(static_cast<int>(PLAYLEVEL::DIALOGUEFONT));
	ShirtFont_->ChangeFont(ShirtsString[ShirtIndex_], { GameEngineWindow::GetInst().GetScale().Half().x - 40.f, 480.f });

	PantsFont_ = GetLevel()->CreateActor<Font>(static_cast<int>(PLAYLEVEL::DIALOGUEFONT));
	PantsFont_->ChangeFont(PantsString[PantsIndex_], { GameEngineWindow::GetInst().GetScale().Half().x - 40.f, 550.f });

}

void CustomBoard::Update()
{

	if (isCustomUpdate_ == true)
	{
		switch (CustomUpdate_)
		{
		case CUSTOM_STATE::WAIT:

			//------< 뒤로가기 버튼 마우스 오버 >---------------------------------------------------------------------------

			if (BackButton_->ButtomMouseOver())
			{
				BackButton_->GetRenderer()->SetIndex(1);
			}
			else
			{
				BackButton_->GetRenderer()->SetIndex(0);
			}

			//------< 뒤로가기 버튼 마우스 오버 >---------------------------------------------------------------------------

			if (BackButton_->ButtonMouseOverAndLeftClick())
			{

				ClickBackButton_ = true;
			}


			//------< 결정 버튼 >---------------------------------------------------------------------------

			if (OKButton_->ButtonMouseOverAndLeftClick())
			{
				GameEngineSound::SoundPlayOneShot("select.wav");
				CustomUpdate_ = CUSTOM_STATE::NEXT;
			}

			//------< 커스텀 버튼 >---------------------------------------------------------------------------

			if (HairAddButton_->ButtonMouseOverAndLeftClick())
			{
				CustomUpdate_ = CUSTOM_STATE::HAIR_ADD;
			}

			if (HairSubButton_->ButtonMouseOverAndLeftClick())
			{
				CustomUpdate_ = CUSTOM_STATE::HAIR_SUB;
			}

			if (ShirtAddButton_->ButtonMouseOverAndLeftClick())
			{
				CustomUpdate_ = CUSTOM_STATE::SHIRTS_ADD;
			}

			if (ShirtSubButton_->ButtonMouseOverAndLeftClick())
			{
				CustomUpdate_ = CUSTOM_STATE::SHIRTS_SUB;
			}

			if (PantsAddButton_->ButtonMouseOverAndLeftClick())
			{
				CustomUpdate_ = CUSTOM_STATE::PANTS_ADD;
			}

			if (PantsSubButton_->ButtonMouseOverAndLeftClick())
			{
				CustomUpdate_ = CUSTOM_STATE::PANTS_SUB;
			}

			if (DirChangeRightArrow_->ButtonMouseOverAndLeftClick())
			{
				CustomUpdate_ = CUSTOM_STATE::CHANGE_RIGHT;
			}

			if (DirChangeLeftArrow_->ButtonMouseOverAndLeftClick())
			{
				CustomUpdate_ = CUSTOM_STATE::CHANGE_LEFT;
			}

			break;
		case CUSTOM_STATE::HAIR_ADD:

			//------< 헤어 커스텀 >---------------------------------------------------------------------------

			if (HairIndex_ < 8)
			{
				HairIndex_ += 4;
				CustomHair_->SetIndex(DirIndex_ + HairIndex_);//0 4 8 / 0 1 2
				HairFont_->ChangeFont(HairString[HairIndex_/4], { GameEngineWindow::GetInst().GetScale().Half().x - 40.f, 410.f });
			}
			else
			{
				HairIndex_ = 0;
				CustomHair_->SetIndex(DirIndex_ + HairIndex_);
				HairFont_->ChangeFont(HairString[HairIndex_ / 4], { GameEngineWindow::GetInst().GetScale().Half().x - 40.f, 410.f });
			}

			CustomUpdate_ = CUSTOM_STATE::WAIT;

			break;
		case CUSTOM_STATE::HAIR_SUB:

			//------< 헤어 커스텀 >---------------------------------------------------------------------------

			if (HairIndex_ > 0)
			{
				HairIndex_ -= 4;
				CustomHair_->SetIndex(DirIndex_ + HairIndex_);
				HairFont_->ChangeFont(HairString[HairIndex_/4], { GameEngineWindow::GetInst().GetScale().Half().x - 40.f , 410.f });
			}
			else
			{
				HairIndex_ = 0;
				CustomHair_->SetIndex(DirIndex_ + HairIndex_);
				HairFont_->ChangeFont(HairString[HairIndex_ / 4], { GameEngineWindow::GetInst().GetScale().Half().x - 40.f , 410.f });
			}

			CustomUpdate_ = CUSTOM_STATE::WAIT;

			break;
		case CUSTOM_STATE::SHIRTS_ADD:

			//------< 셔츠 커스텀 >---------------------------------------------------------------------------

			if (ShirtIndex_ < 16)
			{
				ShirtIndex_ += 4;
				CustomShirts_->SetIndex(DirIndex_ + ShirtIndex_);
				CustomHand_->SetIndex(DirIndex_ + ShirtIndex_);

				ShirtFont_->ChangeFont(ShirtsString[ShirtIndex_/4], { GameEngineWindow::GetInst().GetScale().Half().x - 40.f,  480.f });
			}
			else
			{
				ShirtIndex_ = 0;
				CustomShirts_->SetIndex(DirIndex_ + ShirtIndex_);
				CustomHand_->SetIndex(DirIndex_ + ShirtIndex_);

				ShirtFont_->ChangeFont(ShirtsString[ShirtIndex_ / 4], { GameEngineWindow::GetInst().GetScale().Half().x - 40.f,  480.f });
			}

			CustomUpdate_ = CUSTOM_STATE::WAIT;

			break;
		case CUSTOM_STATE::SHIRTS_SUB:

			//------< 셔츠 커스텀 >---------------------------------------------------------------------------

			if (ShirtIndex_ > 0)
			{
				ShirtIndex_ -= 4;
				CustomShirts_->SetIndex(DirIndex_ + ShirtIndex_);
				CustomHand_->SetIndex(DirIndex_ + ShirtIndex_);

				ShirtFont_->ChangeFont(ShirtsString[ShirtIndex_/4], { GameEngineWindow::GetInst().GetScale().Half().x - 40.f,  480.f });
			}
			else
			{
				ShirtIndex_ = 0;
				CustomShirts_->SetIndex(DirIndex_ + ShirtIndex_);
				CustomHand_->SetIndex(DirIndex_ + ShirtIndex_);

				ShirtFont_->ChangeFont(ShirtsString[ShirtIndex_ / 4], { GameEngineWindow::GetInst().GetScale().Half().x - 40.f,  480.f });
			}

			CustomUpdate_ = CUSTOM_STATE::WAIT;

			break;
		case CUSTOM_STATE::PANTS_ADD:

			//------< 바지 커스텀 >---------------------------------------------------------------------------

			if (PantsIndex_ < 4)
			{
				PantsIndex_ += 4;
				CustomPants_->SetIndex(DirIndex_ + PantsIndex_);

				PantsFont_->ChangeFont(PantsString[PantsIndex_/4], { GameEngineWindow::GetInst().GetScale().Half().x - 40.f,  550.f });
			}
			else
			{
				PantsIndex_ = 0;
				CustomPants_->SetIndex(DirIndex_ + PantsIndex_);

				PantsFont_->ChangeFont(PantsString[PantsIndex_ / 4], { GameEngineWindow::GetInst().GetScale().Half().x - 40.f,  550.f });
			}

			CustomUpdate_ = CUSTOM_STATE::WAIT;

			break;
		case CUSTOM_STATE::PANTS_SUB:

			//------< 바지 커스텀 >---------------------------------------------------------------------------

			if (PantsIndex_ > 0)
			{
				PantsIndex_ -= 4;
				CustomPants_->SetIndex(DirIndex_ + PantsIndex_);

				PantsFont_->ChangeFont(PantsString[PantsIndex_/4], { GameEngineWindow::GetInst().GetScale().Half().x - 40.f,  550.f });
			}
			else
			{
				PantsIndex_ = 0;
				CustomPants_->SetIndex(DirIndex_ + PantsIndex_);

				PantsFont_->ChangeFont(PantsString[PantsIndex_ / 4], { GameEngineWindow::GetInst().GetScale().Half().x - 40.f,  550.f });
			}

			CustomUpdate_ = CUSTOM_STATE::WAIT;

			break;
		case CUSTOM_STATE::CHANGE_RIGHT:

			//------< 방향 변경 >---------------------------------------------------------------------------

			if (DirIndex_ < 3)
			{
				++DirIndex_;

				CustomPants_->SetIndex(DirIndex_ + PantsIndex_);
				CustomShirts_->SetIndex(DirIndex_ + ShirtIndex_);
				CustomHand_->SetIndex(DirIndex_ + ShirtIndex_);
				CustomHair_->SetIndex(DirIndex_ + HairIndex_);
				CustomBody_->SetIndex(DirIndex_ + 0);
				CustomUpdate_ = CUSTOM_STATE::WAIT;
			}

			else
			{
				DirIndex_ = 0;

				CustomPants_->SetIndex(DirIndex_ + PantsIndex_);
				CustomShirts_->SetIndex(DirIndex_ + ShirtIndex_);
				CustomHand_->SetIndex(DirIndex_ + ShirtIndex_);
				CustomHair_->SetIndex(DirIndex_ + HairIndex_);
				CustomBody_->SetIndex(DirIndex_ + 0);

				CustomUpdate_ = CUSTOM_STATE::WAIT;

			}

			break;
		case CUSTOM_STATE::CHANGE_LEFT:

			//------< 방향 변경 >---------------------------------------------------------------------------

			if (DirIndex_ > 0)
			{
				--DirIndex_;

				CustomPants_->SetIndex(DirIndex_ + PantsIndex_);
				CustomShirts_->SetIndex(DirIndex_ + ShirtIndex_);
				CustomHand_->SetIndex(DirIndex_ + ShirtIndex_);
				CustomHair_->SetIndex(DirIndex_ + HairIndex_);
				CustomBody_->SetIndex(DirIndex_ + 0);

				CustomUpdate_ = CUSTOM_STATE::WAIT;
			}

			else
			{
				DirIndex_ = 3;

				CustomPants_->SetIndex(DirIndex_ + PantsIndex_);
				CustomShirts_->SetIndex(DirIndex_ + ShirtIndex_);
				CustomHand_->SetIndex(DirIndex_ + ShirtIndex_);
				CustomHair_->SetIndex(DirIndex_ + HairIndex_);
				CustomBody_->SetIndex(DirIndex_ + 0);

				CustomUpdate_ = CUSTOM_STATE::WAIT;
			}

			break;
		case CUSTOM_STATE::NEXT:
			//------< 다음방향 변경 >---------------------------------------------------------------------------

			GameEngine::GetInst().ChangeLevel("MyHouseLevel");
			CustomUpdate_ = CUSTOM_STATE::WAIT;

			break;
		default:
			break;
		}
	}


}

void CustomBoard::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	switch (HairIndex_)
	{
	case 0 :
		CustomData::GetInst()->SetHairFileName("PlayerHair0.bmp");

		break;
	case 4:
		CustomData::GetInst()->SetHairFileName("PlayerHair1.bmp");

		break;
	case 8:
		CustomData::GetInst()->SetHairFileName("PlayerHair2.bmp");

		break;
	default:
		break;
	}

	switch (ShirtIndex_)
	{
	case 0:
		CustomData::GetInst()->SetShirtsFileName("PlayerShirt0.bmp");
		CustomData::GetInst()->SetHandFileName("PlayerHand0.bmp");

		break;
	case 4:
		CustomData::GetInst()->SetShirtsFileName("PlayerShirt1.bmp");
		CustomData::GetInst()->SetHandFileName("PlayerHand1.bmp");

		break;
	case 8:
		CustomData::GetInst()->SetShirtsFileName("PlayerShirt2.bmp");
		CustomData::GetInst()->SetHandFileName("PlayerHand2.bmp");

		break;
	case 12:
		CustomData::GetInst()->SetShirtsFileName("PlayerShirt3.bmp");
		CustomData::GetInst()->SetHandFileName("PlayerHand4.bmp");

		break;
	case 16:

		CustomData::GetInst()->SetShirtsFileName("PlayerShirt4.bmp");
		CustomData::GetInst()->SetHandFileName("PlayerHand4.bmp");

		break;
	default:
		break;
	}

	switch (PantsIndex_)
	{
	case 0:
		CustomData::GetInst()->SetPantsFileName("PlayerPants0.bmp");
		break;
	case 4:
		CustomData::GetInst()->SetPantsFileName("PlayerPants1.bmp");
		break;
	default:
		break;
	}


}


void CustomBoard::CustomBoardOff()
{
	CustomBoardRenderer_->Off();
	OKButton_->Off();

	HairAddButton_->Off();
	HairSubButton_->Off();

	ShirtAddButton_->Off();
	ShirtSubButton_->Off();

	PantsAddButton_->Off();
	PantsSubButton_->Off();

	CustomBody_->Off();
	CustomHand_->Off();
	CustomShirts_->Off();
	CustomPants_->Off();
	CustomHair_->Off();

	HairFont_->Off();
	ShirtFont_->Off();
	PantsFont_->Off();

	DirChangeLeftArrow_->Off();
	DirChangeRightArrow_->Off();
	BackButton_->Off();

	isCustomUpdate_ = false;
}

void CustomBoard::CustomBoardOn()
{
	CustomBoardRenderer_->On();
	OKButton_->On();

	HairAddButton_->On();
	HairSubButton_->On();

	ShirtAddButton_->On();
	ShirtSubButton_->On();

	PantsAddButton_->On();
	PantsSubButton_->On();

	CustomBody_->On();
	CustomHand_->On();
	CustomShirts_->On();
	CustomPants_->On();
	CustomHair_->On();

	HairFont_->On();
	ShirtFont_->On();
	PantsFont_->On();
	BackButton_->On();

	DirChangeLeftArrow_->On();
	DirChangeRightArrow_->On();

	isCustomUpdate_ = true;
}

