/*
//
// Created by user on 2022-07-16.
//


#include <bits/stdc++.h>
#include <locale>
using namespace std;


struct jw {
    int weight;
    int height;
    jw(const int& a, const int& b){
        weight = a;
        height = b;
    };

};

struct compJW{
    bool operator()(const jw& a, const jw& b) const {
        return a.weight < b.weight;
    }
};


vector<jw> a;
vector<jw> b;


int main(){
    _wsetlocale(LC_ALL, L"Korean");

    jw jw1 = jw(70, 160);
    jw jw2 = jw(60, 200);
    jw jw3 = jw(75, 188);

    int wei = 45;
    int hei = 170;
    for(int i = 0; i < 10; ++ i){
        a.push_back(jw(wei,hei));
        wei ++;
        hei --;
    }
    for(int i = 0; i < 5; ++ i){
        b.push_back(jw(wei,hei));
        wei ++;
        hei --;
    }


//    for(int i = 0; i < 10; ++ i){
//        wprintf_s(L"%d 번째 jw이의 weight: %d, %d 번째 jw이의 height: %d \n", i, a[i].weight, i, a[i].height);
//    }

    int cnt = 0;
    do{
        for(int i = 0; i < 5; ++ i){
            wprintf_s(L"jw이의 weight: %d, jw이의 height: %d \n", b[i].weight, b[i].height);
        }
        cout << endl;
//        cout <<  ++ cnt << endl;

    } while (next_permutation(b.begin(), b.end(), compJW()));



    return 0;
}*/
