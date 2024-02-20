#include <bits/stdc++.h>

using namespace std;

unsigned int start = clock();

int checkbits = 5;

int CountCheckBits(string& s){  
    // count the maximum power of 2 that is <= than number of bits
    // set of bits is splitted on parts with 32 bits in them, but this check is important if total amount of bits !% 32
    int res = 2;
    for (int i = 4, j = 3; i < s.length(); i = pow(2, j), j++) {
        res++;
    }
    return res;
}

string lay1 = "", lay2 = "", lay3 = "", lay4 = "", lay5 = "";
short *  intlay1, *intlay2, *intlay3, *intlay4, *intlay5; // CHANGED

void BuildLays(string& s){
    // builds lays like "10101...", "011001100.." and further to decode the Hamming code
    for (int i = 0; i < s.length(); i++){
        lay1 += to_string((i+1)%2);
    }
    printf("%s\n", lay1.c_str());

    if (checkbits >= 2) {
        for (int i = 0; i < s.length() / 2; i++)
            lay2.push_back('0');
        for (int i = 1; i < s.length(); i = i + 4)
            lay2.insert(i, "11");
        if (lay2.length() > lay1.length()) {
            lay2.pop_back();
        } else if (lay2.length() < lay1.length()) {
            lay2.push_back('0');
        }
        printf("%s\n", lay2.c_str());
    }

    if (checkbits >= 3) {
        lay3 = s;
        replace(lay3.begin(), lay3.end(), '1', '0');

        for (int i = 3; i < s.length(); i = i + 8) {
            lay3.insert(i, "1111");
        }
        if (lay3.length() > lay2.length()) {
            int difference = lay3.length() - lay2.length();
            if (lay3.length() >= lay2.length())
            lay3 = lay3.substr(0, lay3.length() - difference);
        }
        printf("%s\n", lay3.c_str());
    }

    if (checkbits >= 4) {
        lay4 = s;
        replace(lay4.begin(), lay4.end(), '1', '0');

        for (int i = 7; i < s.length(); i = i + 16) {
            lay4.insert(i, "11111111");
        }
        if (lay4.length() > lay3.length()) {
            int difference = lay4.length() - lay3.length();
            if (lay4.length() >= lay3.length())
            lay4 = lay4.substr(0, lay4.length() - difference);
        }
        printf("%s\n", lay4.c_str());
    }

    if (checkbits >= 5) {
        lay5 = s;
        replace(lay5.begin(), lay5.end(), '1', '0');

        for (int i = 15; i < s.length(); i = i + 32) {
            lay5.insert(i, "1111111111111111");
        }
        if (lay5.length() > lay4.length()) {
            int difference = lay5.length() - lay4.length();
            if (lay5.length() >= lay4.length())
            lay5 = lay5.substr(0, lay5.length() - difference);
        }
        printf("%s\n", lay5.c_str());
    }
}

short* StringToInt(string& s){
    // converts the main string of 0 and 1 to list of 0 and 1
    short* res = new short[s.length()];
    for (int i = 0; i < s.length(); i++) res[i] = s[i] - '0';
    return res;
}

void LaysToInt(){
    // converts lays strings of 0 and 1 to lists of 0 and 1
    intlay1 = new short [lay1.length()];
    intlay2 = new short [ lay2.length()];
    intlay3 = new short [lay3.length()];
    intlay4 = new short [lay4.length()];
    intlay5 = new short [lay5.length()];
    if (checkbits > 0) {
        for (int i = 0; i < lay1.length(); i++) {
            intlay1[i] = lay1[i] - '0';
        }
    }
    if (checkbits >= 1) {
        for (int i = 0; i < lay2.length(); i++) {
            intlay2[i] = lay2[i] - '0';
        }
    }
    if (checkbits >= 3) {
        for (int i = 0; i < lay3.length(); i++) {
            intlay3[i] = lay3[i] - '0';
        }
    }
    if (checkbits >= 4) {
        for (int i = 0; i < lay4.length(); i++) {
            intlay4[i] = lay4[i] - '0';
        }
    }
    if (checkbits >= 5) {
        for (int i = 0; i < lay5.length(); i++) {
            intlay5[i] = lay5[i] - '0';
        }
    }
}

char* CalcCheckBits(string& s, short* bits){
    // counts the right check bits 
    char* res = new char[checkbits];
    int t1 = 0, t2 = 0, t3 = 0, t4 = 0, t5 = 0, t;

    for (int i = 1; i < s.length(); i++) {
        t1 += bits[i] * intlay1[i];
    }
    t = t1 % 2;
    if (t) res[0] = '1';
    else res[0] = '0';
    printf("%s %c\n", "Check bit 1 =", res[0]);

    if (checkbits >= 1) {
        for (int i = 2; i < s.length(); i++) {
            t2 += bits[i] & intlay2[i];
        }
        t = t2 % 2;
        if (t) res[1] = '1';
        else res[1] = '0';
        printf("%s %c\n", "Check bit 2 =", res[1]);
    }

    if (checkbits >= 3) {
        for (int i = 4; i < s.length(); i++) {
            t3 += bits[i] & intlay3[i];
        }
        t = t3 % 2;
        if (t) res[2] = '1';
        else res[2] = '0';
        printf("%s %c\n", "Check bit 3 =", res[2]);
    }

    if (checkbits >= 4) {
        for (int i = 8; i < s.length(); i++) {
            t4 += bits[i] & intlay4[i];
        }
        t = t4 % 2;
        if (t) res[3] = '1';
        else res[3] = '0';
        printf("%s %c\n", "Check bit 4 =", res[3]);
    }

    if (checkbits >= 5) {
        for (int i = 16; i < s.length(); i++) {
            t5 += bits[i] & intlay5[i];
        }
        t = t5 % 2;
        if (t) res[4] = '1';
        else res[4] = '0';
        printf("%s %c\n", "Check bit 5 =", res[4]);
    }

    return res;
}

int FindMistake(string& s, short* bits){
    // find a mistaked bit, his position
    char* foundbits = CalcCheckBits(s, bits);
    int res = 0;

    if (foundbits[0] != s[0]) {
        res += 1;
    }
    if (checkbits >= 1) {
        if (foundbits[1] != s[1]) {
            res += 2;
        }
    }
    if (checkbits >= 3) {
        if (foundbits[2] != s[3]) {
            res += 4;
        }
    }
    if (checkbits >= 4) {
        if (foundbits[3] != s[7]) {
            res += 8;
        }
    }
    if (checkbits >= 5) {
        if (foundbits[4] != s[15]) {
            res += 16;
        }
    }
    return res;
}

void CorrectMistake(string& s, short* bits){
    // corrects the wrong bit in the main string
    int pos = FindMistake(s, bits);
    if (pos != 0){
        if (s[pos-1] == '1') s.replace(pos-1, 1, "0");
        else s.replace(pos-1, 1, "1");
        printf("%s %d\n", "Wrong bit is the bit", pos);
    }else printf("%s\n", "No wrong bits");
}

void Print(string& s, string& prev){
    cout << "Was: " << prev << endl;
    cout << "Now: " << s << endl;

    string res = "";
    printf("%s", "Without check bits: ");
    for (int i = 0; i < s.length(); i++){
        if (i == 0 || i == 1 || i == 3 || i == 7 || i == 15) continue;
        else res += s[i];
    }
    printf("%s\n", res.c_str());
}

void hamming(string &s){
    // the main function - unites all upper functions to a one
    string prev;
    prev = s;
    lay1 = ""; lay2 = ""; lay3 = ""; lay4 = ""; lay5 = "";
   	delete[] intlay1; delete[] intlay2; delete[] intlay3; delete[] intlay4; delete[] intlay5;
    printf("%s\n", s.c_str());
    checkbits = CountCheckBits(s);

    BuildLays(s);
    LaysToInt();
    short* mainbits = StringToInt(s);
    CorrectMistake(s, mainbits);

    Print(s, prev);
    printf("\n%s\n\n", "----------------------------------\n");
}

int main() {

    ifstream in;
    in.open("testpic.txt");
    string s = "", prev = "", total = "";
    in >> total;
    in.close();

    int k = 1;
    for (int i = 0; i < total.length(); i++){
        if (k > 31){
            hamming(s);
            s = "";
            k = 0;
        }
        k++;
        s += total[i];
    }
    hamming(s);
    unsigned int end = clock();
    printf("%s %u %s\n", "The programm worked for", end - start, "ms");
    printf("%s %f %s\n", "The programm worked for", (end - start)/1000.0, "s");
    
    return 0;
}