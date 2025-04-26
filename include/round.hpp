#ifndef ROUND_HPP
#define ROUND_HPP

struct Round {
    enum State {
        Choose,
        Place,
        Play,
    };
    State state = Choose;

    void chooseHandler() {
        // spawn 10 random objects
        for (int i = 0; i < 10; i++) {
        }
    }
    void placeHandler() {}
    void playHandler() {}
};

#endif
