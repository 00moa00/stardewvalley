#pragma once
#include <GameEngineBase/GameEngineRandom.h>

#include "Items.h"
#include "TreeTop.h"

enum class TREESTATE
{
	INIT,
	UPDATE
};

// ���� :
class TreeBottom : public Items
{
public:
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
	void SetInitAnimation() override;
	void SetCrushAnimation() override;

private:
	Items* TreeTop_;
	TREESTATE TreeState_;

public:
	void TreeOff() override;

};

