#ifndef MYLETTERBOX_MODEL_H
#define MYLETTERBOX_MODEL_H
#include <string>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <vector>

class Review {
    std::string author;
    std::string text;
    int score;
public:
    Review(std::string a, std::string t, int s) : author(std::move(a)), text(std::move(t)), score(s) {
        if (score < 1 || score > 10) {
            throw std::invalid_argument("Score must be 1-10");
        }
    }
    void print() const {
        std::cout << "  [" << score << "/10] " << author << ": " << text << "\n";
    }
    int getScore() const {
        return score;
    }
};

class Media {
protected:
    std::string title;
    std::vector<Review> reviews;
    std::string genres;
    std::string homepage;
    std::vector<std::string> keywords;

    static std::string low(std::string s) {
        std::transform(s.begin(), s.end(), s.begin(),[](char c){return static_cast<char>(std::tolower(c));});
        return s;
    }

public:
    Media(std::string t, std::string g, std::string hp, std::vector<std::string> kw) : title(std::move(t)), genres(std::move(g)), homepage(std::move(hp)), keywords(std::move(kw)) {}
    virtual ~Media() = default;

    virtual void info() const = 0;
    virtual int getDuration() const = 0;
    std::string getTitle() const {
        return title;
    }
    std::string getGenres() const {
        return genres;
    }
    virtual std::string getType() const = 0;
    virtual bool haveKeyword(const std::string& s) const = 0; // НОВОЕ

    void addReview(const Review& r) {
        reviews.push_back(r);
    }

    double getAveRating() const {
        if (reviews.empty()) {
            return 0.0;
        }
        double sum = 0;
        for (const auto& r : reviews) {
            sum += r.getScore();
        }
        return sum / reviews.size();
    }

    void printReview() const {
        std::cout << "Reviews for " << title << ":\n";
        if (reviews.empty()) {
            std::cout << "No reviews yet\n";
        }
        for (const auto& r : reviews) {
            r.print();
        }
    }
};

class Movie : public Media {
    int duration;
public:
    Movie(std::string t, std::string g, std::string hp, std::vector<std::string> kw, int dur) : Media(std::move(t), std::move(g), std::move(hp), std::move(kw)), duration(dur) {}

    void info() const override {
        std::cout << "[Movie] " << title << " | Genres: " << genres << " | " << duration << " min" << " | Rating: " << getAveRating() << "/10";
        if (!homepage.empty()) {
            std::cout << " | Homepage: " << homepage;
        }
        std::cout << "\n";
    }

    int getDuration() const override {
        return duration;
    }
    std::string getType() const override {
        return "Movie";
    }
    bool haveKeyword(const std::string& s) const override {
        if (s.empty()) {
            return true;
        }
        const std::string q = low(s);
        for (const auto& k : keywords) {
            if (low(k) == q) {
                return true;
            }
        }
        return false;
    }
};

#endif