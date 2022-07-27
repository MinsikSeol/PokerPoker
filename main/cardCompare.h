//
// Created by user on 2022-07-17.
//

#ifndef UNTITLED2_CARDCOMPARE_H
#define UNTITLED2_CARDCOMPARE_H

#include <bits/stdc++.h>
#include "card.h"

typedef long long ll;
#define all(v) (v).begin(),(v).end()
#define repa(i, a, b) for(ll i = a; i <= b; ++ i)
#define compress(v) {sort(all(v)); (v).erase(unique(all(v)),(v).end());}
using namespace std;

bool numPriorCmp(const card& A, const card& B){
    return A.num < B.num;
}


// sample은 7가지 card로 구성됨 + [중요] number 기준으로 sort가 되어있다고 가정

tuple< bool, const vector<card> > chkStraight(const vector<card>& sample){
    vector<card> res;
    vector<int> collectionNum;

    int shpUnq[4] = {1,2,4,8};
    int shpCmp[15] = {};

    int tmpStart;
    bool potentialStraight;

    for(auto &e : sample)
        if(e.num == 14){
            collectionNum.push_back(1);
            shpCmp[1] += shpUnq[e.shp - 1];
        }

    for(int i = 6; i >= 0; i --){
        collectionNum.push_back(sample[i].num);
        shpCmp[sample[i].num] += shpUnq[sample[i].shp - 1];
    }
    compress(collectionNum); // 숫자압축

    for(int i = collectionNum.size()-5; i >= 0; i --){
        potentialStraight = true;
        tmpStart = collectionNum[i];
        for(int j = 1; j <= 4; ++j)
            if (collectionNum[i + j] != tmpStart + j){
                potentialStraight = false;
                break;
            }
        if(potentialStraight == true){
            // 확정
            int anyShp, whtShp;
            repa(l, 0, 4){
                anyShp = 15;
                anyShp &= shpCmp[tmpStart + l];
                whtShp = log2(anyShp & (-anyShp)) + 1;
                res.push_back(card(whtShp,tmpStart + l));
            }
            return {true, res};
        }
    }

    return {false, res};
}


tuple< bool, const vector<card> > chkFlush(const vector<card>& sample){
    vector<card> res;
    int flushShape;
    int flushCount;

    int shapeCount[5] = {0, 0, 0, 0,0};
    for(int i = 0; i < 7; ++ i){
        shapeCount[sample[i].shp] ++;
    }
    for(int i = 4; i >= 1; i --){
        if(shapeCount[i] >= 5) {
            flushShape = i;
            flushCount = 0;
            for(int j = 6; j >= 0; j --){
                if(sample[j].shp == flushShape && flushCount < 5){
                    res.push_back(sample[j]);
                    flushCount ++;
                }
            }
            return {true, res};
        }
    }
    res.resize(0);
    return {false, res};
}



tuple< bool, const vector<card>, int > chkFourCard(const vector<card>& sample){
    vector<card> res = sample;
    int fourCardNumber;
    int eraseCount;

    int numCount[15];
    memset(numCount, 0, sizeof numCount);
    for(int i = 0; i < 7; ++ i){
        numCount[sample[i].num] ++;
    }
    bool potentialPoker = false;
    for(int i = 2; i <= 14; ++ i){
        if(numCount[i] == 4) {
            fourCardNumber = i;
            eraseCount = 0;
            for(int j = 0; j < 7; ++ j){
                if(eraseCount < 2)
                    if(res[j].num != fourCardNumber){
                        card tmp = res[j];
                        auto itr = find(res.begin(),res.end(),tmp);
                        res.erase(itr);
                        eraseCount ++;
                        -- j;
                    }
            }
            return {true, res, fourCardNumber};
        }
    }
    res.resize(0);
    return {false, res, 0};
}

tuple< bool, const vector<card>, int, int > chkFullHouse(const vector<card>& sample){
    vector<card> res;

    int tripleNumber, pairNumber;

    int numCount[15];
    memset(numCount, 0, sizeof numCount);
    for(int i = 0; i < 7; ++ i){
        numCount[sample[i].num] ++;
    }
    for(int i = 14; i >= 2; i --){
        if(numCount[i] == 3) {
            tripleNumber = i;
            for(int j = 14; j >= 2; j --){
                if(j == tripleNumber)
                    continue;
                if(numCount[j] >= 2){
                    // 확정
                    pairNumber = j;
                    for(int k = 6; k >= 0; k --){
                        if(sample[k].num == tripleNumber || sample[k].num == pairNumber)
                            res.push_back(sample[k]);
                    }

                    return {true, res, tripleNumber, pairNumber};
                }
            }
        }
    }
    res.resize(0);
    return {false, res, 0, 0};

}

tuple< bool, const vector<card>, int > chkTriple(const vector<card>& sample){
    vector<card> res = sample;

    int tripleNumber;
    int eraseCount;

    int numCount[15];
    memset(numCount, 0, sizeof numCount);
    for(int i = 0; i < 7; ++ i){
        numCount[sample[i].num] ++;
    }
    bool potentialTriple = false;
    for(int i = 14; i >= 2; i --){
        if(numCount[i] == 3) {
            tripleNumber = i;
            eraseCount = 0;
            for(int j = 0; j < 7; ++ j){
                if(eraseCount < 2)
                    if(res[j].num != tripleNumber){
                        card tmp = res[j];
                        auto itr = find(res.begin(),res.end(),tmp);
                        res.erase(itr);
                        eraseCount ++;
                        -- j;
                    }
            }
            return {true, res, tripleNumber};
        }
    }
    res.resize(0);
    return {false, res, 0};
}


tuple< bool, const vector<card>, int, int, int > chkTwoPair(const vector<card>& sample){
    vector<card> res;
    vector<int> pairNumbers;
    int pushCount;

    int numCount[15];
    memset(numCount, 0, sizeof numCount);
    for(int i = 0; i < 7; ++ i){
        numCount[sample[i].num] ++;
    }
    for(int i = 2; i <= 14; ++ i){
        if(numCount[i] == 2) {
            pairNumbers.push_back(i);
        }
    }
    if(pairNumbers.size() >= 2){
        pushCount = 0;
        int pairN1 = 0, pairN2 = 0, rest;

        try {
            for (int i = 6; i >= 0; i--) {
                if (pushCount < 4)
                    if (find(pairNumbers.begin(), pairNumbers.end(), sample[i].num) != pairNumbers.end()) {
                        res.push_back(sample[i]);
                        pushCount++;
                        if (pushCount == 1)
                            pairN1 = sample[i].num;
                        if (pushCount == 3)
                            pairN2 = sample[i].num;

                        if(pairN1 < 0 || pairN1 > 14 || pairN2 < 0 || pairN2 > 14){
                            cout << pairN1 << " " << pairN2 << endl;
                            throw "exception";
                        }
                    }
            }
        } catch (...){
            cerr << "error" << endl;
            for(auto &e : sample)
                cout << e.num << ' ';
            exit(3);
        }
        for(int i = 6; i >= 0; i --){
            if(find(pairNumbers.begin(),pairNumbers.end(), sample[i].num) != pairNumbers.end())
                continue;
            res.push_back(sample[i]);
            rest = sample[i].num;
            break;
        }
        return {true, res, pairN1, pairN2, rest};
    }
    return {false, res, 0, 0, 0};
}



tuple< bool, const vector<card>, int > chkOnePair(const vector<card>& sample){
    vector<card> res;
    int onePairNumber;
    int countReserves;

    int numCount[15];
    memset(numCount, 0, sizeof numCount);
    for(int i = 0; i < 7; ++ i){
        numCount[sample[i].num] ++;
    }
    for(int i = 14; i >= 2; i --){
        if(numCount[i] == 2){
            onePairNumber = i;
            for(int j = 6; j >= 0; j --)
                if(sample[j].num == onePairNumber)
                    res.push_back(sample[j]);
            countReserves = 0;
            for(int j = 6; j >= 0; j --)
                if(countReserves < 3 && sample[j].num != onePairNumber){
                    res.push_back(sample[j]);
                    countReserves ++;
                }

            return {true, res, onePairNumber};
        }
    }
    return {false, res, 0};
}



tuple< bool, const vector<card> > chkStraightFlush(const vector<card>& sample){
    vector<card> res;
    vector<int> collectionNum;

    int shpUnq[4] = {1,2,4,8};
    int shpCmp[15] = {};

    int tmpStart;
    bool potentialStraight;

    for(auto &e : sample)
        if(e.num == 14){
            collectionNum.push_back(1);
            shpCmp[1] += shpUnq[e.shp - 1];
        }

    for(int i = 6; i >= 0; i --){
        collectionNum.push_back(sample[i].num);
        shpCmp[sample[i].num] += shpUnq[sample[i].shp - 1];
    }
    compress(collectionNum); // 숫자압축

    for(int i = collectionNum.size()-5; i >= 0; i --){
        potentialStraight = true;
        tmpStart = collectionNum[i];
        for(int j = 1; j <= 4; ++j)
            if (collectionNum[i + j] != tmpStart + j){
                potentialStraight = false;
                break;
            }
        if(potentialStraight == true){
            int anyShp = 15;
            repa(k, 0, 4){
                anyShp &= shpCmp[tmpStart + k];
            }
            if(anyShp != 0){
                // 확정
                int whtShp = log2(anyShp & (-anyShp)) + 1;
                repa(l, 0, 4)
                    res.push_back(card(whtShp,tmpStart + l));
                return {true, res};
            }
        }
    }

    return {false, res};
}

tuple< bool, const vector<card> > chkHigh(const vector<card>& sample){
    vector<card> res;
    int highCount = 0;

    for(int i = 6; i >= 0; i --){
        if(highCount < 5){
            res.push_back(sample[i]);
            highCount ++;
        }
    }

    return {true, res};
}



unsigned int handScore(const vector<card>& sample){
//    16진수로 해석되는 정보가 int의 반환값으로 나올 예정

//    StraightFlush,  ->9 o
//    FourCard,       ->8 o
//    FullHouse,      ->7 0
//    Flush,          ->6 o
//    Straight,       ->5 o
//    Triple,         ->4 o
//    TwoPairs,       ->3 o
//    OnePair,        ->2 o
//    High,           ->1 o

    unsigned int rank = 0;
    vector<card> copySampleOri = sample;
    vector<card> result;
    sort(copySampleOri.begin(), copySampleOri.end(), numPriorCmp);

    auto k1 = chkStraightFlush(copySampleOri);
    if(get<0>(k1) == true){
        result = get<1>(k1); // res값 가져옴
        sort(result.begin(),result.end(), numPriorCmp);
        rank += 9 * pow(16, 7);
        rank += pow(16, 6) * result[4].num;
    }
    else{
        auto k2 = chkFourCard(copySampleOri);
        if(get<0>(k2) == true){
            result = get<1>(k2); // res값 가져옴
            sort(result.begin(),result.end(), numPriorCmp);
            rank += 8 * pow(16, 7);
            int four = get<2>(k2); // 4장짜리 숫자
            rank += four * pow(16,6);
            int rest = four; // 남은 숫자 하나
            for(auto &e : result)
                if(rest != e.num){
                    rest = e.num;
                    break;
                }
            rank += rest * pow(16,5);
        }
        else{
            auto k3 = chkFullHouse(copySampleOri);
            if(get<0>(k3) == true){
                result = get<1>(k3);
                sort(result.begin(), result.end(), numPriorCmp);
                rank += 7 * pow(16, 7);
                int tri = get<2>(k3);
                int dou = get<3>(k3);
                rank += tri * pow(16,6);
                rank += dou * pow(16,5);
            }
            else{
                auto k4 = chkFlush(copySampleOri);
                if(get<0>(k4) == true){
                    result = get<1>(k4);
                    sort(result.begin(), result.end(), numPriorCmp);
                    rank += 6 * pow(16, 7);

                    // cnt 중복선언 하긴 했음..
                    int cnt = 0;
                    for(auto &e : result)
                        rank += e.num * pow(16, 2 + cnt++);

                }
                else{
                    auto k5 = chkStraight(copySampleOri);
                    if(get<0>(k5) == true){
                        result = get<1>(k5);
                        sort(result.begin(), result.end(), numPriorCmp);
                        rank += 5 * pow(16, 7);
                        rank += pow(16, 6) * result[4].num;
                    }
                    else{
                        auto k6 = chkTriple(copySampleOri);
                        if(get<0>(k6) == true){
                            result = get<1>(k6);
                            sort(result.begin(), result.end(), numPriorCmp);
                            rank += 4 * pow(16, 7);
                            int triple = get<2>(k6);
                            rank += pow(16,6) * triple;
                            // 일단 확인 필요
                            reverse(result.begin(),result.end());
                            int cnt = 0;
                            for(auto &e : result){
                                if(e.num != triple && cnt < 2)
                                    rank += e.num * pow(16, 5 - cnt++);
                            }
                        }
                        else{
//                            for(auto &e : copySampleOri)
//                                cout << e.num << ' ';
//                            cout << endl;
                            auto k7 = chkTwoPair(copySampleOri);
                            if(get<0>(k7) == true){
                                result = get<1>(k7);
                                sort(result.begin(),result.end(), numPriorCmp);
                                rank += 3 * pow(16, 7);
                                int num1 = get<2>(k7);

                                int num2 = get<3>(k7);
                                // 얘도 아마 중복선언..
                                int rest = get<4>(k7);
                                rank += num1 * pow(16,6);
                                rank += num2 * pow(16,5);
                                rank += rest * pow(16,4);
                            }
                            else{
                                auto k8 = chkOnePair(copySampleOri);
                                if(get<0>(k8) == true){
                                    result = get<1>(k8);
                                    sort(result.begin(),result.end(), numPriorCmp);
                                    rank += 2 * pow(16, 7);
                                    int oneN = get<2>(k8);
                                    rank += oneN * pow(16,6);
                                    reverse(result.begin(), result.end());
                                    int cnt = 0;
                                    for(auto &e : result){
                                        if(e.num != oneN && cnt < 3)
                                            rank += e.num * pow(16, 5 - cnt++);
                                    }

                                }
                                else{
                                    auto k9 = chkHigh(copySampleOri);
                                    result = copySampleOri;
                                    rank += 1 * pow(16, 7);
                                    reverse(result.begin(),result.end());
                                    int cnt = 0;
                                    for(auto &e : result){
                                        if(cnt < 5)
                                            rank += e.num * pow(16, 6 - cnt++);
                                    }
                                }

                            }

                        }

                    }

                }

            }

        }

    }

    return rank;
}


#endif //UNTITLED2_CARDCOMPARE_H
