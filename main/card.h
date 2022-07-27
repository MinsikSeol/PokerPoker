//
// Created by user on 2022-07-03.
//

#ifndef UNTITLED2_CARD_H
#define UNTITLED2_CARD_H

char NumberChr[13] = {'2','3','4','5','6','7','8','9','T','J','Q','K','A'};
// card's num : [0 ~ 12]
int NumberInt[13] = {2,3,4,5,6,7,8,9,10,11,12,13,14};

struct card {
    // shape : club[1] heart[2] diamond[3] spade[4]
    int shp;
    int num;
//    card(){
//
//    }
//    ~card(){
//
//    }
    card(int a = 0, int b = 0) : shp(a), num(b){}

    bool operator<(const card& Other) const {
        if(num == Other.num)
            return shp < Other.shp;
        return num < Other.num;
    }
    bool operator==(const card& Other) const {
        return shp == Other.shp && num == Other.num;
    }


};

std::ostream& operator<<(std::ostream& out, const card& C){
    std::string s[4] = {"(  Club   )", "(  Heart  )", "( Diamond )", "(  Spade  )"};
    out << "shp:" << C.shp << s[C.shp - 1] << ", num:" << C.num;
    return out;
}

std::ofstream& operator<<(std::ofstream& out, const card& C){
    std::string s[4] = {"(  Club   )", "(  Heart  )", "( Diamond )", "(  Spade  )"};
    out << "shp:" << C.shp << s[C.shp - 1] << ", num:" << C.num;
    return out;
}


#endif //UNTITLED2_CARD_H
