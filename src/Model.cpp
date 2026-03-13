#include "../includeh/Model.h"

#include <iostream>
#include <algorithm>
#include <stdexcept>

Review::Review(std::string a, std::string t, int s) : author(std::move(a)), text(std::move(t)), score(s) {
    if (score < 1 || score > 10) {
        throw std::invalid_argument("Score must be 1-10");
    }
}

void Review::print() const {
    std::cout << "  [" << score << "/10] " << author << ": " << text << "\n";
}

int Review::getScore() const {
    return score;
}

std::string Media::low(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), [](char c) {
        return static_cast<char>(std::tolower(c));
    });
    return s;
}

bool Media::haveSubstring(const std::string& text, const std::string& word) {
    if (word.empty()) {
        return true;
    }
    std::string ttext = ' ' + low(text) + ' ';
    const std::string wword = low(word);
    std::string punct = ".,!?:;\"'()[]{}<>-";
    for (char& c : ttext) {
        if (punct.find(c) != std::string::npos) {
            c = ' ';
        }
    }
    return ttext.find(' ' + wword + ' ') != std::string::npos;
}

Media::Media(std::string t, std::string g, std::string hp, std::vector<std::string> kw) : title(std::move(t)), genres(std::move(g)), homepage(std::move(hp)), keywords(std::move(kw)) {}

std::string Media::getTitle() const {
    return title;
}

std::string Media::getGenres() const {
    return genres;
}

void Media::addReview(const Review& r) {
    reviews.push_back(r);
}

double Media::getAveRating() const {
    if (reviews.empty()) {
        return 0.0;
    }
    double sum = 0;
    for (const auto& r : reviews) {
        sum += r.getScore();
    }
    return sum / reviews.size();
}

void Media::printReview() const {
    std::cout << "Reviews for " << title << ":\n";
    if (reviews.empty()) {
        std::cout << "No reviews yet\n";
    }
    for (const auto& r : reviews) {
        r.print();
    }
}

Movie::Movie(std::string t, std::string g, std::string hp, std::vector<std::string> kw, int dur) : Media(std::move(t), std::move(g), std::move(hp), std::move(kw)), duration(dur) {}

void Movie::info() const {
    std::cout << "[Movie] " << title << " | Genres: " << genres << " | " << duration << " min" << " | Rating: " << getAveRating() << "/10";
    if (!homepage.empty()) {
        std::cout << " | Homepage: " << homepage;
    }
    std::cout << "\n";
}

int Movie::getDuration() const {
    return duration;
}

std::string Movie::getType() const {
    return "Movie";
}

bool Movie::haveKeyword(const std::string& s) const {
    if (s.empty()) {
        return true;
    }
    const std::string word = low(s);
    for (const auto& k : keywords) {
        if (low(k) == word) {
            return true;
        }
    }
    return false;
}

Series::Series(std::string name, std::string ov, int ep, int se, std::string poster, std::string g) : Media(std::move(name), std::move(g), "", {}), overview(std::move(ov)), num_episodes(ep), num_seasons(se), poster(std::move(poster)) {}

void Series::info() const {
    std::cout << "[Series] " << title << " | Genres: " << genres << " | Seasons: " << num_seasons << " | Episodes: " << num_episodes << " | Rating: " << getAveRating() << "/10";
    if (!poster.empty()) {
        std::cout << " | Poster: " << poster;
    }
    std::cout << "\n";
}

int Series::getDuration() const {
    return num_episodes * 45;
}

std::string Series::getType() const {
    return "Series";
}

bool Series::haveKeyword(const std::string& s) const {
    return haveSubstring(overview, s);
}

std::string Series::getOverview() const {
    return overview;
}

int Series::getNumEpisodes() const {
    return num_episodes;
}

int Series::getNumSeasons() const {
    return num_seasons;
}

std::string Series::getPoster() const {
    return poster;
}