#pragma once
#include <iostream>
#include <string>
using namespace std;

const string Cards[14] = { "","A","2","3","4","5","6","7","8","9","10","J","Q","K" };

struct BlackJack;

void Homework02_Run();
int RandomCard();
bool Bust(int sum);
int GetScore(const int card);
int SumCal(BlackJack* b);
bool IsBlackJack(BlackJack* b);

struct BlackJack
{
	int Card[30] = {};
	int Count = 0;
	int Sum = 0;
	int AceCount = 0;
	bool bBlackjack = false;


	//1-A 2~10 11-J 12-Q 13-K
	void Init();
};
void TwoCardBlackJack(BlackJack* p, BlackJack* d);
void ShowCard(BlackJack* p, BlackJack* d);
void PlayerTurn(BlackJack* p, BlackJack* d);
void PlayerHit(BlackJack* p, BlackJack* d);
void Stand(BlackJack* p, BlackJack* d);
void DealerTurn(BlackJack* p, BlackJack* d);