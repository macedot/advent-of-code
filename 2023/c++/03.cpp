#include "aoc.hpp"

SVALUE findSymbols(std::string const& L)
{
    SVALUE symbols;
    for (VALUE k = 0; k < L.size(); ++k) {
        if (std::isdigit(L[k]) || L[k] == '.') {
            continue;
        }
        symbols.insert(k);
    }
    return symbols;
}

VVALUE findNumbers(std::string const& L, VALUE lineSize, SVALUE const& S)
{
    auto isValid = [&L, &S, lineSize](VALUE start, VALUE size) -> bool {
        const auto before = (start > 0) ? start - 1 : start;
        const auto after  = [&]() {
            auto res = start + size;
            if (res % lineSize == 0 || res >= L.size()) {
                return res - 1;
            }
            return res;
        }();

        if (S.find(before) != S.end() || S.find(after) != S.end()) {
            return true;
        }

        if (before - lineSize > 0) {
            for (VALUE w = before - lineSize; w <= after - lineSize; ++w) {
                if (S.find(w) != S.end()) {
                    return true;
                }
            }
        }

        if (after + lineSize < L.size()) {
            for (VALUE w = before + lineSize; w <= after + lineSize; ++w) {
                if (S.find(w) != S.end()) {
                    return true;
                }
            }
        }

        return false;
    };

    VVALUE numbers;
    for (VALUE k = 0; k < L.size(); ++k) {
        const auto start = k;
        while (k < L.size() && std::isdigit(L[k])) {
            ++k;
        }
        const auto length = k - start;
        if (length > 0) {
            if (isValid(start, length)) {
                numbers.push_back(std::stoll(L.substr(start, length)));
            }
        }
    }
    return numbers;
}

SVALUE findGears(std::string const& L)
{
    SVALUE symbols;
    for (VALUE k = 0; k < L.size(); ++k) {
        if (L[k] == '*') {
            symbols.insert(k);
        }
    }
    return symbols;
}

VVALUE findRatios(std::string const& L, VALUE lineSize, SVALUE const& G)
{
    VVALUE ratios;
    for (const auto& g : G) {
        VVALUE gears;

        // has something at its left
        if (g > 0) {
            VALUE k = g;
            while (std::isdigit(L[k - 1])) {
                --k;
                if (k % lineSize == 0) {
                    break;
                }
            }
            if (k < g) {
                gears.push_back(std::stoll(L.substr(k, g - k)));
            }
        }

        // has something at its right
        if (g + 1 < L.size()) {
            VALUE k = g;
            while (std::isdigit(L[k + 1])) {
                ++k;
                if (k >= L.size() || k % lineSize == 0) {
                    break;
                }
            }
            if (g < k) {
                gears.push_back(std::stoll(L.substr(g + 1, k - g)));
            }
        }

        auto add_number_from_pos = [&gears, &L, lineSize](VALUE p) {
            VALUE start = p;
            VALUE end   = p;
            while (std::isdigit(L[start - 1])) {
                --start;
                if (start % lineSize == 0) {
                    break;
                }
            }
            while (std::isdigit(L[end + 1])) {
                ++end;
                if (end % lineSize == 0) {
                    break;
                }
            }
            gears.push_back(std::stoll(L.substr(start, end - start + 1)));
        };

        // north
        if (const auto north = g - lineSize; north >= 0) {
            if (std::isdigit(L[north])) {
                add_number_from_pos(north);
            }
            else {
                if (north - 1 >= 0 && std::isdigit(L[north - 1])) {
                    add_number_from_pos(north - 1);
                }
                if (north + 1 % lineSize != 0 && std::isdigit(L[north + 1])) {
                    add_number_from_pos(north + 1);
                }
            }
        }

        if (const auto south = g + lineSize; south < L.size()) {
            if (std::isdigit(L[south])) {
                add_number_from_pos(south);
            }
            else {
                if (south - 1 % lineSize != 0 && std::isdigit(L[south - 1])) {
                    add_number_from_pos(south - 1);
                }
                if (south + 1 < L.size() && std::isdigit(L[south + 1])) {
                    add_number_from_pos(south + 1);
                }
            }
        }

        if (gears.size() > 1) {
            const auto acc =
              std::accumulate(gears.begin(), gears.end(), VALUE(1), std::multiplies<VALUE>());
            ratios.push_back(acc);
        }
    }
    return ratios;
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        throw std::runtime_error("Missing input file from command line");
    }

    VALUE      lineSize = 0;
    const auto values   = readFileString(argv[1], lineSize);

    const auto symbols = findSymbols(values);
    const auto numbers = findNumbers(values, lineSize, symbols);
    const auto ans1    = std::reduce(numbers.begin(), numbers.end());
    fmt::print("{}\n", ans1);

    const auto gears  = findGears(values);
    const auto ratios = findRatios(values, lineSize, gears);
    const auto ans2   = std::reduce(ratios.begin(), ratios.end());
    fmt::print("{}\n", ans2);

    return 0;
}
