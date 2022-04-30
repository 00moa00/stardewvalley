#include "Shop.h"
#include "Player.h"

#include "TulipBulb_Shop.h"
#include "PatatoSeeds_Shop.h"
#include "ParsnipSeeds_Shop.h"
#include "Parsnip_Shop.h"
#include "KaleSeeds_Shop.h"
#include "JazzSeeds_Shop.h"
#include "Dandelion_Shop.h"
#include "Daffodil_Shop.h"
#include "CauliflowerSeeds_Shop.h"
#include "BeanStarter_Shop.h"

#include "Beer_Shop.h"
#include "Bread_Shop.h"
#include "Coffe_Shop.h"
#include "Pizza_Shop.h"
#include "Salad_Shop.h"
#include "Spaghetti_Shop.h"

Shop* Shop::MainShop = nullptr;
ExitBotton* Shop::ExitBotton_ = nullptr;
Font* Shop::Font_ = nullptr;

Shop::Shop() 
	:
	ShopRenderer_(nullptr),
	Mouse_(nullptr),

	Shop_(SHOP::NONE),
	ShopUpdateState_(SHOP_UPDATE::SET_POS_INDEX)
{
}

Shop::~Shop() 
{
}

void Shop::Start()
{
	SetPosition( GameEngineWindow::GetInst().GetScale().Half());

	ShopRenderer_ = CreateRenderer("Shop.bmp");
	ShopRenderer_->CameraEffectOff();
	ShopRenderer_->SetOrder(static_cast<int>(PLAYLEVEL::SHOP));

	ExitBotton_ = GetLevel()->CreateActor<ExitBotton>(static_cast<int>(PLAYLEVEL::ITEM));
	ExitBotton_->SetPosition({1125.f, 620.f});

	Mouse_ = GetLevel()->CreateActor<Mouse>(static_cast<int>(PLAYLEVEL::MOUSE));

	Font_ = GetLevel()->CreateActor<Font>((int)PLAYLEVEL::FONT);
	Font_->ChangeNumMoneyLeftSort(1000, { 280.f, 475.f });


	NewSeedShopItem<TulipBulb_Shop>();
	NewSeedShopItem<PatatoSeeds_Shop>();
	NewSeedShopItem<Parsnip_Shop>();
	NewSeedShopItem<ParsnipSeeds_Shop>();
	NewSeedShopItem<KaleSeeds_Shop>();
	NewSeedShopItem<JazzSeeds_Shop>();
	NewSeedShopItem<Dandelion_Shop>();
	NewSeedShopItem<Daffodil_Shop>();
	NewSeedShopItem<CauliflowerSeeds_Shop>();
	NewSeedShopItem<BeanStarter_Shop>();

	NewSaloonItem<Beer_Shop>();
	NewSaloonItem<Bread_Shop>();
	NewSaloonItem<Coffe_Shop>();
	NewSaloonItem<Pizza_Shop>();
	NewSaloonItem<Salad_Shop>();
	NewSaloonItem<Spaghetti_Shop>();


	//std::map<int, ShopItem*>::iterator StartIter = CurrentShopItemList_.begin();
	//std::map<int, ShopItem*>::iterator EndtIter = CurrentShopItemList_.end();

	//for (int i = 0; StartIter != EndtIter; ++StartIter)
	//{
	//	StartIter->second->SetPosition({715.f, 123.5f + (i * 76.f)});
	//	++i;
	//}

	//고정 인덱스
	for (int i = 0; i < 4; ++i)
	{
		ConstItmePos_.insert(std::make_pair(i, float4({ 715.f, 123.5f + (i * 76.f)})));
	}

	//LevelRegist("Shop");
}

void Shop::Update()
{

	std::map<int, ShopItem*>::iterator ItemStartIter = CurrentShopItemList_.begin();
	std::map<int, ShopItem*>::iterator ItemEndtIter = CurrentShopItemList_.end();

	std::map<int, ShopItem*>::iterator ItemfirstFindtIter = CurrentShopItemList_.begin();

	std::map<int, float4>::iterator ConstStartIter = ConstItmePos_.begin();
	std::map<int, float4>::iterator ConstEndtIter = ConstItmePos_.end();


	switch (ShopUpdateState_)
	{
	case SHOP_UPDATE::SET_POS_INDEX:

		ItemStartIter = CurrentShopItemList_.begin();
		ItemEndtIter = CurrentShopItemList_.end();

		ItemfirstFindtIter = CurrentShopItemList_.begin();

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
		ItemStartIter = CurrentShopItemList_.begin();
		ItemEndtIter = CurrentShopItemList_.end();

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

		ItemStartIter = CurrentShopItemList_.begin();

		for (; ItemStartIter != ItemEndtIter; ++ItemStartIter)
		{
			if (ItemStartIter->second->MouseInItem() 
				&& Mouse_->MouseClickShopIn() 
				&& ItemStartIter->second->GetisHide() == false
				&& Player::MainPlayer->GetMoneySubMoneyCountWait())
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

		ItemStartIter = CurrentShopItemList_.begin();
		ItemEndtIter = CurrentShopItemList_.end();

		for (; ItemStartIter != ItemEndtIter; ++ItemStartIter)
		{
			ItemStartIter->second->AddIndex();
		}

		ShopUpdateState_ = SHOP_UPDATE::SET_POS_INDEX;
		break;

	case SHOP_UPDATE::SCROLL_DOWN:

		ItemStartIter = CurrentShopItemList_.begin();
		ItemEndtIter = CurrentShopItemList_.end();

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


	if (Player::MainPlayer->GetCurrentLevel() == "ShopLevel")
	{


		std::map<int, ShopItem*>::iterator SaloonStartIter = SaloonItemList_.begin();
		std::map<int, ShopItem*>::iterator SaloonEndtIter = SaloonItemList_.end();

		for (; SaloonStartIter != SaloonEndtIter; ++SaloonStartIter)
		{
			SaloonStartIter->second->Off();
		}


		std::map<int, ShopItem*>::iterator SeedShopStartIter = SeedShopItemList_.begin();
		std::map<int, ShopItem*>::iterator SeedShopEndtIter = SeedShopItemList_.end();

		for (; SeedShopStartIter != SeedShopEndtIter; ++SeedShopStartIter)
		{
			SeedShopStartIter->second->On();
		}



		std::copy(SeedShopItemList_.begin(), SeedShopItemList_.end(), std::inserter(CurrentShopItemList_, CurrentShopItemList_.begin()));

		//위치 초기화
		std::map<int, ShopItem*>::iterator StartIter = CurrentShopItemList_.begin();
		std::map<int, ShopItem*>::iterator EndtIter = CurrentShopItemList_.end();

		for (int i = 0; StartIter != EndtIter; ++StartIter)
		{
			StartIter->second->SetPosition({ 715.f, 123.5f + (i * 76.f) });
			++i;
		}
	}

	if (Player::MainPlayer->GetCurrentLevel() == "SaloonLevel")
	{





		std::copy(SaloonItemList_.begin(), SaloonItemList_.end(), std::inserter(CurrentShopItemList_, CurrentShopItemList_.begin()));
	
		//위치 초기화
		std::map<int, ShopItem*>::iterator StartIter = CurrentShopItemList_.begin();
		std::map<int, ShopItem*>::iterator EndtIter = CurrentShopItemList_.end();

		for (int i = 0; StartIter != EndtIter; ++StartIter)
		{
			StartIter->second->SetPosition({ 715.f, 123.5f + (i * 76.f) });
			++i;
		}
	}

}

void Shop::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	std::map<int, ShopItem*>::iterator StartIter = CurrentShopItemList_.begin();
	std::map<int, ShopItem*>::iterator EndtIter = CurrentShopItemList_.end();

	for (; StartIter != EndtIter; ++StartIter)
	{
		StartIter->second->NextLevelOn();
	}
	Font_->NextLevelOn();
	ExitBotton_->NextLevelOn();
	NextLevelOn();

	CurrentShopItemList_.clear();

}

void Shop::ShopOff()
{
	this->Off();
	ExitBotton_->Off();
	Font_->Off();

	std::map<int, ShopItem*>::iterator StartIter = CurrentShopItemList_.begin();
	std::map<int, ShopItem*>::iterator EndtIter = CurrentShopItemList_.end();

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

	std::map<int, ShopItem*>::iterator StartIter = CurrentShopItemList_.begin();
	std::map<int, ShopItem*>::iterator EndtIter = CurrentShopItemList_.end();

	for (; StartIter != EndtIter; ++StartIter)
	{
		StartIter->second->On();
	}

	ShopUpdateState_ = SHOP_UPDATE::HIDE_ITME;

}

void Shop::SetShopMoney(int _Money)
{
	Font_->ChangeNumMoneyLeftSort(_Money, { 280.f, 475.f });
}

