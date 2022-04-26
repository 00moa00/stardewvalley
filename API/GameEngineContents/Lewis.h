#pragma once
#include "Npc.h"

// Ό³Έν :
class Lewis : public Npc
{
public:
	static Lewis* MainLewis;
	static 	DialogueBox* MainDialogueBox_;


	// constrcuter destructer
	Lewis();
	~Lewis();

	// delete Function
	Lewis(const Lewis& _Other) = delete;
	Lewis(Lewis&& _Other) noexcept = delete;
	Lewis& operator=(const Lewis& _Other) = delete;
	Lewis& operator=(Lewis&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

	void OpenDialogue() override;

};

