#include "Effect.h"

Effect::Effect() 
	:
	EffectRenderer_(nullptr),
	MoveDir_(float4::ZERO),
	Count_(0)
{
}

Effect::~Effect() 
{
}

