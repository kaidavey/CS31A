//
// Created by Kai Davey on 11/5/25.
//

// all fns that take ints return -1 if given bad input
// size param of array is how many to check. let x be size, check array from [0,x]

#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int repeat(string a[], int n);
int detectMatch(const string a[], int n, string target);
int detectMax(const string a[], int n);
int circleLeft(string a[], int n, int pos);
int enumerateRuns(const string a[], int n);
int flip(string a[], int n);
int detectDifference(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);

int main() {

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
    if (n1 < 0 || n2 < 0) return -1;


}