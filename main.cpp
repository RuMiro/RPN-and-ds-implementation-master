
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
		
		cout << "1.Конвертор" << endl << "2.Калькулятор" << endl << "3.Выход \n";
		cin >> a;
		string res;
		switch (a)
		{
		case 3: return;
		case 1:
			getRPN();
			break;
		case 2:
			cin.ignore();
			fprintf(stderr, "Калькулятор обратной польской нотации\n\
 q   Выход\n\
 c   Убрать элемент последний стека\n\
 C   Очистить весь стек\n\
доступные операции: +,-,*,/ \n\
 sqrt (4 sqrt результат 2),  log (1 log результат 0), ln(2,7 ln (прибризительно) результат 1, pow (2 3pow результат 8),\n\
 pi = 3.14, sin, cos, tan, asin, acos, atan в радианах\n");

			cout << "Напишите пример в ОПН: ";
			int optype;
			double val, temp, temp2;

			if (argc == 1)
				fp = stdin;
			else
				fopen_s(&fp, argv[1], "r");

			initstack();

			while ((optype = getop(&val)) != EOF) {
				if (optype == OP_QUIT)
					break;
				switch (optype) {
				case OP_QUIT:
					break;

				case OP_PUSH_OLD:
					if (terse == 0)
						printf(">\n");
					val = pop();
					push(val);
					push(val);
					break;

				case OP_PUSH_NEW:
					push(val);
					sign = POS;
					break;

				case OP_PUSHPI:
					push(M_PI);
					sign = POS;
					break;

				case OP_ADD:
					temp = pop();
					val = pop() + temp;
					push(val);
					break;

				case OP_SUB:
					temp = pop();
					val = pop() - temp;
					push(val);
					break;

				case OP_MUL:
					temp = pop();
					val = pop() * temp;
					push(val);
					break;

				case OP_SQRT:
					push(sqrt(pop()));
					break;

				case OP_DEGREE:
					push(((pop()) * M_PI) / 180.0);
					break;

				case OP_SIN:
					push(sin(pop()));
					break;

				case OP_COS:
					push(cos(pop()));
					break;

				case OP_TAN:
					push(tan(pop()));
					break;

				case OP_ASIN:
					push(asin(pop()));
					break;

				case OP_ACOS:
					push(acos(pop()));
					break;

				case OP_ATAN:
					push(atan(pop()));
					break;

				case OP_LN:
					temp = pop();
					if (temp <= 0) {
						fprintf(stderr, "на ноль делить нельзя\n");
						push(temp);
					}
					else
						push(log(temp));
					break;

				case OP_LOG:
					temp = pop();
					if (temp <= 0) {
						fprintf(stderr, "0 в степени 0\n");
						push(temp);
					}
					else
						push(log10(temp));
					break;

				case OP_DIV:
					temp = pop();
					if (temp == 0) {
						fprintf(stderr, "divide by 0\n");
						push(temp);
					}
					else {
						val = pop() / temp;
						push(val);
					}
					break;

				case OP_POW:
					temp = pop();
					temp2 = pop();
					if ((temp == 0) && (temp2 == 0)) {
						fprintf(stderr, "cannot use 2 zeros\n");
						push(temp2);
						push(temp);
					}
					else {
						push(pow(temp2, temp));
					}
					break;

				case OP_NOTHING:
					break;

				case OP_clear:
					pop();
					break;

				case OP_CLEAR:
					initstack();
					break;

				case OP_DISPLAY:
					display(0);
					break;

				case OP_INPUT:
				{
					int d;
					while (((d = getc(fp)) != '\n') && (d != EOF))
						putchar(d);
					if (scanf_s("%lf", &val)) {
						push(val);
						untrailstd();
						break;
					}
					else exit(1);
				}

	
				case OP_NOTNUM:
					fprintf(stderr, "такого числа нет\n");
					break;

				case OP_NOTKEY:
					fprintf(stderr, "такой буквы нет %s\n", keyloc);
					break;

				case OP_PRINT:
				{
					int d;
					while (((d = getc(fp)) != '\n') && (d != EOF))
						putchar(d);
					putchar('\n');
					break;
				}

				case OP_COMMENT:
				{
					int d;
					while (((d = getc(fp)) != '\n') && (d != EOF))
						;
					break;
				}


				case OP_MODULO:
					temp = pop();
					val = (unsigned int)double_abs(pop()) % (unsigned int)double_abs(temp);
					push(val);
					break;

				default:
					fprintf(stderr, "неправильный ввод\n");
					exit(1);
				}
				if ((optype != OP_NOTHING) && (optype != OP_NOTNUM) && (optype != OP_NOTKEY)
					&& (terse == 0))
					display(1);
			}
		}
	}
    
        
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

double pop(void)
{
	if (stackptr == stack) {
		fprintf(stderr, "неправильная запись\n");
		return(0.0);
	}

	return(*--stackptr);
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

int isnotnumber(int c)
{
	return((((c >= '0') && (c <= '9')) || (c == '.')) == 0);
}



double double_abs(double num)
{
	return(num < 0 ? -num : num);
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
		if (!(keycmp(s, "вывод") || keycmp(s, "вход")))
			untrail();
	}
}

int keycmp(char* s, char* t)
{
	for (; *s == *t; s++, t++)
		if (*s == '\0')
			return(1);
	return(0);
}

