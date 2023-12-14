#include "aoc.hpp"

void readParams(VSTRING const& lines, VVALUE& time, VVALUE& distance)
{
    time     = parseNumbers(lines[0].substr(lines[0].find_first_of(':') + 1));
    distance = parseNumbers(lines[1].substr(lines[1].find_first_of(':') + 1));
}

VALUE race(VALUE time, VALUE distance)
{
    VALUE count = 0;
    for (VALUE t = 1; t < time; ++t) {
        count += (t * (time - t) > distance);
    }
    return count;
}

VALUE processPart1(VVALUE& time, VVALUE& distance)
{
    FMT_ASSERT(time.size() == distance.size(), "Invalid input!");
    VALUE res = 1;
    for (size_t i = 0; i < time.size(); ++i) {
        res *= race(time[i], distance[i]);
    }
    return res;
}

VALUE processPart2(VVALUE& time, VVALUE& distance)
{
    FMT_ASSERT(time.size() == distance.size(), "Invalid input!");
    std::string t, d;
    for (size_t i = 0; i < time.size(); ++i) {
        t += std::to_string(time[i]);
        d += std::to_string(distance[i]);
    }
    return race(std::stoll(t), std::stoll(d));
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        throw std::runtime_error("Missing input file from command line");
    }
    const auto lines = readFile(argv[1]);
    VVALUE     time, distance;
    readParams(lines, time, distance);
    const auto ans1 = processPart1(time, distance);
    fmt::print("{}\n", ans1);
    const auto ans2 = processPart2(time, distance);
    fmt::print("{}\n", ans2);
    return 0;
}
