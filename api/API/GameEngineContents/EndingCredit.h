#pragma once

class EndingCredit
{
public:
	EndingCredit();
	~EndingCredit();

	EndingCredit(const EndingCredit& _Other) = delete;
	EndingCredit(EndingCredit&& _Other) noexcept = delete;
	EndingCredit& operator=(const EndingCredit& _Other) = delete;
	EndingCredit& operator=(EndingCredit&& _Other) noexcept = delete;

protected:

private:

};

