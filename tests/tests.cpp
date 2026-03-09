#include <gtest/gtest.h>
#include "../src/Model.h"
#include "../src/User.h"

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

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}