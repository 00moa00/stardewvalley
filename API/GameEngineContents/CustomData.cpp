#include "CustomData.h"

CustomData* CustomData::Inst_ = new CustomData();

CustomData::CustomData() 
	:
		HairIndex_(0),
		ShirtsIndex_(0),
		PantsIndex_(0),
		MoveLock_(false)

{
}

CustomData::~CustomData() 
{
}

