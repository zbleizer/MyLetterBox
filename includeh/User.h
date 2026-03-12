#ifndef MYLETTERBOX_USER_H
#define MYLETTERBOX_USER_H

#include <string>
#include <vector>
#include <memory>
#include "Model.h"
#include "Data.h"

class Custom {
    std::string list_name;
    std::vector<std::shared_ptr<Media>> items;
public:
    Custom(std::string name);
    void addMedia(std::shared_ptr<Media> media);
    void printCustom(bool showReviews = false) const;
    const std::vector<std::shared_ptr<Media>>& getItems() const;
};

class User {
    std::string nickname;
    Custom favs;
    Custom watched;
public:
    User(std::string name);
    std::string getName() const;
    void addToFavs(std::shared_ptr<Media> f);
    void addToWatched(std::shared_ptr<Media> w);
    void showProfile() const;
};

class StartApp {
    Database db;
    std::unique_ptr<User> user;
    void Menu() const;
public:
    StartApp();
    void start();
};

#endif