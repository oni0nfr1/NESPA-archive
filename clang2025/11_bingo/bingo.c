#include <stdio.h>

typedef struct {
    int max_run;
    int count;
} RunCount;

int N, M; // N은 row의 개수, M은 column의 개수
char board[100][101] = {};

RunCount count_by_direction(int r, int c, int dr, int dc) {
    char *seq[100] = {};
    int len = 0;
    while (0 <= r && r < N && 0 <= c && c < M) {
        seq[len] = &board[r][c];
        r += dr; c += dc; len++;
    }

    int max_run = 0, run_count = 0;
    int curr_run = 0;
    for (int i = 0; i < len; i++) {
        if (*seq[i] == '1') curr_run++;
        else if (curr_run > 0) {
            if (curr_run > max_run) {
                max_run = curr_run;
                run_count   = 1;
            } else if (curr_run == max_run) {
                run_count++;
            }
            curr_run = 0;
        }
    }
    if (curr_run > 0) {
        if (curr_run > max_run) {
            max_run = curr_run;
            run_count   = 1;
        } else if (curr_run == max_run) {
            run_count++;
        }
        curr_run = 0;
    }
    return (RunCount){ max_run, run_count };
}

RunCount add_count(RunCount a, RunCount b) {
    if (a.max_run > b.max_run) return a;
    else if(a.max_run < b.max_run) return b;
    else return (RunCount){ a.max_run, a.count + b.count };
}

int main() {

    scanf("%d %d", &N, &M);
    for (int i = 0 ; i < N ; i++) {
        scanf("%s", board[i]);
    }

    RunCount rcount = {0, 0};
    for (int row = 0 ; row < N ; row++) {
        rcount = add_count(rcount, count_by_direction(row, 0,  0, 1)); // 행
        rcount = add_count(rcount, count_by_direction(row, 0,  1, 1)); // 대각선 오른쪽아래 1
        rcount = add_count(rcount, count_by_direction(row, 0, -1, 1)); // 대각선 오른쪽위 1
    }
    for (int col = 0 ; col < M ; col++)
        rcount = add_count(rcount, count_by_direction(0, col, 1, 0)); // 열
    for (int col = 1 ; col < M ; col++) {
        rcount = add_count(rcount, count_by_direction(  0, col,  1, 1)); // 대각선 오른쪽아래 2
        rcount = add_count(rcount, count_by_direction(N-1, col, -1, 1)); // 대각선 오른쪽위 2
    }

    printf("%d %d", rcount.max_run, rcount.count);
}