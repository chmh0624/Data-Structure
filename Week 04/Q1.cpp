/*
  @pre-reading: check out postfix expression, i.e. dealing arithmetic problem with stack
  @author: Kevin Hu
  @comment written: min-hsun
*/

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

template <class T>
class Stack
{
public:
    T *stackArr;
    int stTop, sz;

    Stack(int size)
    {
        this->stackArr = new T[size];
        this->stTop = -1;
        this->sz = 0;
    }

    void push(T data)
    {
        (this->stTop)++;
        stackArr[this->stTop] = data;
        this->sz++;
    }

    T pop()
    {
        if (!isEmpty())
        {
            this->stTop--;
            this->sz--;
            return this->stackArr[this->stTop + 1];
        }
        return -1;
    }

    T top()
    {
        if (!isEmpty())
            return this->stackArr[this->stTop];
        return -1;
    }

    bool isEmpty()
    {
        return (this->stTop <= -1);
    }

    int size()
    {
        return this->sz;
    }
};

int priority(char c)
{
    if (c == '+' || c == '-')
        return 1;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '^')
        return 3;
    else
        return 0;
}

int idx = 0;

string negative(string s)
{
    // '&' represent negative
    int flag = 0;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
            flag = 1;
        if (s[i] == '-')
        {
            if (!flag)
                s[i] = '&';
            else if (s[i + 1] == '-')
            { // '--' = '+'
                s[i] = '+';
                s.erase(i + 1, 1);
            }
        }
        if ((s[i] == '+' || s[i] == '*' || s[i] == '/') && s[i + 1] == '-')
        {
            s[i + 1] = '&';
        }
    }
    return s;
}

bool check(string s)
{
    int len = s.length(), left = 0, right = 0;
    // invalid operators
    if (s[len - 1] == '+' || s[len - 1] == '-' || s[len - 1] == '*' || s[len - 1] == '/' || s[len - 1] == '^' || s[len - 1] == '(')
        return false;
    for (int i = 0; i < len; i++)
    {
        if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/')
        {
            if (s[i + 1] == s[i])
                return false;
        }
        if (s[i] == '(')
            right++;
        else if (s[i] == ')')
            left++;
    }
    if (left != right)
        return false;
    return true;
}

string *transfer(string s)
{
    string *st = new string[2000];
    idx = 0;
    Stack<char> *op = new Stack<char>(2000);
    
    // maintain --
    s = negative(s); 

    // Error control
    if (!check(s))
        return NULL;

    // append characters into string array
    for (int i = 0; i < s.length(); i++)
    {
        // get complete floating numbers
        if (s[i] >= '0' && s[i] <= '9')
        {
            string n = "";
            while ((s[i] >= '0' && s[i] <= '9') || s[i] == '.')
            {
                n += s[i];
                i++;
            }
            idx++;
            st[idx] = n;
            i--;
        }

        // get operators
        else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '^')
        {
            while (op->size() != 0 && priority(s[i]) <= priority(op->top()))
            {
                string _op = "";
                _op += op->pop();
                idx++;
                st[idx] = _op;
            }
            op->push(s[i]);
        }

        // get & with complete floating number
        else if (s[i] == '&')
        {
            i++;
            string n = "&";
            while ((s[i] >= '0' && s[i] <= '9') || s[i] == '.')
            {
                n += s[i];
                i++;
            }
            idx++;
            st[idx] = n;
            i--;
        }

        // get (
        else if (s[i] == '(')
        {
            op->push(s[i]);
        }

        // append operators between () into string array, i.e. clear op stack
        else if (s[i] == ')')
        {
            while (op->size() != 0 && op->top() != '(')
            {
                string _op = "";
                _op += op->pop();
                idx++;
                st[idx] = _op;
            }
            op->pop();
        }
    }

    // pop out all the operators in the op stack
    while (op->size() != 0)
    {
        string _op = "";
        _op += op->pop();
        idx++;
        st[idx] = _op;
    }

    // finally return string array
    return st;
}

// Banker Rounding
double roundHalfToEven(double f)
{
    double r = round(f * 100) / 100;
    double d = r - f;
    int id = (int)(d * 1000);
    if ((id != 5) && (id != -5))
        return r;
    string s = to_string(r);
    if (s[0] == '-' && (s[4] == '2' || s[4] == '4' || s[4] == '6' || s[4] == '8' || s[4] == '0'))
        return r;
    if (s[3] == '2' || s[3] == '4' || s[3] == '6' || s[3] == '8' || s[3] == '0')
        return r;
    return f - d;
}


double compute(string *st)
{
    Stack<double> *d = new Stack<double>(2000);
    for (int i = 0; i <= idx; i++)
    {
        if (st[i][0] >= '0' && st[i][0] <= '9')
        {
            d->push(stod(st[i]));
        }
        else if (st[i][0] == '&')
        {
            d->push(-1 * stod(&st[i][1]));
        }

        // if getting an operator, pop out 2 numbers for computation
        else if (st[i] == "+" || st[i] == "-" || st[i] == "*" || st[i] == "/" || st[i] == "^")
        {
            double b = d->pop();
            double a = d->pop();
            double p;
            if (st[i] == "+")
                p = a + b;
            else if (st[i] == "-")
                p = a - b;
            else if (st[i] == "*")
                p = a * b;
            else if (st[i] == "/")
                p = a / b;
            else if (st[i] == "^")
                p = pow(a, b);

            // rounding after every computation
            p = roundHalfToEven(p);
            d->push(p);
        }
    }

    // the last element in the stack is the answer
    return d->pop();
}

int main()
{
    string s;
    while (cin >> s)
    {
        // split string into string array
        string *str = transfer(s);

        // error detected
        if (str == NULL)
            cout << "ERROR\n";

        // answer returned
        else
        {
            printf("%.2f\n", compute(str));
        }
    }
}
