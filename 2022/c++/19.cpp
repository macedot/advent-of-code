// #!/usr/sbin/python
// #https://github.com/juanplopes/advent-of-code-2022/blob/main/day19.py
// import re
// def T(blueprint, mins):
//     _, co, cc, cb1, cb2, cg1, cg2 = blueprint
//     mo = max(co, cc, cb1, cg1)
//     T = {(0, 0, 0, 1, 0, 0): 0}
//     for minute in range(mins, 1, -1):
//         maxg = max(T.values())
//         Q = {}
//         def p(v, *k): Q[k] = max(Q.get(k, 0), v)
//         for (o, c, b, ro, rc, rb), g in T.items():
//             if g+minute*minute-minute < maxg:
//                 continue
//             bo = o >= co and ro < mo and o+(ro*minute) < mo*minute
//             bc = o >= cc and rc < cb2 and c+(rc*minute) < cb2*minute
//             bb = o >= cb1 and c >= cb2 and rb < cg2
//             bg = o >= cg1 and b >= cg2
//             if minute >= 2:
//                 if bo:
//                     p(g, o+ro-co, c+rc, b+rb, ro+1, rc, rb)
//                 if bc:
//                     p(g, o+ro-cc, c+rc, b+rb, ro, rc+1, rb)
//                 if bb:
//                     p(g, o+ro-cb1, c+rc-cb2, b+rb, ro, rc, rb+1)
//                 if not all((bo, bc, bb, bg)):
//                     p(g, o+ro, c+rc, b+rb, ro, rc, rb)
//             if bg:
//                 p(g + (minute-1), o+ro-cg1, c+rc, b+rb-cg2, ro, rc, rb)
//         T = Q
//     return max(T.values())
// lines = [tuple(map(int, re.findall('\\d+', x))) for x in open(0).readlines()]
// print(sum(x[0] * T(x, 24) for x in lines))
// a, b, c = (T(x, 32) for x in lines[:3])
// print(a * b * c)

#include <algorithm>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>
#include <ranges>
#include <map>
#include <tuple>
#include <vector>
#include <unordered_map>

struct Blueprint {
    int id, co, cc, cb1, cb2, cg1, cg2;
};

// uint64_t T(Blueprint const& bp, int minutes)
// {
//     (void)bp;
//     for (auto i = minutes; i > 1; --i) {
//     }
//     return 0;
// }

// uint32_t max_value(std::map<Blueprint, uint32_t> const& data)
// {
//     uint32_t res = 0;
//     for (const auto& [k, v] : data) {
//         res = std::max(res, v);
//     }
//     return res;
// }

std::vector<std::string> readFile(std::filesystem::path const& inputFile)
{
    std::ifstream            ifs(inputFile, std::ios::binary);
    std::vector<std::string> lines;
    std::string              line;

    while (std::getline(ifs, line)) {
        lines.push_back(line);
    }

    return lines;
}

int main(int argc, char* argv[])
{
    auto ans1 = 0; //T(Blueprint{}, 24);
    std::cout << "ans1=" << ans1 << "\n";
    return 0;
}
