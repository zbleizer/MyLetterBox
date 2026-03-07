#ifndef MYLETTERBOX_MODEL_H
#define MYLETTERBOX_MODEL_H
#include <string>
#include <algorithm>
#include <stdexcept>
#include <iostream>

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
    int year;
    std::vector<Review> reviews;

public:
    Media(std::string t, int y) : title(std::move(t)), year(y) {}
    virtual ~Media() = default;

    virtual void info() const = 0;
    virtual int getDuration() const = 0;

    std::string getTitle() const {
        return title;
    }
    int getYear() const {
        return year;
    }
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
    std::string director;
    int duration;
public:
    Movie(std::string t, int y, std::string d, int dur) : Media(std::move(t), y), director(std::move(d)), duration(dur) {}

    void info() const override {
        std::cout << "[Movie] " << title << " (" << year << ") | Dir: " << director << " | " << duration << " min | Rating: " << getAveRating() << "/10\n";
    }
    int getDuration() const override {
        return duration;
    }
};

#endif