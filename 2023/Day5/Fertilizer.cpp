#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <ios>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int p1_total = 0, p2_total = 0;

static const regex map_line_rgx(R"(([a-z]+)-to-([a-z]+) map:)");
static const regex number_rgx(R"(\d+)");

typedef struct
{
    long long dest;
    long long source;
    long long len;
} Range;

typedef struct
{
    string from;
    string to;
    vector<Range> ranges;
} Map;

/**
 * Traverse the given maps and update the current value based on the ranges.
 *
 * @param current The current value to be updated.
 * @param maps The vector of maps containing ranges.
 *
 * @return The updated value of current after traversing the maps.
 *
 * @throws None
 */
static long long traverse(long long current, vector<Map> maps)
{
    for (Map &map : maps)
    {
        for (Range &range : map.ranges)
        {
            if (current >= range.source && current <= range.source + range.len)
            {
                current = range.dest + (current - range.source);
                break;
            }
        }
    }

    return current;
}

/**
 * Calculates the lowest value obtained from traversing multiple maps using a list of seeds.
 *
 * @param seeds a vector of long long integers representing the seeds
 * @param maps a vector of Map objects representing the maps
 *
 * @return the lowest value obtained from traversing the maps using the seeds
 *
 * @throws None
 */
long long part1(vector<long long> seeds, vector<Map> maps)
{
    long long lowest = numeric_limits<long>::max();
    for (auto seed : seeds)
    {
        long long cur_num = traverse(seed, maps);
        lowest = min(cur_num, lowest);
    }

    return lowest;
}

/**
 * Calculates the lowest value obtained from traversing a range of seeds using a list of maps.
 *
 * @param seeds a vector of long long integers representing the seeds to traverse
 * @param maps a vector of Map objects representing the maps to traverse
 *
 * @return the lowest long long value obtained from traversing the seeds using the maps
 *
 * @throws None
 */
long long part2(vector<long long> seeds, vector<Map> maps)
{
    long long lowest = numeric_limits<long>::max();
    for (auto it = seeds.begin(); it != seeds.end(); it += 2)
    {
        long long from = *it;
        long long to = *(it + 1);

        for (auto seed = from; seed < from + to; ++seed)
        {
            long long cur_num = traverse(seed, maps);
            lowest = min(cur_num, lowest);
        }
    }

    return lowest;
}

/**
 * Reads input from a file and processes it to calculate and print the results.
 *
 * @return 0 indicating successful execution
 *
 * @throws None
 */
int main()
{
    ifstream input("input.txt");
    string line;

    getline(input, line);
    std::istringstream iss(line);
    iss.ignore(6, ':');
    vector<long long> seeds((std::istream_iterator<long long>(iss)),
                            std::istream_iterator<long long>());

    vector<Map> maps;
    Map this_map;
    getline(input, line);
    while (getline(input, line))
    {
        smatch match;

        if (line.empty())
        {
            maps.push_back(this_map);

            this_map = {};

            continue;
        }

        if (regex_search(line, match, map_line_rgx))
        {
            this_map.from = match[1].str();
            this_map.to = match[2].str();

            continue;
        }
        else
        {
            sregex_iterator it(line.begin(), line.end(), number_rgx), end;

            Range this_range;
            this_range.dest = strtol(it->str().c_str(), NULL, 10);
            ++it;
            this_range.source = strtol(it->str().c_str(), NULL, 10);
            ++it;
            this_range.len = strtol(it->str().c_str(), NULL, 10);

            this_map.ranges.push_back(this_range);
        }
    }
    maps.push_back(this_map);

    cout << part1(seeds, maps) << endl;
    cout << part2(seeds, maps) << endl;

    return 0;
}