#ifndef QUALITAIR_UTILS_HPP
#define QUALITAIR_UTILS_HPP

#include <random>
#include <vector>
#include <string>

using namespace std;

/**
 * Random int
 * @param max
 * @return random value in [0, max[
 */
int rnd(int max) {
    return rand() % max;
}

/**
 * Random int
 * @param min
 * @param max
 * @return random value in [0, max[
 */
int rnd(int min, int max) {
    return min + rand() % (max - min);
}

/**
 * Random string
 * @param length
 * @return random string of length "length"
 */
string randomString(size_t length) {
    string str = "";

    const char alphabet[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    const size_t len = (sizeof(alphabet) - 1);

    for (int i = 0; i < length; ++i) {
        str += alphabet[rnd(len)];
    }

    return str;
}


/**
 * Vector to string ex: vector [1, 2, 3] to "1, 2, 3"
 * @param v
 * @param delimiter
 * @return
 */
string join(vector<string> &v, string delimiter = ", "){

    string str = "";
    auto it = v.begin();
    for (;  it < v.end() - 1 ; ++it) {
        str += *it + delimiter;
    }

    return str += *(it++);
}


#endif // QUALITAIR_UTILS_HPP