#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

// global number of processes
#define N 4

// global number of resources available
#define M 3

struct runner_t {
    int* resource_requests;
    int n;
};

struct runner_t* runner_t_constructor(int c, ...) {
    struct runner_t* runner = malloc(sizeof(struct runner_t));
    int* container = malloc((c + 1) * sizeof(int));

    va_list ap;
    int j;
    va_start(ap, c);
    for (j = 0; j < c; ++j) {
        container[j] = va_arg(ap, int);
    }
    runner->resource_requests = container;
    runner->n = j;

    return runner;
}

void runner_t_destructor(struct runner_t* runner) {
    free(runner->resource_requests);
    free(runner);
}

void runner_t_print(struct runner_t* runner) {
    printf("Number of processes: %d\n\n", runner->n);
    for (int i = 0; i < runner->n; ++i) {
        printf("Resource [%c]: %d\n", (char)65 + i,
               runner->resource_requests[i]);
    }
}

int main(int argc, const char* argv[]) {
    // resource allocation matrix
    struct runner_t* process_block =
        (struct runner_t*)malloc(sizeof(struct runner_t*));

    process_block[0] = *runner_t_constructor(M, 0, 1, 0);
    runner_t_print(&process_block[0]);
    runner_t_destructor(&process_block[0]);

    return 0;
}
