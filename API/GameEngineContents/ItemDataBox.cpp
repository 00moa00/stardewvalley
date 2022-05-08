#include "ItemDataBox.h"
#include "RendererData.h"
#include "Inventory.h"

ItemDataBox::ItemDataBox()
	:
	ItemDataBoxRenderer_(nullptr),
	NameFont_(nullptr),
	DataFont_(nullptr)
{
}

ItemDataBox::~ItemDataBox()
{
}

void ItemDataBox::Start()
{
	ItemDataBoxRenderer_ = CreateRenderer("DataBox.bmp");
	ItemDataBoxRenderer_->CameraEffectOff();

	NameFont_ = GetLevel()->CreateActor<Font>(static_cast<int>(PLAYLEVEL::DIALOGUEFONT));
	NameFont_->ChangeFont(" ", { 0,0 });

	DataFont_ = GetLevel()->CreateActor<Font>(static_cast<int>(PLAYLEVEL::DIALOGUEFONT));
	DataFont_->ChangeFont(" ", { 0,0 });

}

void ItemDataBox::Update()
{
}

void ItemDataBox::Render()
{
}

void ItemDataBox::SetData(std::string _Name, std::string _Data , float4 _Pos)
{
	if (Inventory::MainInventory->GetPopUpStateShop())
	{
		ItemDataBoxOff();
	}
	else
	{
		ItemDataBoxOn();
	}


	if (Inventory::MainInventory->GetPopUpStateMini())
	{
		NameFont_->ChangeFont(_Name, { 0, 0 });
		DataFont_->ChangeFont(_Data, { 0 , 0 });
		this->SetPosition({ Inventory::MainInventory->GetMouse()->GetPosition().x + 150.f,  _Pos.y - 100.f });
		NameFont_->SetPosition({ Inventory::MainInventory->GetMouse()->GetPosition().x + 40.f , _Pos.y - 210.f });
		DataFont_->SetPosition({ Inventory::MainInventory->GetMouse()->GetPosition().x + 40.f , _Pos.y - 85.f });
	}

	if(Inventory::MainInventory->GetPopUpStateMain())
	{
		NameFont_->ChangeFont(_Name, { 0, 0 });
		DataFont_->ChangeFont(_Data, { 0 , 0 });
		this->SetPosition({ Inventory::MainInventory->GetMouse()->GetPosition().x + 130.f, _Pos.y + 180.f });
		NameFont_->SetPosition({ Inventory::MainInventory->GetMouse()->GetPosition().x + 20.f , _Pos.y + 60.f });
		DataFont_->SetPosition({ Inventory::MainInventory->GetMouse()->GetPosition().x + 20.f , _Pos.y + 175.f });
	}

}

void ItemDataBox::ItemDataBoxOn()
{
	ItemDataBoxRenderer_->On();
	NameFont_->On();
	DataFont_->On();

}

void ItemDataBox::ItemDataBoxOff()
{
	ItemDataBoxRenderer_->Off();
	NameFont_->Off();
	DataFont_->Off();

}

void ItemDataBox::FontNextLevelOn()
{
	NameFont_->NextLevelOn();
	DataFont_->NextLevelOn();
}
