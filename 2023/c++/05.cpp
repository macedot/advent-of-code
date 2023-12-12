#include "aoc.hpp"

struct MapElem {
    VALUE dst_start;
    VALUE src_start;
    VALUE src_length;
};

using MAP = std::unordered_map<VALUE, VPAIR>;

VALUE parse1(VSTRING const& lines)
{
    VALUE  res = 0;
    VVALUE seeds;

    std::unordered_map<std::string, std::vector<MapElem>> map;
    for (const auto& line : lines) {
        if (line.empty()) {
            continue;
        }
        const auto parts = split(line, ':');
        if (parts[0] == "seeds") {
            seeds = parseNumbers(parts[1]);
            DUMP(join(seeds));
            continue;
        }
        const auto name = split(parts[0], ' ');
    }

    return res;
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        throw std::runtime_error("Missing input file from command line");
    }

    const auto lines = readFile(argv[1]);
    const auto ans1  = parse1(lines);
    fmt::print("{}\n", ans1);

    // const auto ans2 = parse2(cards);
    // fmt::print("{}\n", ans2);

    return 0;
}
