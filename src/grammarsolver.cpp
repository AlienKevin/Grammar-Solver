#include "grammarsolver.h"
#include "map.h"
#include "strlib.h"
#include <iostream>
using namespace std;

Vector<string> grammarGenerate(istream& input, string symbol, int times) {
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
    cout << grammars << endl;
    Vector<string> v;   // this is only here so it will compile
    return v;           // this is only here so it will compile
}
