#include <stdio.h>
#include <unordered_map>
#include <stdlib.h>
#include <sys/time.h>
#include <assert.h>

#define NUM_BENCH 100000
#define NUM_BENCH_NUMS 9
#define NUM_BENCH_TRIES 5

char *random_string(int len) {
    char *res = (char *)malloc(len + 1);
    for (int i = 0; i < len; i++) {
        res[i] = (rand() % (126 - 33)) + 33;
    }
    res[len] = '\0';
    return res;
}

void benchmark() {
    unsigned long times[NUM_BENCH_NUMS][2] = {0};
    int lengths[] = {50, 100, 500, 1000, 5000, 10000, 20000, 50000, 100000, 1000000};
    struct timeval before, after;
    for (int k = 0; k < NUM_BENCH_TRIES; k++) {
        srand(696969);
        char *strings[NUM_BENCH] = {0};

        for (int i = 0; i < NUM_BENCH; i++)
            strings[i] = random_string(20);

        for (int i = 0; i < NUM_BENCH_NUMS; i++) {
            gettimeofday(&before, NULL);
            std::unordered_map<std::string, std::string> table;

            for (int j = 0; j < lengths[i]; j++)
                table.insert({strings[j], "data -- oh yeah"});

            for (int j = 0; j < lengths[i]; j++)
                assert(table.find(strings[j]) != table.end());

            gettimeofday(&after, NULL);
            times[i][0] += after.tv_sec - before.tv_sec;
            times[i][1] += after.tv_usec - before.tv_usec;
        }

        for (int i = 0; i < NUM_BENCH; i++)
            free(strings[i]);
    }

    for (int i = 0; i < NUM_BENCH_NUMS; i++)
        printf("%d: %lf %lf\n", lengths[i],
               (double)times[i][0] / (double)NUM_BENCH_TRIES,
               (double)times[i][1] / (double)NUM_BENCH_TRIES);
}

int main(void) {
    benchmark();
}
