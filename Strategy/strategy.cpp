//
// Created by Nikita Marinosyan on 07.11.16.
//

#include <iostream>
#include <fstream>
#include "string"

using namespace std;
class Strategy {
private:
    int N = 100010;
    char c;
    string s;
    int left[N]; // Minimal number of  river-crosses required
                 // to get to the i interval on the left bank
    int before_left[N]; // Previous interval on the left bank from which there is
                        // no supplies
    int right[N]; // Minimal number of  river-crosses required
                  // to get to the i interval on the right bank
    int before_r[N]; // Previous interval on the right bank from which there is
                     // no supplies
    int a[N];
    int b[N];
    int i, j, n;
public:
    void solve() {
        x[0] = 0; //Pupils are on the
    }
};
