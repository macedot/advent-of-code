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

#define DUMP(var) fmt::print("{} ({}) : {} = {}\n", __func__, __LINE__, #var, var)

using ValueT = int64_t;
struct Elem {
    ValueT      sx, sy, bx, by, d;
    std::string str() const { return fmt::format("({:10d} {:10d} {:10d} {:10d} {:10d})", sx, sy, bx, by, d); }
};
using VElems  = std::vector<Elem>;
using VPairs  = std::vector<std::pair<ValueT, ValueT>>;
using SValueT = std::unordered_set<ValueT>;
using RESULT  = std::pair<VPairs, SValueT>;

VPairs merge_intervals(VPairs& intervals)
{
    std::sort(intervals.begin(), intervals.end());
    VPairs merged{ intervals[0] };
    for (size_t k = 1; k < intervals.size(); ++k) {
        const auto& p   = intervals[k];
        auto&       qhi = merged.back();
        if (p.first > qhi.second + 1) {
            merged.push_back(p);
        }
        else {
            qhi.second = std::max(qhi.second, p.second);
        }
    }
    return merged;
}

RESULT solver(const VElems& G, ValueT y_target)
{
    SValueT known;
    VPairs  intervals;
    for (const auto& e : G) {
        const auto o = e.d - std::abs(e.sy - y_target);
        if (o < 0) {
            continue;
        }
        intervals.emplace_back(std::make_pair(e.sx - o, e.sx + o));
        if (e.by == y_target) {
            known.emplace(e.bx);
        }
    }
    return std::make_pair(merge_intervals(intervals), known);
}

ValueT solve1(const VElems& G, ValueT y_target)
{
    ValueT     total = 0;
    const auto res   = solver(G, y_target);
    for (const auto& [lo, hi] : res.first) {
        total += static_cast<ValueT>(hi - lo + 1);
        for (const auto x : res.second) {
            if (lo <= x && x <= hi) {
                --total;
            }
        }
    }
    return total;
}

ValueT solve2(const VElems& G, ValueT y_target)
{
    for (ValueT Y = 0; Y <= y_target; ++Y) {
        RESULT res = solver(G, Y);
        ValueT x   = 0;
        for (const auto& [lo, hi] : res.first) {
            if (x < lo) {
                return x * y_target + Y;
            }
            x = std::max(x, hi + 1);
            if (x > y_target) {
                break;
            }
        }
    }
    throw std::runtime_error("UNABLE TO FIND SOLUTION!");
}

std::string& filter_string(std::string& s)
{
    s.erase(std::remove_if(
              s.begin(), s.end(), [](unsigned char ch) { return ch != '-' && !std::isdigit(ch) && !std::isspace(ch); }),
            s.end());
    return s;
}

Elem parse_elem(const std::string& inputString)
{
    Elem               elem;
    std::istringstream ss(inputString);
    if (ss >> elem.sx >> elem.sy >> elem.bx >> elem.by) {
        elem.d = std::abs(elem.sx - elem.bx) + std::abs(elem.sy - elem.by);
        return elem;
    }
    throw std::runtime_error(fmt::format("Invalid input string: [{}]", inputString));
}

VElems load_data(const std::filesystem::path& inputFile)
{
    std::ifstream ifs(inputFile, std::ios::binary);
    if (!ifs) {
        throw std::runtime_error("Unable to open input file: " + inputFile.string());
    }

    VElems      velems;
    std::string line;
    while (std::getline(ifs, line)) {
        velems.push_back(parse_elem(filter_string(line)));
    }

    return velems;
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        throw std::runtime_error("Missing input file from command line");
    }

    const VElems G = load_data(argv[1]);
    fmt::print("{}\n", solve1(G, 2000000));
    fmt::print("{}\n", solve2(G, 4000000));

    return 0;
}
