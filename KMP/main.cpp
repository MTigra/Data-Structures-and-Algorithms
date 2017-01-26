#include <iostream>
#include "kmp.cpp"

int main() {
    string s1 = "dsjfhsjkhkfsasabaababaabaababaababa";
    string s2 = "abaababaabaababaababa";
    vector<int>* v = find_substrings(s1, s2);
    for (int i = 0; i < v->size(); ++i) {
        cout << v->at(i) << endl;
    }
    return 0;
}