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
            res += stack.Pop();
            checkPriority = GetPriority(stack.Peek());
        }
        if (line[i] == 'a' && line[i + 1] == 'r' && line[i + 2] == 'c') {
            if ((line[i+3] == 'c' && line[i + 4] == 'o' && line[i + 5] == 's')) {
                stack.Push(' ');
                i += 5;
                stack.Push(line[i]);
                stack.Push(line[i - 1]);
                stack.Push(line[i - 2]);
                stack.Push(line[i - 3]);
                stack.Push(line[i - 4]);
                stack.Push(line[i - 5]);
                continue;
            }
            if ((line[i+3] == 's' && line[i + 4] == 'i' && line[i + 5] == 'n')) {
                stack.Push(' ');
                i += 5;
                stack.Push(line[i]);
                stack.Push(line[i - 1]);
                stack.Push(line[i - 2]);
                stack.Push(line[i - 3]);
                stack.Push(line[i - 4]);
                stack.Push(line[i - 5]);
                continue;
            }
            if (line[i+3] == 't' && line[i + 4] == 'g') {
                stack.Push(' ');
                i += 4;
                stack.Push(line[i]);
                stack.Push(line[i - 1]);
                stack.Push(line[i - 2]);
                stack.Push(line[i - 3]);
                stack.Push(line[i - 4]);
                continue;
            }
        }
        if ((line[i] == 'c' && line[i + 1] == 'o' && line[i+2] == 's')) {
            stack.Push(' ');
            i += 2;
            stack.Push(line[i]);
            stack.Push(line[i - 1]);
            stack.Push(line[i - 2]);
            continue;
        }
        if (line[i] == 'p' && line [i+1] == 'i') {
            stack.Push(' ');
            i += 1;
            stack.Push(line[i]);
            stack.Push(line[i - 1]);
            continue;
        }
        if ((line[i] == 'l' && line[i + 1] == 'n') || (line[i] == 'l' && line[i + 1] == 'o' && line[i + 2] == 'g')) {
            stack.Push(' ');
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
        if ((line[i] == 's' && line[i + 1] == 'i' && line[i + 2] == 'n') || ((line[i] == 's' && line[i + 1] == 'q' && line[i + 2] == 'r' && line[i + 3] == 't'))) {
            stack.Push(' ');
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
        if (currentPriotity != 0) stack.Push(' ');
        stack.Push(line[i]);

    }
    while (stack.Peek() != NULL) {
        res += stack.Pop();
    }
    return res;
}

#endif  
// (1+2)^3+sin(4+5)^(6*7)