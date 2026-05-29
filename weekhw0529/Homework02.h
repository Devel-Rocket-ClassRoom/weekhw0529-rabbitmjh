#pragma once
#include <iostream>
#include <string>
using namespace std;

const string Cards[14] = { "","A","2","3","4","5","6","7","8","9","10","J","Q","K" };

void Homework02_Run();
int RandomCard();
bool Bust(int sum);
int GetScore(const int card);

struct BlackJack
{
	int Card[30] = {};
	int Count = 0;
	int Sum = 0;
	bool bBlackjack = false;
	bool bWin = false;

	//1-A 2~10 11-J 12-Q 13-K
	void Init()
	{
		Card[0] = RandomCard();
		Card[1] = RandomCard();
		Sum += GetScore(Card[0]) + GetScore(Card[1]);
		if ((Card[0] == 1 && Card[1] > 9) || (Card[1] == 1 && Card[0] > 9))
			bBlackjack = true;
		Count = 2;
	}
};

void ShowCard(BlackJack* p, BlackJack* d);
void PlayerTurn(BlackJack* p, BlackJack* d);
void PlayerHit(BlackJack* p, BlackJack* d);
void Stand(BlackJack* p, BlackJack* d);
void DealerTurn(BlackJack* p, BlackJack* d);