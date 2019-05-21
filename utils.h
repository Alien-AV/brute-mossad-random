#ifndef BRUTE_RANDOM_UTILS_H
#define BRUTE_RANDOM_UTILS_H

void write_to_file(const char *filename, char* full_file_contents, size_t size);

void read_from_file(const char *filename, char** full_file_contents, size_t& size);

void generate_state_with_seed(uint32_t * state, uint32_t seed);

#endif //BRUTE_RANDOM_UTILS_H
