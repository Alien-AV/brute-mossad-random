#include <iostream>
#include <fstream>
#include <random>
#include <array>
#include <sstream>
#include <chrono>
#include <thread>
#include <mutex>

void test();
void bruteforce();
void benchmark();

void generate_state_with_seed(uint32_t * state, uint32_t seed);

std::mutex mutex;

int main() {
    test();
    bruteforce();
//    benchmark();
}

void bruteforce() {
    std::vector<std::thread> threads;
    const auto THREADS = 8;
    const uint64_t global_start_seed = 0x00000000;
    const uint64_t global_end_seed = 0xffffffff;
    const auto part_size = (global_end_seed - global_start_seed + 1) / THREADS;

    std::cout << std::hex;
    for (auto i = 0; i < THREADS; i++) {
        uint32_t start_seed = global_start_seed + i * part_size;
        uint32_t end_seed = start_seed + part_size - 1;

        threads.push_back(std::thread([](uint32_t start_seed, uint32_t end_seed) {
            std::mt19937 generator;
            {
                std::lock_guard<std::mutex> lock(mutex);
                std::cout << "thread id: " << std::this_thread::get_id() << ", start seed: " << start_seed
                          << ",end seed: " << end_seed << std::endl;
            }

            for (uint32_t seed = start_seed; seed != end_seed; seed++) {
                generate_state_with_seed(generator._Ax, seed);
                generator._Idx = 0x270;
                if(generator()==0x00bb65fe) {
                    std::lock_guard<std::mutex> lock(mutex);
                    std::cout << "seed: " << seed << std::endl;
                }
                if (seed % 0x01000000 == 0) {
                    {
                        std::lock_guard<std::mutex> lock(mutex);
                        std::cout << "[" << std::this_thread::get_id() << "] percent done:" << std::dec << (uint64_t) (seed - start_seed) * 100 / (end_seed - start_seed) << std::hex << std::endl;
                    }
                }
            }
        }, start_seed, end_seed));
    }

    std::for_each(threads.begin(), threads.end(), [](std::thread &thread) {
        thread.join();
    });
}

void generate_state_with_seed(uint32_t * state, uint32_t seed){
    state[0] = seed;
    for(size_t index = 1; index < 624; index++)
    {
        state[index] = 6069 * state[index-1];
    }
}

void benchmark() {
    std::mt19937 generator;

    uint32_t seed = 0x4D314650;

    auto time_start = std::chrono::high_resolution_clock::now();
    auto millions_of_tries = 10;
    for (auto i = 0; i < millions_of_tries * 1000 * 1000; i++) {
        generate_state_with_seed(generator._Ax, seed);
        generator();
    }
    auto duration = std::chrono::high_resolution_clock::now() - time_start;

    std::cout << millions_of_tries << "m tries in " << std::chrono::duration_cast<std::chrono::seconds>(duration).count() << " seconds"
              << std::endl;
}

void test(){
    std::mt19937 generator;

    generate_state_with_seed(generator._Ax, 0x4D314650);

    for(auto i = 0; i < 700; i++) generator();

    if(generator() == 0xBA8251E3){
        std::cout << "seeding still works";
    }else{
        std::cout << "SEEDING BROKEN!!!";
    }
    std::cout << std::endl;
}