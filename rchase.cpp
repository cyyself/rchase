#include <cstddef>
#include <random>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <sys/mman.h>

void worker(size_t size, size_t iterations = 1e7) {
    volatile size_t *buffer;
    buffer = (size_t *)mmap(nullptr, size * sizeof(size_t),
                          PROT_READ | PROT_WRITE,
                          MAP_PRIVATE | MAP_ANONYMOUS,
                          -1, 0);
    if (buffer == MAP_FAILED) {
        perror("mmap failed");
        exit(1);
    }
    std::mt19937_64 rng(0);
    for (size_t i = 0; i < size; ++i) {
        buffer[i] = rng();
    }
    auto start = std::chrono::high_resolution_clock::now();
    size_t cur_index = 0;
    size_t total_iterations = iterations;
    while (iterations--) {
        size_t rnd = rng();
        size_t next_index = (buffer[cur_index] ^ rnd) % size;
        buffer[cur_index] = rnd;
        cur_index = next_index;
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    double latency = (elapsed.count() * 1e9) / total_iterations;
    printf("Latency: %.2f ns\n", latency);
    munmap((void *)buffer, size * sizeof(long));
}

int main(int argc, char **argv) {
    size_t iterations = 1e7;
    size_t size;
    if (argc > 2) {
        iterations = static_cast<size_t>(std::stoull(argv[2]));
    }
    if (argc > 1) {
        size = static_cast<size_t>(std::stoull(argv[1])) * 1024 * 1024;
    } else {
        printf("Usage: %s <size in MB> [iterations]\n", argv[0]);
        exit(1);
    }
    worker(size / sizeof(size_t), iterations);
    return 0;
}
