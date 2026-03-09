#ifndef MYLETTERBOX_USER_H
#define MYLETTERBOX_USER_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "Model.h"

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
#endif