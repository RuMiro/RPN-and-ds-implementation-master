#pragma once

#ifndef RPN_calc
#define RPN_calc

#include <stdio.h>
#include <math.h>
#include <stdlib.h> 
#include <string>

using namespace std;
#define MAXSTACK    30

#define OP_QUIT      0 
#define OP_PUSH_OLD  1 
#define OP_PUSH_NEW  2
#define OP_ADD       3
#define OP_SUB       4
#define OP_MUL       5
#define OP_DIV       6
#define OP_NOTHING   8 
#define OP_clear     9
#define OP_CLEAR     10
#define OP_NOTNUM    11 
#define OP_SQRT      12
#define OP_POW       13
#define OP_LN        14
#define OP_LOG       15
#define OP_PUSHPI    16 
#define OP_DEGREE    17
#define OP_NOTKEY    18 
#define OP_SIN       19
#define OP_COS       20
#define OP_TAN       21
#define OP_DISPLAY   22
#define OP_INPUT     23
#define OP_REPEAT    24
#define OP_ASIN      25
#define OP_ACOS      26
#define OP_ATAN      27
#define OP_PRINT     28
#define OP_COMMENT   29
#define OP_MODULO    90 //


#define KEYLEN       10 //
#define POS          1
#define NEG         (-1) //
#define MAXINT (double) (((unsigned) ~((unsigned) 0))>>1)
#define M_PI       ((double) 3.14159265358979323846)

static double stack[MAXSTACK]; //
static double* stackptr;
static int sign = POS;


struct key {
	char* name;
	int  op;
};

static struct key keys[] = {
	"sqrt", OP_SQRT,
	"pow", OP_POW,
	"ln", OP_LN,
	"log", OP_LOG,
	"pi", OP_PUSHPI,
	"d", OP_DEGREE,
	"sin", OP_SIN,
	"cos", OP_COS,
	"tan", OP_TAN,
	"asin", OP_ASIN,
	"acos", OP_ACOS,
	"atan", OP_ATAN,
	"q", OP_QUIT,
	"c", OP_clear,
	"C", OP_CLEAR,
	"display", OP_DISPLAY,
	"input", OP_INPUT,
	"print", OP_PRINT,
	"#", OP_COMMENT,
	"z", OP_NOTKEY 
};

static char keyloc[KEYLEN];
FILE* fp, * fopen();
static int terse = 0;

int getop(double* numptr);
void initstack(void);
void push(double num);
double pop(void);
void display(int longe);
void untrail(void);
void untrailstd(void);
int isnotnumber(int c);
int ischar(int c);
double double_abs(double num);
void getkey(char* s, int c);
int keycmp(char* s, char* t);



#endif