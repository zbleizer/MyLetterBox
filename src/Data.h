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

class CSVParser {
public:
    static std::vector<std::shared_ptr<Media>> parseMovie(const std::string& file);

    static std::vector<std::shared_ptr<Media>> parseSeries(const std::string& file);

};


#endif //MYLETTERBOX_DATA_H