#pragma once
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngine/GameEngineFont.h>

// Ό³Έν :
class DialogueBox : public GameEngineActor
{
public:
	// constrcuter destructer
	DialogueBox();
	~DialogueBox();

	// delete Function
	DialogueBox(const DialogueBox& _Other) = delete;
	DialogueBox(DialogueBox&& _Other) noexcept = delete;
	DialogueBox& operator=(const DialogueBox& _Other) = delete;
	DialogueBox& operator=(DialogueBox&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;
	void Render() override;

private:
	GameEngineRenderer* DialogueRenderer_;
	GameEngineRenderer* PortraitRenderer_;

	GameEngineFont DialogueFont_1;

	std::string Dialogue_1;

private:
public:
	void SetDialogue(std::string _Text);

	void SetPierre();
	void SetLewis();

};

