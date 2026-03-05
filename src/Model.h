#ifndef MYLETTERBOX_MODEL_H
#define MYLETTERBOX_MODEL_H
#include <string>
#include <algorithm>

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