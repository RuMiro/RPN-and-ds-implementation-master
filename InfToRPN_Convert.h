#pragma once
#ifndef InfToRPN_Convert
#define InfToRPN_Convert

#include <iostream>
#include <string>
#include "stack.h"

;
int GetPriority(char op) {      
	switch (op) {
	case's':
	case'i':
	case'n':
	case'c':
	case'o':
    case'l':
    case'g':
    case't':
    case'a':
    case'r':
    case '^':
		return 4;
		break;
	case '/':
	case '*':
		return 3;
		break;
	case '+':
	case '-':
		return 2;
		break;
	case '(': case ')':
		return 1;
		break;
	}
	return 0;
}





string RPN(char* line, int maxLength);



int getRPN() {          // получение строки  из инфиксной в польскую нотацию
    cin.ignore();
	char line[128];
    std::cout << "Пример в инфиксной записи: ";
    cin.getline(line, 128);
    string res = RPN(line, 128);
	std::cout << "Пример в обратной польской нотации: " << res  << "\n";
	return 0;
}


string RPN(char* line, int maxLength) { // алгоритм перевода, основанный на приоритетах 
    Stack<char> stack = Stack<char>();
    string res = "";

    for (int i = 0; line[i] != '\0' && i < maxLength; i++)
    {
        
        if (line[i] == ' ') continue;

        if (i != 0 && i != 1) {
            if (GetPriority(line[i + 1]) > 1) {
                if (!ischar(line[i + 1])) {
                    res += ' ';
                }
            }
            if (GetPriority(line[i - 1]) > 1) {
                if (!ischar(line[i - 1])) {
                    res += ' ';
                }
            }
        }

        int currentPriotity = GetPriority(line[i]);

        if (currentPriotity == 0)
        {
            if (line[i] == 'p'  && line[i+1] == 'i') {
                res += ' ';
                i += 1;
                res += line[i - 1];
                res += line[i];
                res += ' ';
                continue;
            }
            res += line[i];
            if (i < maxLength - 1 && (GetPriority(line[i + 1]) != 0 || line[i + 1] == ' ')) res += ' ';
            continue;
        }

        if (currentPriotity == 1)
        {
            if (line[i] == '(') stack.Push('(');
            else
            {
                while (stack.Peek() != '(')
                {
                    res += stack.Pop();
                }
                stack.Pop();
            }
            continue;
        }

        int checkPriority = GetPriority(stack.Peek());
        while (checkPriority >= currentPriotity && checkPriority != 1 && stack.Peek() != NULL)
        {
            char c = stack.Pop();
            res += c;
            if (GetPriority(c) != 4 && GetPriority(c) != 0) res += ' ';
            checkPriority = GetPriority(stack.Peek());
        }
        if (line[i] == 'a') {
            if ((line[i+1] == 'c' && line[i + 2] == 'o' && line[i + 3] == 's')) {
                i += 3;
                stack.Push(line[i]);
                stack.Push(line[i - 1]);
                stack.Push(line[i - 2]);
                stack.Push(line[i - 3]);
                stack.Push(' ');
                continue;
            }
            if ((line[i+1] == 's' && line[i + 2] == 'i' && line[i + 3] == 'n')) {
                i += 3;
                stack.Push(line[i]);
                stack.Push(line[i - 1]);
                stack.Push(line[i - 2]);
                stack.Push(line[i - 3]);
 
                continue;
            }
            if ((line[i + 1] == 't' && line[i + 2] == 'a' && line[i + 3] == 'n')) {
                i += 3;
                stack.Push(line[i]);
                stack.Push(line[i - 1]);
                stack.Push(line[i - 2]);
                stack.Push(line[i - 3]);
                stack.Push(' ');
                continue;
            }
        }
        if ((line[i] == 't' && line[i + 1] == 'a' && line[i + 2] == 'n')) {
            i += 2;
            stack.Push(line[i]);
            stack.Push(line[i - 1]);
            stack.Push(line[i - 2]);
            stack.Push(' ');
            continue;
        }
        if ((line[i] == 'c' && line[i + 1] == 'o' && line[i+2] == 's')) {
            i += 2;
            stack.Push(line[i]);
            stack.Push(line[i - 1]);
            stack.Push(line[i - 2]);
            stack.Push(' ');

            continue;
        }
        
        if ((line[i] == 'l' && line[i + 1] == 'n') || (line[i] == 'l' && line[i + 1] == 'o' && line[i + 2] == 'g')) {
            if (line[i + 1] == 'n') {
                i += 1;
                stack.Push(line[i]);
                stack.Push(line[i - 1]);
                stack.Push(' ');
                continue;

                }
            i += 2;
            stack.Push(line[i]);
            stack.Push(line[i - 1]);
            stack.Push(line[i - 2]);
            stack.Push(' ');
            continue;
        }
        if ((line[i] == 's' && line[i + 1] == 'i' && line[i + 2] == 'n') || ((line[i] == 's' && line[i + 1] == 'q' && line[i + 2] == 'r' && line[i + 3] == 't'))) {
            if (line[i + 1] == 'q') {

                i += 3;
                stack.Push(line[i]);
                stack.Push(line[i - 1]);
                stack.Push(line[i - 2]);
                stack.Push(line[i - 3]);
                stack.Push(' ');
                continue;
            }
            i += 2;
            stack.Push(line[i]);
            stack.Push(line[i - 1]);
            stack.Push(line[i - 2]);
            stack.Push(' ');
            continue;
        }   
      
        

        if (currentPriotity != 0) stack.Push(' ');
        stack.Push(line[i]);

    }
    while (stack.Peek() != NULL) {
        char c = stack.Pop();
        if (GetPriority(c) > 1) {
            if (!ischar(c)) {
                res += ' ';
            }
        }
        res += c;

    }
    res += ' ';
    size_t pos;
    while ((pos = res.find("  ")) != string::npos)
        res = res.replace(pos, 2, " ");


    return res;
}

#endif  
// (1+2)^3+sin(4+5)^(6*7)