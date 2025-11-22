#include "PMrandom.h"
#define MYSEED 20251113
#define EXPERIMENT_COUNT 100000
#define BONUS_RULES_MAX 5

typedef struct {
    int score;
    int bonus;
} GameState;

park_miller_t rng;
GameState bonuses[BONUS_RULES_MAX];
int k;

int dicegame_simulate() {
    GameState state = {};
    while (state.score <= bonuses[k-1].score) {
        state.score += park_miller_range(&rng, 1, 6);
        for (int i = 0 ; i < k ; i++)
            if (state.score == bonuses[i].score)
                state.bonus += bonuses[i].bonus;
        state.bonus++;
    }
    return state.bonus;
}

int main() {
    scanf("%d", &k);
    park_miller_init(&rng, MYSEED);
    
    for (int i = 0 ; i < k ; i++) {
        int s, p;
        scanf("%d %d", &s, &p);
        bonuses[i] = (GameState){ s, p };
    }
    
    long long sum = 0;
    for (int i = 0 ; i < EXPERIMENT_COUNT ; i++)
        sum += dicegame_simulate();
    printf("%.1f", sum / (double)(EXPERIMENT_COUNT));

}