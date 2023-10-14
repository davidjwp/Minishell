/*
this is an "indexed" function-like macros, this allows only one macro to be
used with a value that can specify which object macro to use
example :
int	main(void)
{
	printf ("%s\n", IN1(1));
	return 0;	
}
by giving a different value to IN1 it will expand to whatever macro is chosen 
just be careful of the type of macro in the ternary operation 

#define	EXP1 "expression1"
#define	EXP2 "expression2"
#define	EXP3 "expression3"
#define	EXP4 "expression4"

#define IN3(val) (val == 0 ? EXP3 : EXP4)
#define IN2(val) (val == 0 ? EXP2 : IN2(val))
#define IN1(val) (val == 0 ? EXP1 : IN2(val))
*/

#include <stdio.h>
#include <ctype.h>

#define BIT_SIZ 8

#define HE HI
#define LLO _THERE
#define HELLO "HI THERE"
#define CAT(a,b) a##b
#define XCAT(a,b) CAT(a,b)
#define CALL(fn) fn(HE,LLO)

int error = 0;

enum operation_type{
	AND,
	OR,
	XOR,
	NOT,
	RSH,
	LSH
};

char *bit_conversion(int integer)
{
	char	bit[BIT_SIZ];

	bit[BIT_SIZ] = 0;
	for (int i = 0; i <= BIT_SIZ; i++)
		bit[(BIT_SIZ - 1) - i] = (integer & (1 << i) ? '1' : '0');
	return (bit);
}

int	op_AND(int x, int y)
{

	printf ("\t1\t%i\t%s\n", x, bit_conversion(x));
	printf ("\t\t\t&\n");
	printf ("\t1\t%i\t%s\n", y, bit_conversion(y));
	printf ("\t-------------\n");
	printf ("");
}

int	bit_operation(int n, int x, int y)
{
	switch (n){
		case AND:
			return (op_AND(x, y));
		case OR:
			return (x | y);
		case XOR:
			return (x ^ y);
		case NOT:
			return ((x > 0 ? ~x : (y > 0 ? ~y : 0)));
		case RSH:
			return (x >> y);
		case LSH:
			return (x << y);			
	}
}

int	atoi(char *str)
{
	int	res = 0;
	int	i;

	if (*str == 45)
		return (error = 1, 0);
	for (i = 0; str[i] && (str[i] >= 48 && str[i] <= 57); i++){
		res *= 10;
		res += (str[i] - 48);
	}
	if (str[i])
		return (error = 1, 0);
	return (res);
}

int	main(int argc, char **argv)
{
	if (argc < 4){
		printf ("Error: not enough arguments\n<program> <integer> <n> <bit operation>\n");
		return (0);
	}

	int	x = atoi(argv[1]);
	int	y = atoi(argv[2]);
	int	bit_op = atoi(argv[3]);

	if (x > 126|| y > 126 || bit_op > 5)
		return (printf("Error: bad values\n"));

	if (error){
		printf ("Error: wrong input\n");
		return (0);
	}

	printf ("\targument\tdecimal\tbinary\toperand\n");
	bit_operation(bit_op, x, y);
	return (0);
}
