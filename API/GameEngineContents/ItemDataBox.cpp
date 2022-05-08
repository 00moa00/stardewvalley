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
	if (Inventory::MainInventory->GetPopUpStateMini())
	{
		NameFont_->ChangeFont(_Name, { 0, 0 });
		DataFont_->ChangeFont(_Data, { 0 , 0 });
		this->SetPosition({ _Pos.x, _Pos.y - 180.f });
		NameFont_->SetPosition({ _Pos.x - 110.f , _Pos.y - 280.f });
		DataFont_->SetPosition({ _Pos.x - 110.f , _Pos.y - 160.f });
	}

	if(Inventory::MainInventory->GetPopUpStateMain())
	{
		NameFont_->ChangeFont(_Name, { 0, 0 });
		DataFont_->ChangeFont(_Data, { 0 , 0 });
		this->SetPosition({ _Pos.x, _Pos.y + 180.f });
		NameFont_->SetPosition({ _Pos.x - 110.f , _Pos.y + 160.f });
		DataFont_->SetPosition({ _Pos.x - 110.f , _Pos.y + 280.f });
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
