#pragma once

// Ό³Έν :
class DayOffLevel
{
public:
	// constrcuter destructer
	DayOffLevel();
	~DayOffLevel();

	// delete Function
	DayOffLevel(const DayOffLevel& _Other) = delete;
	DayOffLevel(DayOffLevel&& _Other) noexcept = delete;
	DayOffLevel& operator=(const DayOffLevel& _Other) = delete;
	DayOffLevel& operator=(DayOffLevel&& _Other) noexcept = delete;

protected:

private:

};

