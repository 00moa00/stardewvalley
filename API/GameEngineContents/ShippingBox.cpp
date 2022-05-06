#include "ShippingBox.h"

ShippingBox* ShippingBox::MainShippingBox;

ShippingBox::ShippingBox() 
	:
	isOpenAnimation(false),
	ShippingBoxTop_(nullptr),
	ShippingUpdateState_(SHIPPINGBOX_UPDATE::INIT)
{
}

ShippingBox::~ShippingBox() 
{
}

void ShippingBox::Start()
{
	ItemRenderer_ = CreateRenderer("ShippingBin.bmp");
	ItemCollider_ = CreateCollision("MapObject", { 90, 90 });

	SetScale({ 120, 140 });

	ItemName_ = "ShippingBox";
	ObjectType_ = OBJECTTYPE::SHIPPINGBOX;

	ShippingBoxTop_ = GetLevel()->CreateActor<ShippingBoxTop>(static_cast<int>(PLAYLEVEL::OBJECT));
}

void ShippingBox::Update()
{
	switch (ShippingUpdateState_)
	{
	case SHIPPINGBOX_UPDATE::INIT:

		ShippingBoxTop_->SetPosition({ this->GetPosition().x, this->GetPosition().y - 75.f/2});
		ShippingUpdateState_ = SHIPPINGBOX_UPDATE::UPDATE;

		break;
	case SHIPPINGBOX_UPDATE::UPDATE:

		break;
	default:
		break;
	}
}

void ShippingBox::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainShippingBox = this;
}

void ShippingBox::ItemCollPlayer()
{
	ShippingBoxTop_->SetShippingBoxTopAnimationOpen();
	isOpenAnimation = true;
}

void ShippingBox::ItemCollFalsePlayer()
{
	if (isOpenAnimation == true)
	{
		ShippingBoxTop_->SetShippingBoxTopAnimationClose();
		isOpenAnimation = false;
	}

}
