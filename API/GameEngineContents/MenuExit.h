#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class MenuExit : public GameEngineActor
{
public:
	// constrcuter destructer
	MenuExit();
	~MenuExit();

	// delete Function
	MenuExit(const MenuExit& _Other) = delete;
	MenuExit(MenuExit&& _Other) noexcept = delete;
	MenuExit& operator=(const MenuExit& _Other) = delete;
	MenuExit& operator=(MenuExit&& _Other) noexcept = delete;

	bool GetIsClick() {
		return isClick_;
	}

	inline void SetIsClick(const bool b) {
		isClick_ = b;
	}


protected:
	void Start()override;
	void Render()override;
	void Update() override;
private:

	bool isClick_;
	GameEngineRenderer* MenuExit_;

};

