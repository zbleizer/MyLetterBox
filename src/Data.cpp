#include "../includeh/Data.h"
#include <sstream>
#include <fstream>

std::vector<std::string> SplitkeywordsbySpace(const std::string& s) {
    std::vector<std::string> out;
    std::istringstream iss(s);
    std::string tok;
    while (iss >> tok) {
        out.push_back(tok);
    }
    return out;
}

std::vector<std::shared_ptr<Media>> CSVParser::parseMovie(const std::string& filename) {
    std::vector<std::shared_ptr<Media>> data;
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
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

std::vector<std::shared_ptr<Media>> CSVParser::parseSeries(const std::string& filename) {
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
            data.push_back(std::make_shared<Series>(name, overview, episodes, seasons, poster, genres));
        } catch (...) {
            continue;
        }
    }
    return data;
}

void Database::loadMovies(const std::string& file) {
    auto movies = CSVParser::parseMovie(file);
    lib.insert(lib.end(), movies.begin(), movies.end());
}
void Database::loadSeries(const std::string& file) {
    auto series = CSVParser::parseSeries(file);
    lib.insert(lib.end(), series.begin(), series.end());
}
void Database::loadAll(const std::string& movFile, const std::string& serFile) {
    loadMovies(movFile);
    loadSeries(serFile);
}

const std::vector<std::shared_ptr<Media>>& Database::getAll() const {
    return lib;
}

std::optional<std::shared_ptr<Media>> Database::findbyTittle(const std::string& title) const {
    for (const auto& media : lib) {
        if (media->getTitle() == title) {
            return media;
        }
    }
    return std::nullopt;
}

std::vector<std::shared_ptr<Media>> Database::findbyKeyword(const std::string& k) const {
    std::vector<std::shared_ptr<Media>> res;
    for (const auto& media : lib) {
        if (media->haveKeyword(k)) {
            res.push_back(media);
        }
    }
    return res;
}

std::vector<std::shared_ptr<Media>> Database::filterbyType(const std::string& type) const {
    std::vector<std::shared_ptr<Media>> res;
    for (const auto& m : lib) {
        if (m->getType() == type) {
            res.push_back(m);
        }
    }
    return res;
}

std::vector<std::shared_ptr<Media>> Database::search(const Search& a) const {
    return std::visit([this](const auto& media) -> std::vector<std::shared_ptr<Media>> {
        using T = std::decay_t<decltype(media)>;
        if constexpr (std::is_same_v<T, Genre>) {
            std::vector<std::shared_ptr<Media>> res;
            for (const auto& i : lib) {
                if (i->getGenres().find(media.genre) != std::string::npos) {
                    res.push_back(i);
                }
            }
            return res;
        } else if constexpr (std::is_same_v<T, Keyword>) {
            return this->findbyKeyword(media.keyword);
        } else {
            return {};
        }
    }, a);
}

int Analytics::calculate(const std::vector<std::shared_ptr<Media>>& list) {
    int c = 0;
    for (const auto& m : list) {
        c += m->getDuration();
    }
    return c;
}
