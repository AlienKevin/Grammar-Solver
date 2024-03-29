/**
 * Grammar Solver assignment for CS106B at Stanford Summer Session 2019
 * Author: Kevin Li
 * Description: This program randomly generate a symbol (e.g sentence, expression, ...) based on
 * a set of grammar rules. There are several rules of the BNF parser used by this program:
 * 1. Terminals must be surrounded by single quotes (') or double quotes (")
 * 2. Spaces are NOT permitted in terminals because it is used to split tokens in a rule
 * 3. No whitespace is inserted by default between symbols
 * 4. To add a single space between symbols, use <sp> special reserved non-terminal
 * 5. You can include comments in your grammar text file but they must be on their
 *    own lines and starts with a semicolon ";".
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
        if (stringContains(line, "::=") && !startsWith(line, ";")) { // exclude comments and empty lines
            string nonterminal = trim(stringSplit(line, "::=")[0]);
            Vector<string> rules = stringSplit(trim(stringSplit(line, "::=")[1]), "|");
            if (grammars.containsKey(nonterminal)) { // duplicated rules
                throw "Error: Duplicated rules.";
            } else {
                grammars[nonterminal] = rules;
            }
        }
    }
    cout << grammars << endl;
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
        if ((startsWith(symbol, '"') && endsWith(symbol, '"')) ||
                (startsWith(symbol, "'") && endsWith(symbol, "'"))) { // double-quoted string
//            cout << symbol << endl;
            return symbol.substr(1, symbol.size() - 2);
        } else if (symbol == "<sp>") { // special space symbol, " " is unusable because space is used to split tokens
            return " ";
        } else {
            throw "Unrecognized symbol: " + symbol;
        }
    } else {
        Vector<string> rules = grammars[symbol];
        string randomRule = trim(randomElement(rules));
        Vector<string> tokens = stringSplit(randomRule, " ");
        string result = "";
        for (string token : tokens) {
            if (token != "") {
                result += grammarGenerateHelper(token, grammars);
            }
        }
        return trim(result);
    }
}
