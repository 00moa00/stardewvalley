#include "ShopItem.h"

ShopItem::ShopItem()
	:
	ShopItemListRenderer_(nullptr),
	ShopItemListCollider_(nullptr),

	isHide_(false),

	BuyPrice_(0),
	Index_(0)
{
}

ShopItem::~ShopItem()
{
}

