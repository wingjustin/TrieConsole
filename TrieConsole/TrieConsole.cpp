// TrieConsole.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <string>
#include<conio.h>
#include "Tree.h"

#define NORMAL_STYLE (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED)
#define HIGHLINE_STYLE (BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_BLUE & FOREGROUND_GREEN & FOREGROUND_RED)

using namespace std;
using namespace Tree;

int main()
{
    Trie* trie = new Trie();

    char operKey = 'W';
    do {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        //title
        SetConsoleTextAttribute(hConsole, HIGHLINE_STYLE ^ BACKGROUND_RED);
        cout << "Trie Word Searching";
        SetConsoleTextAttribute(hConsole, NORMAL_STYLE);
        cout << endl << "------------------------------------------------------------------------------------------" << endl;
        string inputWord = "";
        char temp;

        if (operKey == 'w' || operKey == 'W') {
            trie->Clear();

            cout << "Please input Words ";
            SetConsoleTextAttribute(hConsole, HIGHLINE_STYLE);
            cout << "( Pattern = word1 word2 ... wordN )";
            SetConsoleTextAttribute(hConsole, NORMAL_STYLE);
            cout << " : " << "\n";

            //insert words
            inputWord = "";
            temp;
            while (cin.get(temp) && temp != '\n') {
                if ((temp == ' ') && (static_cast<int>(inputWord.length()) != 0)) {
                    trie->AddWord(inputWord);
                    inputWord = "";
                }
                else if (trie->IsValidChar(temp))
                    inputWord += temp;
            }
            if (static_cast<int>(inputWord.length()) != 0) {
                trie->AddWord(inputWord);
                inputWord = "";
            }

            cout << endl;
        }
        cout << "Please input ";
        SetConsoleTextAttribute(hConsole, HIGHLINE_STYLE);
        cout << "Prefix";
        SetConsoleTextAttribute(hConsole, NORMAL_STYLE);
        cout << " : " << "\n";
        SetConsoleTextAttribute(hConsole, HIGHLINE_STYLE);

        inputWord = "";
        temp = '\0';
        while (cin.get(temp) && temp != '\n') {
            inputWord += temp;
        }

        string prefix = inputWord;

        SetConsoleTextAttribute(hConsole, NORMAL_STYLE);

        cout << "------------------------------------------------------------------------------------------" << endl;

        //find words match the prefix
        string* foundWords;
        int count = trie->GetWords(prefix, foundWords);

        //show the count of matchs
        cout << "Found ";
        SetConsoleTextAttribute(hConsole, NORMAL_STYLE ^ FOREGROUND_BLUE);
        cout << to_string(count);
        SetConsoleTextAttribute(hConsole, NORMAL_STYLE);
        cout << " Results : " << "\n";

        //show where the words are
        if (count > 0) {
            SetConsoleTextAttribute(hConsole, HIGHLINE_STYLE | FOREGROUND_RED);
            cout << foundWords[0];
            SetConsoleTextAttribute(hConsole, NORMAL_STYLE);
            for (int i = 1; i < count; i++) {
                cout << " ";
                SetConsoleTextAttribute(hConsole, HIGHLINE_STYLE | FOREGROUND_RED);
                cout << foundWords[i];
                SetConsoleTextAttribute(hConsole, NORMAL_STYLE);
            }
        }

        delete[] foundWords;

        cout << endl << endl;

        //check continue
        cout << "Press Any Key to start from Prefix; \"W\" start from Word; \"E\" for Exit : ";
        operKey = _getch();
        cout << "\n=========================================================================" << endl;
    } while (operKey != 'e' && operKey != 'E');

    delete trie;
    
    system("pause");
}

// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的提示: 
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案
