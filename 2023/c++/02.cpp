#include "aoc.hpp"

auto get_id(std::string const& src) -> uint32_t
{
    std::stringstream ss(src);
    std::string       tmp;
    uint32_t          id = 0;
    ss >> tmp >> id;
    return id;
};

auto get_cube(std::string const& src)
{
    std::stringstream ss(src);
    std::string       color;
    uint32_t          qt = 0;
    ss >> qt >> color;
    return std::make_pair(color, qt);
};

uint32_t funcParse1(uint32_t lhs, std::string const& game)
{
    static const std::unordered_map<std::string, uint32_t> cubeMax{
        { "red", 12 },
        { "green", 13 },
        { "blue", 14 },
    };

    const auto seg = split(game, ':');
    const auto id  = get_id(seg[0]);
    FMT_ASSERT(id > 0, "INVALID ID");
    for (const auto& game_param : split(seg[1], ';')) {
        for (const auto& cube : split(game_param, ',')) {
            const auto c = get_cube(cube);
            if (cubeMax.at(c.first) < c.second) {
                return lhs;
            }
        }
    }
    return lhs + id;
}

uint32_t funcParse2(uint32_t lhs, std::string const& game)
{
    std::unordered_map<std::string, uint32_t> cubeMax{
        { "red", 1 },
        { "green", 1 },
        { "blue", 1 },
    };

    const auto seg = split(game, ':');
    for (const auto& game_param : split(seg[1], ';')) {
        for (const auto& cube : split(game_param, ',')) {
            const auto c     = get_cube(cube);
            cubeMax[c.first] = std::max(c.second, cubeMax.at(c.first));
        }
    }

    uint32_t power = 1;
    for (const auto& [k, v] : cubeMax) {
        power *= v;
    }

    return lhs + power;
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        throw std::runtime_error("Missing input file from command line");
    }

    const auto games = readFile(argv[1]);

    const auto ans1 = std::accumulate(games.begin(), games.end(), 0UL, funcParse1);
    fmt::print("{}\n", ans1);

    const auto ans2 = std::accumulate(games.begin(), games.end(), 0UL, funcParse2);
    fmt::print("{}\n", ans2);

    return 0;
}
