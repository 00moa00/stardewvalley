#pragma once
#include "Npc.h"

// Ό³Έν :
class Gus : public Npc
{
public:
	// constrcuter destructer
	Gus();
	~Gus();

	// delete Function
	Gus(const Gus& _Other) = delete;
	Gus(Gus&& _Other) noexcept = delete;
	Gus& operator=(const Gus& _Other) = delete;
	Gus& operator=(Gus&& _Other) noexcept = delete;

private:
	DialogueBox* MainDialogueBox_;

	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

	void OpenDialogue() override;
};

