#include "aoc.hpp"

using MAP = std::unordered_map<std::string, std::pair<std::string, std::string>>;

MAP parseMap(VSTRING const& lines)
{
    MAP map;
    for (size_t i = 2; i < lines.size(); ++i) {
        const auto parts = split(lines[i], '=');
        const auto dir   = split(parts[1], ',');
        map[parts[0]]    = std::make_pair(dir[0].substr(1), dir[1].substr(0, dir[1].size() - 1));
    }
    return map;
}

VALUE simpleWalk(std::string const& instructions, MAP const& map)
{
    std::string atu = "AAA";
    if (!map.contains(atu)) {
        return 0;
    }
    for (VALUE res = 0;;) {
        for (const auto& i : instructions) {
            ++res;
            atu = (i == 'L' ? map.at(atu).first : map.at(atu).second);
            if (atu == "ZZZ") {
                return res;
            }
        }
    }
    throw std::runtime_error("WTF?!");
}

VALUE walkSuffix(std::string const& instructions, MAP const& map, std::string const& src)
{
    std::string atu = src;
    for (VALUE res = 0;;) {
        for (const auto& i : instructions) {
            ++res;
            atu = (i == 'L' ? map.at(atu).first : map.at(atu).second);
            if (atu.ends_with('Z')) {
                return res;
            }
        }
    }
    throw std::runtime_error("WTF?!");
}

VALUE combinedWalk(std::string const& instructions, MAP const& map)
{
    VSTRING V;
    for (const auto& [key, value] : map) {
        if (key.ends_with('A')) {
            V.push_back(key);
        }
    }

    std::vector<std::future<VALUE>> tasks;
    for (const auto& src : V) {
        tasks.push_back(std::async(std::launch::async, walkSuffix, instructions, map, src));
    }

    VALUE ans = 1;
    for (auto& task : tasks) {
        if (task.valid()) {
            ans = std::lcm(ans, task.get());
        }
    }
    return ans;
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        throw std::runtime_error("Missing input file from command line");
    }

    const auto lines        = readFile(argv[1]);
    const auto instructions = lines[0];
    const auto map          = parseMap(lines);

    const auto ans1 = simpleWalk(instructions, map);
    fmt::print("{}\n", ans1);

    const auto ans2 = combinedWalk(instructions, map);
    fmt::print("{}\n", ans2);

    return 0;
}
