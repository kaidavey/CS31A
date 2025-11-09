//
// Created by Kai Davey on 11/5/25.
//

// all fns that take ints return -1 if given bad input
// size param of array is how many to check. let x be size, check array from [0,x]

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int repeat(string a[], int n);
int detectMatch(const string a[], int n, string target);
int detectMax(const string a[], int n);
int circleLeft(string a[], int n, int pos);
int enumerateRuns(const string a[], int n);
int flip(string a[], int n);
int detectDifference(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int detectAny(const string a1[], int n1, const string a2[], int n2);
int split(string a[], int n, string splitter);

int main() {
    string a[4] = { "ma", "can", "tu", "do" };
    assert(repeat(a, 4) == 4 && a[0] == "mama" && a[3] == "dodo");

    string b[7] = { "will", "yoshi", "shohei", "freddie", "", "max", "shohei" };
    assert(detectMatch(b, 7, "shohei") == 2);
    assert(detectMatch(b, 2, "shohei") == -1);
    assert(detectMax(b, 7) == 1);

    string c[3] = { "max", "shohei", "tommy" };
    assert(detectAny(b, 7, c, 3) == 2);
    assert(flip(c, 3) == 3 && c[0] == "tommy" && c[2] == "max");

    string d[4] = { "will", "yoshi", "freddie", "max" };
    assert(detectDifference(b, 4, d, 4) == 2);
    assert(circleLeft(d, 4, 1) == 1 && d[1] == "freddie" && d[3] == "yoshi");

    string e[4] = { "shohei", "freddie", "", "max" };
    assert(subsequence(b, 7, e, 4) == 2);

    string f[5] = { "max", "max", "max", "yoshi", "yoshi" };
    assert(enumerateRuns(f, 5) == 2);

    assert(split(b, 7, "shohei") == 3);

    cout << "All tests succeeded" << endl;
}

int repeat(string a[], int n) {
    if (n < 0) return -1;

    for (int i = 0; i < n; i++) {
        a[i] = a[i] + a[i];
    }
    return n;
}

int detectMatch(const string a[], int n, string target) {
    for (int i = 0; i < n; i++) {
        if (a[i] == target) {
            return i;
        }
    }
    return -1;
}

int detectMax(const string a[], int n) {
    int max = -1;

    for (int i = 0, max = 0; i < n; i++) {
        if (a[i] >= a[max]) {
            max = i;
        }
    }
    return max;
}

int circleLeft(string a[], int n, int pos) {
    if (pos > n - 1 || n < 0) return -1;

    string temp = a[pos];

    for (int i = pos; i < n - 1; i++) {
        a[i] = a[i + 1];
    }
    a[n - 1] = temp;
    return pos;
}

int enumerateRuns(const string a[], int n) {
    if (n < 0) return -1;
    if (n == 1) return 1;

    int runs = 0;
    string curr = a[0];
    for (int i = 0; i < n; i++) {
        if (a[i] != curr) {
            runs++;
        }
        curr = a[i];
    }
    return runs;
}

int flip(string a[], int n) {
    if (n < 0) return - 1;

    string temp[n];
    int i;
    int j;

    for (i = n - 1, j = 0; i >= 0; i--, j++) {
        temp[j] = a[i];
    }

    for (i = 0; i < n; i++) {
        a[i] = temp[i];
    }
    return n;
}

int detectDifference(const string a1[], int n1, const string a2[], int n2) {
    if (n1 < 0 || n2 < 0) return -1;

    int smallest = n1 < n2 ? n1 : n2;

    int i = 0;
    while (i < n1 && i < n2) {
        if (a1[i] != a2[i]) {
            return i;
        }
        i++;
    }
    return smallest;
}

int subsequence(const string a1[], int n1, const string a2[], int n2) {
    int i;
    int j;
    int foundIndex = -1;
    outer: for (i = 0, j = 0; i < n1; i++) {
        if (a1[i] == a2[j]) {
            int tempIndex = i;
            while (tempIndex < n1 && j < n2) {
                if (a1[i] == a2[j]) {
                    tempIndex++;
                    j++;
                } else {
                    j = 0;
                    foundIndex = -1;
                    goto outer;
                }
            }
            foundIndex = i;
            break;
        }
    }
    return foundIndex;
}

int detectAny(const string a1[], int n1, const string a2[], int n2) {
    for (int i = 0; i < n1; i++) {
        string curr = a1[i];
        for (int j = 0; j < n2; j++) {
            if (curr == a2[j]) {
                return i;
            }
        }
    }
    return -1;
}

int split(string a[], int n, string splitter) {
    bool swapped;

    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            string curr = a[j];
            string next = a[j + 1];
            if (curr > splitter && next < splitter) {
                a[j] = next;
                a[j + 1] = curr;
                swapped = true;
            }
        }

        if (!swapped) {
            break;
        }
    }

    int returnVal = n;
    for (int i = 0; i < n; i++) {
        if (a[i] > splitter) {
            returnVal = i;
            break;
        }
    }
    return returnVal;
}