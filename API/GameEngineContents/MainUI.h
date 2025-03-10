#pragma once
#include <GameEngine/GameEngineActor.h>
#include "Font.h"
#include "PlayerData.h"


enum class TIME_STATE
{
	UPDATE
};

enum class AM_PM
{
	AM,
	PM
};

//enum class DAY
//{
//	MON,
//	TUE,
//	WED,
//	THU,
//	FRI,
//	SAT,
//	SUN
//};



// ���� :
class MainUI : public GameEngineActor
{
public:
	static MainUI* MainMainUI;
	static Font* MoneyFont_;
	static Font* MinuteFont_;
	static Font* HourFont_;
	static Font* DayFont_;


	// constrcuter destructer
	MainUI();
	~MainUI();

	// delete Function
	MainUI(const MainUI& _Other) = delete;
	MainUI(MainUI&& _Other) noexcept = delete;
	MainUI& operator=(const MainUI& _Other) = delete;
	MainUI& operator=(MainUI&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update() override;
	void Render() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:
	Font* Font_;


	int SecondTimeInt_;
	int PrevSecondTime_;
	int MinuteTime_;
	int HourTime_;
	
	int ExtraHourTime_;

	int Day_;
	int AddTIme_;
	int DayIndex_;

	int DayFadeAlpha_;

	float SecondTime_;

	bool isExtraDay_;
	bool Sleep_;

	AM_PM AmPm_;

	MINUTE_STATE MinuteState_;

	GameEngineRenderer* MainUIRenderer_;
	GameEngineRenderer* DayRenderer_;
	GameEngineRenderer* AmPmRenderer_;

	GameEngineRenderer* DayFade_;

private:
	void UpdateMinuteFont();
	void UpdateHourTime();
	void UpdateSetPm();
	void UpdateSetAm();
	void ExtraDayAndAddDay();


	void SetMon()
	{
		DayRenderer_->SetImage("Mon.bmp");
	}

	void AddDay()
	{
		if (DayIndex_ == 6)
		{
			DayIndex_ = 0;
			DayRenderer_->SetIndex(DayIndex_);
			return;
		}

		++DayIndex_;
		DayRenderer_->SetIndex(DayIndex_);

	}


	void SetAm()
	{
		AmPmRenderer_->SetImage("am.bmp");
	}

	void SetPm() 
	{
		AmPmRenderer_->SetImage("pm.bmp");
	}


public:
	void SetDayOff();

	void SetMainUIMoney(int _Money);

	void SetDayFadeReset();



	void SetSleep(bool _Flag)
	{
		Sleep_ = _Flag;
	}

	int GetDay()
	{
		return Day_;
	}

	int GetHour()
	{
		return HourTime_;
	}

	bool DayOver()
	{
		if (HourTime_ == 25)
		{
			return true;
		}

		else
		{
			return false;
		}
	}

	bool DayEnd()
	{
		if (HourTime_ == 24 && MinuteTime_ == 50)
		{
			return true;
		}

		else
		{
			return false;
		}
	}

	bool PlayerSleep()
	{
		return Sleep_;
	}

	

};

