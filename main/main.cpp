/*
#include <bits/stdc++.h>
#include <thread>
#include <locale>
#include "card.h"
using namespace std;


struct CardSets {
private:
    vector<card> Sets;
public:
    enum class Rank {
        StraightFlush,
        Poker,
        FullHouse,
        Flush,
        Straight,
        Triple,
        TwoPairs,
        OnePair,
        High,
    };
    int FindGrade(CardSets K){
        int amt = K.Sets.size();
        if (amt < 5)
            return 10;
        bool flush;
        bool straight;


    };

};


class Poker {
private:
    vector<card> CardDeck;
    int ComputerNumbers;
    int Round;
    int PlayerMoney;

public:
    card DrawOne();
    void Shuffle();
    void StartGame();
    void EndGame();
    void JudgeCard();
    void setComputerNumbers(const int&);
    void setRound(const int&);
    void Settings();

};

card Poker::DrawOne() {

}

void Poker::Shuffle() {

}

void Poker::StartGame() {
    wprintf_s(L"포커[텍사스 홀덤]에 오신 것을 환영합니다.\n");

}

void Poker::EndGame() {
    wprintf_s(L"정말 나가시겠습니까?\n");
}

void Poker::JudgeCard() {

}



class PersonalCardSet {
private:
    vector<card> CardSets;
    int CardRank;
public:
    void sayRaise();
    void sayCall();
    void sayDie();
};

class ComputerCardSet {
private:
    vector<card> CardSets;
    int CardRank;
public:

};

int main() {
    _wsetlocale(LC_ALL, L"Korean");
    wprintf_s(L"종료하려면 아무키나 누르세요.\n");

    wchar_t wHeart[] = L"\u2661";
    wchar_t wDiamond[] = L"\u2662";
    wchar_t wSpade[] = L"\u2664";
    wchar_t wClovers[] = L"\u2667";

    wprintf_s(L"%s\n",wSpade);
    wprintf_s(L"%s\n",wDiamond);
    wprintf_s(L"%s\n",wHeart);
    wprintf_s(L"%s\n",wClovers);

    wchar_t bHeart[] = L"\u2665";
    wchar_t bDiamond[] = L"\u2666";
    wchar_t bSpade[] = L"\u2660";
    wchar_t bClovers[] = L"\u2663";

    wprintf_s(L"%s\n",bSpade);
    wprintf_s(L"%s\n",bDiamond);
    wprintf_s(L"%s\n",bHeart);
    wprintf_s(L"%s\n",bClovers);

    wprintf_s(L"♤ ♢ ♡ ♧\n♠ ♦ ♥ ♣\n");
//    std::this_thread::sleep_for(3000ms);
    string cmd;
    cin >> cmd;

    return 0;
}
*/
