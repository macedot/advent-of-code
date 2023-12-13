#include "aoc.hpp"

using UMAP = std::unordered_map<char, VALUE>;
const UMAP cardRank1{
    { 'A', 13 }, { 'K', 12 }, { 'Q', 11 }, { 'J', 10 }, { 'T', 9 }, { '9', 8 }, { '8', 7 },
    { '7', 6 },  { '6', 5 },  { '5', 4 },  { '4', 3 },  { '3', 2 }, { '2', 1 },
};

const UMAP cardRank2{
    { 'A', 13 }, { 'K', 12 }, { 'Q', 11 }, { 'J', 0 }, { 'T', 9 }, { '9', 8 }, { '8', 7 },
    { '7', 6 },  { '6', 5 },  { '5', 4 },  { '4', 3 }, { '3', 2 }, { '2', 1 },
};

struct HAND {
    std::string cards{};
    VALUE       value = 0;
};
using VHAND = std::vector<HAND>;

struct CARD {
    char  card;
    VALUE count;
};

std::vector<CARD> countCards(std::string const& cards)
{
    UMAP G;
    for (const auto c : cards) {
        G[c]++;
    }
    std::vector<CARD> V;
    for (const auto& [k, v] : G) {
        V.push_back(CARD{ .card = k, .count = v });
    }
    std::sort(V.begin(), V.end(), [](CARD const& l, CARD const& r) { return l.count > r.count; });
    return V;
}

VALUE switchSize(size_t vsize, VALUE v0count, VALUE rank)
{
    switch (vsize) {
        case 1:
            // Five of a kind
            return 9e10 + rank;
        case 2:
            // Four of a kind
            if (v0count == 4) {
                return 8e10 + rank;
            }
            // Full house
            return 7e10 + rank;
        case 3:
            // Three of a kind
            if (v0count == 3) {
                return 6e10 + rank;
            }
            // Two pair
            return 5e10 + rank;
        case 4:
            // One pair
            return 4e10 + rank;
    }
    return rank;
}

VALUE baseRank(std::string const& cards, UMAP const& cardRank)
{
    VALUE rank = 0;
    for (size_t i = 0; i < cards.size(); ++i) {
        rank = rank * 100 + cardRank.at(cards[i]);
    }
    return rank;
}

VALUE rankCards1(std::string const& cards, std::vector<CARD> const& V)
{
    const auto rank = baseRank(cards, cardRank1);
    return switchSize(V.size(), V[0].count, rank);
}

VALUE rankCards2(std::string const& cards, VALUE baseRank)
{
    UMAP G;
    for (const auto c : cards) {
        G[c]++;
    }

    std::vector<CARD> V;
    for (const auto& [k, v] : G) {
        V.push_back(CARD{ .card = k, .count = v });
    }
    std::sort(V.begin(), V.end(), [](CARD const& l, CARD const& r) { return l.count > r.count; });

    if (G['J'] == 0 || G.size() == 1) {
        // no joker -> as is;
        return switchSize(V.size(), V[0].count, baseRank);
    }

    const auto dst = [V]() {
        for (const auto& v : V) {
            if (v.card != 'J') {
                return v.card;
            }
        }
        return 'X';
    }();

    std::string jokers = cards;
    std::replace(jokers.begin(), jokers.end(), 'J', dst);
    return rankCards2(jokers, baseRank);
}

VALUE scoreHand1(HAND const& h)
{
    return rankCards1(h.cards, countCards(h.cards));
}

VALUE scoreHand2(HAND const& h)
{
    const auto rank = baseRank(h.cards, cardRank2);
    return rankCards2(h.cards, rank);
}

VHAND parseHands(VSTRING const& lines)
{
    VHAND hands;
    for (const auto& line : lines) {
        std::stringstream ss(line);
        HAND              h;
        ss >> h.cards >> h.value;
        hands.push_back(h);
    }
    return hands;
}

VALUE processHands(VHAND& hands, std::function<VALUE(HAND const&)> scoreHand)
{
    std::sort(hands.begin(), hands.end(), [&scoreHand](auto& left, auto& right) {
        return scoreHand(left) < scoreHand(right);
    });
    VALUE res = 0;
    for (size_t i = 0; i < hands.size(); ++i) {
        res += (i + 1) * hands[i].value;
    }
    return res;
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        throw std::runtime_error("Missing input file from command line");
    }

    auto hands = parseHands(readFile(argv[1]));

    const auto ans1 = processHands(hands, scoreHand1);
    fmt::print("{}\n", ans1);

    const auto ans2 = processHands(hands, scoreHand2);
    fmt::print("{}\n", ans2);

    return 0;
}
