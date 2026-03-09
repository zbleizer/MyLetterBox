#ifndef MYLETTERBOX_DATA_H
#define MYLETTERBOX_DATA_H
#include "Model.h"
#include <vector>

inline std::vector<std::string> SplitkeywordsbySpace(const std::string& s) {
    std::vector<std::string> out;
    std::istringstream iss(s);
    std::string tok;
    while (iss >> tok) {
        out.push_back(tok);
    }
    return out;
}



#endif //MYLETTERBOX_DATA_H