#pragma once
#include "Npc.h"

// Ό³Έν :
class Lewis : public Npc
{
public:
	// constrcuter destructer
	Lewis();
	~Lewis();

	// delete Function
	Lewis(const Lewis& _Other) = delete;
	Lewis(Lewis&& _Other) noexcept = delete;
	Lewis& operator=(const Lewis& _Other) = delete;
	Lewis& operator=(Lewis&& _Other) noexcept = delete;

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

