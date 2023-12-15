#include "aoc.hpp"

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

VALUE walkMaze(VSTRING const& M, PVALUE start)
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

    SPAIR V;
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

int main(int argc, char* argv[])
{
    if (argc < 2) {
        throw std::runtime_error("Missing input file from command line");
    }

    const auto grid  = readFile(argv[1]);
    const auto start = findStart(grid);
    const auto ans1  = walkMaze(grid, start);
    fmt::print("{}\n", ans1);

    return 0;
}
