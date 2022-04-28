#include "PlayerCustomClothes.h"
#include "CustomData.h"
#include "PlayerSpriteData.h"

PlayerCustomClothes* PlayerCustomClothes::MainPlayerCustomClothes = nullptr;

PlayerCustomClothes::PlayerCustomClothes()
	:
	ClothesShirts_(nullptr),
	ClothesPants_(nullptr)
{
}

PlayerCustomClothes::~PlayerCustomClothes()
{
}

void PlayerCustomClothes::Start()
{
}

void PlayerCustomClothes::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	if (ClothesShirts_ == nullptr)
	{
		ClothesShirts_ = CreateRenderer(CustomData::GetInst()->GetShirtsFileName());
		ClothesPants_ = CreateRenderer(CustomData::GetInst()->GetPantsFileName());

		ClothesShirts_->SetIndex(static_cast<int>(PLAYER::FRONT_INIT));
		ClothesPants_->SetIndex(static_cast<int>(PLAYER::FRONT_INIT));

		ClothesShirts_->CameraEffectOff();
		ClothesPants_->CameraEffectOff();

		ClothesShirts_->SetPivot({748.f, 475.f});
		ClothesPants_->SetPivot({ 748.f, 520.f });

	}

}

void PlayerCustomClothes::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	MainPlayerCustomClothes = this;
}

void PlayerCustomClothes::UpdateOn()
{
	ClothesShirts_->On();
	ClothesPants_->On();

}

void PlayerCustomClothes::UpdateOff()
{
	ClothesShirts_->Off();
	ClothesPants_->Off();
}
