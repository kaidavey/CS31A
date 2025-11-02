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

    // Empty string
    instr = "ex"; bad = -1;
    assert(translateDance("", instr, bad) == 0 && instr == "" && bad == -1);

    // Simple tap
    instr = "ex"; bad = -1;
    assert(translateDance("l/", instr, bad) == 0 && instr == "l" && bad == -1);

    // Rest beat (just slash)
    instr = "ex"; bad = -1;
    assert(translateDance("/", instr, bad) == 0 && instr == "." && bad == -1);

    // Valid freeze with two beats
    instr = "ex"; bad = -1;
    assert(translateDance("2L//", instr, bad) == 0 && instr == "LL" && bad == -1);

    // Spec example
    instr = "ex"; bad = -1;
    assert(translateDance("u//d/3r///d/", instr, bad) == 0 && instr == "u.dRRRd" && bad == -1);

    // Return 1 for syntax error
    instr = "ex"; bad = -1;
    assert(translateDance("L", instr, bad) == 1 && instr == "ex" && bad == -1);

    // Return 2 for freeze count too small
    instr = "ex"; bad = -1;
    assert(translateDance("1L/", instr, bad) == 2 && bad == 1 && instr == "ex");

    // Return 3 for interruption during freeze
    instr = "ex"; bad = -1;
    assert(translateDance("3L//u/", instr, bad) == 3 && bad == 3 && instr == "ex");

    // Return 4 for ending freeze early
    instr = "ex"; bad = -1;
    assert(translateDance("5r//", instr, bad) == 4 && bad == 3 && instr == "ex");

    // Two-digit freeze
    instr = "ex"; bad = -1;
    assert(translateDance("10r//////////", instr, bad) == 0 && instr == "RRRRRRRRRR" && bad == -1);

    // badBeat preserved?
    instr = "ex"; bad = 999;
    assert(translateDance("l/", instr, bad) == 0 && instr == "l" && bad == 999);

    // Instructions preserved on error (return 3)
    instr = "preserve"; bad = -1;
    assert(translateDance("3L//u/", instr, bad) == 3 && bad == 3 && instr == "preserve");

    // Return 3 for interrupting freeze
    instr = "ex"; bad = -1;
    assert(translateDance("d/3r//u/", instr, bad) == 3 && bad == 4 && instr == "ex");

    // All types of beats
    instr = "ex"; bad = -1;
    assert(translateDance("2l//r//3u///d/", instr, bad) == 0 && instr == "LLr.UUUd" && bad == -1);

    cout << "All tests passed" << endl;
}

// Helper function takes in a char and returns true if it's a valid direction, false if not
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
        while (i < dance.size()) { // Go through the string
            if (isdigit(dance[i])) {
                if (i + 1 >= dance.size()) { // If current char is a digit and there's no char after it, return false
                    return false;
                }
                if (isdigit(dance[i + 1])) { // If current char is a digit and there's another digit after it,
                    if (i + 2 >= dance.size() || !isDirection(dance[i + 2])) { // return false if there's no char after the digits, or the next char is not a direction
                        return false;
                    }
                    i += 2; // If there's no issues, increment the index past the two digits
                } else {
                    if (!isDirection(dance[i + 1])) { // If the char after single digit is not a direction, return false
                        return false;
                    }
                    i++; // If there's only one digit, increment the index past it
                }
            }
            else if (isDirection(dance[i])) {
                if (i + 1 >= dance.size() || dance[i + 1] != '/') { // If current char is a direction and there's no char after it or the next char isn't a slash, return false
                    return false;
                }
                i += 2; // If there's no issues, increment past the direction and slash
            }
            else if (dance[i] == '/') {
                i++; // If current char is just a slash, increment past it
            } else {
                return false; // If current char is anything other than a digit, direction, or slash, return false
            }
        }
        return true; // If there's no failing points, the string is syntactically correct
    }
}

int translateDance(string dance, string& instructions, int& badBeat) {
    // Keep track of original value
    int originalBadBeat = badBeat;

    bool isFreeze = false;
    int freezeCount = 0;
    int slashCount = 0;
    int beatCount = 0;
    string newInstructions;

    // If dance isn't syntactically correct, return 1
    if (!isSyntacticallyCorrect(dance)) {
        return 1;
    }

    int i = 0;
    while (i < dance.size()) { // Go through the string
        char curr = dance[i]; // For readability, curr is set to the current char

        if (isdigit(curr)) { // If the curr is a digit and...
            if (i + 1 < dance.size() && isdigit(dance[i + 1])) { // the next char is a digit,
                string combined = string(1, curr) + string(1, dance[i + 1]);
                freezeCount = stoi(combined); // establish the freeze count as that two-digit number
                i += 2; // Increment the index past the two digits
            } else {
                freezeCount = stoi(string(1, curr)); // Otherwise, establish the freeze count as the digit
                i++; // Increment past the digit
            }
            if (freezeCount < 2) { // If the freeze count is less than two,
                badBeat = beatCount + 1; // set badBeat to the count of beats before + 1 (the current one)
                return 2;
            }
            isFreeze = true; // Turn isFreeze on
        }

        else if (isDirection(curr)) { // If curr is a direction...
            if (isFreeze) { // and a freeze is in place,
                i++; // move the index to the slash after the direction

                // Count how many slashes there are after the direction
                // as long as index doesn't go off the end,
                // and until there are as many slashes as freeze count
                while (i < dance.size() && dance[i] == '/' && slashCount < freezeCount) {
                    slashCount++;
                    i++; // Increment i each time there's a slash
                }
                if (freezeCount != slashCount) { // If there are fewer slashes than required,
                    badBeat = beatCount + slashCount + 1; // return the previous num of beats, plus the num of slashes (beats), plus 1 (the current beat it failed on)

                    // If i reached the end without right num of slashes, return 4
                    // Otherwise, the freeze was interrupted so return 3
                    if (i >= dance.size()) {
                        return 4;
                    } else {
                        return 3;
                    }
                }
                // Add freezeCount num of directions to instructions
                for (int j = 0; j < freezeCount; j++) {
                    newInstructions += static_cast<char>(toupper(static_cast<unsigned char>(curr)));
                    beatCount++; // increment beat count each time
                }
                // Reset everything
                freezeCount = 0;
                slashCount = 0;
                isFreeze = false;
            } else { // add the direction to the instructions (because we know a '/' comes after from isSyntacticallyCorrect)
                newInstructions += static_cast<char>(tolower(static_cast<unsigned char>(curr)));
                beatCount++;
                i+= 2; // Increment past the direction and slash
            }
        }

        else if (curr == '/') { // If curr is just a slash,
            newInstructions += "."; // add a '.'
            beatCount++; // increment beat
            i++; // and move index past slash
        }
    }
    badBeat = originalBadBeat; // before returning successful, reestablish badBeat to original value
    instructions = newInstructions; // set instructions
    return 0; // return successful
}