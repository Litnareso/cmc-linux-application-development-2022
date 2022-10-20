#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

typedef struct ranges
{
    int32_t start;
    int32_t stop;
    int32_t step;
    int32_t cur;
} range;

void argparse(int argc, char *argv[], int32_t *start, int32_t *stop, int32_t *step)
{
    char *end;
    switch (argc) {
    case 2:
        *start = 0;
        *stop = strtol(argv[1], &end, 10);
        *step = 1;
        break;
    case 3:
        *start = strtol(argv[1], &end, 10);
        *stop = strtol(argv[2], &end, 10);
        *step = 1;
        break;
    case 4:
        *start = strtol(argv[1], &end, 10);
        *stop = strtol(argv[2], &end, 10);
        *step = strtol(argv[3], &end, 10);
        break;
    default:
        printf("Программа при запуске\n"
               "c одним параметром N — выводит в столбик последовательность [0, 1, … N-1];\n"
               "c двумя — M, N — последовательность [M, M+1, … N-1];\n"
               "c тремя — M, N, S — последовательность [M, M+S, M+2S, … N-1].\n"
        );
    }
    return;
}

void range_init(range *rng)
{
    rng->cur = rng->start;
    return;
}

int range_run(range *rng)
{
    return (rng->cur < rng->stop);
}

void range_next(range *rng)
{
    rng->cur += rng->step;
    return;
}

int32_t range_get(range *rng)
{
    return rng->cur;
}

int main(int argc, char *argv[])
{
    range I;
    argparse(argc, argv, &I.start, &I.stop, &I.step);
    for(range_init(&I); range_run(&I); range_next(&I)) {
        printf("%" PRId32 "\n", range_get(&I));
    }
    return 0;
}
