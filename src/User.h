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
        std::cout<<std::endl<<"|1| View all media"<<std::endl
        <<"|2| View movies"<<std::endl
        <<"|3| View series"<<std::endl
        <<"|4| Search by title"<<std::endl
        <<"|5| Search by keyword"<<std::endl
        <<"|6| Search by genre"<<std::endl
        <<"|7| Add to watched"<<std::endl
        <<"|8| Add to favorites"<<std::endl
        <<"|9| Write a review"<<std::endl
        <<"|10| Go to profile"<<std::endl
        <<"|0| Exit"<<std::endl
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
                continue;
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
            } else if (choice==4) {
                std::cout<<"Enter title: ";
                std::string title;
                std::getline(std::cin, title);
                auto found= db.findbyTittle(title);
                if (found) {
                    found.value()->info();
                    found.value()->printReview();
                } else {
                    std::cout<<"Not found"<<std::endl;
                }
            } else if (choice== 5) {
                std::cout<<"Enter keyword: ";
                std::string key;
                std::getline(std::cin,key);
                auto res=db.search(Search{Keyword{key}});
                if (res.size()==1) {
                    std::cout<<"Found "<<res.size()<<" item:"<<std::endl;
                }
                else if (res.size()>1){
                    std::cout<<"Found "<<res.size()<<" items:"<<std::endl;
                }
                else {
                    std::cout<<"Not found"<<std::endl;
                }
                for (const auto& m : res) {
                    m->info();
                }
            } else if (choice==6) {
                std::cout<<"Enter genre: ";
                std::string g;
                std::getline(std::cin, g);
                auto res=db.search(Search{Genre{g}});
                if (res.size()==1) {
                    std::cout<<"Found "<<res.size()<<" item:"<<std::endl;
                }
                else if (res.size()>1){
                    std::cout<<"Found "<<res.size()<<" items:"<<std::endl;
                }
                else {
                    std::cout<<"Not found"<<std::endl;
                }
                for (const auto& m : res) {
                    m->info();
                }
            } else if (choice==7 || choice ==8 || choice==9) {
                std::cout<<"Enter title: ";
                std::string title;
                std::getline(std::cin, title);
                auto media=db.findbyTittle(title);
                if (!media) {
                    std::cout<<"Not found"<<std::endl;
                    continue;
                }
                if (choice==7) {
                    user->addToWatched(media.value());
                    std::cout<<"Added to watched"<<std::endl;
                } else if (choice==8) {
                    user->addToFavs(media.value());
                    std::cout<<"Added to favorites"<<std::endl;
                }
                else if (choice==9) {
                    std::cout<<"Rating (1-10): ";
                    int rating;
                    std::cin>>rating;
                    std::cin.ignore();
                    std::cout<<"Review text: ";
                    std::string text;
                    std::getline(std::cin, text);
                    try {
                        media.value()->addReview(Review(user->getName(), text, rating));
                        std::cout << "Review added"<<std::endl;
                    } catch (const std::exception& e) {
                        std::cout << "error: " << e.what() << std::endl;
                    }
                }
            }else if (choice==10) {
                    user->showProfile();
            }
        }
    }
};
#endif