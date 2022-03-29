#pragma once
#include <GameEngine/GameEngineActor.h>
#include <map>
#include <string>
// Ό³Έν :
class Item : public GameEngineActor
{
public:
	// constrcuter destructer
	Item();
	~Item();

	// delete Function
	Item(const Item& _Other) = delete;
	Item(Item&& _Other) noexcept = delete;
	Item& operator=(const Item& _Other) = delete;
	Item& operator=(Item&& _Other) noexcept = delete;

protected:

private:
	std::map<std::string, GameEngineRenderer*> AllRes;

};

