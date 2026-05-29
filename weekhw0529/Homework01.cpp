#include "Homework01.h"
//요일 구하기
//1년 1월 1일(월요일)을 기준으로 입력한 날짜까지 며칠이 지났는지 계산한 후, 7로 나눈 나머지로 요일을 구하기.
//윤년도 올바르게 처리할 것
//입력받은 연, 월, 일을 기준으로 요일을 출력.
//예시 입력 : 2026 5 29 → 결과 : 금요일
//Homework01_Run(); 함수로 실행 가능해야 함.
void Homework01_Run()
{
	std::ios_base::sync_with_stdio(false);

	Date hw01;
	hw01.GetInput();
	hw01.PrintDotw();
}