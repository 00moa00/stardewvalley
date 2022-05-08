#pragma once
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngine.h>
//#include <GameEngine/GameEngineFont.h>
#include <GameEngineBase/GameEngineRandom.h>

#include "NpcData.h"
#include "Font.h"

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
	GameEngineRenderer* DialogueBoxRenderer_;
	GameEngineRenderer* PortraitRenderer_;
	GameEngineRenderer* DialogueName_;

	Font* Dialoue_;

	GameEngineRandom DialogueRandom_;

	std::string PierreDialogue[5];
	std::string LewiseDialogue[5];
	std::string PennyDialogue[5];
	std::string GusDialogue[5];
	std::string AbigailDialogue[5];

private:
public:
	void SetDialogue(std::string _Text);

	void SetPierre();
	void SetLewis();
	void SetPenny();
	void SetAbigail();
	void SetGus();

	void DialogueOn();
	void DialogueOff();



};

