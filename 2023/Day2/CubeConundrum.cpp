#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

// This struct represents a game and stores its ID and subsets of data.
struct Game
{
    int id;
    vector<map<string, int>> subsets;
};

/**
 * Splits a string into substrings based on a specified delimiter.
 *
 * @param s The input string to be split.
 * @param delimiter The delimiter character to split the string by.
 *
 * @return A vector of substrings obtained by splitting the input string.
 *
 * @throws None.
 */
vector<string> split(const string &s, char delimiter)
{
    vector<string> substrings;
    size_t start = 0;
    size_t end = s.find(delimiter);

    while (end != std::string::npos)
    {
        substrings.push_back(s.substr(start, end - start));
        start = end + 1;
        end = s.find(delimiter, start);
    }

    substrings.push_back(s.substr(start, end));

    return substrings;
}

/**
 * Reads a subset of strings and returns a map with the count of each color.
 *
 * @param str_subset the subset of strings to process
 *
 * @return a map with the count of each color in the subset
 *
 * @throws None
 */
map<string, int> read_subset(string str_subset)
{
    map<string, int> current_subset = {{"red", 0}, {"green", 0}, {"blue", 0}};
    vector<string> str_cubes = split(str_subset, ',');

    for (auto str_cube : str_cubes)
        current_subset[split(str_cube, ' ')[2]] += stoi(split(str_cube, ' ')[1]);

    return current_subset;
}

/**
 * Reads a game from a given string line.
 *
 * @param line the string line containing the game information
 *
 * @return the game object generated from the string line
 *
 * @throws ErrorType if there is an error parsing the string line
 */
Game read_game(string line)
{
    Game game;
    map<string, int> current_subset;

    vector<string> str_divided = split(line, ':');

    game.id = stoi(split(str_divided[0], ' ')[1]);

    for (auto str_subset : split(str_divided[1], ';'))
        game.subsets.push_back(read_subset(str_subset));

    return game;
}

/**
 * Reads a file named "input.txt" and calculates the total sum of the product of the maximum values of "red", "green", and "blue" for each line in the file.
 *
 * @return the total sum of the product of the maximum values of "red", "green", and "blue"
 *
 * @throws ifstream::failure if the file cannot be opened
 */
int main()
{
    const string filename = "input.txt";
    ifstream file(filename);

    string line;
    int total_sum = 0;

    while (getline(file, line))
    {
        Game current_game = read_game(line);

        int max_red = -1, max_green = -1, max_blue = -1;

        for (auto s : current_game.subsets)
        {
            if (s["red"] > max_red)
                max_red = s["red"];
            if (s["green"] > max_green)
                max_green = s["green"];
            if (s["blue"] > max_blue)
                max_blue = s["blue"];
        }

        total_sum += max_red * max_green * max_blue;
    }

    cout << total_sum << endl;

    return 0;
}