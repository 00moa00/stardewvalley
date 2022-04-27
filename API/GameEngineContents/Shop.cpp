#include "Shop.h"
#include "Player.h"

Shop* Shop::MainShop = nullptr;
ExitBotton* Shop::ExitBotton_ = nullptr;
Font* Shop::Font_ = nullptr;

Shop::Shop() 
	:
	ShopRenderer_(nullptr),
	//ExitBotton_(nullptr),
	Mouse_(nullptr),

	ShopUpdateState_(SHOP_UPDATE::SET_POS_INDEX)
{
}

Shop::~Shop() 
{
}

void Shop::Start()
{
	ShopRenderer_ = CreateRenderer("Shop.bmp");
	ShopRenderer_->CameraEffectOff();
	ShopRenderer_->SetOrder(static_cast<int>(PLAYLEVEL::SHOP));

	ExitBotton_ = GetLevel()->CreateActor<ExitBotton>(static_cast<int>(PLAYLEVEL::ITEM));
	ExitBotton_->SetPosition({1125.f, 620.f});

	Mouse_ = GetLevel()->CreateActor<Mouse>(static_cast<int>(PLAYLEVEL::MOUSE));

	SetPosition( GameEngineWindow::GetInst().GetScale().Half());

	NewShopItem<TulipBulb_Shop>();
	NewShopItem<PatatoSeeds_Shop>();
	NewShopItem<Parsnip_Shop>();
	NewShopItem<ParsnipSeeds_Shop>();

	NewShopItem<KaleSeeds_Shop>();
	NewShopItem<JazzSeeds_Shop>();
	NewShopItem<Dandelion_Shop>();
	NewShopItem<Daffodil_Shop>();
	NewShopItem<CauliflowerSeeds_Shop>();
	NewShopItem<BeanStarter_Shop>();

	Font_ = GetLevel()->CreateActor<Font>((int)PLAYLEVEL::FONT);
	Font_->ChangeNumRightSort(1000);
	Font_->SetPositionRightSort({ 136.f, 475.f });


	std::map<int, ShopItem*>::iterator StartIter = ShopItemList_.begin();
	std::map<int, ShopItem*>::iterator EndtIter = ShopItemList_.end();

	for (int i = 0; StartIter != EndtIter; ++StartIter)
	{
		StartIter->second->SetPosition({715.f, 123.5f + (i * 76.f)});
		++i;
	}

	//고정 인덱스
	for (int i = 0; i < 4; ++i)
	{
		ConstItmePos_.insert(std::make_pair(i, float4({ 715.f, 123.5f + (i * 76.f)})));
	}

	//LevelRegist("Shop");
}

void Shop::Update()
{

	std::map<int, ShopItem*>::iterator ItemStartIter = ShopItemList_.begin();
	std::map<int, ShopItem*>::iterator ItemEndtIter = ShopItemList_.end();

	std::map<int, ShopItem*>::iterator ItemfirstFindtIter = ShopItemList_.begin();

	std::map<int, float4>::iterator ConstStartIter = ConstItmePos_.begin();
	std::map<int, float4>::iterator ConstEndtIter = ConstItmePos_.end();


	switch (ShopUpdateState_)
	{
	case SHOP_UPDATE::SET_POS_INDEX:

		ItemStartIter = ShopItemList_.begin();
		ItemEndtIter = ShopItemList_.end();

		ItemfirstFindtIter = ShopItemList_.begin();

		ConstStartIter = ConstItmePos_.begin();
		ConstEndtIter = ConstItmePos_.end();


		// 고정 인덱스에 위치를 맞춘다
		for (; ConstStartIter != ConstEndtIter; ++ConstStartIter)
		{
			for (; ItemStartIter != ItemEndtIter; )
			{
				if (ItemStartIter->second->GetIndex() == ConstStartIter->first)
				{
					ItemStartIter->second->SetPosition(ConstStartIter->second);

					//변경하면 for문 종료
					++ItemStartIter;
					break;
				}

				else
				{
					++ItemStartIter;
				}
			}
		}

		ShopUpdateState_ = SHOP_UPDATE::HIDE_ITME;
		break;

	case SHOP_UPDATE::HIDE_ITME:

		// 4개 이상은 숨김
		ItemStartIter = ShopItemList_.begin();
		ItemEndtIter = ShopItemList_.end();

		for (; ItemStartIter != ItemEndtIter; ++ItemStartIter)
		{
			if (ItemStartIter->second->GetIndex() > 3 || ItemStartIter->second->GetIndex() < 0)
			{
				ItemStartIter->second->Off();
				ItemStartIter->second->SetisHide(true);
			}

			else
			{
				ItemStartIter->second->On();
				ItemStartIter->second->SetisHide(false);

			}
		}

		ShopUpdateState_ = SHOP_UPDATE::INIT;
		break;

	case SHOP_UPDATE::INIT:

		ItemStartIter = ShopItemList_.begin();

		for (; ItemStartIter != ItemEndtIter; ++ItemStartIter)
		{
			if (ItemStartIter->second->MouseInItem() 
				&& Mouse_->MouseClickShopIn() 
				&& ItemStartIter->second->GetisHide() == false)
			{
				if (Player::MainPlayer->SubMoney(ItemStartIter->second->GetBuyPrice()) == true)
				{
					ItemStartIter->second->InventoryNewItem();
				}

				else
				{
					ShopUpdateState_ = SHOP_UPDATE::INIT;
					break;
				}
			}
		}

		if (ExitBotton_->MouseClick() == true)
		{
			Player::MainPlayer->SetisShopping(false);
		}


		if ( GameEngineInput::GetInst()->GetMouseWheel() == 120 )
		{

			if (ItemfirstFindtIter->second->GetIndex() == 0)
			{
				ShopUpdateState_ = SHOP_UPDATE::INIT;
			}

			else
			{
				ShopUpdateState_ = SHOP_UPDATE::SCROLL_UP;
			}
		}

		if (GameEngineInput::GetInst()->GetMouseWheel() == -120)
		{

			if (ItemfirstFindtIter->second->GetIndex() == -6)
			{
				ShopUpdateState_ = SHOP_UPDATE::INIT;
			}

			else
			{
				ShopUpdateState_ = SHOP_UPDATE::SCROLL_DOWN;
			}
		}

		break;

	case SHOP_UPDATE::SCROLL_UP:

		ItemStartIter = ShopItemList_.begin();
		ItemEndtIter = ShopItemList_.end();

		for (; ItemStartIter != ItemEndtIter; ++ItemStartIter)
		{
			ItemStartIter->second->AddIndex();
		}

		ShopUpdateState_ = SHOP_UPDATE::SET_POS_INDEX;
		break;

	case SHOP_UPDATE::SCROLL_DOWN:

		ItemStartIter = ShopItemList_.begin();
		ItemEndtIter = ShopItemList_.end();

		for (; ItemStartIter != ItemEndtIter; ++ItemStartIter)
		{
			ItemStartIter->second->SubIndex();
		}

		ShopUpdateState_ = SHOP_UPDATE::SET_POS_INDEX;
		break;

	default:
		break;
	}

}

void Shop::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainShop = this;
	Font_ = Font_;
	ExitBotton_ = ExitBotton_;
}

void Shop::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	std::map<int, ShopItem*>::iterator StartIter = ShopItemList_.begin();
	std::map<int, ShopItem*>::iterator EndtIter = ShopItemList_.end();

	for (; StartIter != EndtIter; ++StartIter)
	{
		StartIter->second->NextLevelOn();
	}
	Font_->NextLevelOn();
	ExitBotton_->NextLevelOn();
	NextLevelOn();
}

void Shop::ShopOff()
{
	this->Off();
	ExitBotton_->Off();
	Font_->Off();

	std::map<int, ShopItem*>::iterator StartIter = ShopItemList_.begin();
	std::map<int, ShopItem*>::iterator EndtIter = ShopItemList_.end();

	for (; StartIter != EndtIter; ++StartIter)
	{
		StartIter->second->Off();
	}

}

void Shop::ShopOn()
{
	this->On();
	ExitBotton_->On();
	Font_->On();

	std::map<int, ShopItem*>::iterator StartIter = ShopItemList_.begin();
	std::map<int, ShopItem*>::iterator EndtIter = ShopItemList_.end();

	for (; StartIter != EndtIter; ++StartIter)
	{
		StartIter->second->On();
	}

	ShopUpdateState_ = SHOP_UPDATE::HIDE_ITME;

}

void Shop::SetShopMoney(int _Money)
{
	Font_->ChangeNumRightSort(_Money);
}

