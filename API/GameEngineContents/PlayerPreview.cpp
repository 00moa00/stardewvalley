#include "PlayerPreview.h"
#include "PlayerSpriteData.h"
PlayerPreview* PlayerPreview::MainPlayerPreview = nullptr;

PlayerPreview::PlayerPreview()
	:
	PreviewRendererBody(nullptr),
	PreviewRendererHand(nullptr),
	PreviewRendererPants(nullptr),
	PreviewRendererShirts(nullptr),
	PreviewRendererhair(nullptr)

{
}

PlayerPreview::~PlayerPreview() 
{
}

void PlayerPreview::Start()
{


}

void PlayerPreview::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	if (PreviewRendererhair == nullptr)
	{

		PreviewRendererBody = CreateRenderer("PlayerBody0.bmp");
		PreviewRendererHand = CreateRenderer(CustomData::GetInst()->GetHandFileName());
		PreviewRendererPants = CreateRenderer(CustomData::GetInst()->GetPantsFileName());
		PreviewRendererShirts = CreateRenderer(CustomData::GetInst()->GetShirtsFileName());
		PreviewRendererhair = CreateRenderer(CustomData::GetInst()->GetHairFileName());

		PreviewRendererBody->SetIndex(static_cast<int>(PLAYER::FRONT_INIT));
		PreviewRendererHand->SetIndex(static_cast<int>(PLAYER::FRONT_INIT));
		PreviewRendererPants->SetIndex(static_cast<int>(PLAYER::FRONT_INIT));
		PreviewRendererShirts->SetIndex(static_cast<int>(PLAYER::FRONT_INIT));
		PreviewRendererhair->SetIndex(static_cast<int>(PLAYER::FRONT_INIT));


		PreviewRendererBody -> CameraEffectOff();
		PreviewRendererHand -> CameraEffectOff();
		PreviewRendererPants -> CameraEffectOff();
		PreviewRendererShirts -> CameraEffectOff();
		PreviewRendererhair -> CameraEffectOff();


	}
	//커스텀 데이터 설정
}

void PlayerPreview::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	MainPlayerPreview = this;
}

void PlayerPreview::UpdateOn()
{
	PreviewRendererBody->On();
	PreviewRendererHand->On();
	PreviewRendererPants->On();
	PreviewRendererShirts->On();
	PreviewRendererhair->On();

}

void PlayerPreview::UpdateOff()
{
	PreviewRendererBody->Off();
	PreviewRendererHand->Off();
	PreviewRendererPants->Off();
	PreviewRendererShirts->Off();
	PreviewRendererhair->Off();
}

