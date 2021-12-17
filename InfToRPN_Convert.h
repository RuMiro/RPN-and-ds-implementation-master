#pragma once
#ifndef InfToRPN_Convert
#define InfToRPN_Convert

#include <iostream>
#include <string>
#include "stack.h"

using namespace std;

int priority(char op) {
	switch (op) {
	case '^':
		return 3;
		break;
	case '/':
	case '*':
		return 2;
		break;
	case '+':
	case '-':
		return 1;
		break;
	default:
		return 0;
		break;
	}
}

std::string topostfix(std::string s) {
	stacks<std::string> qq;
	std::string result;

	if (s == "") return "empty line!"; else {
		for (int i = 0; i < s.size(); i++) {

		}

		for (int i = 0; i < s.size(); i++) {
			if (s[i] >= '0' && s[i] <= '9') result += s[i];
			else {
				switch (s[i]) {
				case '(':
					qq.push("(");
					break;
				case ')':
					if (qq.top() != "(") {
						while (qq.top() != "(") {
							result += qq.top();
							qq.pop();
						}
					}
					qq.pop();
					break;
				case 'l':
					if (s[i + 1] == 'n') {
						qq.push(s.substr(i, 2));
						i += 1;
						continue;
						break;
					}
					qq.push(s.substr(i, 3));
					i += 2;
					continue;
					break;

				case 's':
				case 'c':
					qq.push(s.substr(i, 3));
					i += 2;
					continue;
					break;
				default:
					while (qq.notempty() && priority(s[i]) <= priority(qq.top()[0]) && (s[i] != '^' && priority(s[i]) == priority(qq.top()[0]))) {
						result += qq.top();
						qq.pop();
					}
					qq.push(std::string(1, s[i]));
					break;
				}
			}
		}

		while (qq.notempty()) {
			result += qq.top();
			qq.pop();
		}
		return result;
	}
}

int getRPN() {
	cin.ignore();
	std::string s;
	std::cout << "Enter the expression: ";
	getline(std::cin, s);
	s.erase(std::remove_if(s.begin(), s.end(), std::isspace), s.end());
	std::cout << "Result: " << topostfix(s) << "\n";
	return 0;
}
#endif