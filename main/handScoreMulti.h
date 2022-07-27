//
// Created by user on 2022-07-25.
//

#ifndef POKERTEST_HANDSCOREMULTI_H
#define POKERTEST_HANDSCOREMULTI_H

#include "card.h"
#include "cardCompare.h"

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

extern vector<vector<unsigned int>> allCaseScore;
extern ll rowAllCase;
extern vector<vector<card>> allCase;
extern int people;



void allCaseSetting(int idx){
    int peopleNum = 0;
    vector<card> peopleCase(5);
    repa(k, 0, 4)
        peopleCase[k] = allCase[idx][k];

    while(peopleNum < people -1) {
        repa(j, 5 + 2 * peopleNum, 5 + 2 * peopleNum +1) {
            peopleCase.push_back(allCase[idx][j]);
        }
        allCaseScore[idx][peopleNum] = handScore(peopleCase);
        peopleCase.resize(5);
        peopleNum ++;
    }
}

void ccExecution(int threadNum){
    ll rowUnit = rowAllCase / threadNum;

    vector<thread> th(threadNum);
    for(int i = 0; i < threadNum; i ++){
        if(i == threadNum - 1){
            th[i] = thread ([](ll sta, ll end){
                for(int j = sta; j < end; j ++)
                    allCaseSetting(j);
            }, rowUnit * (threadNum - 1), rowAllCase);
        }
        else{
            th[i] = thread ([](ll sta, ll end){
                for(int j = sta; j < end; j ++)
                    allCaseSetting(j);
            }, rowUnit * i, rowUnit * (i + 1));
        }
    }
    for(int i = 0; i < threadNum; i ++)
        th[i].join();

}


#endif //POKERTEST_HANDSCOREMULTI_H
