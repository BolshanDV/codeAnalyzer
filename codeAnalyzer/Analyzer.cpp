//
// Created by Дмитрий on 16.04.2022.
//

#include "Analyzer.h"
#include <iostream>
#include <utility>
#include <vector>
#include <regex>

using namespace std;

void Analyzer::codeHandler(const string& text) {
    handlingSpacesBetweenOperators(text);
    handlingSpacesCurlyBraces(text);
    checkingForStringLength(text);
    checkingForMarginsBetweenBlocks(text);
    checkingVariableNames(text);
    checkingTabError(text);
}



void Analyzer::handlingSpacesBetweenOperators(const string& text) {
    for (int i = 1; i < text.length() ; i++) {

        if (text[i] == '*' || text[i] == '/' || text[i] == '-'){
            if (text[i - 1] != ' ') {
                increaseMistakeOperators();
            }
            if (text[i + 1] != ' ') {
                increaseMistakeOperators();
            }
        }

        if (text[i] == '<' && text[i + 1] == '<') {
            if (text[i - 1] != ' ') {
                increaseMistakeOperators();
            }
            if (text[i + 2] != ' ') {
                increaseMistakeOperators();
            }
        }

        if (text[i] == '>' && text[i + 1] == '>') {
            if (text[i - 1] != ' ') {
                increaseMistakeOperators();
            }
            if (text[i + 2] != ' ') {
                increaseMistakeOperators();
            }
        }

        if (text[i] == '<' && text[i - 1] != '<' && text[i + 1] != '<' && text[i + 1] != '=') {
            if (text[i - 1] != ' ') {
                increaseMistakeOperators();
            }
            if (text[i + 1] != ' ') {
                increaseMistakeOperators();
            }
        }

//        if (text[i] == '+' && text[i + 1] == '+') {
//            if (text[i + 2] != ' ') {
//                increaseMistakeOperators();
//            }
//        }

        if (text[i] == '+' && text[i + 1] != '+' && text[i - 1] != '+' ) {
            if (text[i - 1] != ' ') {
                increaseMistakeOperators();
            }
            if (text[i + 1] != ' ') {
                increaseMistakeOperators();
            }
        }

        if(text[i] == '=') {
            if (text[i - 1] == '<') {
                if(text[i - 2] != ' ') {
                    increaseMistakeOperators();
                }
                if (text[i + 1] != ' ') {
                    increaseMistakeOperators();
                }
            } else {
                if (text[i - 1] != ' ') {
                    increaseMistakeOperators();
                }
                if (text[i + 1] != ' ') {
                    increaseMistakeOperators();
                }
            }
        }

    }
}

void Analyzer::handlingSpacesCurlyBraces(const string &text) {

    for (int i = 1; i < text.length(); i++) {
        if ( text[i] == '{' || text[i] == '}') {
            if (text[i - 1] != ' ') {
                increaseCurlyBracesError();
            }
            if (text[i + 1] != '\n') {
                increaseCurlyBracesError();
            }
        }
    }

}

void Analyzer::checkingForStringLength(const string &text) {
    int counter = 0;
    for (char i : text) {
        if( i != '\n') {
            counter++;
        } else {
            counter = 0;
        }
        if (counter >= 100) {
            counter = 0;
            increaseStringLengthError();
        }


    }
}

void Analyzer::checkingForMarginsBetweenBlocks(const string &text) {
    for (int i = 0; i < text.length(); ++i) {
        if( text[i] == '}' && text[i + 1] != '\n' ) {
            increaseMarginsBlocksError();
        }
    }
}

string& leftTrim(string& str)
{
    string chars = "/ ";

    str.erase(0, str.find_first_not_of(chars));
    return str;
}

vector<string> Analyzer::split(const string &s, const string &delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

void Analyzer::checkingVariableNames(const string &text) {
    string newText = regex_replace(text,regex(R"([^A-Za-z0-9])"), "/ ");

    vector<string> arr = split(newText, "/");
    vector<string> newArr;
    for (auto & i : arr) {
        if (i != " ") {
            newArr.push_back(regex_replace(i,regex(" "), ""));
        }
    }
    for (auto & i : newArr) {
        if( i.length() < 4 && i != "int" && i != "i" && i != "j" && i != "cin" && i != "std") {
            increaseVariableNamesError();
        }
    }
}

void Analyzer::checkingTabError(const string &text) {
    int flagFigure = 0;
    int flagRound = 0;
    for (char i : text) {
        if (i == '(') {
            flagRound++;
        }
        if (i == ')') {
            flagRound--;
        }
        if (i == '{') {
            flagFigure++;
        }
        if (i == '}') {
            flagFigure--;
        }
        if (flagFigure > 0 && i == ';' && flagRound == 0) {
            increaseTabError();
        }
    }
}

void Analyzer::increaseMistakeOperators() {
    this -> mistakeOperators++;
}

void Analyzer::increaseCurlyBracesError() {
    this -> curlyBracesError++;
}

void Analyzer::increaseStringLengthError() {
    this->stringLengthError++;
}

void Analyzer::increaseMarginsBlocksError() {
    this->marginsBlocksError++;
}

void Analyzer::increaseVariableNamesError() {
    this->variableNamesError++;
}

void Analyzer::increaseTabError() {
    this->tabError++;
}

void Analyzer::getAnalytics() const {
    cout << "Ошибка табуляции: " << tabError << endl;
    cout << "Ошибка названия переменных: " << variableNamesError << endl;
    cout << "Ошибка отступов между блоками: " << marginsBlocksError << endl;
    cout << "Ошибка длины строки кода: " << stringLengthError << endl;
    cout << "Ошибка отступов между операторами и операндами: " << mistakeOperators << endl;
    cout << "Ошибка выделения блока кода: " << curlyBracesError << endl;
    cout << "--------------------------------" << endl;
    cout << "Оценка кода: " <<   "будет" << endl;

}

Analyzer::Analyzer() = default;
