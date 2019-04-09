#include <iostream>
#include <stack>
#include <string>

using namespace std;

struct Bracket
{
    Bracket(char type, int position) : type(type), position(position)
    {
    }

    bool Matchc(char c)
    {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main()
{
    std::string text;
    getline(std::cin, text);

    std::stack<Bracket> opening_brackets_stack;

    int length = text.length();
    for (int position = 0; position < text.length(); ++position)
    {
        if (position)
        {
            if ((opening_brackets_stack.empty()))
            {
                length -= position;
                // cout << length << endl;
            }
        }
        char next = text[position];
        Bracket bracket(next, position);
        if (next == '(' || next == '[' || next == '{')
        {
            // Process opening bracket, write your code here
            opening_brackets_stack.push(bracket);
        }

        if (next == ')' || next == ']' || next == '}')
        {
            // Process closing bracket, write your code here
            // cout<<opening_brackets_stack.pop()
            if (opening_brackets_stack.empty())
            {
                // bracket = opening_brackets_stack.top();
                cout << position + 1 << endl;
                goto endOfLoop;
            }
            else
            {
                bracket = opening_brackets_stack.top();
                if (bracket.Matchc(next))
                {
                    opening_brackets_stack.pop();
                }
                else
                {
                    cout << position + 1 << endl;
                    goto endOfLoop;
                }
            }
        }
    }
    if (opening_brackets_stack.empty())
    {
        cout << "Success" << endl;
        goto endOfLoop;
    }
    else
    {
        Bracket bracketLoopend = opening_brackets_stack.top();
        cout << bracketLoopend.position + 1 << endl;
        goto endOfLoop;
    }

endOfLoop:;

    // Printing answer, write your code here

    return 0;
}
