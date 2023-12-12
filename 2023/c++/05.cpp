#include "aoc.hpp"

struct ELEM {
    VALUE src, dst, length;
};
using VELEM = std::vector<ELEM>;

VELEM readMap(VSTRING const& L, size_t& i)
{
    VELEM V;
    for (; i < L.size(); ++i) {
        if (L[i].empty()) {
            break;
        }
        std::stringstream ss(L[i]);
        ELEM              elem;
        ss >> elem.dst >> elem.src >> elem.length;
        V.push_back(elem);
    }
    std::sort(V.begin(), V.end(), [](auto& left, auto& right) { return left.src < right.src; });
    return V;
}

std::vector<PVALUE> seedRange(VVALUE const& seeds)
{
    FMT_ASSERT(seeds.size() % 2 == 0, "Invalid SEED array!");
    std::vector<PVALUE> pairs;
    for (size_t i = 0; i < seeds.size(); i += 2) {
        pairs.push_back(P(seeds[i], seeds[i] + seeds[i + 1]));
    }
    return pairs;
}

std::vector<PVALUE> seedValues(VVALUE const& seeds)
{
    std::vector<PVALUE> pairs;
    for (const auto& seed : seeds) {
        pairs.push_back(P(seed, seed + 1));
    }
    return pairs;
}

std::vector<PVALUE> parseSeeds(VSTRING const& lines, bool expand_seeds)
{
    const auto& line = lines[0];
    if (!line.contains("seeds")) {
        throw std::runtime_error("Invalid input file!");
    }
    const auto seeds = parseNumbers(line.substr(line.find_first_of(':') + 1));
    return expand_seeds ? seedRange(seeds) : seedValues(seeds);
}

std::vector<VELEM> parseMaps(VSTRING const& lines)
{
    std::vector<VELEM> maps;
    for (size_t i = 0; i < lines.size(); ++i) {
        const auto& line = lines[i];
        if (!line.contains("map:")) {
            continue;
        }
        maps.push_back(readMap(lines, ++i));
    }
    return maps;
}

VALUE walk(VALUE val, std::vector<VELEM> const& maps)
{
    for (const auto& map : maps) {
        for (const auto& elem : map) {
            if (elem.src > val) {
                break;
            }
            if (elem.src <= val && val < elem.src + elem.length) {
                val += (elem.dst - elem.src);
                break;
            }
        }
    }
    return val;
}

VALUE processPair(PVALUE pair, std::vector<VELEM> const& maps)
{
    VALUE ans = std::numeric_limits<VALUE>::max();
    for (VALUE val = pair.first; val < pair.second; ++val) {
        const auto res = walk(val, maps);
        if (res < ans) {
            ans = res;
        }
    }
    return ans;
}

VALUE processSeeds(std::vector<PVALUE> const& seeds, std::vector<VELEM> const& maps)
{
    std::vector<std::future<VALUE>> tasks;
    for (const auto& pair : seeds) {
        tasks.push_back(std::async(std::launch::async, processPair, pair, maps));
    }
    VALUE ans = std::numeric_limits<VALUE>::max();
    for (auto& task : tasks) {
        if (task.valid()) {
            const auto res = task.get();
            if (res < ans) {
                ans = res;
            }
        }
    }
    return ans;
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        throw std::runtime_error("Missing input file from command line");
    }

    const auto lines  = readFile(argv[1]);
    const auto maps   = parseMaps(lines);
    const auto seeds1 = parseSeeds(lines, false);
    const auto ans1   = processSeeds(seeds1, maps);
    fmt::print("{}\n", ans1);

    const auto seeds2 = parseSeeds(lines, true);
    const auto ans2   = processSeeds(seeds2, maps);
    fmt::print("{}\n", ans2);

    return 0;
}
