#pragma once

#include <algorithm>
#include <deque>
#include <filesystem>
#include <fstream>
#include <functional>
#include <future>
#include <iostream>
#include <limits>
#include <numeric>
#include <ranges>
#include <sstream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#define FMT_HEADER_ONLY
#include <fmt/format.h>

using STRING  = std::string;
using VSTRING = std::vector<STRING>;

using VALUE  = int64_t;
using DVALUE = std::deque<VALUE>;
using PVALUE = std::pair<VALUE, VALUE>;
using SVALUE = std::unordered_set<VALUE>;
using VVALUE = std::vector<VALUE>;

struct hashPVALUE {
    size_t operator()(const PVALUE& x) const
    {
        return static_cast<size_t>(x.first) ^ static_cast<size_t>(x.second);
    }
};

using DPAIR  = std::deque<PVALUE>;
using SPAIR  = std::unordered_set<PVALUE, hashPVALUE>;
using MSPAIR = std::unordered_map<PVALUE, SPAIR, hashPVALUE>;
using MVPAIR = std::unordered_map<PVALUE, VALUE, hashPVALUE>;

[[nodiscard]] PVALUE P(auto i, auto j)
{
    return std::make_pair(static_cast<VALUE>(i), static_cast<VALUE>(j));
}

#define DUMP(var)                                                              \
    fmt::print("{} ({}) : {} = [{}]\n", __func__, __LINE__, #var, var)

void ltrim(std::string& s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
                return !std::isspace(ch);
            }));
}

void rtrim(std::string& s)
{
    s.erase(std::find_if(s.rbegin(),
                         s.rend(),
                         [](unsigned char ch) { return !std::isspace(ch); })
              .base(),
            s.end());
}

void trim(std::string& s)
{
    ltrim(s);
    rtrim(s);
}

[[nodiscard]] VSTRING readFile(std::filesystem::path const& inputFile)
{
    std::ifstream ifs(inputFile, std::ios::in | std::ios::binary);
    if (!ifs) {
        throw std::runtime_error("Unable to open input file: " +
                                 inputFile.string());
    }

    VSTRING     content;
    std::string line;
    while (std::getline(ifs, line)) {
        content.push_back(line);
    }
    return content;
}

[[nodiscard]] inline std::string readFileString(
  std::filesystem::path const& inputFile,
  VALUE&                       lineSize)
{
    std::ifstream ifs(inputFile, std::ios::in | std::ios::binary);
    if (!ifs) {
        throw std::runtime_error("Unable to open input file: " +
                                 inputFile.string());
    }

    std::string content;
    std::string line;
    while (std::getline(ifs, line)) {
        if (line.empty()) {
            continue;
        }
        lineSize = std::max<VALUE>(lineSize, static_cast<VALUE>(line.size()));
        content.append(line);
    }
    return content;
}

[[nodiscard]] VSTRING split(std::string const& src,
                            char               delim,
                            bool               do_trim = true)
{
    std::stringstream ss(src);
    VSTRING           dst;
    std::string       segment;

    while (std::getline(ss, segment, delim)) {
        if (do_trim) {
            trim(segment);
        }
        dst.push_back(segment);
    }
    return dst;
}

template<typename Range>
[[nodiscard]] std::string join(Range&& src, std::string_view sep = ",")
{
    return fmt::format("[{}]", fmt::join(src, sep));
}

[[nodiscard]] VVALUE parseNumbers(std::string const& src)
{
    std::stringstream ss(src);
    VVALUE            values;
    VALUE             value;
    while (ss >> value) {
        values.push_back(value);
    }
    return values;
}

template<typename Range>
[[nodiscard]] SVALUE toSet(Range&& src)
{
    SVALUE res(src.begin(), src.end());
    return res;
}
