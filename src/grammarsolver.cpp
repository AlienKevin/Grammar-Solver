#include "grammarsolver.h"
#include "map.h"
#include "strlib.h"
#include <iostream>
#include "random.h"
using namespace std;

Vector<string> grammarGenerate(istream& input, string symbol, int times);
string grammarGenerateHelper(string symbol, const Map<string, Vector<string>>& grammars);

Vector<string> grammarGenerate(istream& input, string symbol, int times) {
    if (times == 0) {
        Vector<string> emptyVector;
        return emptyVector;
    }
    // load input grammars into map
    Map<string, Vector<string>> grammars;
    string line;
    while (getline(input, line)) {
        string nonterminal = stringSplit(line, "::=")[0];
        Vector<string> rules = stringSplit(stringSplit(line, "::=")[1], "|");
        if (grammars.containsKey(nonterminal)) { // duplicated rules
            throw "Error: Duplicated rules.";
        } else {
            grammars[nonterminal] = rules;
        }
    }

    // generate random symbol
    Vector<string> results;
    for (int i = 0; i < times; i++) {
        results.add(grammarGenerateHelper(symbol, grammars));
    }
    return results;
}

string grammarGenerateHelper(string symbol, const Map<string, Vector<string>>& grammars) {
    if (symbol == "") {
        throw "Error: Empty symbol. Must be a terminal or non-terminal.";
    }
    if (!grammars.containsKey(symbol)) { // not a nonterminal
        return symbol;
    } else {
        Vector<string> rules = grammars[symbol];
        string randomRule = randomElement(rules);
        Vector<string> tokens = stringSplit(randomRule, " ");
        string result = "";
        for (string token : tokens) {
            result += grammarGenerateHelper(token, grammars) + " ";
        }
        return trim(result);
    }
}
