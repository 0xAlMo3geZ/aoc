#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <cmath>

using namespace std;

// The Number struct Represents a number with associated line, column, length, and validity information.
struct Number
{
    int num, line, col, len;
    bool valid;
    Number(int num, int line, int col, int len, int valid) : num(num), line(line), col(col), len(len), valid(valid) {}
};

// The Asterisk struct represents a point in a grid with a line and column number.
struct Asterisk
{
    size_t line, col;
    set<int> numbers;
    Asterisk(int line, int col) : line(line), col(col) {}
};

/**
 * Generates a vector of Asterisk objects based on the given line and line number.
 *
 * @param line the string representation of the line
 * @param line_n the line number
 *
 * @return a vector of Asterisk objects representing the asterisks in the line
 *
 * @throws None
 */
vector<Asterisk> get_line_asterisks(string line, int line_n)
{
    vector<Asterisk> line_asterisks;
    for (size_t i = 0; i < line.size(); i++)
        if (line[i] == '*')
        {
            Asterisk a(line_n, i);
            line_asterisks.push_back(a);
        }
    return line_asterisks;
}

/**
 * Retrieves the line numbers from a given string line.
 *
 * @param line the string line to extract line numbers from
 * @param line_n the line number of the string line
 *
 * @return a vector of Number objects representing the line numbers
 *
 * @throws None
 */
vector<Number> get_line_numbers(string line, int line_n)
{
    vector<Number> line_numbers;
    int k = 0, current_num = 0;

    for (int i = line.size() - 1; i >= 0; i--)
    {
        if (isdigit(line[i]))
            current_num += (line[i] - '0') * pow(10, k++);
        else
        {
            if (k > 0)
            {
                Number n(current_num, line_n, i + 1, k, false);
                line_numbers.push_back(n);
            }
            k = 0;
            current_num = 0;
        }
    }

    if (k > 0)
    {
        Number n(current_num, line_n, 0, k, false);
        line_numbers.push_back(n);
    }

    return line_numbers;
}

/**
 * The main function of the C++ program.
 *
 * @return int The exit status of the program.
 */
int main()
{
    const string filename = "input.txt";
    fstream file(filename);

    vector<string> input_matrix;
    vector<Number> numbers;
    vector<Asterisk> asterisks;
    string line;

    int line_n = 0, total_sum = 0;

    while (getline(file, line))
    {
        input_matrix.push_back(line);
        for (Number n : get_line_numbers(line, line_n))
            numbers.push_back(n);

        for (Asterisk a : get_line_asterisks(line, line_n))
            asterisks.push_back(a);

        line_n++;
    }

    for (Number n : numbers)
        for (int i = n.col; i < n.col + n.len; i++)
            for (int j = -1; j <= 1; j++)
                for (int k = -1; k <= 1; k++)
                {
                    size_t row = n.line + j;
                    size_t col = i + k;

                    if (row < input_matrix.size() && col < input_matrix[0].size())
                    {
                        char current_char = input_matrix[row][col];
                        if (!isdigit(current_char) && current_char != '.')
                            n.valid = true;
                        // gear check
                        if (current_char == '*')
                            for (Asterisk &a : asterisks)
                                if (a.line == row && a.col == col)
                                    a.numbers.insert(n.num);
                    }
                }

    int gear_ratio;
    for (Asterisk a : asterisks)
    {
        gear_ratio = 1;
        if (!a.numbers.empty() && a.numbers.size() > 1)
        {
            for (int n : a.numbers)
                gear_ratio *= n;
            total_sum += gear_ratio;
        }
    }

    cout << total_sum << endl;

    return 0;
}