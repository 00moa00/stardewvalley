#pragma once
#include <GameEngine/GameEngineActor.h>
\
// Ό³Έν :
class MenuLoad : public GameEngineActor
{
public:
	// constrcuter destructer
	MenuLoad();
	~MenuLoad();

	// delete Function
	MenuLoad(const MenuLoad& _Other) = delete;
	MenuLoad(MenuLoad&& _Other) noexcept = delete;
	MenuLoad& operator=(const MenuLoad& _Other) = delete;
	MenuLoad& operator=(MenuLoad&& _Other) noexcept = delete;

	bool GetIsClick() {

		return isClick_;
	}

	void SetIsSClick(bool b) {

		isClick_ = b;

	}

protected:
	void Start()override;
	void Render()override;
	void Update() override;
private:

	bool isClick_;


	GameEngineRenderer* MenuLoad_;

};

