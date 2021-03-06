/*
unix2dos implementation.
Copyright 2016 Sam Saint-Pettersen.

Released under the MIT License; 
see LICENSE file.
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

bool is_ascii(string filename) {
    bool ascii = false;
    int c = -1;
    ifstream f(filename.c_str());
    while((c = f.get()) != EOF && c <= 127);
    if(c == EOF) {
        ascii = true;
    }
    f.close();
    return ascii;
}

bool is_dos_eol(string filename) {
    bool dos_eol = false;
    string l;
    ifstream f;
    f.open(filename.c_str(), ios::binary);
    while(getline(f, l)) {
        for(char& c : l) {
            if (c == '\r') {
                dos_eol = true;
                break;
            }
        }
    }
    f.close();
    return dos_eol;
}

string to_dos_line_endings(string contents) {
    int i = 0;
    string dcontents;
    for(char& c : contents) {
        if(c != '\n') dcontents.push_back(c);
        else {
            dcontents.push_back('\r');
            dcontents.push_back('\n');
        } 
    }
    return dcontents;
}

int main(int argc, char const *argv[]) {
    if(is_ascii(string(argv[1])) && !is_dos_eol(string(argv[1]))) {
        ifstream i;
        stringstream contents;
        i.open(argv[1], ios::binary);
        contents << i.rdbuf();
        i.close();
        string out = to_dos_line_endings(contents.str());
        ofstream o;
        o.open(argv[1], ios::out | ios::binary);
        o << out;
        o.close();
    }
    else {
        cout << "File already has DOS line endings or is binary." << endl;
    }
    return 0;
}
