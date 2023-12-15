#include "aoc.hpp"

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

VALUE walkMaze(VSTRING const& M, MVPAIR& V, DPAIR& Q, VALUE atu)
{
    return atu;
    // const auto& [j, i] = pos;
    // if (j < 0 || j >= M.size()) {
    //     return atu;
    // }
    // if (i < 0 || i >= M[j].size()) {
    //     return atu;
    // }
    // if (V.contains(pos)) {
    //     if (V.at(pos) < atu + 1) {
    //         return atu;
    //     }
    // }

    // atu++;
    // V.insert(pos);
    // for (const auto& p : V) {
    //     fmt::print("({},{}),", p.first, p.second);
    // }
    // fmt::print(" -> {},{},{}\n", j, i, atu);

    // const auto X   = M[j][i];
    // const auto res = [&]() {
    //     switch (X) {
    //         case '|':
    //             return std::max(walkMaze(M, V, P(j - 1, i), atu),
    //                             walkMaze(M, V, P(j + 1, i), atu));
    //         case '-':
    //             return std::max(walkMaze(M, V, P(j, i - 1), atu),
    //                             walkMaze(M, V, P(j, i + 1), atu));
    //         case 'L':
    //             return std::max(walkMaze(M, V, P(j - 1, i), atu),
    //                             walkMaze(M, V, P(j, i + 1), atu));
    //         case 'J':
    //             return std::max(walkMaze(M, V, P(j - 1, i), atu),
    //                             walkMaze(M, V, P(j, i - 1), atu));
    //         case '7':
    //             return std::max(walkMaze(M, V, P(j + 1, i), atu),
    //                             walkMaze(M, V, P(j, i - 1), atu));
    //         case 'F':
    //             return std::max(walkMaze(M, V, P(j + 1, i), atu),
    //                             walkMaze(M, V, P(j, i + 1), atu));
    //     }
    //     //case '.':
    //     return atu - 1;
    // }();

    // return std::max(atu, res);
}

VALUE walkStart(VSTRING const& M, PVALUE pos)
{
    const auto& [j, i] = pos;

    MVPAIR V;
    V[pos] = 0;

    DPAIR Q;
    if (j > 0) {
        const auto N = M[j - 1][i];
        if (N == '|' || N == 'F' || N == '7') {
            Q.emplace_back(P(j - 1, i));
        }
    }

    if (j + 1 < M.size()) {
        const auto S = M[j + 1][i];
        if (S == '|' || S == 'L' || S == 'J') {
            Q.emplace_back(P(j + 1, i));
        }
    }

    if (i > 0) {
        const auto W = M[j][i - 1];
        if (W == '-' || W == 'F' || W == 'L') {
            Q.emplace_back(P(j, i - 1));
        }
    }

    if (i + 1 < M[j].size()) {
        const auto E = M[j][i + 1];
        if (E == '-' || E == 'J' || E == '7') {
            Q.emplace_back(P(j, i + 1));
        }
    }

    return walkMaze(M, V, Q, 0);
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        throw std::runtime_error("Missing input file from command line");
    }

    const auto grid  = readFile(argv[1]);
    const auto start = findStart(grid);
    const auto ans1  = walkStart(grid, start);
    fmt::print("{}\n", ans1);

    return 0;
}
