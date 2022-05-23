//
// Created by Дмитрий on 16.04.2022.
//

#include "Analyzer.h"
#include <iostream>
#include <utility>
#include <vector>
#include <regex>
#include <filesystem>
#include <cmath>
#include <cctype>

using namespace std;
using namespace std::__fs::filesystem;

void Analyzer::codeHandler(const string& text) {
    handlingSpacesBetweenOperators(text);
    handlingSpacesCurlyBraces(text);
    checkingForStringLength(text);
    checkingForMarginsBetweenBlocks(text);
    checkingVariableNames(text);
    checkingTabError(text);
    calculatingCodeQualityScore();
}



void Analyzer::handlingSpacesBetweenOperators(const string& text) {
    for (int i = text.find('{'); i < text.length() ; i++) {

        if (text[i] == '-') {
            if (text[i - 1] != ' ') {
                increaseMistakeOperators();
            }
            if (text[i + 1] != ' ') {
                increaseMistakeOperators();
            }
        }

        if (text[i] == '*' && isalpha(text[i + 1]) == 0) {
            if (text[i - 1] != ' ') {
                increaseMistakeOperators();
            }
            if (text[i + 1] != ' ') {
                increaseMistakeOperators();
            }
        }

        if (text[i] == '*' && isalpha(text[i + 1]) != 0) {
            if (text[i - 1] != ' ') {
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
            if (text[i - 1] != ' ' &&  text[i - 1] != '<') {
                increaseMistakeOperators();
            }
            if (text[i + 1] != ' ') {
                increaseMistakeOperators();
            }
        }
    }
}

void Analyzer::handlingSpacesCurlyBraces(const string &text) {

    for (int i = 1; i < text.length(); i++) {
        if ( text[i] == '{' || text[i] == '}') {
            if (text[i - 1] != ' ' && text[i] == '{') {
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
        if( i != '\n' ) {
            counter++;
        } else {
            counter = 0;
        }
        if (counter > 115) {
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
        if( i.length() < 4 && i != "int" && i != "i" && i != "j" && i != "cin" && i != "std" && i != "if") {
            increaseVariableNamesError();
        }
    }
}

void Analyzer::checkingTabError(const string &text) {
    int flagFigure = 0;
    int flagRound = 0;
    for (int i = text.find('{'); i < text.length(); i++) {
        if (text[i] == '(') {
            flagRound++;
        }
        if (text[i] == ')') {
            flagRound--;
        }
        if (text[i] == '{') {
            flagFigure++;
        }
        if (text[i] == '}') {
            flagFigure--;
        }
        string s = "";
        s =  s + text[i + 2] + text[i + 3] + text[i + 4] +  text[i + 5];

        int iter = flagFigure;

        while (iter != 0) {
            if (text[i] == '{' && flagFigure > 0 && s != "    ") {
                increaseTabError();
            }
            if (flagFigure > 0 && text[i] == ';' && flagRound == 0 && text[i + 1] != '\n' && s != "    " ) {
                increaseTabError();
            }
            iter--;
        }
    }
}

void Analyzer::getAnalytics() const {
    cout << "Ошибка табуляции: " << tabError << endl;
    cout << "Ошибка названия переменных: " << variableNamesError << endl;
    cout << "Ошибка отступов между блоками: " << marginsBlocksError << endl;
    cout << "Ошибка длины строки кода: " << stringLengthError << endl;
    cout << "Ошибка отступов между операторами и операндами: " << mistakeOperators << endl;
    cout << "Ошибка выделения блока кода: " << curlyBracesError << endl;
    cout << "--------------------------------" << endl;
    cout << "Оценка кода: " << codeQualityAssessment << endl;

}
void Analyzer::calculatingCodeQualityScore() {
    double size = file_size("/Users/dmitrij/CLionProjects/codeAnalyzerScript/text/result.txt");
    double sumError = mistakeOperators + curlyBracesError + stringLengthError + marginsBlocksError + variableNamesError + tabError;
    double i = 100 - round((sumError/size) * 10000) / 100;
    setCodeQualityAssessment(i);
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

void Analyzer::setCodeQualityAssessment(double number) {
    Analyzer::codeQualityAssessment = number;
}

Analyzer::Analyzer() = default;
