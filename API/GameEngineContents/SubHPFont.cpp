#include "SubHPFont.h"
#include "RendererData.h"
SubHPFont::SubHPFont() 
	:
	SubHPFont_(nullptr)
{
}

SubHPFont::~SubHPFont() 
{
}

void SubHPFont::Start()
{
	SubHPFont_ = GetLevel()->CreateActor<Font>(static_cast<int>(PLAYLEVEL::EFFECT));
}

void SubHPFont::Update()
{
}

void SubHPFont::SetPosition(float4 _Pos)
{
	SubHPFont_->SetPosition(_Pos);
}

