#include <bits/stdc++.h>
#define INF 999999999
using namespace std;

bool DBG = false;

unordered_map<string, int> numberValue;
int nrNums = 88;
string nums[] = {"I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X", "XI", "XII", "XIII", "XIV", "XV", "XVI", "XVII", "XVIII", "XIX", "XX", "XXI", "XXII", "XXIII", "XXIV", "XXV", "XXVI", "XXVII", "XXVIII", "XXIX", "XXX", "XXXI", "XXXII", "XXXIII", "XXXIV", "XXXV", "XXXVI", "XXXVII", "XXXVIII", "XXXIX", "XL", "XLI", "XLII", "XLIII", "XLIV", "XLV", "XLVI", "XLVII", "XLVIII", "XLIX", "L", "LI", "LII", "LIII", "LIV", "LV", "LVI", "LVII", "LVIII", "LIX", "LX", "LXI", "LXII", "LXIII", "LXIV", "LXV", "LXVI", "LXVII", "LXVIII", "LXIX", "LXX", "LXXI", "LXXII", "LXXIII", "LXXIV", "LXXV", "LXXVI", "LXXVII", "LXXVIII", "LXXIX", "LXXX", "LXXXI", "LXXXII", "LXXXIII", "LXXXIV", "LXXXV", "LXXXVI", "LXXXVII", "LXXXVIII", "LXXXIX" };

bool validNumChr(char ch) {
    return ch == 'I' || ch == 'V' || ch == 'X' || ch == 'L';
}

bool validNumRepr(const string& str, int& res) {
    if (!numberValue.count(str)) {
        return false;
    }
    res = numberValue[str];
    return true;
}

bool validNum(const string& str, int& i, int& res) {
    if (!validNumChr(str[i])) {
        return false;
    }
    string numr;
    numr.push_back(str[i]);
    while (i + 1 < str.size() && validNumChr(str[i+1])) {
        ++i;
        numr.push_back(str[i]);
    }
    return validNumRepr(numr, res);
}

bool valid(const string& str) {
    int lst = INF;
    int act = 0;
    int sign = 1;
    int equals = 0;
    for (int i=0;i<str.size();++i) {
        if (str[i] == '=') {
            ++equals;
        }
        if (equals > 1) {
            return false;
        }
    }
    for (int i=0;i<str.size();++i) {
        if (str[i] == '=') {
            if (i + 1 == str.size() || i == 0) {
                return false;
            }
            if (lst != INF) {
                if (lst != act) {
                    return false;
                }
            }
            lst = act;
            sign = 1;
            act = 0;
            continue;
        } else if (str[i] == '-' || str[i] == '+') {
            if (i == 0 || str[i-1] == '=') {
                return false;
            }
            int num = 1;
            while (i + 1 < str.size() && (str[i+1] == '-' || str[i+1] == '+' || str[i+1] == '=')) {
                ++num;
                ++i;
            }
            if (num > 1 || i + 1 == str.size()) {
                return false;
            }
            if (str[i] == '-') {
                sign = 2;
            } else {
                sign = 1;
            }
        } else {
            int num = 0;
            if (!validNum(str, i, num)) {
                return false;
            }
            if (sign == 1) {
                act += num;
            } else {
                act -= num;
            }
        }
    }
    if (lst == INF) {
        return false;
    }
    return lst == act;
}

void init() {
    for (int i=1;i<=nrNums;++i) {
        numberValue[nums[i-1]] = i;
    }
}

vector<string> tests = {
    "V-XV=I-XI",
    "X-XX=I-XI",
    "II-I=II-I",
    "II-II=I-I",
    "III-I-I=I"
};

int main()
{
    /*freopen("out.txt","w",stdout);
    ifstream fin("roman.txt");
    int nr = 1;
    string str;
    cout << "string nums[] = {";
    while (fin >> str) {
        cout << "\"" << str << "\", ";
    }
    cout << "};\n";
    return 0;*/
    init();
    unordered_set<string> afterRem;
    unordered_set<string> afterAdd;
    string s;
    cin>>s;

    vector<pair<char,char>> repl;
    repl.push_back(make_pair('I', '-'));
    repl.push_back(make_pair('L', '+'));
    repl.push_back(make_pair('=', '+'));
    repl.push_back(make_pair('V', 'X'));

    vector<char> vanishes;
    vanishes.push_back('I');
    vanishes.push_back('-');

    vector<pair<char,char>> extractions;
    extractions.push_back(make_pair('L','I'));
    extractions.push_back(make_pair('+','I'));
    extractions.push_back(make_pair('+','-'));
    extractions.push_back(make_pair('=','-'));

    string before = "";
    string after = s;

    for (int i=0;i<s.size();++i) {
        after.erase(after.begin());

        for (auto x : repl) {
            if (s[i] == x.first) {
                afterAdd.insert(before + string{x.second} + after);
            } else if (s[i] == x.second) {
                afterAdd.insert(before + string{x.first} + after);
            }
        }

        for (auto x : vanishes) {
            if (s[i] == x) {
                afterRem.insert(before + after);
            }
        }

        for (auto x : extractions) {
            if (s[i] == x.first) {
                afterRem.insert(before + string{x.second} + after);
            }
        }

        before.push_back(s[i]);
    }

    vector<pair<char,char>> insertions;
    insertions.push_back(make_pair('I', 'L'));
    insertions.push_back(make_pair('I', '+'));
    insertions.push_back(make_pair('-', '='));
    insertions.push_back(make_pair('-', '+'));

    vector<char> layed;
    layed.push_back('I');
    layed.push_back('-');

    for (auto& str : afterRem) {
        before = "";
        after = str;

        for (auto x : layed) {
            afterAdd.insert(before + string{x} + after);
        }

        for (int i=0;i<str.size();++i) {
            after.erase(after.begin());
            for (auto x : insertions) {
                if (x.first == str[i]) {
                    afterAdd.insert(before + string{x.second} + after);
                }
            }
            before.push_back(str[i]);
            for (auto x : layed) {
                afterAdd.insert(before + string{x} + after);
            }
        }
    }

    for (auto& str : afterAdd) {
        if (valid(str)) {
            cout << str << '\n';
        } else {
            if (DBG) {
                cout << str << '\n';
            }
        }
    }
    return 0;
}
