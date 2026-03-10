#ifndef MYLETTERBOX_USER_H
#define MYLETTERBOX_USER_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "Model.h"
#include "Data.h"

class Custom{
    std::string list_name;
    std::vector<std::shared_ptr<Media>> items;
public:
    Custom(std::string name):list_name(std::move(name)){}

    void addMedia(std::shared_ptr<Media> media) {
        items.emplace_back(std::move(media));
    }

    void printCustom() const {
        std::cout<<std::endl<<"-> List: "<<list_name<<" <-"<<std::endl;
        if (items.empty()) {
            std::cout<<"Empty... :("<<std::endl;
        }
        for (auto& i:items){
            i->info();
        }
    }
    const std::vector<std::shared_ptr<Media>>& getItems() const {
        return items;
    }
};

class User {
    std::string nickname;
    Custom favs;
    Custom watched;
public:
    User(std::string name):nickname(std::move(name)),favs("Favorites"), watched("Watched"){}

    std::string getName() const {
        return nickname;
    }

    void addToFavs(std::shared_ptr<Media> f) {
        favs.addMedia(std::move(f));
    }

    void addToWatched(std::shared_ptr<Media> w) {
        watched.addMedia(std::move(w));
    }

    void showProfile() const {
        std::cout<<std::endl<<"| User Profile: "<<nickname<<" |"<<std::endl;
        favs.printCustom();
        watched.printCustom();
        std::cout<<"Total watch time: "<<Analytics::calculate(watched.getItems())<<" minutes"<<std::endl;
    }
};
#endif