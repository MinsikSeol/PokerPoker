//
// Created by user on 2022-07-17.
//



#include <bits/stdc++.h>
#include "card.h"
#include "cardCompare.h"
#include "handScoreMulti.h"

#define endl '\n'
#define all(v) (v).begin(),(v).end()
typedef long long ll;
#define repa(i, a, b) for(ll i = a; i <= b; ++ i)
#define repb(i, a, b) for(ll i = a; i >= b; -- i)
#define fixD(d, x) fixed << setprecision(d) << x
#define findIdxK(v, k) find(all(v),k) - (v).begin() + 1
using namespace std;

vector<string> shpCandidate = {"SPADE", "DIAMOND", "HEART", "CLUB"};
vector<string> numCandidate = {"2","3","4","5","6","7","8","9","10","J","Q","K","A"};
string inputA, inputB;
unsigned int myScore;

// ostream 묶음
template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& data){
    for (const T& t : data)
        out << t << '\n';
    return out;
}
template <typename T>
void printCurrent(const T& data) {
    for(const auto &x : data)
        cout << x;
    cout << '\n';
}

int chkRealRandom[15];
int iterationNum;
int people;
vector<card> myCardSet(7);

vector<card> deck;
card status[7];
int permutationDepth;
ll rowAllCase;

vector<vector<card>> allCase;
vector<vector<unsigned int>> allCaseScore;

int TurnRiver;
double winCount, tieCount, winRate, tieRate;


double permutation(int m, int n){
    if(n == 1)
        return m;
    else
        return m * permutation(m - 1, n - 1);
}


void countWinTie(int sta, int end, unsigned int myScore, ofstream& writer){

    winCount = 0;
    tieCount = 0;

    repa(i, sta, end){
        bool potenWin = true ;
        bool potenTie = false ;
        repa(j, 0, people-2){
            if(myScore < allCaseScore[i][j]){
                potenWin = false;
                potenTie = false;
                break;
            } else if(myScore > allCaseScore[i][j]){ // 이김
                continue;
            } else if(myScore == allCaseScore[i][j]){ // 비김
                potenTie = true;
                potenWin = false;
            }
        }
        if(potenWin == true){ // 이김
            winCount ++;
        }
        else if(potenTie == true){ // 비김
            tieCount ++;
        }
    }

}

void toUpper(string& str){
    repa(i, 0, str.length()-1)
        str[i] = toupper(str[i]);
}

void statusInput(const int& i){
    cin >> inputA >> inputB;
    if(inputA == "0" && inputB == "0"){
        status[i].shp = 0;
        status[i].num = 0;
        return;
    }
    toUpper(inputA);
    toUpper(inputB);
    while(find(all(shpCandidate), inputA) == shpCandidate.end() || find(all(numCandidate), inputB) == numCandidate.end()){
        cout << "입력이 잘못되었습니다. 다시 입력해주세요: " <<  endl;
        cin >> inputA >> inputB;
        if(inputA == "0" && inputB == "0"){
            status[i].shp = 0;
            status[i].num = 0;
            return;
        }
        toUpper(inputA);
        toUpper(inputB);
    }
    status[i].shp = findIdxK(shpCandidate, inputA);
    status[i].num = findIdxK(numCandidate, inputB) + 1;

}

void initialSetting(ifstream& reader){

    cout << "          < Welcome to 포커 입력기 >          " << endl;
    cout << "--------------   [입력 시작]   --------------" << endl;
    cout << "모양 : SPADE / DIAMOND / HEART / CLUB 중 하나로,\n"
            "숫자 : A 2 3 4 5 6 7 8 9 10 J Q K 중 하나로 입력.\n" << endl;
    cout << "   입력 방식 : [모양] [숫자] ex( spade A )" << endl;
    cout << "   생략할 카드는 [반드시  0  0  으로] 입력 !" << endl;
    cout << endl;

    cout << "< 내 패 2장 입력 >" << endl;
    cout << "Hand 1번째 장:";
    statusInput(5);

    cout << "Hand 2번째 장:";
    statusInput(6);

    cout << "< Flop 3장 입력 >" << endl;
    repa(i, 0, 2){
        cout << "Flop " << i + 1 << "번째 장:";
        statusInput(i);
    }

    cout << "< Turn 카드 입력 >:";
    statusInput(3);
    cout << "< River 카드 입력 >:";
    statusInput(4);

    cout << "[ 자신 포함 인원수 ]:";
    cin >> people;

    cout << "[ set Iteration ]:";
    cin >> iterationNum;

}


int main(){
//    std::cout << std::filesystem::current_path().string() << endl;
    clock_t start, end;
    double timeTaken;
    ifstream reader;
    ofstream writer;
    shared_ptr<void> deferReader;
    shared_ptr<void> deferWriter;

//    reader.open("C:\\Users\\USER\\CLionProjects\\untitled\\input.txt");
//    writer.open("C:\\Users\\USER\\CLionProjects\\untitled\\output.txt");
//
//    if (reader.is_open() && writer.is_open()){
//        deferReader = shared_ptr<void>(nullptr, [&reader](...){ reader.close(); });
//        deferWriter = shared_ptr<void>(nullptr, [&writer](...){ writer.close(); });
//    }
//    else{
//        perror("not opened");
//        exit(3);
//    }

    deck = vector<card> (52);
    int idx = 0;
    repa(i, 1, 4){
        repa(j, 2, 14){
            deck[idx].shp = i;
            deck[idx].num = j;
            ++ idx;
        }
    }

    initialSetting(reader);


    // status[0 ~ 6] (flop부터 turn, river까지 내 패까지 deck에서 제거)
    repa(i, 0, 6){
        auto itr = find(all(deck), card(status[i].shp, status[i].num));
        // 없으면 없는대로 못지운다. 편하게 지정해도 됨
        if(itr != deck.end())
            deck.erase(itr);
    }
    permutationDepth = deck.size() - 43;
//    cout << "deck size:" << deck.size() << endl;
//    cout << "depth:" << permutationDepth << endl;


    start = clock(); //시간 측정 시작

    rowAllCase = iterationNum;
    srand((unsigned int)time(NULL));


//    cout  << "rowAllCase:" << rowAllCase << endl;
    allCase = vector<vector<card>> (rowAllCase,vector<card>(7 + 2*(people-2)));
    int known = 4 - permutationDepth;

// 7장으로 구성된 가능 무작위 카드덱 경우 생성 시작
    vector<card> statusStorage;
    repa(k, 0, 6){
        if(status[k].shp !=0)
            statusStorage.push_back(status[k]);

    }
    int statusStorageLength = statusStorage.size() ;
    repa(i, 0, rowAllCase -1){
        repa(j, 0, 2 + known)
        allCase[i][j] = status[j];

        repa(j, 3 + known, 4 +2*(people-1)){
            allCase[i][j].num = rand() % 13 + 2;
            allCase[i][j].shp = rand() % 4 + 1;
            while(find(all(statusStorage), allCase[i][j]) != statusStorage.end()){
                allCase[i][j].num = rand() % 13 + 2;
                allCase[i][j].shp = rand() % 4 + 1;
                chkRealRandom[allCase[i][j].shp] ++;
            }
            statusStorage.push_back(allCase[i][j]);
        }
        statusStorage.resize(statusStorageLength);

    }
// 7장으로 구성된 가능 무작위 카드덱 경우 생성 끝

    cout << "핸드스코어 계산중..." << endl;

    // rowAllCase는 현재부로 변경되었다.
    rowAllCase = allCase.size();
//    cout  << "New rowAllCase:" << rowAllCase << endl;

    allCaseScore = vector<vector<unsigned int>> (rowAllCase,vector<unsigned int>(people-1));
    //////멀티 스레드 개수 입력란///////
    ccExecution(4);

    cout << "이길 확률 계산중..." << endl;


    repa(i, 0, 2)
        myCardSet[i] = status[i];
    repa(i, 5, 6)
        myCardSet[i] = status[i];

    if(known == 0){ // 알려진게 없음
        TurnRiver = 1; //random iteration 이므로 반복은 1가지
        int z = 0;
        while(z < rowAllCase){
            repa(i, 3, 4){
                myCardSet[i] = allCase[z][i];
            }
            myScore = handScore(myCardSet);

            countWinTie(z, z + TurnRiver-1, myScore, writer);

            winRate += winCount;
            tieRate += tieCount;
            z += TurnRiver;
        }

//        cout << "winCount: " << winRate << endl;
//        cout << "tieCount: " << tieRate << endl;
        winRate = winRate / (iterationNum);
        tieRate = tieRate / (iterationNum);
        cout << "winRate: " << fixD(1, winRate * 100) << "%" << endl;
        cout << "tieRate: " << fixD(1, tieRate * 100) << "%" << endl;
    }
    else if (known == 1){ // turn 만 나옴
        TurnRiver = 1; //random iteration 이므로 반복은 1가지
        repa(i, 3, 3){
            myCardSet[i] = status[i];
        }

        int z = 0;
        while(z < rowAllCase){
            repa(i, 4, 4){
                myCardSet[i] = allCase[z][i];
            }
            myScore = handScore(myCardSet);

            countWinTie(z, z + TurnRiver-1, myScore, writer);

            winRate += winCount;
            tieRate += tieCount;
            z += TurnRiver;
        }

//        cout << "winCount: " << winRate << endl;
//        cout << "tieCount: " << tieRate << endl;
        winRate = winRate / (iterationNum);
        tieRate = tieRate / (iterationNum);
        cout << "winRate: " << fixD(1, winRate * 100) << "%" << endl;
        cout << "tieRate: " << fixD(1, tieRate * 100) << "%" << endl;
    }
    else{   // knwon = 2 -> turn river 다 앎
        TurnRiver = 1; //random iteration 이므로 반복은 1가지
        repa(i, 3, 4){
            myCardSet[i] = status[i];
        }
        int z = 0;

        while(z < rowAllCase){
            myScore = handScore(myCardSet);

            countWinTie(z, z + TurnRiver-1, myScore, writer);

            winRate += winCount;
            tieRate += tieCount;
            z += TurnRiver;
        }

//        cout << "winCount: " << winRate << endl;
//        cout << "tieCount: " << tieRate << endl;
        winRate = winRate / (iterationNum);
        tieRate = tieRate / (iterationNum);
        cout << "winRate: " << fixD(1, winRate * 100) << "%" << endl;
        cout << "tieRate: " << fixD(1, tieRate * 100) << "%" << endl;
    }

    end = clock(); // 시간 측정 끝
    timeTaken = (double)(end-start);
    cout << "timeTaken : "<<timeTaken << " ms" << endl;

    return 0;
}
