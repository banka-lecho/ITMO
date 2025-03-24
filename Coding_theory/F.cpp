#include <iostream>
#include <cassert>
#include <cmath>
#include <random>
#include <vector>
#include <algorithm>

using namespace std;

mt19937 Generator;
int n, simple_polynom;
vector<int> elements_power;
int delta, m, k;
vector<int> power_elements;

class ElementOperators {
public:
    static int inverse(const int x) {
        return power_elements[n - elements_power[x]];
    }

    static int multiply(const int x1, const int x2) {
        if (x1 && x2) {
            return power_elements[elements_power[x1] + elements_power[x2]];
        }
        return 0;
    }
};

void normalization(vector<int> &x) {
    while (x.size() > 1 && x.back() == 0) x.pop_back();
}

class PoylomOperators {
public:
    static int evaluation(const vector<int> &polynom, int x) {
        int res = polynom.back();
        int n = static_cast<int>(polynom.size());
        for (int i = n - 2; i >= 0; i--) res = polynom[i] ^ ElementOperators::multiply(x, res);
        return res;
    }

    static vector<int> multiplication(const vector<int> &x1, const vector<int> &x2) {
        int n = static_cast<int>(x1.size());
        int m = static_cast<int>(x2.size());
        vector<int> result(n + m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) result[i + j] = result[i + j] ^ ElementOperators::multiply(x1[i], x2[j]);
        }
        normalization(result);
        return result;
    }

    static int exponentiation(const vector<int> &polynom) {
        int degree = 0;
        int n = static_cast<int>(polynom.size());
        for (int i = n - 1; i >= 0 && i < n; i--) {
            if (polynom[i]) {
                degree = i;
                break;
            }
        }
        return degree;
    }

    static pair<vector<int>, vector<int> > division(const vector<int> &x1, vector<int> x2) {
        normalization(x2);
        vector<int> remainder = x1;
        vector<int> quotient(x1.size());

        while (remainder.size() >= x2.size() && (remainder.back() >= 1 || remainder.size() >= 2)) {
            int inv = ElementOperators::inverse(x2.back());
            int coef = ElementOperators::multiply(remainder.back(), inv);
            int diff = remainder.size() - x2.size();
            quotient[diff] = coef;
            transform(
                diff + remainder.begin(), diff + x2.size() + remainder.begin(),
                x2.begin(),
                remainder.begin() + diff,
                [coef](int a, int b) { return a ^ ElementOperators::multiply(coef, b); }
            );
            normalization(remainder);
        }
        normalization(quotient);
        return {quotient, remainder};
    }

    static vector<int> addition(const vector<int> &x1, const vector<int> &x2) {
        int n = static_cast<int>(x1.size());
        int m = static_cast<int>(x2.size());
        if (n < m) return addition(x2, x1);
        vector<int> res = x1;
        for (int iter = 0; iter < m; iter++) res[iter] = res[iter] ^ x2[iter];
        return res;
    }
};


class Decoder {
public:
    static vector<int> apply_forny(vector<int> decoded, const vector<int> &lambda,
                                   const vector<int> &lambda_derivative, const vector<int> &gamma) {
        for (int i = 0; i < decoded.size(); ++i) {
            int el_inv = ElementOperators::inverse(power_elements[i]);
            int el_ev = PoylomOperators::evaluation(lambda, el_inv);
            if (el_ev == 0) {
                int den = PoylomOperators::evaluation(lambda_derivative, el_inv);
                decoded[i] = decoded[i] ^ ElementOperators::multiply(PoylomOperators::evaluation(gamma, el_inv),
                                                                     ElementOperators::inverse(den));
            }
        }
        return decoded;
    }

    static vector<int> decode(const vector<int> &y) {
        const auto t = (delta - 1) / 2;
        vector<int> syndromes(delta - 1);
        vector<int> a(delta);
        vector<int> ua{0}, ub{1};
        vector<int> ui;
        for (int i = 0; i < delta - 1; i++) syndromes[i] = PoylomOperators::evaluation(y, power_elements[i + 1]);

        vector<int> b = syndromes;
        a.back() = 1;

        while (t <= PoylomOperators::exponentiation(b)) {
            auto [q, r] = PoylomOperators::division(a, b);
            ui = PoylomOperators::addition(ua, PoylomOperators::multiplication(q, ub));
            swap(a, b);
            swap(b, r);
            swap(ua, ub);
            swap(ub, ui);
        }

        vector<int> gamma = b;
        vector<int> lambda = ub;

        int normalize_coeff = lambda[0];
        if (normalize_coeff > 1) {
            normalize_coeff = ElementOperators::inverse(normalize_coeff);
            auto multiply_by_coeff = [normalize_coeff](auto &vec) {
                for (auto &value: vec) {
                    value = ElementOperators::multiply(value, normalize_coeff);
                }
            };
            multiply_by_coeff(lambda);
            multiply_by_coeff(gamma);
        }
        int n = lambda.size();
        vector<int> derivative(n - 1);
        for (int k = 1; k < n; k++) {
            for (int l = 0; l < k; l++) derivative[k - 1] = derivative[k - 1] ^ lambda[k];
        }
        vector<int> decoded = apply_forny(y, lambda, derivative, gamma);
        return decoded;
    }
};

vector<int> encode(const vector<int> &a, const vector<int> &g) {
    vector<int> c(n - k + 1);
    c[n - k] = 1;
    c = PoylomOperators::multiplication(c, a);
    c = PoylomOperators::addition(c, PoylomOperators::division(c, g).second);
    c.resize(n);
    return c;
}

class Simulator {
public:
    static vector<int> generate_random_sequence(int k, uniform_int_distribution<> &elements) {
        vector<int> seq(k);
        for (int &i: seq) {
            i = elements(Generator);
        }
        return seq;
    }

    static vector<int> add_noise(const vector<int> &encoded, double noise, uniform_real_distribution<> &distribution,
                                 uniform_int_distribution<> &elements) {
        auto noised = encoded;
        for (auto &i: noised) {
            if (distribution(Generator) < noise) {
                i ^= elements(Generator);
            }
        }
        return noised;
    }

    static double simulate(const vector<int> &g, double noise, int iterations_count, int max_count_errors) {
        int iters = 0;
        int errs = 0;
        uniform_int_distribution<> elements(1, n);
        uniform_real_distribution<> distribution(0, 1);

        while (iters < iterations_count && errs < max_count_errors) {
            vector<int> seq = generate_random_sequence(k, elements);
            vector<int> encoded = encode(seq, g);
            vector<int> noised = add_noise(encoded, noise, distribution, elements);
            vector<int> decoded = Decoder::decode(noised);
            if (decoded != encoded) errs++;
            iters++;
        }
        return static_cast<double>(errs) / iters;
    }
};

void process_encode(const vector<int> &g, int k) {
    vector<int> a(k);
    for (int i = 0; i < a.size(); i++) cin >> a[i];
    auto encoded = encode(a, g);
    for (int i = 0; i < encoded.size(); i++) cout << encoded[i] << " ";
    cout << endl;
}

void process_decode() {
    vector<int> y(n);
    for (int i = 0; i < y.size(); i++) cin >> y[i];
    auto d = Decoder::decode(y);
    if (d.empty()) {
        cout << "ERROR" << endl;
    } else {
        for (int i = 0; i < d.size(); i++) {
            cout << d[i] << " ";
        }
        cout << endl;
    }
}

void process_simulate(const vector<int> &g) {
    int iterations_count, max_errors;
    double noise;
    cin >> noise >> iterations_count >> max_errors;
    cout << Simulator::simulate(g, noise, iterations_count, max_errors) << endl;
}

void generate_galois_field() {
    elements_power.resize(n + 1);
    power_elements.resize(2 * n);
    for (int i = 0, el = 1; i < n; i++) {
        elements_power[el] = i;
        power_elements[i] = el;
        el <<= 1;
        double degree_el = log2(el);
        if (static_cast<int>(floor(degree_el)) == m) {
            el = el ^ simple_polynom;
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin >> n >> simple_polynom >> delta;

    k = n - delta + 1;
    m = log2(n + 1);

    generate_galois_field();
    copy(power_elements.begin(), power_elements.begin() + n, power_elements.begin() + n);

    Generator = mt19937(1337);
    vector g = {1};
    for (int i = 0; i < delta - 1; ++i) {
        g = PoylomOperators::multiplication(g, {power_elements[i + 1], 1});
    }

    cout << k << endl;
    for (int i = 0; i < g.size(); i++) {
        cout << g[i] << " ";
    }
    cout << endl;

    string command;
    while (cin >> command) {
        if (command == "Encode") {
            process_encode(g, k);
        } else if (command == "Decode") {
            process_decode();
        } else if (command == "Simulate") {
            process_simulate(g);
        } else {
            cout << "FAILURE" << endl;
            break;
        }
    }
}
