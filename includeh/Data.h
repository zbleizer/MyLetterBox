#ifndef MYLETTERBOX_DATA_H
#define MYLETTERBOX_DATA_H
#include "Model.h"
#include <vector>
#include <string>
#include <memory>
#include <variant>
#include <optional>

std::vector<std::string> SplitkeywordsbySpace(const std::string& s);

class CSVParser {
public:
    static std::vector<std::shared_ptr<Media>> parseMovie(const std::string& filename);
    static std::vector<std::shared_ptr<Media>> parseSeries(const std::string& filename);
};

struct Genre {
    std::string genre;
};
struct Keyword {
    std::string keyword;
};
using Search = std::variant<Genre, Keyword>;

class Database {
    std::vector<std::shared_ptr<Media>> lib;
public:
    void loadMovies(const std::string& file);
    void loadSeries(const std::string& file);
    void loadAll(const std::string& movFile, const std::string& serFile);

    const std::vector<std::shared_ptr<Media>>& getAll() const;
    std::optional<std::shared_ptr<Media>> findbyTittle(const std::string& title) const;
    std::vector<std::shared_ptr<Media>> findbyKeyword(const std::string& k) const;
    std::vector<std::shared_ptr<Media>> filterbyType(const std::string& type) const;
    std::vector<std::shared_ptr<Media>> search(const Search& a) const;
};

class Analytics {
public:
    static int calculate(const std::vector<std::shared_ptr<Media>>& list);
};

#endif