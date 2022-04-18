//
// Created by Дмитрий on 16.04.2022.
//

#ifndef CODEANALYZER_ANALYZER_H
#define CODEANALYZER_ANALYZER_H
#include <iostream>

using namespace std;

class Analyzer {
private:
    int mistakeOperators = 0;
    int curlyBracesError = 0;
    int stringLengthError = 0;
    int marginsBlocksError = 0;
    int variableNamesError = 0;

public:
    Analyzer();

public:
    void increaseMistakeOperators();
    void increaseCurlyBracesError();
    void increaseStringLengthError();
    void increaseMarginsBlocksError();
    void increaseVariableNamesError();
    void codeHandler(const string& text);
    void handlingSpacesBetweenOperators(const string& text);
    void handlingSpacesCurlyBraces(const string& text);
    void checkingForStringLength(const string& text);
    void checkingForMarginsBetweenBlocks(const string& text);
    void checkingVariableNames(const string& text);
};


#endif //CODEANALYZER_ANALYZER_H
