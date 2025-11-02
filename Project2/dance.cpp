//
// Created by Kai Davey on 10/31/25.
//

#include <cassert>
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

bool isSyntacticallyCorrect (string dance);
int translateDance(string dance, string& instructions, int& badBeat);

int main() {
    string instr;
    int bad;

    // Test empty
    instr = "XXX"; bad = -1;
    assert(translateDance("", instr, bad) == 0 && instr == "" && bad == -1);
    // Test simple tap
    instr = "XXX"; bad = -1;
    assert(translateDance("l/", instr, bad) == 0 && instr == "l" && bad == -1);
    // Test freeze
    instr = "XXX"; bad = -1;
    assert(translateDance("2L//", instr, bad) == 0 && instr == "LL" && bad == -1);
    // Test invalid freeze count (< 2)
    instr = "XXX"; bad = -1;
    assert(translateDance("1L/", instr, bad) == 2 && bad == 1 && instr == "XXX");
    // Test 0 freeze count
    instr = "XXX"; bad = -1;
    assert(translateDance("0L/", instr, bad) == 2 && bad == 1 && instr == "XXX");
    // Test premature end (return 4)
    instr = "XXX"; bad = -1;
    assert(translateDance("5L//", instr, bad) == 4 && bad == 4 && instr == "XXX");
    // Test non-slash during freeze (return 3)
    instr = "XXX"; bad = -1;
    assert(translateDance("3L//u/", instr, bad) == 3 && bad == 3 && instr == "XXX");
    // Test from spec: "u//d/3r///d/"
    instr = "XXX"; bad = -1;
    assert(translateDance("u//d/3r///d/", instr, bad) == 0 && instr == "u.dRRRd" && bad == -1);
    // Test rest beats
    instr = "XXX"; bad = -1;
    assert(translateDance("///", instr, bad) == 0 && instr == "..." && bad == -1);
    // Test case insensitivity
    instr = "XXX"; bad = -1;
    assert(translateDance("U/", instr, bad) == 0 && instr == "u" && bad == -1);
    // Test two-digit freeze
    instr = "XXX"; bad = -1;
    assert(translateDance("10r//////////", instr, bad) == 0 && instr == "RRRRRRRRRR" && bad == -1);
    // Test syntax error
    instr = "XXX"; bad = -1;
    assert(translateDance("d/z//", instr, bad) == 1 && instr == "XXX" && bad == -1);
    // Test complex: "d/3r//u/" - error at beat 4
    instr = "XXX"; bad = -1;
    assert(translateDance("d/3r//u/", instr, bad) == 3 && bad == 4 && instr == "XXX");
    cerr << "All tests passed!" << endl;
    return 0;
}

bool isDirection(char letter) {
    if (letter == 'L' || letter == 'R' || letter == 'D' || letter == 'U'|| letter == 'l' || letter == 'r' || letter == 'd' || letter == 'u') {
        return true;
    }
    return false;
}

bool isSyntacticallyCorrect (string dance) {
    if (dance == "") {
        return true;
    } else {
        int i = 0;
        while (i < dance.size()) {
            if (isdigit(dance[i])) {
                if (i + 1 >= dance.size()) {
                    return false;
                }
                if (isdigit(dance[i + 1])) {
                    if (i + 2 >= dance.size() || !isDirection(dance[i + 2])) {
                        return false;
                    }
                    i += 2;
                } else {
                    i++;
                }
            }
            else if (isDirection(dance[i])) {
                if (i + 1 >= dance.size()) {
                    return false;
                }
                if (dance[i + 1] != '/') {
                    return false;
                }
                i += 2;
            }
            else if (dance[i] == '/') {
                i++;
            } else {
                return false;
            }
        }
        return true;
    }
}

int translateDance(string dance, string& instructions, int& badBeat) {
    string originalInstructions = instructions;
    int originalBadBeat = badBeat;

    bool isFreeze = false;
    int freezeCount = 0;
    int slashCount = 0;
    int beatCount = 0;
    string newInstructions;

    if (!isSyntacticallyCorrect(dance)) {
        badBeat = originalBadBeat;
        return 1;
    }

    int i = 0;
    while (i < dance.size()) {
        char curr = dance[i];

        if (isdigit(curr)) {
            if (i + 1 < dance.size() && isdigit(dance[i + 1])) {
                string combined = string(1, curr) + string(1, dance[i + 1]);
                freezeCount = stoi(combined);
                i += 2;
            } else {
                freezeCount = stoi(string(1, curr));
                i++;
            }
            if (freezeCount < 2) {
                badBeat = beatCount + 1;
                return 2;
            }
            isFreeze = true;
        }

        else if (isDirection(curr)) {
            if (isFreeze) {
                i++;
                while (i < dance.size() && dance[i] == '/' && slashCount < freezeCount) {
                    slashCount++;
                    i++;
                }
                if (freezeCount != slashCount) {
                    badBeat = beatCount + slashCount + 1;
                    if (i >= dance.size()) {
                        return 4;
                    } else {
                        return 3;
                    }
                }
                for (int j = 0; j < freezeCount; j++) {
                    newInstructions += static_cast<char>(toupper(static_cast<unsigned char>(curr)));
                    beatCount++;
                }
                freezeCount = 0;
                slashCount = 0;
                isFreeze = false;
            } else {
                newInstructions += static_cast<char>(tolower(static_cast<unsigned char>(curr)));
                beatCount++;
                i+= 2;
            }
        }

        else if (curr == '/') {
            newInstructions += ".";
            beatCount++;
            i++;
        }
    }
    badBeat = originalBadBeat;
    instructions = newInstructions;
    return 0;
}