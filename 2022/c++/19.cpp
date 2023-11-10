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

#define FMT_HEADER_ONLY
#include <fmt/format.h>

#define DUMP(var) fmt::print("{} ({}) : {} = {}\n", __func__, __LINE__, #var, var)

using VTYPE  = int;
using VALUES = std::vector<VTYPE>;
using VTUPLE = std::tuple<VTYPE, VTYPE, VTYPE, VTYPE, VTYPE, VTYPE>;

int timeto(int req, int cur, int prod)
{
    return 1 + std::max(0, ((req - cur + prod - 1) / prod));
}

VTYPE processBlueprint(const VALUES& blueprint, VTYPE minutes)
{
    auto const& co   = blueprint[1];
    auto const& cc   = blueprint[2];
    auto const& cb1  = blueprint[3];
    auto const& cb2  = blueprint[4];
    auto const& cg1  = blueprint[5];
    auto const& cg2  = blueprint[6];
    const auto  mo   = std::max(cc, std::max(cb1, cg1));
    VTYPE       maxx = 0;

    std::function<void(int, int, int, int, int, int, int, int)> dfs;

    dfs = [&](VTYPE g, VTYPE t, VTYPE o, VTYPE c, VTYPE b, VTYPE ro, VTYPE rc, VTYPE rb) -> void {
        auto maxg = g + t * t - t;
        if (t <= 0 or maxg <= maxx) {
            return;
        }
        maxx    = std::max(maxx, g);
        auto dt = 0;
        if (rb) { // create geode robot?
            dt = std::max(timeto(cg1, o, ro), timeto(cg2, b, rb));
            dfs(g + std::max(t - dt, 0), t - dt, o + dt * ro - cg1, c + dt * rc, b + dt * rb - cg2, ro, rc, rb);
        }
        if (maxg <= maxx) {
            return;
        }
        if (rc and b + (rb * t) < cg2 * t) { // create obsidian robot?
            dt = std::max(timeto(cb1, o, ro), timeto(cb2, c, rc));
            dfs(g, t - dt, o + dt * ro - cb1, c + dt * rc - cb2, b + dt * rb, ro, rc, rb + 1);
        }
        if (maxg <= maxx) {
            return;
        }
        if (c + (rc * t) < cb2 * t) { // create clay robot?
            dt = timeto(cc, o, ro);
            dfs(g, t - dt, o + dt * ro - cc, c + dt * rc, b + dt * rb, ro, rc + 1, rb);
        }
        if (maxg <= maxx) {
            return;
        }
        if (o + (ro * t) < mo * t) { // create ore robot?
            dt = timeto(co, o, ro);
            dfs(g, t - dt, o + dt * ro - co, c + dt * rc, b + dt * rb, ro + 1, rc, rb);
        }
    };

    dfs(0, minutes, 0, 0, 0, 1, 0, 0);
    return maxx;
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

std::string filter_string(std::string s)
{
    s.erase(std::remove_if(s.begin(), s.end(), [](unsigned char ch) { return !std::isdigit(ch) && !std::isspace(ch); }),
            s.end());
    return s;
}

VALUES parseBlueprint(std::string const& input_string)
{
    VALUES             values;
    VTYPE              number;
    std::istringstream ss(filter_string(input_string));
    while (ss >> number) {
        values.push_back(number);
    }
    return values;
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        throw std::runtime_error("Missing input file from command line");
    }

    const auto lines = readFile(argv[1]);

    // total1 = sum(x[0] * T(x, 24) for x in lines)
    VTYPE ans1 = 0;
    for (auto const& line : lines) {
        const auto values = parseBlueprint(line);
        ans1 += (values[0] * processBlueprint(values, 24));
    }
    fmt::print("{}\n", ans1);

    // total2 = functools.reduce(lambda a, b: a*b, (T(x, 32) for x in lines[:3]), 1)
    VTYPE ans2 = 1;
    for (size_t i = 0; i < 3; ++i) {
        const auto values = parseBlueprint(lines[i]);
        ans2 *= processBlueprint(values, 32);
    }
    fmt::print("{}\n", ans2);

    return 0;
}
