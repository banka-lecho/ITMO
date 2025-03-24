#include <random>
#include <iostream>
#include <set>
#include <iomanip>
#include <algorithm>
#define all(v) v.begin(), v.end()


std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> uniform(0, 1);
std::uniform_real_distribution<double> distribution(0, 1);

double noise_level;
int max_count_iterations, max_errors;

void printVector(std::ostream &stream, const std::vector<int> &v) {
    for (int i = 0; i < v.size(); i++) {
        stream << v[i] << " ";
    }
    stream << '\n';
}

class Operators {
public:
    static std::vector<int> xor_vectors(const std::vector<int> &first, const std::vector<int> &second) {
        std::vector result(first);
        for (int i = 0; i < first.size(); i++) {
            result[i] = result[i] ^ second[i];
        }
        return result;
    }

    static int multiplication(const int first, const int second, const int n, const std::vector<int> &alphas,
                              const std::vector<int> &degrees) {
        if (first * second == 0) {
            return 0;
        }
        return alphas[(degrees[second] + degrees[first]) % n];
    }

    static std::vector<int> multiplication(const std::vector<int> &v, int value, const int n,
                                           const std::vector<int> &alphas,
                                           const std::vector<int> &degrees) {
        std::vector result(v);
        int v_size = v.size();
        for (int j = 0; j < v_size; j++) {
            result[j] = multiplication(v[j], value, n, alphas, degrees);
        }
        return result;
    }

    static std::vector<int> multiplication(const std::vector<int> &first, const std::vector<int> &second, const int n,
                                           const std::vector<int> &alphas,
                                           const std::vector<int> &degrees) {
        int second_size = second.size();
        int first_size = first.size();
        std::vector res(first_size + second_size - 1, 0);
        for (int i = 0; i < first_size; i++) {
            for (int j = 0; j < second_size; j++) {
                int mult = multiplication(first[i], second[j], n, alphas, degrees);
                res[i + j] ^= mult;
            }
        }
        return res;
    }
};

class Modules {
public:
    static int index_of_maxbit(int val) {
        double index = 0;
        while (val > 0) {
            ++index;
            val >>= 1;
        }
        return index;
    }

    static int modul_by_p(int result, int p_max_index, int p) {
        int shift = index_of_maxbit(result) - p_max_index;
        while (shift >= 0) {
            result = result ^ p << shift;
            int index_maxbit = index_of_maxbit(result);
            shift = index_maxbit - p_max_index;
        }
        return result;
    }

    static std::vector<int> modul_by_g(const std::vector<int> &v, std::vector<int> g, int n) {
        int g_size = g.size();
        std::vector<int> result = v;
        int v_size = v.size();
        for (int i = 0; i < v_size - g_size + 1; i++) {
            int new_ind = n - 1 - i;
            if (result[new_ind] == 0) {
                continue;
            }
            int j = 0;
            while (j < g.size()) {
                result[n - g_size - i + j] ^= g[j];
                j++;
            }
        }
        return result;
    }
};

class Shift {
public:
    static std::vector<int> left(int shift, const std::vector<int> &v) {
        std::vector result(v);
        result.resize(v.size() + shift, 0);
        return result;
    }

    static std::vector<int> right(int shift, const std::vector<int> &v) {
        std::vector result(shift + v.size(), 0);
        copy(v.begin(), v.end(), result.begin() + shift);
        return result;
    }
};

class Decoder {
public:
    int n = 0, k = 0, p = 0, dist = 0, p_maxi_index = 0;
    double noise_level;
    int iters, max_count_errors;
    std::vector<int> alphas, degrees, g;

    Decoder(int distance, int n, int primitive) {
        this->max_count_errors = 0;
        this->n = n;
        this->noise_level = 0;
        this->p = primitive;
        this->p_maxi_index = Modules::index_of_maxbit(p);
        this->dist = distance;
        this->iters = 0;
        this->alphas.resize(n);
        alphas[0] = 1;
        this->degrees.resize(n + 1);

        int i = 1;
        while (i < n) {
            alphas[i] = Modules::modul_by_p(alphas[i - 1] << 1, p_maxi_index, p);
            degrees[alphas[i]] = i;
            i++;
        }

        g = {1};
        std::set<int> used;
        int ind = 1;
        while (ind < dist) {
            int degree_of_x = ind;
            std::vector<int> cyclotomic_class;
            if (used.end() == used.find(degree_of_x)) {
                cyclotomic_class.clear();
                do {
                    cyclotomic_class.push_back(degree_of_x);
                    used.insert(degree_of_x);
                    degree_of_x <<= 1;
                    degree_of_x = degree_of_x % n;
                } while (used.find(degree_of_x) == used.end());

                for (int j = 0; j < cyclotomic_class.size(); j++) {
                    g = Operators::multiplication(g, {alphas[cyclotomic_class[j]], 1}, n, alphas, degrees);
                }
            }
            ind++;
        }
        this->k = n + 1 - g.size();
        std::cout << k << '\n';
        printVector(std::cout, g);
    }

    std::vector<int> decode(const std::vector<int> &y) {
        std::vector<int> S(dist - 1);
        int size_s = S.size();
        int acc, index;
        for (int j = 1; j <= size_s; j++) {
            acc = 0;
            for (int k = 0; k < y.size(); k++) {
                index = j * k % n;
                int mult = Operators::multiplication(y[k], alphas[index], n, alphas, degrees);
                acc ^= mult;
            }
            S[j - 1] = acc;
        }
        int l = 0;
        std::vector L = {1};
        std::vector B = {1};
        int delta;
        for (int r = 1; r < dist; r++) {
            delta = 0;
            for (int j = 0; j <= l; j++) {
                int mult = Operators::multiplication(L[j], S[r - j - 1], n, alphas, degrees);
                delta ^= mult;
            }

            B = Shift::right(1, B);

            if (delta != 0) {
                L = Shift::left(B.size() - L.size(), L);
                B = Shift::left(L.size() - B.size(), B);
                std::vector<int> mult = Operators::multiplication(B, delta, n, alphas, degrees);
                std::vector<int> T = Operators::xor_vectors(L, mult);

                if (2 * l <= r - 1) {
                    B = Operators::multiplication(L, alphas[(n - degrees[delta]) % n], n, alphas, degrees);
                    l = r - l;
                }
                L = T;
            }
        }
        return get_result_decoded(L, y);
    }

    [[nodiscard]] std::vector<int> encode(std::vector<int> &x) {
        std::vector<int> encoded = Shift::right(n - k, x);
        return Operators::xor_vectors(encoded, Modules::modul_by_g(encoded, g, n));
    }

    std::vector<int> get_result_decoded(std::vector<int> l, std::vector<int> y) {
        // Формирование результата
        std::vector<int> decoded = y;
        int acc = 0;
        int l_size = l.size();
        for (int i = 1; i <= n; i++) {
            acc = 0;
            for (int j = 0; j < l_size; j++) {
                int mult = Operators::multiplication(l[j], alphas[degrees[i] * j % n], n, alphas, degrees);
                acc ^= mult;
            }
            if (acc == 0) {
                int new_index = (n - degrees[i]) % n;
                decoded[new_index] = !decoded[new_index];
            }
        }
        return decoded;
    }

    double run_simulate(int max_count_errors, double noise_level, int max_count_iterations) {
        int errors = 0;
        std::vector<int> x;
        for (int iter = 0; iter < max_count_iterations; iter++) {
            x.clear();
            x.resize(k);
            std::generate_n(x.begin(), k, [&]() { return uniform(gen); });

            auto encoded = encode(x);

            std::vector<int> withNoise(encoded.size());
            std::transform(encoded.begin(), encoded.end(), withNoise.begin(), [&](int bit) {
                return distribution(gen) < noise_level ? !bit : bit;
            });

            auto decoded = decode(withNoise);

            auto mismatchPair = std::mismatch(encoded.begin(), encoded.end(), decoded.begin());
            if (mismatchPair.first != encoded.end()) {
                errors++;
            }
            if (max_count_errors == errors) {
                return 1.0 * errors / (1 + iter);
            }
        }
        return 1.0 * errors / max_count_iterations;
    }
};

void readVector(std::vector<int> &vec, int size) {
    for (int i = 0; i < size; ++i) {
        std::cin >> vec[i];
    }
}

void process_encode(Decoder &decoder) {
    std::vector<int> x(decoder.k);
    readVector(x, decoder.k);
    auto encoded = decoder.encode(x);
    printVector(std::cout, move(encoded));
}

void process_decode(Decoder &decoder, int n) {
    std::vector<int> x(n);
    readVector(x, n);
    auto decoded = decoder.decode(x);
    printVector(std::cout, move(decoded));
}

void process_simulate(Decoder &decoder) {
    std::cin >> noise_level >> max_count_iterations >> max_errors;
    std::cout << std::setprecision(16);
    std::cout << decoder.run_simulate(max_errors, noise_level, max_count_iterations) << '\n';
}

int main() {
    int n, primitive, distance;
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    std::cin >> n >> primitive >> distance;
    Decoder decoder = Decoder(distance, n, primitive);
    while (std::cin) {
        std::string command;
        std::cin >> command;
        if (command == "Encode") {
            process_encode(decoder);
        } else if (command == "Decode") {
            process_decode(decoder, n);
        } else if (command == "Simulate") {
            process_simulate(decoder);
        }
    }
    return 0;
}
