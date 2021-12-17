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
	case'p':
    case'l':
    case'g':
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



int getRPN() {
    cin.ignore();
	char line[128];
    std::cout << "infix: ";
    cin.getline(line, 128);
    string res = RPN(line, 128);
	std::cout << "Result rpn: " << res  << "\n";
	return 0;
}


string RPN(char* line, int maxLength) {
    Stack<char> stack = Stack<char>();
    string res = "";

    for (int i = 0; line[i] != '\0' && i < maxLength; i++)
    {
        
        if (line[i] == ' ') continue;

        int currentPriotity = GetPriority(line[i]);

        if (currentPriotity == 0)
        {
            res += line[i];
            if (i < maxLength - 1 && (GetPriority(line[i + 1]) != 0 || line[i + 1] == ' ' || line[i + 1] == '\0')) res += ' ';
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
                    res += ' ';
                }
                stack.Pop();
            }
            continue;
        }

        int checkPriority = GetPriority(stack.Peek());
        while (checkPriority >= currentPriotity && checkPriority != 1 && stack.Peek() != NULL)
        {
            res += stack.Pop();
            res += ' ';
            checkPriority = GetPriority(stack.Peek());
        }
        if (line[i] == 'c') {
            i += 2;
            stack.Push(line[i]);
            stack.Push(line[i - 1]);
            stack.Push(line[i - 2]);
            continue;
        }
        if (line[i] == 'p') {
            i += 1;
            stack.Push(line[i]);
            stack.Push(line[i - 1]);
            continue;
        }
        if (line[i] == 'l') {
            if (line[i + 1] == 'n') {
                i += 1;
                stack.Push(line[i]);
                stack.Push(line[i - 1]);
                continue;
                }
            i += 2;
            stack.Push(line[i]);
            stack.Push(line[i - 1]);
            stack.Push(line[i - 2]);
            continue;
        }
        if (line[i] == 's') {
            if (line[i + 1] == 'q') {
                i += 3;
                stack.Push(line[i]);
                stack.Push(line[i - 1]);
                stack.Push(line[i - 2]);
                stack.Push(line[i - 3]);
                continue;
            }
            i += 2;
            stack.Push(line[i]);
            stack.Push(line[i - 1]);
            stack.Push(line[i - 2]);
            continue;
        }
        stack.Push(line[i]);

    }
    while (stack.Peek() != NULL) {
        res += stack.Pop();
        res += ' ';
    }
    return res;
}

#endif