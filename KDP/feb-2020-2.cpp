#include "common.h"

#include <queue>
#include <vector>

using namespace std;

const int N = 100;

struct Table {
    int drinks[N] = {-1};
    queue<int> drinkQueues[N];
};
Table table;

void philosophizing();
void drinking();
vector<int> getDrinkRound();

void philosopher(int id) {
    while (true) {
        vector<int> drinks = getDrinkRound();
        region (table) {
            for (int drink : drinks) {
                if (table.drinks[drink] == -1) {
                    table.drinks[drink] = id;
                } else {
                    table.drinkQueues[drink].push(id);
                    await (table.drinks[drink] == id);
                }
            }
        }
        drinking();
        region (table) {
            for (int drink : drinks) {
                if (table.drinkQueues[drink].empty()) {
                    table.drinks[drink] = -1;
                } else {
                    table.drinks[drink] = table.drinkQueues[drink].front();
                    table.drinkQueues[drink].pop();
                }
            }
        }
        philosophizing();
    }
}
