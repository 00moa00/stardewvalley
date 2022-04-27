#include "CustomData.h"

CustomData* CustomData::Inst_ = new CustomData();

CustomData::CustomData()
	:
	HairFileName_("PlayerHair0.bmp"),
	ShirtsFileName_("PlayerShirt0.bmp"),
	HandFileName_("PlayerHand0.bmp"),
	PantsName_("PlayerPants0.bmp")

{
}

CustomData::~CustomData() 
{
}

