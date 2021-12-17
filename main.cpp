
#include "RPN_calc.h"
#include "InfToRPN_Convert.h"

#include <iostream>
#include <string>

using namespace std;




void main(int argc, char* argv[])
{
    setlocale(LC_ALL, "rus");
	

    //main2();
    int a(0);
	while (true) {
		cout << "1.Конвертор" << endl << "2.Калькулятор" << endl;
		cin >> a;
		string res;
		switch (a)
		{
		case 1:
			getRPN();
			break;
		case 2:
			break;
    
        
}



int getop(double* numptr)
{
int hex_num;
int c;
struct key* keyptr;

while (((c = getc(fp)) == ' ') || (c == '\t'))
;
switch (c) {
case EOF:
	return(EOF);
case '\n':
	return(OP_PUSH_OLD);
case '*':
	untrail();
	return(OP_MUL);

case '/':
	untrail();
	return(OP_DIV);

case '%':
	untrail();
	return(OP_MODULO);

case '-':
	if (isnotnumber(c = getc(fp))) { /*subtraction*/
		ungetc(c, fp);
		untrail();
		return(OP_SUB);
	}
	else { /*negative number*/
		sign = NEG;
		ungetc(c, fp);
		return(OP_NOTHING);
	}

case '+':
	if (isnotnumber(c = getc(fp))) { /*addition*/
		ungetc(c, fp);
		untrail();
		return(OP_ADD);
	}
	else { /*positive number*/
		ungetc(c, fp);
		return(OP_NOTHING);
	}

default:
	if (isnotnumber(c)) {
		getkey(keyloc, c);
		for (keyptr = keys; (*(keyptr->name) != 'z') && (keycmp(keyptr->name, keyloc) == 0); keyptr++)
			;
		return(keyptr->op);
	}
	else {  /*number*/
		if (c == '0')
			if ((c = getc(fp)) == 'x') {
				if (fscanf_s(fp, "%x", &hex_num)) {
					*numptr = (hex_num * sign);
					untrail();
					return(OP_PUSH_NEW);
				}
				else {
					getc(fp);
					untrail();
					return(OP_NOTNUM);
				}
			}
			else {
				ungetc(c, fp);
				c = '0';
			}

		ungetc(c, fp);
		if (fscanf_s(fp, "%lf", numptr)) {
			untrail();
			*numptr = (*numptr * sign);
			return(OP_PUSH_NEW);
		}
		else {
			getc(fp);
			untrail();
			return(OP_NOTNUM);
		}
	} /*number*/
}  /*switch (c) */
}


void initstack(void)
{
	int n;
	for (n = 0; n < MAXSTACK; n++)
		stack[n] = 0;
	stackptr = stack;
}

void push(double num)
{
	if (stackptr == (stack + MAXSTACK)) {
		fprintf(stderr, "неправильная запись\n");
		return;
	}

	*stackptr++ = num;
}



void display(int longe)
{
	double* ptr, double_abs(double);
	printf("--------------------\n");
	if (longe == 1)
		ptr = stack;
	else
		ptr = stackptr - 1;
	for (; ptr < stackptr; ptr++) {
		if (((double_abs(*ptr) < 1.0e7) && (double_abs(*ptr) > 1.0e-7)) || (*ptr == 0))
			printf("%.5f", *ptr);
		else
			printf("%.5e", *ptr);
		if ((*ptr <= MAXINT) && (*ptr >= (-MAXINT - 1.0)))
			printf("\n", (int)*ptr);
		else
			printf("--------------------\n");
	}
}

void untrail(void)
{
	int c;
	while (((c = getc(fp)) == ' ') || (c == '\t'))
		;
	if (c != '\n')
		ungetc(c, fp);
}

void untrailstd(void)
{
	int c;
	while (((c = getc(stdin)) == ' ') || (c == '\t'))
		;
	if (c != '\n')
		ungetc(c, stdin);
}







void getkey(char* s, int c)
{
	if (c == '#')
	{
		*s = c;
		*(s + 1) = '\0';
		return;
	}
	{
		char* t;
		t = s;
		do
			*t++ = c;
		while ((ischar(c = getc(fp))) && ((t - s) < (KEYLEN - 1)));
		*t = '\0';
		ungetc(c, fp);
		if (!(keycmp(s, "print") || keycmp(s, "input")))
			untrail();
	}
}


