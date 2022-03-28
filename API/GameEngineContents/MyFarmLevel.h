#pragma once

// Ό³Έν :
class MyFarmLevel
{
public:
	// constrcuter destructer
	MyFarmLevel();
	~MyFarmLevel();

	// delete Function
	MyFarmLevel(const MyFarmLevel& _Other) = delete;
	MyFarmLevel(MyFarmLevel&& _Other) noexcept = delete;
	MyFarmLevel& operator=(const MyFarmLevel& _Other) = delete;
	MyFarmLevel& operator=(MyFarmLevel&& _Other) noexcept = delete;

protected:

private:

};

