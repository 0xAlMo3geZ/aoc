#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>

using namespace std;

// Represents a card with an ID, number of matches, a list of winning cards, and a list of players who have this card.
struct Card
{
    int id, matches;
    vector<int> winning;
    vector<int> player;

    /**
     * Compares this Card object with another Card object.
     *
     * @param c the Card object to compare with
     *
     * @return true if this Card object is less than the specified Card object;
     *         false otherwise
     */
    bool operator<(const Card &c) const
    {
        return id < c.id;
    }
};

/**
 * Splits a given string into substrings based on a delimiter.
 *
 * @param s The string to be split.
 * @param delimiter The delimiter character.
 *
 * @return A vector of substrings.
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
 * Reads a card from a string and returns a Card object.
 *
 * @param line the string containing the card information in the format "id: numbers|points"
 *
 * @return a Card object representing the card read from the string
 *
 * @throws ErrorType if the input string is not in the correct format
 */
Card read_card(string line)
{
    Card c;

    vector<string> aux = split(line, ':');

    // id
    for (auto x : split(aux[0], ' '))
        if (x != "" && x != "  " && x != "Card")
            c.id = stoi(x);

    // numbers, points, matches
    aux = split(aux[1], '|');

    for (auto x : split(aux[0], ' '))
        if (x != "")
            c.winning.push_back(stoi(x));

    for (auto x : split(aux[1], ' '))
        if (x != "")
            c.player.push_back(stoi(x));

    vector<int> intersect;

    sort(c.winning.begin(), c.winning.end());
    sort(c.player.begin(), c.player.end());

    set_intersection(c.winning.begin(), c.winning.end(),
                     c.player.begin(), c.player.end(),
                     back_inserter(intersect));

    c.matches = intersect.size();

    return c;
}

/**
 * Retrieves a card from a vector of cards based on its ID.
 *
 * @param cards The vector of cards to search through.
 * @param id The ID of the card to retrieve.
 *
 * @return The card with the specified ID, or an empty card if not found.
 *
 * @throws None
 */
Card get_card(vector<Card> cards, int id)
{
    Card c;
    for (Card x : cards)
        if (x.id == id)
        {
            c = x;
            break;
        }
    return c;
}

/**
 * Main function that reads a file, processes its contents, and prints the total sum.
 *
 * @return 0 upon successful completion
 */
int main()
{
    const string filename = "input.txt";
    fstream file(filename);

    string line;

    vector<Card> cards;
    map<int, int> card_counter;

    int total_sum = 0;

    while (getline(file, line))
    {
        Card c = read_card(line);
        cards.push_back(c);
        card_counter[c.id]++;
        total_sum++;
    }

    for (auto c : cards)
        while (card_counter[c.id] != 0)
        {
            for (int i = 1; i <= c.matches; i++)
            {
                card_counter[c.id + i]++;
                total_sum++;
            }
            card_counter[c.id]--;
        }

    cout << total_sum << endl;

    return 0;
}