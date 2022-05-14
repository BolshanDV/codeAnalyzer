//
// Created by Дмитрий on 16.04.2022.
//

#ifndef CODEANALYZER_ANALYZER_H
#define CODEANALYZER_ANALYZER_H
#include <iostream>
#include <vector>

using namespace std;

class Analyzer {
private:
    int mistakeOperators = 0;
    int curlyBracesError = 0;
    int stringLengthError = 0;
    int marginsBlocksError = 0;
    int variableNamesError = 0;
    int tabError = 0;
    double codeQualityAssessment{};
public:
    void setCodeQualityAssessment(double codeQualityAssessment);

public:
    void getAnalytics() const;

public:
    Analyzer();
    void codeHandler(const string& text);

private:
    vector<string> split(const string &s, const string &delimiter);
    void increaseMistakeOperators();
    void increaseCurlyBracesError();
    void increaseStringLengthError();
    void increaseMarginsBlocksError();
    void increaseVariableNamesError();
    void increaseTabError();
    void handlingSpacesBetweenOperators(const string& text);
    void handlingSpacesCurlyBraces(const string& text);
    void checkingForStringLength(const string& text);
    void checkingForMarginsBetweenBlocks(const string& text);
    void checkingVariableNames(const string& text);
    void checkingTabError(const string& text);
    void calculatingCodeQualityScore();
};


#endif //CODEANALYZER_ANALYZER_H
