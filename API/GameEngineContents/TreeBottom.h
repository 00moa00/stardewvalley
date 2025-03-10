#pragma once
#include <GameEngineBase/GameEngineRandom.h>

#include "Items.h"
#include "TreeTop.h"

enum class TREESTATE
{
	INIT,
	UPDATE,
	TREETOP_DIE
};

// ���� :
class TreeBottom : public Items
{
public:
	static TreeBottom* MainTreeBottom;

	// constrcuter destructer
	TreeBottom();
	~TreeBottom();

	// delete Function
	TreeBottom(const TreeBottom& _Other) = delete;
	TreeBottom(TreeBottom&& _Other) noexcept = delete;
	TreeBottom& operator=(const TreeBottom& _Other) = delete;
	TreeBottom& operator=(TreeBottom&& _Other) noexcept = delete;

private:

	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

	void SetInitAnimation() override;
	void SetCrushAnimation() override;
	void DropItemInMap() override;

private:
	Items* TreeTop_;
	TREESTATE TreeState_;

public:
	void TreeOff() override;

};

