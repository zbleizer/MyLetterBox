#ifndef MYLETTERBOX_MODEL_H
#define MYLETTERBOX_MODEL_H
#include <string>
#include <vector>

class Review {
    std::string author;
    std::string text;
    int score;
public:
    Review(std::string a, std::string t, int s);
    void print() const;
    int getScore() const;
};

class Media {
protected:
    std::string title;
    std::vector<Review> reviews;
    std::string genres;
    std::string homepage;
    std::vector<std::string> keywords;

    static std::string low(std::string s);
    static bool haveSubstring(const std::string& t, const std::string& s);

public:
    Media(std::string t, std::string g, std::string hp, std::vector<std::string> kw);
    virtual ~Media() = default;

    virtual void info() const = 0;
    virtual int getDuration() const = 0;
    virtual std::string getType() const = 0;
    virtual bool haveKeyword(const std::string& s) const = 0;

    std::string getTitle() const;
    std::string getGenres() const;
    void addReview(const Review& r);
    double getAveRating() const;
    void printReview() const;
};

class Movie : public Media {
    int duration;
public:
    Movie(std::string t, std::string g, std::string hp, std::vector<std::string> kw, int dur);

    void info() const override;
    int getDuration() const override;
    std::string getType() const override;
    bool haveKeyword(const std::string& s) const override;
};

class Series : public Media {
    std::string overview;
    int num_episodes;
    int num_seasons;
    std::string poster;
public:
    Series(std::string name, std::string ov, int ep, int se, std::string poster, std::string g);

    void info() const override;
    int getDuration() const override;
    std::string getType() const override;
    bool haveKeyword(const std::string& s) const override;

    std::string getOverview() const;
    int getNumEpisodes() const;
    int getNumSeasons() const;
    std::string getPoster() const;
};

#endif