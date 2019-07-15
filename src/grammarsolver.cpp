/**
 * Grammar Solver assignment for CS106B at Stanford Summer Session 2019
 * Author: Kevin Li
 * Description: This program randomly generate a symbol (e.g sentence, expression, ...) based on
 * a set of grammar rules
 */
#include "grammarsolver.h"
#include "map.h"
#include "strlib.h"
#include <iostream>
#include "random.h"
using namespace std;

Vector<string> grammarGenerate(istream& input, string symbol, int times);
string grammarGenerateHelper(string symbol, const Map<string, Vector<string>>& grammars);

/**
 * @brief Generate a type of symbol a number of times based on input grammar rules
 * @param input the inputted grammar rules to follow
 * @param symbol the symbol to generate
 * @param times the number of times to generate
 * @return a Vector containing all randomly generated symbols
 */
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

/**
 * @brief Helper function for generating symbols recursively
 * @param symbol the symbol to generate
 * @param grammars the grammar rules to follow
 * @return a string containg the symbol generated
 */
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
