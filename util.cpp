//
// util.cpp
//
//   Code to read in song data from a specified file
//
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

//
// alpha_only
//   purpose: converts a string to lowercase and alphabetic characters
//            only. E.g., "Bang!" becomes "bang"
//   arguments: a string
//   returns: the alpha-only string
//   does: converts the string
//
string alpha_only(string s){
        ostringstream ss;
        for (size_t i=0;i<s.length();i++) {
                if (isalnum(s[i])){
                        ss << (char)(tolower(s[i]));
                }
        }
        return ss.str();
}
