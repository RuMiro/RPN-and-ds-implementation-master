
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
			cin.ignore();
			fprintf(stderr, "Reverse Polish notation calculator\n\
 q     quits\n\
 c     removes last stack position\n\
 C     clears  stack\n\
 operators are +,-,*,/ (+ and - also unary)\n\
 sqrt (4 sqrt result 2), exp, log (1 log result 0), ln(2,7 ln (прибризительно) result 1, pow (2 3pow result 8), pi = 3.14, sin, cos, tan  arguments in radials, asin, acos, atan  results in radials\n");

			cout << "Write RPN: ";
			int optype;
			double val, temp, temp2;
			/* double exp(), log(), log10(),pow(), sqrt(),sin(),cos(),tan(),asin(),acos(),atan(); */

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

				case OP_CHS:
					push(-(pop()));
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

				case OP_EXP:
					push(exp(pop()));
					break;

				case OP_LN:
					temp = pop();
					if (temp <= 0) {
						fprintf(stderr, "cannot use 0 or negative\n");
						push(temp);
					}
					else
						push(log(temp));
					break;

				case OP_LOG:
					temp = pop();
					if (temp <= 0) {
						fprintf(stderr, "cannot use 0 or negative\n");
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

				case OP_SWAP:
					temp = pop();
					temp2 = pop();
					push(temp);
					push(temp2);
					break;

				case OP_STO:
					push(store = pop());
					break;

				case OP_STOA:
					push(storea = pop());
					break;

				case OP_STOB:
					push(storeb = pop());
					break;

				case OP_STOC:
					push(storec = pop());
					break;

				case OP_STOD:
					push(stored = pop());
					break;

				case OP_STOE:
					push(storee = pop());
					break;

				case OP_STOF:
					push(storef = pop());
					break;

				case OP_STOG:
					push(storeg = pop());
					break;

				case OP_STOH:
					push(storeh = pop());
					break;

				case OP_STOI:
					push(storei = pop());
					break;

				case OP_STOJ:
					push(storej = pop());
					break;

				case OP_STOK:
					push(storek = pop());
					break;

				case OP_STOL:
					push(storel = pop());
					break;

				case OP_STOM:
					push(storem = pop());
					break;

				case OP_STON:
					push(storen = pop());
					break;

				case OP_STOO:
					push(storeo = pop());
					break;

				case OP_STOP:
					push(storep = pop());
					break;

				case OP_STOQ:
					push(storeq = pop());
					break;

				case OP_STOR:
					push(storer = pop());
					break;

				case OP_STOS:
					push(stores = pop());
					break;

				case OP_STOT:
					push(storet = pop());
					break;

				case OP_STOU:
					push(storeu = pop());
					break;

				case OP_STOV:
					push(storev = pop());
					break;

				case OP_STOW:
					push(storew = pop());
					break;

				case OP_STOX:
					push(storex = pop());
					break;

				case OP_STOY:
					push(storey = pop());
					break;

				case OP_STOZ:
					push(storez = pop());
					break;

				case OP_RCL:
					push(store);
					break;

				case OP_RCLA:
					push(storea);
					break;

				case OP_RCLB:
					push(storeb);
					break;

				case OP_RCLC:
					push(storec);
					break;

				case OP_RCLD:
					push(stored);
					break;

				case OP_RCLE:
					push(storee);
					break;

				case OP_RCLF:
					push(storef);
					break;

				case OP_RCLG:
					push(storeg);
					break;

				case OP_RCLH:
					push(storeh);
					break;

				case OP_RCLI:
					push(storei);
					break;

				case OP_RCLJ:
					push(storej);
					break;

				case OP_RCLK:
					push(storek);
					break;

				case OP_RCLL:
					push(storel);
					break;

				case OP_RCLM:
					push(storem);
					break;

				case OP_RCLN:
					push(storen);
					break;

				case OP_RCLO:
					push(storeo);
					break;

				case OP_RCLP:
					push(storep);
					break;

				case OP_RCLQ:
					push(storeq);
					break;

				case OP_RCLR:
					push(storer);
					break;

				case OP_RCLS:
					push(stores);
					break;

				case OP_RCLT:
					push(storet);
					break;

				case OP_RCLU:
					push(storeu);
					break;

				case OP_RCLV:
					push(storev);
					break;

				case OP_RCLW:
					push(storew);
					break;

				case OP_RCLX:
					push(storex);
					break;

				case OP_RCLY:
					push(storey);
					break;

				case OP_RCLZ:
					push(storez);
					break;

				case OP_TERSE:
					terse = 1;
					break;

				case OP_VERBOSE:
					terse = 0;
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

				case OP_REPEAT:
					if (fp != stdin) {
						fclose(fp);
						fopen_s(&fp, argv[1], "r");
					}
					initstack();
					break;

				case OP_NOTNUM:
					fprintf(stderr, "not a number\n");
					break;

				case OP_NOTKEY:
					fprintf(stderr, "not a keyword: %s\n", keyloc);
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

				case OP_RSP:
				{
					double c = pop();//close
					double l = pop();//low
					double h = pop();//high
					double p = (h + l + c) / 3;//pivot
					push(p + (h - l));//R2
					push((2 * p) - l);//R1
					push((2 * p) - h + 0.68 * (h - l));//P1
					push(p);                 //Pivot
					push((2 * p) - h + 0.32 * (h - l));//P2
					push((2 * p) - h);//S1
					push(p - (h - l));//S2
					break;
				}

				case OP_MODULO:
					temp = pop();
					val = (unsigned int)double_abs(pop()) % (unsigned int)double_abs(temp);
					push(val);
					break;

				default:
					fprintf(stderr, "bad input\n");
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

int ischar(int c)
{
	return(((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')));
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
		if (!(keycmp(s, "print") || keycmp(s, "input")))
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

