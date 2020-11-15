#include <string>
#include <stack>
#include <iostream>
#include <vector>
#include<exception>
#include <iomanip>
using namespace std;

//定义栈数据结构体
struct stack_data {
    char Operator;
    double Number;
};

//计算符号判定
bool isOperator(char ch)
{
    switch (ch)
    {
    case'+':
    case'-':
    case'*':
    case'/':
        return true;
    default:
        return false;
    }
}

//数字判定
bool isNumber(char ch)
{
    string number = "0123456789.";
    return number.find(ch) != -1;
}


//优先级判定
int priority(char a) {
    int temp = 0;
    if (a == '*' || a == '/')
        temp = 1;
    else if (a == '+' || a == '-')
        temp = 0;
    return temp;
}

//获取数字栈顶双数
void getTwoNums(stack<double>& num_stack, double& first, double& second)
{
    second = num_stack.top();
    num_stack.pop();

    first = num_stack.top();
    num_stack.pop();
}

//计算后缀表达式
double postfixCalculate(vector<stack_data>& postfix)
{
    double first, second;
    stack<double> num_stack;
    for (auto p : postfix)
    {
        switch (p.Operator)
        {
        case '*':
            getTwoNums(num_stack, first, second);
            num_stack.push(first * second);
            break;
        case '/':
            getTwoNums(num_stack, first, second);
            num_stack.push(first / second);
            break;
        case '+':
            getTwoNums(num_stack, first, second);
            num_stack.push(first + second);
            break;
        case '-':
            getTwoNums(num_stack, first, second);
            num_stack.push(first - second);
            break;
        default:
            num_stack.push(p.Number);
            break;
        }
    }
    double result = num_stack.top();
    num_stack.pop();
    return result;
}

//做分割
vector<stack_data> getSeparate(string& infix)
{
    vector<stack_data> postfix;
    string str_num;
    for (auto p : infix)
    {
        if (isOperator(p))
        {
            if (!str_num.empty()) postfix.emplace_back(stack_data{ ' ', stod(str_num) });
            str_num = "";
            postfix.emplace_back(stack_data{ p, 0 });
        }

        else if (isNumber(p))
        {
            str_num += p;
        }
        else if (p == '(' or p == ')')
        {
            if (!str_num.empty()) postfix.emplace_back(stack_data{ ' ', stod(str_num) });
            str_num = "";
            postfix.emplace_back(stack_data{ p, 0 });
        }
    }
    if (!str_num.empty())  postfix.emplace_back(stack_data{ ' ', stod(str_num) });
    str_num = "";

    //前导缺损+-符号补0
    vector<stack_data> new_postfix;
    char pre_char = '(';
    for (auto p : postfix)
    {
        if (p.Operator != ' ') {
            if (pre_char == '(' and (p.Operator == '-' or p.Operator == '+')) new_postfix.emplace_back(stack_data{ ' ', 0 });
            pre_char = p.Operator;
        }
        else pre_char = ' ';
        new_postfix.emplace_back(p);
    }
    return new_postfix;
}

//表达式输出
string printSeparate(vector<stack_data>& temp)
{
    string out;
    for (auto t : temp)
    {
        if (t.Operator != ' ')
            out += t.Operator;
        else
            out += to_string(t.Number);
        out += ' ';
    }
    return out;
}

//后缀表达式转换
vector<stack_data> getPostfixExp(vector<stack_data>& infix)
{
    stack<char> operator_stack;
    vector<stack_data> postfix;
    for (auto p : infix)
    {
        if (isOperator(p.Operator))
        {
            while (
                !operator_stack.empty() and
                isOperator(operator_stack.top()) and
                priority(operator_stack.top()) >= priority(p.Operator))
            {
                postfix.emplace_back(stack_data{ operator_stack.top(), 0 });
                operator_stack.pop();
            }
            operator_stack.push(p.Operator);
        }
        else if (p.Operator == '(')
        {
            operator_stack.push(p.Operator);
        }
        else if (p.Operator == ')')
        {
            while (operator_stack.top() != '(')
            {
                postfix.push_back(stack_data{ operator_stack.top() });
                operator_stack.pop();
            }
            operator_stack.pop();
        }
        else
        {
            postfix.push_back(p);
        }

    }
    while (!operator_stack.empty())
    {
        postfix.push_back(stack_data{ operator_stack.top(), 0 });
        operator_stack.pop();
    }
    return postfix;
}


int main()
{
    string infix;
    cout << "请输入字符串表达式，例如：" << endl;
    //cout << "16-(8 + (0.7 - 0.2)*5.41 + 6.8)+1" << endl;
    cout << "((8.6 - 10.2)*44 + 55 + 2.7) /3" << endl << endl;
    getline(cin, infix);

    vector<stack_data> postfix = getSeparate(infix);
    cout << "标准化字串表达式: " << printSeparate(postfix) << endl;
    vector<stack_data> postfixExp = getPostfixExp(postfix);
    cout << "转换的后缀表达式: " << printSeparate(postfixExp) << endl;
    double result = postfixCalculate(postfixExp);
    cout << "答案为: " << setprecision(10) << result;
    return 0;
}