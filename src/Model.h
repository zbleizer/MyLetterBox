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

};
#endif