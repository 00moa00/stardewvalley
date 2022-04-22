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

enum class WEEK
{
	MON,
	TUE,
	WED,
	THU,
	FRI,
	SAT,
	SUN
};



// Ό³Έν :
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

	float SecondTime_;
	int SecondTimeInt_;
	int PrevSecondTime_;

	int MinuteTime_;
	int HourTime_;
	int Day_;

	int AddTIme_;

	int WeekIndex_;
	AM_PM AmPm_;

	MINUTE_STATE MinuteState_;

	GameEngineRenderer* MainUIRenderer_;
	//GameEngineRenderer* Day_;
	GameEngineRenderer* WeekRenderer_;
	GameEngineRenderer* AmPmRenderer_;

private:
	void UpdateMinuteTime();
	void UpdateMinuteFont();
	void UpdateHourTime();
	void UpdateSetPm();
	void UpdateAddDay();

	void SetMon()
	{
		WeekRenderer_->SetImage("Mon.bmp");
	}

	void AddWeek()
	{
		if (WeekIndex_ == 6)
		{
			WeekIndex_ = 0;
			WeekRenderer_->SetIndex(WeekIndex_);
			return;
		}

		++WeekIndex_;
		WeekRenderer_->SetIndex(WeekIndex_);
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

	void SetMainUIMoney(int _Money);

};

