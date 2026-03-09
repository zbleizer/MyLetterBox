#ifndef MYLETTERBOX_DATA_H
#define MYLETTERBOX_DATA_H
#include "Model.h"
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <memory>

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
    static std::vector<std::shared_ptr<Media>> parseMovie(const std::string& filen) {
        std::vector<std::shared_ptr<Media>> data;
        std::ifstream file(filen);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file: " + filen);
        }
        std::string line;
        std::getline(file, line);
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string genres, homepage, keywordsStr, title, durationStr;
            std::getline(ss, genres, ';');
            std::getline(ss, homepage, ';');
            std::getline(ss, keywordsStr, ';');
            std::getline(ss, title, ';');
            std::getline(ss, durationStr, ';');
            try {
                int dur = durationStr.empty() ? 0 : std::stoi(durationStr);
                auto kw = SplitkeywordsbySpace(keywordsStr);
                data.push_back(std::make_shared<Movie>(title, genres, homepage, kw, dur));
            } catch (...) {
                continue;
            }
        }
        return data;
    }
    static std::vector<std::shared_ptr<Media>> parseSeries(const std::string& filename) {
        std::vector<std::shared_ptr<Media>> data;
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file: " + filename);
        }
        std::string line;
        std::getline(file, line);
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string name, overview, episode, season, poster, genres;
            std::getline(ss, name, ';');
            std::getline(ss, overview, ';');
            std::getline(ss, episode, ';');
            std::getline(ss, season, ';');
            std::getline(ss, poster, ';');
            std::getline(ss, genres, ';');
            try {
                int episodes = episode.empty() ? 0 : std::stoi(episode);
                int seasons  = season.empty() ? 0 : std::stoi(season);
                data.push_back(std::make_shared<Series>(name,overview, episodes,seasons, poster,genres));
            } catch (...) {
                continue;
            }
        }
        return data;
    }
};

class Database {
    std::vector<std::shared_ptr<Media>> lib;
public:
    void loadMovies(const std::string& file) {
        auto movies = CSVParser::parseMovie(file);
        lib.insert(lib.end(), movies.begin(), movies.end());
    }
    void loadSeries(const std::string& file) {
        auto series = CSVParser::parseSeries(file);
        lib.insert(lib.end(), series.begin(), series.end());
    }
    void loadAll(const std::string& movF, const std::string& serF) {
        loadMovies(movF);
        loadSeries(serF);
    }
    const std::vector<std::shared_ptr<Media>>& getAll() const {
        return lib;
    }
    std::optional<std::shared_ptr<Media>> findbyTittle(const std::string& title) const {
        for (const auto& m : lib) {
            if (m->getTitle() == title) {
                return m;
            }
        }
        return std::nullopt;
    }
    std::vector<std::shared_ptr<Media>> findbyKeyword(const std::string& k) const {
        std::vector<std::shared_ptr<Media>> res;
        for (const auto& m : lib) {
            if (m->haveKeyword(k)) {
                res.push_back(m);
            }
        }
        return res;
    }
    std::vector<std::shared_ptr<Media>> filterbyType(const std::string& type) const {
        std::vector<std::shared_ptr<Media>> res;
        for (const auto& m : lib) {
            if (m->getType() == type) {
                res.push_back(m);
            }
        }
        return res;
    }
};
#endif //MYLETTERBOX_DATA_H