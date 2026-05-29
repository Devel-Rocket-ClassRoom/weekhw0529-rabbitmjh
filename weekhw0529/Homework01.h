#pragma once
#include <iostream>
#include <string>
struct Date
{
	const int MonthDay[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	const std::string WeekDays[7]= { "일요일", "월요일", "화요일", "수요일", "목요일", "금요일", "토요일" };
	int Year;
	int Month;
	int Day;

	Date()
	{
		Year = 1;
		Month = 1;
		Day = 1;
	}

	Date(const int y, const int m, const int d)
		:Year(y), Month(m), Day(d)
	{ }

	void PrintDotw()
	{
		std::cout << Year<<"년 "<<Month<<"월 "<<Day<<"일은 "<< GetDotw(&Year, &Month, &Day) << "입니다." << std::endl;
	}
	std::string GetDotw(const int* y, const int* m, const int* d)
	{
		int DaySum = 0;
		for (int i = 1; i < *y; i++)
			DaySum += (IsLeepYear(i) ? 366 : 365);
		for (int i = 1; i < *m; i++)
			DaySum += MonthDay[i];
		if (*m > 2 && IsLeepYear(*y))
			DaySum++;
		DaySum += *d;

		return WeekDays[DaySum % 7];
	}
	
	bool IsLeepYear(const int& y)
	{
		if (y % 400 == 0) return true;
		else if (y % 100 == 0)return false;
		else if (y % 4 == 0)return true;
		else return false;
	}

	void GetInput()
	{
		using namespace std;
		cout << "연도를 입력하세요: ";
		cin >> Year;
		while (Year < 1)
		{
			cout << "연도를 입력하세요: ";
			cin >> Year;
		}

		cout << "월을 입력하세요: ";
		cin >> Month;
		while (Month < 1 || Month>12)
		{
			cout << "월을 입력하세요: ";
			cin >> Month;
		}

		cout << "일을 입력하세요: ";
		cin >> Day;
		while (((IsLeepYear(Year) && Month == 2) && Day > 29) || (!IsLeepYear(Year) && (MonthDay[Month] < Day)))
		{
			cout << "일을 입력하세요: ";
			cin >> Day;
		}
	}
};

void Homework01_Run();