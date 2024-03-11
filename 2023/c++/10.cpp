#include "aoc.hpp"

constexpr auto IN  = 'I';
constexpr auto OUT = 'O';

struct ELEM {
    PVALUE pos;
    VALUE  value;
};
using QUEUE = std::deque<ELEM>;

PVALUE findStart(VSTRING const& M)
{
    PVALUE start;
    for (const auto& row : M) {
        const auto pos = row.find_first_of('S');
        if (pos != std::string::npos) {
            start.second = pos;
            return start;
        }
        ++start.first;
    }
    throw std::runtime_error("Invalid input!");
}

VALUE walkMaze(VSTRING const& M, SPAIR& V, PVALUE start)
{
    const auto& [j, i] = start;

    QUEUE Q;
    if (j > 0) {
        const auto N = M[j - 1][i];
        if (N == '|' || N == 'F' || N == '7') {
            Q.emplace_back(ELEM{ P(j - 1, i), 1 });
        }
    }

    if (j + 1 < M.size()) {
        const auto S = M[j + 1][i];
        if (S == '|' || S == 'L' || S == 'J') {
            Q.emplace_back(ELEM{ P(j + 1, i), 1 });
        }
    }

    if (i > 0) {
        const auto W = M[j][i - 1];
        if (W == '-' || W == 'F' || W == 'L') {
            Q.emplace_back(ELEM{ P(j, i - 1), 1 });
        }
    }

    if (i + 1 < M[j].size()) {
        const auto E = M[j][i + 1];
        if (E == '-' || E == 'J' || E == '7') {
            Q.emplace_back(ELEM{ P(j, i + 1), 1 });
        }
    }

    V.insert(start);

    VALUE res = 0;
    while (!Q.empty()) {
        const auto elem = Q.front();
        Q.pop_front();

        const auto& [j, i] = elem.pos;
        if (j < 0 || j >= M.size()) {
            continue;
        }
        if (i < 0 || i >= M[j].size()) {
            continue;
        }
        if (V.contains(elem.pos)) {
            continue;
        }

        V.insert(elem.pos);
        res = std::max(res, elem.value);

        switch (M[j][i]) {
            case '|':
                Q.emplace_back(ELEM{ P(j - 1, i), elem.value + 1 });
                Q.emplace_back(ELEM{ P(j + 1, i), elem.value + 1 });
                break;
            case '-':
                Q.emplace_back(ELEM{ P(j, i - 1), elem.value + 1 });
                Q.emplace_back(ELEM{ P(j, i + 1), elem.value + 1 });
                break;
            case 'L':
                Q.emplace_back(ELEM{ P(j - 1, i), elem.value + 1 });
                Q.emplace_back(ELEM{ P(j, i + 1), elem.value + 1 });
                break;
            case 'J':
                Q.emplace_back(ELEM{ P(j - 1, i), elem.value + 1 });
                Q.emplace_back(ELEM{ P(j, i - 1), elem.value + 1 });
                break;
            case '7':
                Q.emplace_back(ELEM{ P(j + 1, i), elem.value + 1 });
                Q.emplace_back(ELEM{ P(j, i - 1), elem.value + 1 });
                break;
            case 'F':
                Q.emplace_back(ELEM{ P(j + 1, i), elem.value + 1 });
                Q.emplace_back(ELEM{ P(j, i + 1), elem.value + 1 });
                break;
        }
    }

    return res;
}

VALUE countEnclosed(VSTRING M, SPAIR const& V, PVALUE start)
{
    const auto& [sj, si] = start;

    M[sj][si] = 'L'; // TODO: hack :(

    for (size_t j = 0; j < M.size(); ++j) {
        for (size_t i = 0; i < M[j].size(); ++i) {
            if (!V.contains(P(j, i))) {
                M[j][i] = (j == 0 || i == 0 || j == M.size() - 1 ||
                           i == M[j].size() - 1)
                            ? OUT
                            : '.'; // clear invalid
            }
        }
    }

    auto propagate = [&](VALUE j, VALUE i) {
        if (M[j][i] != '.') {
            return M[j][i];
        }
        if (j > 0 && M[j - 1][i] == OUT) {
            return OUT;
        }
        if (i > 0 && M[j][i - 1] == OUT) {
            return OUT;
        }
        if (j < M.size() - 1 && M[j + 1][i] == OUT) {
            return OUT;
        }
        if (i < M[j].size() - 1 && M[j][i + 1] == OUT) {
            return OUT;
        }
        return M[j][i];
    };

    for (auto round = 0; round < 2; ++round) {
        for (size_t j = 1; j < M.size() - 1; ++j) {
            for (size_t i = 1; i < M[0].size() - 1; ++i) {
                M[j][i] = propagate(j, i);
            }
            for (size_t i = M[0].size() - 2; i > 0; --i) {
                M[j][i] = propagate(j, i);
            }
        }
        for (size_t i = 1; i < M[0].size() - 1; ++i) {
            for (size_t j = 1; j < M.size() - 1; ++j) {
                M[j][i] = propagate(j, i);
            }
            for (size_t j = M.size() - 2; j > 0; --j) {
                M[j][i] = propagate(j, i);
            }
        }
    }

    for (const auto& line : M) {
        fmt::print("{}\n", line);
    }

    auto count_bound = [&](VALUE j, VALUE i) {
        VALUE count = 0;
        for (size_t x = 0; x < i; ++x) {
            if (!V.contains(P(j, x))) {
                continue;
            }
            if (M[j][x] == OUT) {
                break;
            }
            count += (M[j][x] == '|' || M[j][x] == 'J' || M[j][x] == 'L');
        }
        return count;
    };

    VALUE inside = 0;
    for (size_t j = 0; j < M.size(); ++j) {
        for (size_t i = 0; i < M[j].size(); ++i) {
            if (V.contains(P(j, i))) {
                continue;
            }
            if (count_bound(j, i) % 2 != 0) {
                M[j][i] = IN;
                ++inside;
            }
            else {
                M[j][i] = OUT;
            }
        }
    }

    fmt::print("\n");
    for (const auto& line : M) {
        fmt::print("{}\n", line);
    }

    return inside;
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        throw std::runtime_error("Missing input file from command line");
    }

    const auto grid = readFile(argv[1]);

    SPAIR      visited;
    const auto start = findStart(grid);
    const auto ans1  = walkMaze(grid, visited, start);
    fmt::print("{}\n", ans1);

    const auto ans2 = countEnclosed(grid, visited, start);
    fmt::print("{}\n", ans2);

    return 0;
}
