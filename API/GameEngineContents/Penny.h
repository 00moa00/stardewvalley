#pragma once
#include "Npc.h"

// Ό³Έν :
class Penny : public Npc
{
public:
	//static Penny* MainPenny;

	// constrcuter destructer
	Penny();
	~Penny();

	// delete Function
	Penny(const Penny& _Other) = delete;
	Penny(Penny&& _Other) noexcept = delete;
	Penny& operator=(const Penny& _Other) = delete;
	Penny& operator=(Penny&& _Other) noexcept = delete;
	
private:
	DialogueBox* MainDialogueBox_;

private:
	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

	void OpenDialogue() override;

private:

	bool MoveRight() override;
	bool MoveLeft() override;
	bool MoveDown() override;
	bool MoveUp() override;
	bool MoveWait() override;

};

