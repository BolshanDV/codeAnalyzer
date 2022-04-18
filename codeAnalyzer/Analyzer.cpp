//
// Created by Дмитрий on 16.04.2022.
//

#include "Analyzer.h"
#include <iostream>

using namespace std;

void Analyzer::codeHandler(const string& text) {
    handlingSpacesBetweenOperators(text);
    handlingSpacesCurlyBraces(text);
    checkingForStringLength(text);
    checkingForMarginsBetweenBlocks(text);
    checkingVariableNames(text);
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

void Analyzer::checkingVariableNames(const string &text) {

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



Analyzer::Analyzer() = default;
