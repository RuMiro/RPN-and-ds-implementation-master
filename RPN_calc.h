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
#define OP_ERR       7
#define OP_NOTHING   8
#define OP_clear     9
#define OP_CLEAR     10
#define OP_NOTNUM    11
#define OP_SWAP      12
#define OP_SQRT      13
#define OP_EXP       14
#define OP_POW       15
#define OP_LN        16
#define OP_LOG       17
#define OP_PUSHPI    18
#define OP_DEGREE    19
#define OP_NOTKEY    20
#define OP_SIN       21
#define OP_COS       22
#define OP_TAN       23
#define OP_STO       24
#define OP_RCL       25
#define OP_TERSE     26
#define OP_VERBOSE   27
#define OP_DISPLAY   28
#define OP_INPUT     29
#define OP_REPEAT    30
#define OP_ASIN      31
#define OP_ACOS      32
#define OP_ATAN      33
#define OP_CHS       34
#define OP_STOA      35
#define OP_STOB      36
#define OP_STOC      37
#define OP_STOD      38
#define OP_STOE      39
#define OP_STOF      40
#define OP_STOG      41
#define OP_STOH      42
#define OP_STOI      43
#define OP_STOJ      44
#define OP_STOK      45
#define OP_STOL      46
#define OP_STOM      47
#define OP_STON      48
#define OP_STOO      49
#define OP_STOP      50
#define OP_STOQ      51
#define OP_STOR      52
#define OP_STOS      53
#define OP_STOT      54
#define OP_STOU      55
#define OP_STOV      56
#define OP_STOW      57
#define OP_STOX      58
#define OP_STOY      59
#define OP_STOZ      60
#define OP_RCLA      61
#define OP_RCLB      62
#define OP_RCLC      63
#define OP_RCLD      64
#define OP_RCLE      65
#define OP_RCLF      66
#define OP_RCLG      67
#define OP_RCLH      68
#define OP_RCLI      69
#define OP_RCLJ      70
#define OP_RCLK      71
#define OP_RCLL      72
#define OP_RCLM      73
#define OP_RCLN      74
#define OP_RCLO      75
#define OP_RCLP      76
#define OP_RCLQ      77
#define OP_RCLR      78
#define OP_RCLS      79
#define OP_RCLT      80
#define OP_RCLU      81
#define OP_RCLV      82
#define OP_RCLW      83
#define OP_RCLX      84
#define OP_RCLY      85
#define OP_RCLZ      86
#define OP_PRINT     87
#define OP_COMMENT   88
#define OP_RSP       89
#define OP_MODULO    90


#define KEYLEN       10
#define POS          1
#define NEG         (-1)
#define MAXINT (double) (((unsigned) ~((unsigned) 0))>>1)
#define M_PI       ((double) 3.14159265358979323846)

static double stack[MAXSTACK];
static double* stackptr;
static int sign = POS;
static double store;
static double storea;
static double storeb;
static double storec;
static double stored;
static double storee;
static double storef;
static double storeg;
static double storeh;
static double storei;
static double storej;
static double storek;
static double storel;
static double storem;
static double storen;
static double storeo;
static double storep;
static double storeq;
static double storer;
static double stores;
static double storet;
static double storeu;
static double storev;
static double storew;
static double storex;
static double storey;
static double storez;

struct key {
	char* name;
	int  op;
};

static struct key keys[] = {
	"c", OP_clear,
	"C", OP_CLEAR,
	"s", OP_SWAP,
	"sto", OP_STO,
	"stoa", OP_STOA,
	"stob", OP_STOB,
	"stoc", OP_STOC,
	"stod", OP_STOD,
	"stoe", OP_STOE,
	"stof", OP_STOF,
	"stog", OP_STOG,
	"stoh", OP_STOH,
	"stoi", OP_STOI,
	"stoj", OP_STOJ,
	"stok", OP_STOK,
	"stol", OP_STOL,
	"stom", OP_STOM,
	"ston", OP_STON,
	"stoo", OP_STOO,
	"stop", OP_STOP,
	"stoq", OP_STOQ,
	"stor", OP_STOR,
	"stos", OP_STOS,
	"stot", OP_STOT,
	"stou", OP_STOU,
	"stov", OP_STOV,
	"stow", OP_STOW,
	"stox", OP_STOX,
	"stoy", OP_STOY,
	"stoz", OP_STOZ,
	"rcl", OP_RCL,
	"rcla", OP_RCLA,
	"rclb", OP_RCLB,
	"rclc", OP_RCLC,
	"rcld", OP_RCLD,
	"rcle", OP_RCLE,
	"rclf", OP_RCLF,
	"rclg", OP_RCLG,
	"rclh", OP_RCLH,
	"rcli", OP_RCLI,
	"rclj", OP_RCLJ,
	"rclk", OP_RCLK,
	"rcll", OP_RCLL,
	"rclm", OP_RCLM,
	"rcln", OP_RCLN,
	"rclo", OP_RCLO,
	"rclp", OP_RCLP,
	"rclq", OP_RCLQ,
	"rclr", OP_RCLR,
	"rcls", OP_RCLS,
	"rclt", OP_RCLT,
	"rclu", OP_RCLU,
	"rclv", OP_RCLV,
	"rclw", OP_RCLW,
	"rclx", OP_RCLX,
	"rcly", OP_RCLY,
	"rclz", OP_RCLZ,
	"sqrt", OP_SQRT,
	"exp", OP_EXP,
	"xp", OP_EXP,
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
	"terse", OP_TERSE,
	"verbose", OP_VERBOSE,
	"display", OP_DISPLAY,
	"input", OP_INPUT,
	"repeat", OP_REPEAT,
	"chs", OP_CHS,
	"print", OP_PRINT,
	"#", OP_COMMENT,
	"rsp", OP_RSP,
	"z", OP_NOTKEY };

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