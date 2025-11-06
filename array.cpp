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

}