#include "common.h"

typedef pair<int, int> Card;

template<typename T>
T randomChoice(vector<T>& vec) {
    int index = rand() * vec.size() / RAND_MAX;
    T ret = vec[index];
    vec.erase(vec.begin() + index);
    return ret;
}

bool hasWon(vector<Card>& cards) {
    bool colors[4] = {false};
    colors[cards[0].first] = true;
    int num = cards[0].second;
    for (int i = 1; i < 4; ++i) {
        if (cards[i].second != num || colors[cards[i].first]) {
            return false;
        }
        colors[cards[i].first] = true;
    }
    return true;
}

void player(int i) {
    vector<Card> cards;
    Card c;
    for (int i = 0; i < 4; ++i) {
        in("player", i, &c);
        cards.push_back(c);
    }
    while (true) {
        if (hasWon(cards)) {
            in("can set game over");
            if (!rdp("game over")) {
                out("game over");
            }
            out("can set game over");
            out("deck", (i + 1) % 4, Card(-1, -1));
            break;
        }
        c = randomChoice(cards);
        out("deck", (i + 1) % 4, c);
        in("deck", i, &c);
        if (rdp("game over")) {
            break;
        }
        cards.push_back(c);
    }
}

void initialize() {
    // Празнимо простор торки од претходне игре
    while (inp("deck") || inp("player") || inp("game over") || inp("can set game over"));
    // Вршимо насумичну расподелу шпила
    vector<Card> cards;
    for (int color = 0; color < 4; ++color) {
        for (int number = 0; number < 6; ++number) {
            cards.push_back({color, number});
        }
    }
    for (int d = 0; d < 4; ++d) {
        for (int c = 0; c < 2; ++c) {
            Card card = randomChoice(cards);
            out("deck", d, card);
        }
    }
    for (int p = 0; p < 4; ++p) {
        for (int c = 0; c < 4; ++c) {
            Card card = randomChoice(cards);
            out("player", p, card);
        }
        eval(player, p);
    }
    out("can set game over");
}
