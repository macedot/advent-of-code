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

#define DUMP(var)
//fmt::print("{} ({}) : {} = {}\n", __func__, __LINE__, #var, var)

using VTYPE  = uint32_t;
using VALUES = std::vector<VTYPE>;
using VTUPLE = std::tuple<VTYPE, VTYPE, VTYPE, VTYPE, VTYPE, VTYPE>;

struct STEP {
    VTYPE o  = 0;
    VTYPE c  = 0;
    VTYPE b  = 0;
    VTYPE ro = 0;
    VTYPE rc = 0;
    VTYPE rb = 0;

    STEP(VTYPE _o, VTYPE _c, VTYPE _b, VTYPE _ro, VTYPE _rc, VTYPE _rb)
      : o(_o)
      , c(_c)
      , b(_b)
      , ro(_ro)
      , rc(_rc)
      , rb(_rb)
    {
    }

    std::string str() const { return fmt::format("({},{},{},{},{},{})", o, c, b, ro, rc, rb); }

    bool operator==(const STEP& rhs) const
    {
        return (o == rhs.o && c == rhs.c && b == rhs.b && ro == rhs.ro && rc == rhs.rc && rb == rhs.rb);
    }
};

namespace std {
template<>
struct hash<STEP> {
    auto operator()(const STEP& s) const -> uint64_t
    {
        return (s.rb << 16 | s.rc << 8 | s.ro) ^ (s.b << 16 | s.c << 8 | s.o);
    }
};
} // namespace std

using STEPS  = std::vector<STEP>;
using VSTEPS = std::unordered_map<STEP, VTYPE>;

VTYPE max_value_g(const VSTEPS& steps)
{
    VTYPE res = 0;
    for (const auto& [k, v] : steps) {
        res = std::max(res, v);
    }
    return res;
}

std::string join(const VALUES& values)
{
    std::string res = "[";
    if (!values.empty()) {
        res += std::to_string(values[0]);
        for (size_t i = 1; i < values.size(); ++i) {
            res += ",";
            res += std::to_string(values[i]);
        }
    }
    res += "]";
    return res;
}

VTYPE processBlueprint(const VALUES& blueprint, VTYPE minutes)
{
    auto const& id  = blueprint[0];
    auto const& co  = blueprint[1];
    auto const& cc  = blueprint[2];
    auto const& cb1 = blueprint[3];
    auto const& cb2 = blueprint[4];
    auto const& cg1 = blueprint[5];
    auto const& cg2 = blueprint[6];
    const auto  mo  = std::max(co, std::max(cc, std::max(cb1, cg1)));
    DUMP(join(blueprint));
    DUMP(mo);

    VSTEPS T, Q;
    T.emplace(std::make_pair(STEP{ 0, 0, 0, 1, 0, 0 }, 0));

    // def p(v, *k): Q[k] = max(Q.get(k, 0), v)
    auto p = [&Q](VTYPE g, STEP t) {
        DUMP(t.str());
        Q[t] = std::max(g, Q[t]);
    };

    for (auto minute = minutes; minute > 1; --minute) {
        DUMP(minute);
        const auto maxg = max_value_g(T);
        DUMP(maxg);
        Q.clear();
        for (const auto& [t, g] : T) {
            DUMP(t.str());
            if (g + minute * minute - minute < maxg) {
                continue;
            }
            const auto bo = (t.o >= co && t.ro < mo && t.o + (t.ro * minute) < mo * minute);
            const auto bc = (t.o >= cc && t.rc < cb2 && t.c + (t.rc * minute) < cb2 * minute);
            const auto bb = (t.o >= cb1 && t.c >= cb2 && t.rb < cg2);
            //const auto bb = (t.o >= cb1 && t.c >= cb2 && t.rb < cg2 && t.b + (t.rb * minute) < cg2 * minute);
            const auto bg = (t.o >= cg1 && t.b >= cg2);
            if (minute >= 2) {
                if (bo) {
                    DUMP(bo);
                    p(g, STEP{ t.o + t.ro - co, t.c + t.rc, t.b + t.rb, t.ro + 1, t.rc, t.rb });
                }
                if (bc) {
                    DUMP(bc);
                    p(g, STEP{ t.o + t.ro - cc, t.c + t.rc, t.b + t.rb, t.ro, t.rc + 1, t.rb });
                }
                if (bb) {
                    DUMP(bb);
                    p(g, STEP{ t.o + t.ro - cb1, t.c + t.rc - cb2, t.b + t.rb, t.ro, t.rc, t.rb + 1 });
                }
                if (!(bo && bc && bb && bg)) {
                    DUMP(!(bo && bc && bb && bg));
                    p(g, STEP{ t.o + t.ro, t.c + t.rc, t.b + t.rb, t.ro, t.rc, t.rb });
                }
            }
            if (bg) {
                p(g + (minute - 1), STEP{ t.o + t.ro - cg1, t.c + t.rc, t.b + t.rb - cg2, t.ro, t.rc, t.rb });
            }
        }
        T = Q;
    }

    DUMP(max_value_g(T));
    return id * max_value_g(T);
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

    //print(sum(x[0] * proc(x, 24) for x in lines))
    // uint64_t ans1 = 0;
    // for (auto const& line : lines) {
    //     const auto values = parseBlueprint(line);
    //     DUMP(join(values));
    //     ans1 += processBlueprint(values, 40);
    //     break;
    // }

    const auto values = parseBlueprint(lines[1]);
    uint64_t   ans1   = processBlueprint(values, 24);
    fmt::print("{}\n", ans1);

    // uint64_t ans2 = 1;
    // for (auto i = 0; i < 3; ++i) {
    //     ans2 *= processBlueprint(lines[i], 32);
    // }
    // DUMP(ans2);

    return 0;
}
