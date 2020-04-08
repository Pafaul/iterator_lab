#ifndef MISC_H
#define MISC_H
#include <iostream>

class Misc {
public:
    Misc(){};
    static bool startsWith(std::string s, std::string sub) {
        bool flag = true;
        for (int i = 0; i < sub.length() && flag; i++)
        {
            if (s[i] != sub[i]) flag = false;
        }
        return flag;
    }
    static bool matchCount(std::string s, std::string sub) {
        int count = 0;
        for (int i = 0; i < sub.length(); i++)
        {
            if (s[i] == sub[i])
                count++;
            else
                break;
        }
        return count;
    }
};

#endif // MISC_H
