#pragma once
#include <GameEngine/GameEngineRenderer.h>
#include "CustomData.h"

// Ό³Έν :
class PlayerPreview : public GameEngineActor
{
public:
	static PlayerPreview* MainPlayerPreview;

	// constrcuter destructer
	PlayerPreview();
	~PlayerPreview();

	// delete Function
	PlayerPreview(const PlayerPreview& _Other) = delete;
	PlayerPreview(PlayerPreview&& _Other) noexcept = delete;
	PlayerPreview& operator=(const PlayerPreview& _Other) = delete;
	PlayerPreview& operator=(PlayerPreview&& _Other) noexcept = delete;
private:

	void Start() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:
	GameEngineRenderer* PreviewRendererBody;
	GameEngineRenderer* PreviewRendererHand;
	GameEngineRenderer* PreviewRendererPants;
	GameEngineRenderer* PreviewRendererShirts;
	GameEngineRenderer* PreviewRendererhair;

public:
	void UpdateOn();
	void UpdateOff();
};

