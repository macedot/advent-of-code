#include <algorithm>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <ranges>
#include <sstream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

#define FMT_HEADER_ONLY
#include <fmt/format.h>

#define DUMP(var) fmt::print("{} ({}) : {} = {}\n", __func__, __LINE__, #var, var)

static void ltrim(std::string& s)
{
    s.erase(s.begin(),
            std::find_if(s.begin(), s.end(), [](unsigned char ch) { return !std::isspace(ch); }));
}

static void rtrim(std::string& s)
{
    s.erase(
      std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(),
      s.end());
}

static void trim(std::string& s)
{
    ltrim(s);
    rtrim(s);
}

[[nodiscard]] static std::vector<std::string> readFile(std::filesystem::path const& inputFile)
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

[[nodiscard]] static std::vector<std::string> split(std::string const& src,
                                                    char               delim,
                                                    bool               do_trim = true)
{
    std::stringstream        ss(src);
    std::vector<std::string> dst;
    std::string              segment;

    while (std::getline(ss, segment, delim)) {
        if (do_trim) {
            trim(segment);
        }
        dst.push_back(segment);
    }
    return dst;
}
