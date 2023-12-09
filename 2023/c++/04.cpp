#include "aoc.hpp"

SVALUE parseNumbers(std::string const& src)
{
    std::stringstream ss(src);
    SVALUE            values;
    VALUE             value;
    while (ss >> value) {
        values.insert(value);
    }
    return values;
}

VALUE getPoints1(VALUE lhs, std::string const& line)
{
    const auto& values  = line.substr(line.find_first_of(':') + 1);
    const auto  parts   = split(values, '|');
    const auto  winning = parseNumbers(parts[0]);
    const auto  numbers = parseNumbers(parts[1]);

    VALUE total = 0;
    for (const auto n : numbers) {
        if (winning.find(n) != winning.end()) {
            total += (total == 0) ? 1 : total;
        }
    }
    return lhs + total;
}

VALUE count_intersection(SVALUE const& lhs, SVALUE const& rhs)
{
    VALUE matches = 0;
    for (const auto n : lhs) {
        matches += (rhs.find(n) != rhs.end());
    }
    return matches;
}

VALUE processPart2(VSTRING const& cards)
{
    VVALUE matches(cards.size(), 0);
    VVALUE copies(cards.size(), 1);
    for (size_t idx = 0; idx < cards.size(); ++idx) {
        const auto& card    = cards[idx];
        const auto& values  = card.substr(card.find_first_of(':') + 1);
        const auto  parts   = split(values, '|');
        const auto  winning = parseNumbers(parts[0]);
        const auto  numbers = parseNumbers(parts[1]);
        matches[idx]        = count_intersection(winning, numbers);
        for (size_t c = 0; c < matches[idx]; ++c) {
            copies[idx + c + 1] += copies[idx];
        }
    }
    return std::reduce(copies.begin(), copies.end());
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        throw std::runtime_error("Missing input file from command line");
    }

    const auto cards = readFile(argv[1]);
    const auto ans1  = std::accumulate(cards.begin(), cards.end(), VALUE(0), getPoints1);
    fmt::print("{}\n", ans1);

    const auto ans2 = processPart2(cards);
    fmt::print("{}\n", ans2);

    return 0;
}
