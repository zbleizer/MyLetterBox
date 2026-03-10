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

class StartApp {
    Database db;
    std::unique_ptr<User> user;
    void Menu() const {
        std::cout<<"|1| View all media"<<std::endl
        <<"|2| View movies"<<std::endl
        <<"|3| View series"<<std::endl
        <<"Choose action: ";
    }
public:
    StartApp() {
        try {
            db.loadAll("data/movies.csv","data/series.csv");
            std::cout<<"Loaded total: "<<db.getAll().size()<<" items (movies + series)"<<std::endl;
        } catch (const std::exception& e) {
            std::cout<<"error: "<<e.what()<<std::endl;
        }
    }

    void start() {
        std::string name;
        std::cout<<"Enter nickname to login: ";
        std::getline(std::cin, name);
        user = std::make_unique<User>(name);

        int choice = -1;
        while (choice != 0) {
            Menu();
            if (!(std::cin >> choice)) {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                std::cout<<"Please, enter a number between 0-10";
                continue;
            }
            if (choice<0 || choice>10) {
                std::cout<<"Please, enter a number between 0-10";
            }
            std::cin.ignore();

            if (choice == 1) {
                for (const auto& m : db.getAll()) {
                    m->info();
                }
            } else if (choice == 2) {
                auto movies = db.filterbyType("Movie");
                for (const auto& m : movies) {
                    m->info();
                }
            } else if (choice == 3) {
                auto series = db.filterbyType("Series");
                for (const auto& s : series) {
                    s->info();
                }
            }
        }
    }
};
#endif