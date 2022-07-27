/*
//
// Created by user on 2022-07-17.
//

#include <bits/stdc++.h>
#include "card.h"
#include "cardCompare.h"

#define endl '\n'
#define all(v) (v).begin(),(v).end()
#define compress(v) {sort(all(v)); (v).erase(unique(all(v)),(v).end());}
//#define findIdxK(v, k) lower_bound(all(v),k) - (v).begin() + 1
typedef long long ll;
#define dump(x) cerr << "Line " << __LINE__ << ": "<< #x << " = " << (x) << endl
#define repa(i, a, b) for(ll i = a; i <= b; ++ i)
#define repb(i, a, b) for(ll i = a; i >= b; -- i)
#define FastIO cin.tie(NULL), cout.tie(NULL), ios_base::sync_with_stdio(false)
#define fixD(d, x) fixed << setprecision(d) << x
// #define Mod 1000007
//const int inf = 987654321;
// const ll infl = 0x3f3f3f3f3f3f3f3f;
using namespace std;
const int MAXN = 100001;


template <typename T>
void printCurrent(const T& data){
    for(auto &e : data)
        cout << e.num << " ";
    cout << endl << "--------------------" << endl;
}




int main(){
    // 2 10 1 10
    vector<card> deck1 = {card(2,10),card(1,10),card(3,10),card(2,12),card(4,13),card(2,14),card(4,14)};
    vector<card> deck2 = {card(2,9),card(1,10),card(2,10),card(2,11),card(3,11),card(1,12),card(1,13)};
    vector<card> deck3 = {card(1,2),card(4,2),card(2,3),card(3,6),card(3,13),card(2,13),card(1,14)};

    vector<card> set;
    sort(all(deck1), numPriorCmp);
    sort(all(deck2), numPriorCmp);
    sort(all(deck3), numPriorCmp);

//    printCurrent(deck1);

//    set = get<1>(chkHigh(deck3));
//    if(!set.empty())
//        for(auto &e : set)
//            cout << "shape: "<< e.shp << ", number: " << e.num << endl;
//    else
//        cout << "J 원더" << endl;

    cout << hex << handScore(deck1) << endl;
    cout << hex << handScore(deck2) << endl;
    cout << hex << handScore(deck3) << endl;



//    cout << chkStraight(ref(deck1)) << endl;
//    cout << chkStraight(ref(deck2)) << endl;
//    cout << chkStraight(ref(deck3)) << endl;
//    cout << endl;
//
//    cout << chkFlush(ref(deck1)) << endl;
//    cout << chkFlush(ref(deck2)) << endl;
//    cout << chkFlush(ref(deck3)) << endl;
//    cout << endl;
//
//    cout << chkFourCard(ref(deck1)) << endl;
//    cout << chkFourCard(ref(deck2)) << endl;
//    cout << chkFourCard(ref(deck3)) << endl;
//    cout << endl;
//
//    cout << chkOnePair(ref(deck1)) << endl;
//    cout << chkOnePair(ref(deck2)) << endl;
//    cout << chkOnePair(ref(deck3)) << endl;
//    cout << endl;
//
//    cout << chkStraightFlush(ref(deck1)) << endl;
//    cout << chkStraightFlush(ref(deck2)) << endl;
//    cout << chkStraightFlush(ref(deck3)) << endl;
//    cout << endl;


    return 0;
}
*/
