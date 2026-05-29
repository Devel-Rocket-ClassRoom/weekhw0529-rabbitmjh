#include "Homework02.h"
#include <iostream>
#include <ctime>
#include <cctype>
using namespace std;
//블랙잭 만들기
//두 카드의 합이 21에 가깝게 만들되, 21을 넘지 않는 것이 목표
//21을 초과하면(버스트, Bust)  즉시 패배
//배팅은 없음
//카드의 값
//2~10: 카드 숫자 그대로 점수.
//J(잭), Q(퀸), K(킹) : 각각 10점.
//A(에이스) : 1점 또는 11점(유리한 쪽으로 자동 선택).
//게임 진행 절차
//초기 배분
//딜러와 플레이어 모두 2장씩 카드를 받음.
//플레이어의 카드는 두 장 모두 공개.
//딜러는 한 장은 공개(오픈 카드), 한 장은 비공개(홀 카드).
//플레이어 턴
//플레이어가 먼저 행동.
//선택지:
//Hit(히트) : 카드를 한 장 더 받음.
//Stand(스탠드) : 더 이상 카드를 받지 않고 멈춤.
//플레이어가 21을 초과하면(버스트) 즉시 패배.
//딜러 턴
//플레이어가 스탠드를 하면 딜러 차례.
//딜러는 자신의 카드 합이 17 이상이 될 때까지 계속 히트(카드 받기)해야 함.
//A가 포함된 "소프트 17"(A + 6 = 7 또는 17)도 멈춤.
//17 이상이면 멈추고, 21을 넘으면 딜러 패배.
//승패 판정
//버스트가 아닌 경우, 점수 비교.
//플레이어가 21에 더 가까우면 승리.
//동점이면 무승부(Push).
//딜러가 더 가까우면 패배.
//블랙잭: 처음 받은 두 장이 A + 10(또는 J, Q, K)이면 블랙잭.일반적으로 블랙잭이 단순 21점보다 우선함.
//Homework02_Run(); 함수로 실행 가능해야 함.
void Homework02_Run()
{
	ios_base::sync_with_stdio(false);
	unsigned int Seed = (unsigned int)time(0);
	srand(Seed);	

	BlackJack Player;
	BlackJack Dealer;
	Player.Init();
	if (Player.bBlackjack)
	{
		cout << "\n@@@@@@@@@@BLACKJACK@@@@@@@@@@\n";
		return;
	}
	Dealer.Init();

	ShowCard(&Player, &Dealer);
	PlayerTurn(&Player, &Dealer);
	// RandomCard()로 JQK 받으면 Card[]에 처리하는거 해야함
	// 플레이어 버스트 처리해야함
	// A 1또는 11 처리해야함
	// 승패판정 후 게임 종료 처리해야함
}

int RandomCard()
{
	return rand() % 13 + 1;
}

bool Bust(int sum)
{
	return (sum > 21 ? true : false);
}

int GetScore(const int card)
{
	if (card >= 11 && card <= 13)
		return 10;

	return card;
}

void ShowCard(BlackJack* p, BlackJack* d)
{
	cout << "==========BlackJack==========\n" << endl;

	cout << "플레이어의 카드는 " << Cards[p->Card[0]] << ", " << Cards[p->Card[1]] << "입니다." << endl;
	cout << "딜러의 공개 카드는 " << Cards[d->Card[0]] << "입니다." << endl;
}

void PlayerTurn(BlackJack* p, BlackJack* d)
{
	cout << "\n=========Player Turn=========" << endl;
	cout << "Hit(카드를 1장 더 받음) 또는\nStand(더 이상 카드를 받지 않고 멈춤)\n둘 중 하나를 입력하세요: ";

	string Choice;
	cin >> Choice;
	for (int i = 0; i < Choice.size(); i++)
		Choice[i] = toupper(Choice[i]);
	while (Choice != "HIT" && Choice != "STAND")
	{
		cout << "Hit(카드를 1장 더 받음) 또는\nStand(더 이상 카드를 받지 않고 멈춤)\n둘 중 하나를 입력하세요: ";
		cin >> Choice;
		for (int i = 0; i < Choice.size(); i++)
			Choice[i] = toupper(Choice[i]);
	}
	if (Choice == "HIT")
		PlayerHit(p, d);
	else // STAND
		Stand(p, d);
}

void PlayerHit(BlackJack* p, BlackJack* d)
{
	p->Card[p->Count] = RandomCard();
	p->Sum += GetScore(p->Card[p->Count]);
	cout << "\n==========PlayerHit==========\n";
	cout << "카드: " << Cards[p->Card[p->Count]] << "를 받았습니다. 현재 카드의 합: " << p->Sum << endl;
	p->Count++;
	if (Bust(p->Sum))
	{	
		cout << "==========DealerWin==========" << endl;
		p->bWin = false;
		d->bWin = true;
	}
	else
		PlayerTurn(p, d);
}

void Stand(BlackJack* p, BlackJack* d)
{
	cout << "\n=========PlayerStand=========\n";
	DealerTurn(p, d);
}

void DealerTurn(BlackJack* p, BlackJack* d)
{
	cout << "\n=========Dealer Turn=========\n";
	cout << "딜러의 비공개 카드는: " << Cards[d->Card[1]] << "입니다.\n";
	cout << "현재 딜러의 카드의 합: " << d->Sum << ", 딜러의 카드 수: " << d->Count << endl;
	while (d->Sum < 17)
	{
		d->Card[d->Count] = RandomCard();
		d->Sum += GetScore(d->Card[d->Count]);
		cout << "\n==========DealerHit==========\n";
		cout << "딜러가 카드: " << Cards[d->Card[d->Count]] << "를 받았습니다. 현재 딜러의 카드 합: " << d->Sum << endl;
		d->Count++;
	}
	if (Bust(d->Sum) || d->Sum < p->Sum) // 플레이어 승
	{
		p->bWin = true;
		d->bWin = false;
		cout << "==========PlayerWin==========" << endl;
	}
	else if (d->Sum == p->Sum) // 비김
	{
		cout << "=============DRAW============" << endl;
		p->bWin = false;
		d->bWin = false;
	}
	else if (d->Sum > p->Sum) // 딜러 승
	{
		cout << "==========DealerWin==========" << endl;
		p->bWin = false;
		d->bWin = true;
	}
}