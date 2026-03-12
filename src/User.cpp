#include "../includeh/User.h"
#include <iostream>

Custom::Custom(std::string name) : list_name(std::move(name)) {}

void Custom::addMedia(std::shared_ptr<Media> media) {
    items.emplace_back(std::move(media));
}

void Custom::printCustom(bool showReviews) const {
    std::cout << std::endl << "-> List: " << list_name << " <-" << std::endl;
    if (items.empty()) {
        std::cout << "Empty... :(" << std::endl;
    }
    for (auto& i : items) {
        i->info();
        if (showReviews) {
            i->printReview();
        }
    }
}

const std::vector<std::shared_ptr<Media>>& Custom::getItems() const {
    return items;
}


User::User(std::string name) : nickname(std::move(name)), favs("Favorites"), watched("Watched") {}

std::string User::getName() const {
    return nickname;
}

void User::addToFavs(std::shared_ptr<Media> f) {
    favs.addMedia(std::move(f));
}

void User::addToWatched(std::shared_ptr<Media> w) {
    watched.addMedia(std::move(w));
}

void User::showProfile() const {
    std::cout << std::endl << "| User Profile: " << nickname << " |" << std::endl;
    favs.printCustom(false);
    watched.printCustom(true);
    std::cout << std::endl << "Total watch time: " << Analytics::calculate(watched.getItems()) << " minutes" << std::endl;
}


StartApp::StartApp() {
    try {
        db.loadAll("data/movies.csv", "data/series.csv");
        std::cout << "Loaded total: " << db.getAll().size() << " items (movies + series)" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "error: " << e.what() << std::endl;
    }
}

void StartApp::Menu() const {
    std::cout << std::endl << "|1| View all media" << std::endl
              << "|2| View movies" << std::endl
              << "|3| View series" << std::endl
              << "|4| Search by title" << std::endl
              << "|5| Search by keyword" << std::endl
              << "|6| Search by genre" << std::endl
              << "|7| Add to watched" << std::endl
              << "|8| Add to favorites" << std::endl
              << "|9| Write a review" << std::endl
              << "|10| Go to profile" << std::endl
              << "|0| Exit" << std::endl
              << "Choose action: ";
}

void StartApp::start() {
    std::string name;
    std::cout << "Enter nickname to login: ";
    std::getline(std::cin, name);
    user = std::make_unique<User>(name);
    int choice = -1;

    while (choice != 0) {
        Menu();
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }
        std::cin.ignore();

        if (choice < 0 || choice > 10) {
            std::cout << "Please, enter a number between 0-10" << std::endl;
            continue;
        }

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
        } else if (choice == 4) {
            std::cout << "Enter title: ";
            std::string title;
            std::getline(std::cin, title);
            auto found = db.findbyTittle(title);
            if (found) {
                found.value()->info();
                found.value()->printReview();
            } else {
                std::cout << "Not found" << std::endl;
            }
        } else if (choice == 5) {
            std::cout << "Enter keyword: ";
            std::string key;
            std::getline(std::cin, key);
            auto res = db.search(Search{Keyword{key}});
            if (res.size() == 1) {
                std::cout << "Found " << res.size() << " item:" << std::endl;
            } else if (res.size() > 1) {
                std::cout << "Found " << res.size() << " items:" << std::endl;
            } else {
                std::cout << "Not found" << std::endl;
            }
            for (const auto& m : res) {
                m->info();
            }
        } else if (choice == 6) {
            std::cout << "Enter genre: ";
            std::string g;
            std::getline(std::cin, g);
            auto res = db.search(Search{Genre{g}});
            if (res.size() == 1) {
                std::cout << "Found " << res.size() << " item:" << std::endl;
            } else if (res.size() > 1) {
                std::cout << "Found " << res.size() << " items:" << std::endl;
            } else {
                std::cout << "Not found" << std::endl;
            }
            for (const auto& m : res) {
                m->info();
            }
        } else if (choice == 7 || choice == 8 || choice == 9) {
            std::cout << "Enter title: ";
            std::string title;
            std::getline(std::cin, title);
            auto media = db.findbyTittle(title);
            if (!media) {
                std::cout << "Not found" << std::endl;
                continue;
            }

            if (choice == 7) {
                user->addToWatched(media.value());
                std::cout << "Added to watched" << std::endl;
            } else if (choice == 8) {
                user->addToFavs(media.value());
                std::cout << "Added to favorites" << std::endl;
            } else if (choice == 9) {
                std::cout << "Rating (1-10): ";
                int rating;
                std::cin >> rating;
                std::cin.ignore();
                std::cout << "Review text: ";
                std::string text;
                std::getline(std::cin, text);
                try {
                    media.value()->addReview(Review(user->getName(), text, rating));
                    std::cout << "Review added" << std::endl;
                } catch (const std::exception& e) {
                    std::cout << "error: " << e.what() << std::endl;
                }
            }
        } else if (choice == 10) {
            user->showProfile();
        }
    }
}