#include <gtest/gtest.h>
#include "../src/Model.h"
#include "../src/User.h"
#include "../src/Data.h"

TEST(ReviewTest, ShouldPass) {
    EXPECT_NO_THROW(Review("liza1", "super", 10));

    Review r("liza", "norm", 7);
    EXPECT_EQ(r.getScore(), 7);
}

TEST(ReviewTest, NeedException) {
    EXPECT_THROW(Review("liza2", "plus vibe", 15), std::invalid_argument);
    EXPECT_THROW(Review("liza3", "minus vibe", -5), std::invalid_argument);

}



TEST(MovieTest, ShouldPass_Init) {
    Movie m("Forrest Gump", "Drama", "https://forrestgump.com", {"fast", "speed"}, 142);

    EXPECT_EQ(m.getTitle(), "Forrest Gump");
    EXPECT_EQ(m.getGenres(), "Drama");
    EXPECT_EQ(m.getType(), "Movie");
    EXPECT_EQ(m.getDuration(), 142);
    EXPECT_EQ(m.getAveRating(), 0.0);

    EXPECT_NO_THROW(m.info());
}


TEST(MovieTest, ShouldPass_AveRate) {
    Movie m("Forrest Gump", "Drama", "https://forrestgump.com", {"fast", "speed"}, 142);


    m.addReview(Review("liza1", "amazing", 10));
    EXPECT_EQ(m.getAveRating(), 10.0);
    m.addReview(Review("liza2", "norm", 5));
    EXPECT_EQ(m.getAveRating(), 7.5);
}

TEST(MovieTest, ShouldPass_Keywords) {
    Movie m("Forrest Gump", "Drama", "https://forrestgump.com", {"fast", "speed"}, 142);
    EXPECT_TRUE(m.haveKeyword("Fast"));
    EXPECT_TRUE(m.haveKeyword("SPEED"));
    EXPECT_FALSE(m.haveKeyword("gg"));
}


TEST(SeriesTest, ShouldPass_Init) {
    Series s("Breaking Bad", "A chemistry teacher becomes a xxxx producer", 62, 5, "/bb.jpg", "Crime Drama");

    EXPECT_EQ(s.getTitle(), "Breaking Bad");
    EXPECT_EQ(s.getGenres(), "Crime Drama");
    EXPECT_EQ(s.getNumEpisodes(), 62);
    EXPECT_EQ(s.getNumSeasons(), 5);
    EXPECT_EQ(s.getPoster(), "/bb.jpg");
    EXPECT_EQ(s.getType(), "Series");

    EXPECT_EQ(s.getDuration(), 62 * 45);

    EXPECT_NO_THROW(s.info());
}

TEST(SeriesTest, ShouldPass_Keywords) {
    Series s("Breaking Bad", "A chemistry teacher becomes a xxxx producer", 62, 5, "/bb.jpg", "Crime Drama");

    EXPECT_TRUE(s.haveKeyword("producer"));
    EXPECT_TRUE(s.haveKeyword("CHEMISTRY"));
    EXPECT_TRUE(s.haveKeyword("Teacher"));
    EXPECT_FALSE(s.haveKeyword("be"));
}

TEST(CustomTest, ShouldPass) {
    Custom c("Favs");
    EXPECT_EQ(c.getItems().size(),0);

    auto p=std::make_shared<Movie>("Pulp Fiction", "Crime", "", std::vector<std::string>{"drug"}, 154);
    c.addMedia(p);

    EXPECT_EQ(c.getItems().size(), 1);
    EXPECT_EQ(c.getItems()[0]->getTitle(), "Pulp Fiction");
}

TEST(CustomTestSecond, ShouldPass) {
    Custom c("Favs");
    EXPECT_EQ(c.getItems().size(),0);

    auto p=std::make_shared<Movie>("Pulp Fiction", "Crime", "", std::vector<std::string>{"drug"}, 154);
    c.addMedia(p);

    auto h=std::make_shared<Movie>("Harry Potter and the Half-Blood Prince", "Fantasy", "", std::vector<std::string>{"magic"}, 153);
    c.addMedia(h);

    EXPECT_EQ(c.getItems().size(), 2);
    EXPECT_EQ(c.getItems()[0]->getTitle(), "Pulp Fiction");
    EXPECT_EQ(c.getItems()[1]->getTitle(), "Harry Potter and the Half-Blood Prince");
}

TEST(CustomTestThird, ShouldPassSeries) {
    Custom w("Watched");
    auto s=std::make_shared<Series>("Shameless","gallagher",1,1,"/9akij7PqZ1g6zl42DQQTtL9CTSb.jpg","Drama");
    w.addMedia(s);
}

static void writeTextFile(const std::string& path, const std::string& content) {
    std::ofstream out(path, std::ios::binary);
    if (!out.is_open()) throw std::runtime_error("Can't write test file: " + path);
    out << content;
    out.close();
}

TEST(CSVParserTest, ShouldPass_ParseMoviesFile) {
    const std::string path = "test_movies.csv";
    writeTextFile(path,
        "genres;homepage;keywords;title;duration\n"
        "Sci-Fi;https://site;dream heist;Inception;148\n"
        "Drama;;prison hope;Shawshank;142\n"
    );
    auto vec = CSVParser::parseMovie(path);
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec[0]->getType(), "Movie");
    EXPECT_EQ(vec[0]->getTitle(), "Inception");
    EXPECT_EQ(vec[0]->getDuration(), 148);
    std::remove(path.c_str());
}

TEST(CSVParserTest, ShouldPass_ParseSeriesFile) {
    const std::string path = "test_series.csv";
    writeTextFile(path,
        "name;overview;number_of_episodes;number_of_seasons;poster_path;genres\n"
        "Breaking Bad;A chemistry teacher becomes a meth producer;62;5;/bb.jpg;Crime Drama\n"
        "Chernobyl;A dramatization of the nuclear disaster;5;1;/ch.jpg;Drama History\n"
    );
    auto vec = CSVParser::parseSeries(path);
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec[0]->getType(), "Series");
    EXPECT_EQ(vec[0]->getTitle(), "Breaking Bad");
    EXPECT_EQ(vec[0]->getDuration(), 62 * 45);
    std::remove(path.c_str());
}

TEST(CSVParserTest, NeedException) {
    EXPECT_THROW(CSVParser::parseMovie("no_movies.csv"), std::runtime_error);
    EXPECT_THROW(CSVParser::parseSeries("no_series.csv"), std::runtime_error);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}