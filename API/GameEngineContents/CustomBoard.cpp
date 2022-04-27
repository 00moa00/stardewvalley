#include "CustomBoard.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngine.h>
#include "RendererData.h"
#include "Player.h"
#include "CustomData.h"

CustomBoard::CustomBoard() 
	:
	HairIndex_(0),
	ShirtIndex_(0),
	PantsIndex_(0),


	isCustomUpdate_(false),

	CustomUpdate_(CUSTOM_STATE::WAIT),

	CustomBoardRenderer_(nullptr),
	OKButton_(nullptr),
	HairFont_(nullptr),
	ShirtFont_(nullptr),
	PantsFont_(nullptr)
{
	HairString[0] = "Hair0";
	HairString[1] = "Hair1";
	HairString[2] = "Hair2";

	ShirtsString[0] = "Shirt0";
	ShirtsString[1] = "Shirt1";
	ShirtsString[2] = "Shirt3";
	ShirtsString[3] = "Shirt4";
	ShirtsString[4] = "Shirt5";

	PantsString[0] = "Pants0";
	PantsString[1] = "Pants1";

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

	CustomShirts_ = CreateRenderer("ShirtsSheet.bmp");
	CustomShirts_->SetIndex(0);
	CustomShirts_->SetPivot({ 0, -80.f });

	CustomPants_ = CreateRenderer("PantsSheet.bmp");
	CustomPants_->SetIndex(0);
	CustomPants_->SetPivot({ 0, -80.f });

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


	OKButton_ = GetLevel()->CreateActor<MenuButton>(static_cast<int>(TITLELEVEL::CUSTROM_BUTTON));
	OKButton_->CreateButtonRenderer("OkButton.bmp");
	OKButton_->CreateButtonCollision("OkButton", {50,47});
	OKButton_->SetPosition({810.f, 560.f });
	OKButton_->GetRenderer()->CameraEffectOff();

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

			if (OKButton_->ButtonMouseOverAndLeftClick())
			{
				CustomUpdate_ = CUSTOM_STATE::NEXT;
			}

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


			break;

		case CUSTOM_STATE::HAIR_ADD:

			if (HairIndex_ < 2)
			{
				++HairIndex_;
				CustomHair_->SetIndex(4 * HairIndex_);
				HairFont_->ChangeFont(HairString[HairIndex_], { GameEngineWindow::GetInst().GetScale().Half().x - 40.f, 410.f });
			}

			CustomUpdate_ = CUSTOM_STATE::WAIT;


			break;
		case CUSTOM_STATE::HAIR_SUB:

			if (HairIndex_ > 0)
			{
				--HairIndex_;
				CustomHair_->SetIndex(4 * HairIndex_);
				HairFont_->ChangeFont(HairString[HairIndex_], { GameEngineWindow::GetInst().GetScale().Half().x - 40.f , 410.f });

			}

			CustomUpdate_ = CUSTOM_STATE::WAIT;

			break;
		case CUSTOM_STATE::SHIRTS_ADD:

			if (ShirtIndex_ < 4)
			{
				++ShirtIndex_;
				CustomShirts_->SetIndex(4 * ShirtIndex_);
				CustomHand_->SetIndex(4 * ShirtIndex_);

				ShirtFont_->ChangeFont(ShirtsString[ShirtIndex_], { GameEngineWindow::GetInst().GetScale().Half().x - 40.f,  480.f });

			}

			CustomUpdate_ = CUSTOM_STATE::WAIT;

			break;
		case CUSTOM_STATE::SHIRTS_SUB:

			if (ShirtIndex_ > 0)
			{
				--ShirtIndex_;
				CustomShirts_->SetIndex(4 * ShirtIndex_);
				CustomHand_->SetIndex(4 * ShirtIndex_);

				ShirtFont_->ChangeFont(ShirtsString[ShirtIndex_], { GameEngineWindow::GetInst().GetScale().Half().x - 40.f,  480.f });

			}

			CustomUpdate_ = CUSTOM_STATE::WAIT;

			break;
		case CUSTOM_STATE::PANTS_ADD:

			if (PantsIndex_ < 1)
			{
				++PantsIndex_;
				CustomPants_->SetIndex(4 * PantsIndex_);

				PantsFont_->ChangeFont(PantsString[PantsIndex_], { GameEngineWindow::GetInst().GetScale().Half().x - 40.f,  550.f });

			}

			CustomUpdate_ = CUSTOM_STATE::WAIT;

			break;
		case CUSTOM_STATE::PANTS_SUB:

			if (PantsIndex_ > 0)
			{

				--PantsIndex_;
				CustomPants_->SetIndex(4 * PantsIndex_);

				PantsFont_->ChangeFont(PantsString[PantsIndex_], { GameEngineWindow::GetInst().GetScale().Half().x - 40.f,  550.f });
			}

			CustomUpdate_ = CUSTOM_STATE::WAIT;

			break;

		case CUSTOM_STATE::NEXT:

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
	case 1:
		CustomData::GetInst()->SetHairFileName("PlayerHair1.bmp");
		break;
	case 2:
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
	case 1:
		CustomData::GetInst()->SetShirtsFileName("PlayerShirt1.bmp");
		CustomData::GetInst()->SetHandFileName("PlayerHand1.bmp");
		break;
	case 2:
		CustomData::GetInst()->SetShirtsFileName("PlayerShirt2.bmp");
		CustomData::GetInst()->SetHandFileName("PlayerHand2.bmp");
		break;
	case 3:
		CustomData::GetInst()->SetShirtsFileName("PlayerShirt3.bmp");
		CustomData::GetInst()->SetHandFileName("PlayerHand4.bmp");
		break;
	case 4:
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
	case 1:
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

	isCustomUpdate_ = true;
}

