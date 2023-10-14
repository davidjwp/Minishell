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

#include <stdlib.h>
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

int	op_cmp(char *arg)
{
	char	*bitwise_op[7]; 

	bitwise_op[6] = NULL;
	for (int i = 0; i < 7; i++)
		bitwise_op[i] = (char* [7]){"AND", "OR", "XOR", "NOT", "RSH", "LSH", NULL}[i];

	for (int i = 0; bitwise_op[i]; i++){
		int	y = 0;
		while (arg[y] == bitwise_op[i][y] && arg[y])
			y++;
		if (!arg[y] && !bitwise_op[i][y])
			return (i);
	}
	return (10);
}

char *bit_conversion(int integer, char *bit)
{
	for (int i = 0; i < BIT_SIZ; i++)
		bit[(BIT_SIZ - 1) - i] = (integer & (1 << i) ? '1' : '0');
	return (bit);
}

int	op_AND(int x, int y)
{
	char	*bit = (char *)malloc(sizeof(char) * (BIT_SIZ + 1));

	bit[BIT_SIZ] = 0;
	printf ("\tdec\tbin\t\top\n");
	printf ("\t%i\t%s\n", x, bit_conversion(x, bit));
	printf ("\t\t\t\tAND\n");
	printf ("\t%i\t%s\n", y, bit_conversion(y, bit));
	printf ("\t-------------\n");
	printf ("\t%i\t%s\n", x & y, bit_conversion(x & y, bit));
	free(bit);
	return (1);
}

int	op_OR(int x, int y)
{
	char	*bit = (char *)malloc(sizeof(char) * (BIT_SIZ + 1));

	bit[BIT_SIZ] = 0;
	printf ("\tdec\tbin\t\top\n");
	printf ("\t%i\t%s\n", x, bit_conversion(x, bit));
	printf ("\t\t\t\tOR\n");
	printf ("\t%i\t%s\n", y, bit_conversion(y, bit));
	printf ("\t-------------\n");
	printf ("\t%i\t%s\n", x | y, bit_conversion(x | y, bit));
	free(bit);
	return (1);
}

int	op_NOT(int x, int y)
{
	char	*bit = (char *)malloc(sizeof(char) * (BIT_SIZ + 1));

	bit[BIT_SIZ] = 0;
	printf ("\tdec\tbin\t\top\n");
	printf ("\t\t\t\tNOT\n");
	printf ("\t%i\t%s\n", x, bit_conversion(x, bit));
	printf ("\t%i\t%s\n", ~x, bit_conversion(~x, bit));
	printf ("\t-------------\n");
	printf ("\t%i\t%s\n", y, bit_conversion(y, bit));
	printf ("\t%i\t%s\n", ~y, bit_conversion(~y, bit));
	free(bit);
	printf ("\t-------------\n");
	return (1);
}

int	op_XOR(int x, int y)
{
	char	*bit = (char *)malloc(sizeof(char) * (BIT_SIZ + 1));

	bit[BIT_SIZ] = 0;
	printf ("\tdec\tbin\t\top\n");
	printf ("\t%i\t%s\n", x, bit_conversion(x, bit));
	printf ("\t\t\t\tXOR\n");
	printf ("\t%i\t%s\n", y, bit_conversion(y, bit));
	printf ("\t-------------\n");
	printf ("\t%i\t%s\n", x ^ y, bit_conversion(x ^ y, bit));
	free(bit);
	return (1);
}

int	op_RSH(int x, int y)
{
	char	*bit = (char *)malloc(sizeof(char) * (BIT_SIZ + 1));

	bit[BIT_SIZ] = 0;
	printf ("\tdec\tbin\t\top\n");
	printf ("\t%i\t%s\n", x, bit_conversion(x, bit));
	printf ("\t\t\t\tRIGHT_SHIFT\n");
	printf ("\t%i\t%s\n", y, bit_conversion(y, bit));
	printf ("\t-------------\n");
	printf ("\t%i\t%s\n", x >> y, bit_conversion(x >> y, bit));
	free(bit);
	return (1);
}

int	op_LSH(int x, int y)
{
	char	*bit = (char *)malloc(sizeof(char) * (BIT_SIZ + 1));

	bit[BIT_SIZ] = 0;
	printf ("\tdec\tbin\t\top\n");
	printf ("\t%i\t%s\n", x, bit_conversion(x, bit));
	printf ("\t\t\t\tLEFT_SHIFT\n");
	printf ("\t%i\t%s\n", y, bit_conversion(y, bit));
	printf ("\t-------------\n");
	printf ("\t%i\t%s\n", x << y, bit_conversion(x << y, bit));
	free(bit);
	return (1);
}


int	bit_operation(char *arg, int x, int y)
{
	switch (op_cmp(arg)){
		case AND:
			return (op_AND(x, y));
		case OR:
			return (op_OR(x, y));
		case XOR:
			return (op_XOR(x, y));
		case NOT:
			return (op_NOT(x, y));
		case RSH:
			return (op_RSH(x, y));
		case LSH:
			return (op_LSH(x, y));
		case 10:
			return (printf ("Error: bad bit operator\nAND, OR, XOR, NOT, RSH, LSH\n"));
	}
}

int	ft_atoi(char *str)
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
		printf ("Error: not enough arguments\n<program> <integer> <n> <bit operator>\n\
		(bit operators) AND, OR, XOR, NOT, RSH, LSH\n");
		return (0);
	}

	int	x = ft_atoi(argv[1]);
	int	y = ft_atoi(argv[2]);

	if (x > 256|| y > 256)
		return (printf("Error: bad values\n"));

	if (error){
		printf ("Error: wrong input\n");
		return (0);
	}

	bit_operation(argv[3], x, y);
	return (0);
}
