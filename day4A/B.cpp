#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <queue>
#include <utility>
#include <set>
#include <unordered_set>
#define nmax 24
#define byte unsigned char
#define ll long long

// #define LOAD_DEBUG_INFO

using namespace std;

const ll BASE = 2;
ll pw[nmax];

int n = nmax;
vector<byte> board;

#ifdef LOAD_DEBUG_INFO
int printMat[7][7];
void readPrintInfo() {
    ifstream fin("cells.txt");
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            fin >> printMat[i][j];
        }
    }
    fin.close();
}
void debugBoard(const vector<byte>& board) {
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            if (printMat[i][j] == -1) {
                cout << '0';
            }
            else {
                cout << char(board[printMat[i][j]] + '0');
            }
        }
        cout << '\n';
    }
}
void debugBoard(const int& board) {
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            if (printMat[i][j] == -1) {
                cout << '0';
            }
            else {
                if (board & (1 << printMat[i][j])) {
                    cout << '1';
                }
                else {
                    cout << '0';
                }
            }
        }
        cout << '\n';
    }
}
#endif

int lines[4][7] = {
    {
        0, 2, 6, 11, 15, 20, 22
    },
    {
        1, 3, 8, 12, 17, 21, 23
    },
    {
        4, 5, 6, 7, 8, 9, 10
    },
    {
        13, 14, 15, 16, 17, 18, 19
    }
};

int circle[8] = {
    6, 7, 8, 11, 12, 15, 16, 17
};

ll getHash(int value, const vector<byte>& board) {
    ll res = 0;
    for (int i = 0; i < n; ++i) {
        if (board[i] == value) {
            res = res + pw[i];
        }
    }
    return res;
}

void fillCircle(int value, int& board) {
    for (int i = 0; i < 8; ++i) {
        board |= (1 << circle[i]);
    }
}

void printt(const vector<byte>& board) {
    for (int i = 0; i < n; ++i) {
        cout << board[i];
    }
    cout << '\n';
}

vector<byte> emptyBoard() {
    vector<byte> emptyB;
    for (int i = 0; i < n; ++i) {
        emptyB.push_back(0);
    }
    return emptyB;
}

void resetBoard(vector<byte>& board) {
    board = emptyBoard();
}

void resetFillCircle(int value, int& board) {
    board = 0;
    fillCircle(value, board);
}

struct Mov;

vector<Mov> moves;

struct Mov {
    char letter;
    int line;
    char reverseMove;
    void (*apply)(int, int&);
    Mov(char letter, int line, char reverseMove, void (*apply)(int, int&)) {
        this->letter = letter;
        this->line = line;
        this->reverseMove = reverseMove;
        this->apply = apply;
    }

    char applyMov(int& board) {
        this->apply(this->line, board);
        return this->letter;
    }

    char applyRevMov(int& board) {
        this->apply(this->line, board);
        return this->reverseMove;
    }
};

void setBit(int& v, int bit) {
    v |= (1 << bit);
}

void resetBit(int& v, int bit) {
    v &= ((~0) ^ (1 << bit));
}

int valueOfBit(int v, int bit) {
    return (v & (1 << bit)) != 0;
}

void applyShiftUp(int line, int& board) {
    int aux = valueOfBit(board, lines[line][0]), b;
    for (int i = 0; i < 6; ++i) {
        b = valueOfBit(board, lines[line][i + 1]);
        if (b) {
            setBit(board, lines[line][i]);
        }
        else {
            resetBit(board, lines[line][i]);
        }
    }
    if (aux) {
        setBit(board, lines[line][6]);
    }
    else {
        resetBit(board, lines[line][6]);
    }
}

void applyShiftDown(int line, int& board) {
    int aux = valueOfBit(board, lines[line][6]), b;
    for (int i = 6; i > 0; --i) {
        b = valueOfBit(board, lines[line][i - 1]);
        if (b) {
            setBit(board, lines[line][i]);
        }
        else {
            resetBit(board, lines[line][i]);
        }
    }
    if (aux) {
        setBit(board, lines[line][0]);
    }
    else {
        resetBit(board, lines[line][0]);
    }
}

void init() {
    moves.push_back(Mov('A', 0, 'F', applyShiftUp)); // 0
    moves.push_back(Mov('B', 1, 'E', applyShiftUp)); // 1
    moves.push_back(Mov('C', 2, 'H', applyShiftDown));// 2
    moves.push_back(Mov('D', 3, 'G', applyShiftDown));// 3
    moves.push_back(Mov('E', 1, 'B', applyShiftDown));// 4
    moves.push_back(Mov('F', 0, 'A', applyShiftDown));// 5
    moves.push_back(Mov('G', 3, 'D', applyShiftUp)); // 6
    moves.push_back(Mov('H', 2, 'C', applyShiftUp)); // 7

    sort(moves.begin(), moves.end(), [](const Mov& m1, const Mov& m2) {
        return m1.reverseMove > m2.reverseMove;
        });

    pw[0] = 1LL;
    for (int i = 1; i < n; ++i) {
        pw[i] = pw[i - 1] * BASE;
    }
}

unordered_map<int, pair<int, pair<int, char>>> mp;

void preCalc() {
    queue<pair<int, int>> q;
    int ini = 0;
    fillCircle(1, ini);
    mp[ini] = make_pair(-1, make_pair(0, '\0'));
    q.push(make_pair(ini, 0));

    //int num = 0;

    while (!q.empty()) {
        auto act = q.front();
        q.pop();

        /*debugBoard(act);
        cout << mp[act].first << ' ' << mp[act].second << '\n';
        ++num;
        if (num == 9) {
            exit(0);
        }*/
        for (int i = 0; i < 8; ++i) {
            int v = act.first;
            char move = moves[i].applyRevMov(v);
            if (!mp.count(v)) {
                mp[v] = make_pair(act.first, make_pair(act.second + 1, move));
                q.push(make_pair(v, act.second + 1));
            }
            else if (mp[v].second.first == act.second + 1 && mp[v].second.second > move) {
                mp[v] = make_pair(act.first, make_pair(act.second + 1, move));
            }
        }
    }
}

string getAns(int hsh) {
    string res("");

    while (mp[hsh].first != -1) {
        int nxt = mp[hsh].first;
        res.push_back(mp[hsh].second.second);
        hsh = nxt;
    }

    return res;
}

int main()
{
#ifdef LOAD_DEBUG_INFO
    readPrintInfo();
#endif // LOAD_DEBUG_INFO
    init();
    preCalc();
    board = emptyBoard();
    while (cin >> board[0]) {
        board[0] -= '0';
        if (!board[0]) {
            break;
        }
        for (int i = 1; i < n; ++i) {
            cin >> board[i];
            board[i] -= '0';
        }

        // debugBoard(board);

        ll h1 = getHash(1, board);
        ll h2 = getHash(2, board);
        ll h3 = getHash(3, board);
        vector<pair<string, int>> ans;
        ans.push_back(make_pair(getAns(h1), 1));
        ans.push_back(make_pair(getAns(h2), 2));
        ans.push_back(make_pair(getAns(h3), 3));
        sort(ans.begin(), ans.end(), [](const pair<string, int>& p1, const pair<string, int>& p2) {
            if (p1.first.size() == p2.first.size()) {
                return p1.first < p2.first;
            }
            return p1.first.size() < p2.first.size();
            });
        if (ans[0].first == "") {
            cout << "No moves needed\n";
        }
        else {
            cout << ans[0].first << '\n';
        }
        cout << ans[0].second << '\n';
    }
    return 0;
}