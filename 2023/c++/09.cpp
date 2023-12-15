#include "aoc.hpp"

using VVALUES = std::vector<VVALUE>;

VVALUE getDiff(VVALUE const& V, bool& all_zero)
{
    if (V.size() < 2) {
        return VVALUE{ V.front() };
    }
    all_zero = true;
    VVALUE D;
    VALUE  d;
    for (size_t i = 0; i < V.size() - 1; ++i) {
        d = V[i + 1] - V[i];
        all_zero &= (d == 0);
        D.push_back(d);
    }
    return D;
}

VVALUES buildValues(STRING const& line)
{
    VVALUES values;
    values.push_back(parseNumbers(line));
    for (bool all_zero = false;;) {
        auto res = getDiff(values.back(), all_zero);
        if (all_zero) {
            break;
        }
        values.push_back(res);
    }
    return values;
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        throw std::runtime_error("Missing input file from command line");
    }

    const auto lines = readFile(argv[1]);

    VALUE ans1 = 0, ans2 = 0;
    for (const auto& line : lines) {
        const auto values = buildValues(line);
        VALUE      front = 0, back = 0;
        for (VALUE i = values.size() - 1; i >= 0; --i) {
            back += values[i].back();
            front = values[i].front() - front;
        }
        ans1 += back;
        ans2 += front;
    }
    fmt::print("{}\n", ans1);
    fmt::print("{}\n", ans2);

    return 0;
}
