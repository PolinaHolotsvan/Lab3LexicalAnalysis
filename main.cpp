#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include <windows.h>
#include "patterns.h"

using namespace std;

class RegexAndColor {
public:
    regex lexemeRegex;
    string hexColor;
    WORD ansiColor;

    RegexAndColor(const string &regexTemplate, const string &hexColor, WORD ansiColor) {
        this->lexemeRegex = regex(regexTemplate);
        this->hexColor = hexColor;
        this->ansiColor = ansiColor;
    }
};

struct ColoredWord {
    RegexAndColor col;
    int start;
    int end;
};

vector<RegexAndColor> getPatterns() {
    return vector<RegexAndColor>{
            RegexAndColor(getMultilineComments(), "#7A7E85", 8),
            RegexAndColor(getSingleLineComment(), "#7A7E85", 8),
            RegexAndColor(getString(), "#6AAB73", 2),
            RegexAndColor(getChar(), "#6AAB73", 2),

            RegexAndColor(getTypeNames(), "#CF8E6D", 6),
            RegexAndColor(getDirectives(), "#B3AE60", 14),
            RegexAndColor(getLibraries(), "#6AAB73", 2),
            RegexAndColor(getCLibraries(), "#6AAB73", 2),
            RegexAndColor(getAdditionalLibraries(), "#6AAB73", 2),
            RegexAndColor(getReservedWords(), "#CF8E6D", 6),

            RegexAndColor(getOperators(), "#BCBEC4", 15),

            RegexAndColor(getMain(), "#56A8F5", 3),
            RegexAndColor(getFunctionDefinition(), "#56A8F5", 3),
            RegexAndColor(getFunctionCall(), "#56A8F5", 3),
            RegexAndColor(getVariable(), "#BCBEC4", 15),

            RegexAndColor(getBoolean(), "#CF8E6D", 6),
            RegexAndColor(getIntFloatScientific(), "#2AACB8", 11),
            RegexAndColor(getIntFloat(), "#2AACB8", 11),
            RegexAndColor(getHexNumbers(), "#2AACB8", 11),
            RegexAndColor(getBinaryNumbers(), "#2AACB8", 11),
            RegexAndColor(getOctalNumbers(), "#2AACB8", 11),

            RegexAndColor(getTypeDefinition(), "#6f0187", 1),
            RegexAndColor(getDelimiters(), "#BCBEC4", 15),
            RegexAndColor(getLinesAndSpaces(), "#BCBEC4", 15),
            RegexAndColor(getError(), "#FA6675", 4)
    };
}

string readFromFile(const string &fileName) {
    ifstream file(fileName);
    if (file.is_open()) {
        string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        file.close();
        return content;
    } else {
        cerr << "Unable to open file: " << fileName << endl;
        return "";
    }
}

vector<int> colorWords(const string &source) {
    vector<int> coloredText(source.length(), -1);
    auto patterns = getPatterns();

    for (int j = 0; j < patterns.size(); j++) {
        sregex_iterator iter(source.begin(), source.end(), patterns[j].lexemeRegex);
        sregex_iterator end;

        while (iter != end) {
            for (size_t i = iter->position(); i < iter->position() + iter->length(); i++) {
                if (coloredText[i] == -1)
                    coloredText[i] = j;
            }
            ++iter;
        }
    }
    return coloredText;
}

vector<ColoredWord> colorText(const string &source) {
    auto coloredWords = colorWords(source);
    auto patterns = getPatterns();

    vector<ColoredWord> coloredText = {};

    int start = 0;

    while (start < coloredWords.size()) {
        int end = start;
        while (coloredWords[start] == coloredWords[end]) end++;
        coloredText.push_back(ColoredWord{patterns[coloredWords[start]], start, end - 1});
        start = end;
    }

    return coloredText;
}

void writeToConsole(const string &source) {
    auto colors = colorText(source);

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (auto &color: colors) {
        SetConsoleTextAttribute(hConsole, color.col.ansiColor);
        cout << source.substr(color.start, color.end - color.start + 1);
    }
}

void createHtml(const string &source, const string &outFileName) {
    auto colors = colorText(source);
    ofstream outFile(outFileName);
    outFile << "<!DOCTYPE html>\n"
               "<html lang=\"en\">\n"
               "<head>\n"
               "    <meta charset=\"UTF-8\">\n"
               "    <title>Colored C++ code</title>\n"
               "</head>\n"
               "<style>\n"
               "html {\n"
               "    font-family: monospace;\n"
               "    font-size: 14px;\n"
               "    line-height: 100%;\n"
               "}\n"
               "\n"
               "span {\n"
               "    white-space: pre-wrap;\n"
               "}\n"
               "</style>\n"
               "<body bgcolor=\"#282923\">\n";

    for (auto &color: colors) {

        string word = source.substr(color.start, color.end - color.start + 1);

        if (word.find('>') != string::npos || word.find('<') != string::npos) {
            for (char letter: word)
                outFile << "<span style='color:" << color.col.hexColor << ";'>"
                        << letter << "</span>";
        } else
            outFile << "<span style='color:" << color.col.hexColor << ";'>"
                    << word << "</span>";
    }

    outFile << "</body>\n"
               "</html>";
}

int main() {
    string inputFilename = R"(input.txt)";
    string outputFilename = R"(output.html)";
    string source = readFromFile(inputFilename);
    if (!source.empty()) {
        createHtml(source, outputFilename);
        writeToConsole(source);
    }

    return 0;
}