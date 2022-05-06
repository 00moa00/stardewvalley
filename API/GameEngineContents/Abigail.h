#pragma once
#include "Npc.h"

// Ό³Έν :
class Abigail : public Npc
{
public:
	// constrcuter destructer
	Abigail();
	~Abigail();

	// delete Function
	Abigail(const Abigail& _Other) = delete;
	Abigail(Abigail&& _Other) noexcept = delete;
	Abigail& operator=(const Abigail& _Other) = delete;
	Abigail& operator=(Abigail&& _Other) noexcept = delete;

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

