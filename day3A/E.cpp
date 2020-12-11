#include <bits/stdc++.h>
using namespace std;
string text;
vector<string> tokens;
bool match(int startIndex, vector<string> tks) {
    for (int i=0;i<tks.size();++i) {
        if (tokens[i+startIndex] != tks[i]) {
            return false;
        }
    }
    return true;
}
unordered_map<string,int>digits;
unordered_map<string,int>nums;
void init() {
    digits["zero"] = 0;
    digits["one"] = 1;
    digits["two"] = 2;
    digits["three"] = 3;
    digits["four"] = 4;
    digits["five"] = 5;
    digits["six"] = 6;
    digits["seven"] = 7;
    digits["eight"] = 8;
    digits["nine"] = 9;
    digits["ten"] = 10;
    digits["eleven"] = 11;
    digits["twelve"] = 12;
    digits["thirteen"] = 13;
    digits["fourteen"] = 14;
    digits["fifteen"] = 15;
    digits["sixteen"] = 16;
    digits["seventeen"] = 17;
    digits["eighteen"] = 18;
    digits["nineteen"] = 19;

    nums["twenty"] = 20;
    nums["thirty"] = 30;
    nums["forty"] = 40;
    nums["fifty"] = 50;
    nums["sixty"] = 60;
    nums["seventy"] = 70;
    nums["eighty"] = 80;
    nums["ninety"] = 90;
}
int parseNum(int& index) {
    if (digits.count(tokens[index])) {
        return digits[tokens[index]];
    }
    int res = nums[tokens[index]];
    ++index;
    if (digits.count(tokens[index])) {
        res += digits[tokens[index]];
    } else {
        --index;
    }
    return res;
}
string numToStr(int num) {
    if (num == 0) {
        return string("0");
    }
    string ans;
    while (num) {
        ans.push_back(char(num%10+'0'));
        num /= 10;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}
int main()
{
    //freopen("out.txt","w",stdout);
    init();
    char c;
    while (scanf("%c",&c) != EOF) {
        if (c != '\n' && c != '\t') {
            text.push_back(c);
        } else {
            text.push_back(' ');
        }
    }
    char strStart = 0;
    string token;
    for (auto x : text) {
        if (x == ' ') {
            if (strStart) {
                token.push_back(x);
                continue;
            }
            if (token.size()) {
                tokens.push_back(token);
                token.clear();
            }
        } else if (x == '\'') {
            if (strStart == '\'') {
                tokens.push_back(token);
                token.clear();
                strStart = 0;
            } else if (strStart == '\"') {
                token.push_back(x);
            } else {
                strStart = '\'';
            }
        } else if (x == '\"') {
            if (strStart == '\"') {
                tokens.push_back(token);
                token.clear();
                strStart = 0;
            } else if (strStart == '\'') {
                token.push_back(x);
            } else {
                strStart = '\"';
            }
        } else if (x == '.') {
            if (strStart) {
                token.push_back('.');
                continue;
            }
            if (token.size()) {
                tokens.push_back(token);
                token.clear();
            }
            tokens.push_back(".");
        } else {
            token.push_back(x);
        }
    }
    for (int i=0;i<=10;++i) {
        tokens.push_back("");
    }
    string lineStr;
    int lastType = -1;
    int printFlag = -1;
    // -1 nothing
    // 0 print the next .. lines
    // 1 empty
    // 2 print next lines
    // 3
    int flag = -1;
    int numOfLines = -1;
    // 0 - the first line / the next line
    // 2 - the next ... lines part 1
    // 3 - the next ... lines part 2
    // 4 - first line contains -> parse
    for (int i=0;i<tokens.size();++i) {
        if (tokens[i] == "") {
            continue;
        }
        if (tokens[i] == ".") {
            lastType = -1;
            if (printFlag == -1) {
                continue;
            }
            if (printFlag == 0) {
                for (int j=1;j<=numOfLines;++j) {
                    cout << lineStr << '\n';
                }
                lineStr.clear();
                printFlag = -1;
                numOfLines = -1;
                continue;
            }
            if (printFlag == 1) {
                cout << '\n';
                printFlag = -1;
                continue;
            }
            if (printFlag == 2) {
                cout << lineStr << '\n';
                lineStr.clear();
                printFlag = -1;
                continue;
            }
            if (printFlag == 3) {
                for (int j=1;j<=numOfLines;++j) {
                    cout << '\n';
                }
                printFlag = -1;
                numOfLines = -1;
                continue;
            }
            continue;
        }
        if (match(i, vector<string>({"The", "first", "line"}))) {
            i += 2;
            flag = 0;
            continue;
        }
        if (match(i, vector<string>({"The", "next", "line"}))) {
            i += 2;
            flag = 0;
            continue;
        }
        if (match(i, vector<string>({"The", "next"}))) {
            ++i;
            flag = 2;
            continue;
        }
        if (flag == 0) {
            if (match(i, vector<string>({"is", "empty"}))) {
                printFlag = 1;
                flag = -1;
                ++i;
                continue;
            } else if (match(i, vector<string>({"contains"}))) {
                flag = 4;
                printFlag = 2;
                continue;
            }
        } else if (flag == 2) {
            numOfLines = parseNum(i);
            flag = 3;
            continue;
        } else if (flag == 3) {
            if (match(i, vector<string>({"are", "empty"}))) {
                printFlag = 3;
                continue;
            } else if (match(i, vector<string>({"contain"}))) {
                printFlag = 0;
                flag = 4;
                continue;
            }
        } else if (flag == 4) {
            if (match(i, vector<string>({"number"}))) {
                if (lastType == 1 || lastType == 2) {
                    lineStr.push_back(' ');
                }
                ++i;
                int num = parseNum(i);
                lineStr += numToStr(num);
                lastType = 1;
                continue;
            } else if (match(i, vector<string>({"string"}))) {
                if (lastType == 1) {
                    lineStr.push_back(' ');
                }
                ++i;
                lineStr += tokens[i];
                lastType = 2;
                continue;
            } else if (match(i, vector<string>({"space"}))) {
                lineStr.push_back(' ');
                lastType = -1;
                continue;
            } else if (match(i, vector<string>({"followed", "by"}))) {
                ++i;
                continue;
            } else {
                int repetitions = parseNum(i);
                ++i;
                if (match(i, vector<string>({"numbers"}))) {
                    ++i;
                    int nm = parseNum(i);
                    string strNum = numToStr(nm);
                    if (lastType == 1 || lastType == 2) {
                        lineStr.push_back(' ');
                    }
                    for (int j=1;j<repetitions;++j) {
                        lineStr += strNum;
                        lineStr.push_back(' ');
                    }
                    lineStr += strNum;
                    lastType = 1;
                    continue;
                } else if (match(i, vector<string>({"strings"}))) {
                    ++i;
                    if (lastType == 1) {
                        lineStr.push_back(' ');
                    }
                    for (int j=1;j<=repetitions;++j) {
                        lineStr += tokens[i];
                    }
                    lastType = 2;
                    continue;
                } else if (match(i, vector<string>({"spaces"}))) {
                    for (int j=1;j<=repetitions;++j) {
                        lineStr.push_back(' ');
                    }
                    lastType = -1;
                    continue;
                } else {
                    int breakk = 1 / 0;
                }
            }
        }
    }
    return 0;
}
