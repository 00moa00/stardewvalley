#include "Shop.h"

Shop::Shop() 
	:
	ShopRenderer_(nullptr),
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


}

void Shop::Update()
{

	std::map<int, ShopItem*>::iterator ItemStartIter = ShopItemList_.begin();
	std::map<int, ShopItem*>::iterator ItemEndtIter = ShopItemList_.end();

	std::map<int, ShopItem*>::iterator ItemfirstFindtIter = ShopItemList_.begin();

	//std::map<int, ShopItem*>::iterator StartIter = ShopItemList_.begin();
	//std::map<int, ShopItem*>::iterator EndtIter = ShopItemList_.end();


	std::map<int, float4>::iterator ConstStartIter = ConstItmePos_.begin();
	std::map<int, float4>::iterator ConstEndtIter = ConstItmePos_.end();

	int count = 0;


	switch (ShopUpdateState_)
	{
	case SHOP_UPDATE::SET_POS_INDEX:



		ItemStartIter = ShopItemList_.begin();
		ItemEndtIter = ShopItemList_.end();

		ItemfirstFindtIter = ShopItemList_.begin();

		//std::map<int, ShopItem*>::iterator StartIter = ShopItemList_.begin();
		//std::map<int, ShopItem*>::iterator EndtIter = ShopItemList_.end();


		ConstStartIter = ConstItmePos_.begin();
		ConstEndtIter = ConstItmePos_.end();


		// 고정 인덱스에 맞춘다

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

		//	ItemStartIter = ShopItemList_.find(count);
		}

		
		ShopUpdateState_ = SHOP_UPDATE::HIDE_ITME;
		break;

	case SHOP_UPDATE::HIDE_ITME:
		// 4개 이상은 숨김


		 ItemStartIter = ShopItemList_.begin();
		 ItemEndtIter = ShopItemList_.end();

		for (int i = 0; ItemStartIter != ItemEndtIter; ++ItemStartIter)
		{
			if (ItemStartIter->second->GetIndex() > 3 || ItemStartIter->second->GetIndex() < 0)
			{
				ItemStartIter->second->Off();
			}

			else
			{
				ItemStartIter->second->On();
			}
		}

		ShopUpdateState_ = SHOP_UPDATE::INIT;
		break;

	case SHOP_UPDATE::INIT:

		if (true == GameEngineInput::GetInst()->IsDown("KeyUp") )
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

		if (true == GameEngineInput::GetInst()->IsDown("KeyDown"))
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

void Shop::ShopOff()
{
	this->Off();

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

	std::map<int, ShopItem*>::iterator StartIter = ShopItemList_.begin();
	std::map<int, ShopItem*>::iterator EndtIter = ShopItemList_.end();

	for (; StartIter != EndtIter; ++StartIter)
	{
		StartIter->second->On();

	}
	ShopUpdateState_ = SHOP_UPDATE::HIDE_ITME;


}

