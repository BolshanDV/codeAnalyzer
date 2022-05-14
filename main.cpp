#include <iostream>
#include "fstream"
#include "codeAnalyzer/Analyzer.h"

using namespace std;

string readingFile() {
    ifstream file("/Users/dmitrij/CLionProjects/codeAnalyzerScript/text/correctFormatting.txt");
    string str;
    string content;
    while (getline(file, str)) {
        content += str;
        content.push_back('\n');
    };
    return content;
}

int main() {
    Analyzer analyzer;
    analyzer.codeHandler(readingFile());
    analyzer.getAnalytics();
    cout << "Анализ кода выполнен успешно!" << endl;
    return 0;
}
