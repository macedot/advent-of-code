#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <functional>
#include <filesystem>
#include <string>
#include <ranges>
#include <map>
#include <tuple>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#define FMT_HEADER_ONLY
#include <fmt/format.h>

using VALUE   = int32_t;
using IPAIR   = std::pair<VALUE, VALUE>;
using VSTRING = std::vector<std::string>;

struct hashFunction {
    size_t operator()(const IPAIR& x) const { return static_cast<size_t>(x.first) ^ static_cast<size_t>(x.second); }
};

using SPAIR = std::unordered_set<IPAIR, hashFunction>;
using MPAIR = std::unordered_map<IPAIR, SPAIR, hashFunction>;

#define DUMP(var) fmt::print("{} ({}) : {} = {}\n", __func__, __LINE__, #var, var)

IPAIR P(auto i, auto j)
{
    return std::make_pair(static_cast<VALUE>(i), static_cast<VALUE>(j));
}

std::vector<std::string> readFile(std::filesystem::path const& inputFile)
{
    std::ifstream            ifs(inputFile, std::ios::binary);
    std::vector<std::string> lines;

    if (!ifs) {
        throw std::runtime_error("Unable to open input file: " + inputFile.string());
    }

    std::string line;
    while (std::getline(ifs, line)) {
        lines.push_back(line);
    }

    return lines;
}

SPAIR parseData(const VSTRING& lines)
{
    SPAIR set;
    for (size_t i = 0; i < lines.size(); ++i) {
        for (size_t j = 0; j < lines[i].size(); ++j) {
            if (lines[i][j] == '#') {
                set.emplace(P(i, j));
            }
        }
    }
    return set;
}

bool can_go(const SPAIR& T, const IPAIR& p)
{
    for (int k1 = -1; k1 <= 1; ++k1) {
        for (int k2 = -1; k2 <= 1; ++k2) {
            if (k1 == 0 && k2 == 0) {
                continue;
            }
            if (T.find(P(p.first + k1, p.second + k2)) != T.end()) {
                return false;
            }
        }
    }
    return true;
}

struct OPTS {
    bool  valid;
    IPAIR pair;
};
using VOPTS = std::vector<OPTS>;

IPAIR decide(const SPAIR& T, size_t round, const IPAIR& p)
{
    if (can_go(T, p)) {
        return p;
    }

    auto check_i = [&T](VALUE i, VALUE j) {
        for (int k = -1; k <= 1; ++k) {
            if (T.find(P(i + k, j)) != T.end()) {
                return false;
            }
        }
        return true;
    };

    auto check_j = [&T](VALUE i, VALUE j) {
        for (int k = -1; k <= 1; ++k) {
            if (T.find(P(i, j + k)) != T.end()) {
                return false;
            }
        }
        return true;
    };

    const VOPTS opts = {
        { check_j(p.first - 1, p.second), P(p.first - 1, p.second) },
        { check_j(p.first + 1, p.second), P(p.first + 1, p.second) },
        { check_i(p.first, p.second - 1), P(p.first, p.second - 1) },
        { check_i(p.first, p.second + 1), P(p.first, p.second + 1) },
    };

    for (size_t k = 0; k < opts.size(); ++k) {
        if (const size_t idx = (k + round) % 4; opts[idx].valid) {
            return opts[idx].pair;
        }
    }

    return p;
}

template<size_t IDX>
auto get_max(const SPAIR& N) -> VALUE
{
    return std::get<IDX>(
      *std::max_element(N.begin(), N.end(), [](auto& l, auto& r) { return std::get<IDX>(l) < std::get<IDX>(r); }));
};

template<size_t IDX>
auto get_min(const SPAIR& N) -> VALUE
{
    return std::get<IDX>(
      *std::min_element(N.begin(), N.end(), [](auto& l, auto& r) { return std::get<IDX>(l) < std::get<IDX>(r); }));
};

int main(int argc, char* argv[])
{
    if (argc < 2) {
        throw std::runtime_error("Missing input file from command line");
    }

    SPAIR T = parseData(readFile(argv[1]));

    VALUE total1 = 0, total2 = 0;

    for (size_t r = 0; r < 1000; ++r) {
        MPAIR Q;
        for (const auto& p : T) {
            Q[decide(T, r, p)].emplace(p);
        }
        SPAIR N;
        for (auto& [k, v] : Q) {
            if (v.size() == 1) {
                N.emplace(k);
            }
            else {
                N.merge(v);
            }
        }
        if (r == 9) {
            const VALUE x = get_max<0>(N) - get_min<0>(N) + 1;
            const VALUE y = get_max<1>(N) - get_min<1>(N) + 1;
            total1        = x * y - static_cast<VALUE>(T.size());
        }
        if (N == T) {
            total2 = static_cast<VALUE>(r + 1);
            break;
        }
        T = N;
    }

    fmt::print("{}\n", total1);
    fmt::print("{}\n", total2);

    return 0;
}
