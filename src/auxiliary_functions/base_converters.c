#include <stdio.h>
#include <string.h>

static void	recursive_print_itoa(int num, const char *base, int len, FILE *file)
{
	if (num / len < 1)
		fprintf(file, "%c", base[num]);
	else
	{
		recursive_print_itoa(num / len, base, len, file);
		fprintf(file, "%c", base[num % len]);
	}
}

void	itoa_base(int num, const char *base, FILE *file)
{
	if (num < 0)
	{
		fprintf(file, "-");
		recursive_print_itoa(num * -1, base, strlen(base), file);
	}
	else
		recursive_print_itoa(num, base, strlen(base), file);
}

static void	recursive_print_ftoa(float num, const char *base, int len, FILE *file, int precision)
{
	int fractional_digit;

	if (num <= 0 || precision <= 0)
		return ;
	fractional_digit = num;
	fprintf(file, "%c", base[fractional_digit]);
	num -= fractional_digit;
	recursive_print_ftoa(num * len, base, len, file, precision - 1);
}

void	ftoa_base(float num, const char *base, FILE *file)
{
	int		integer_part;
	int		precision;
	float	fraction_part;

	integer_part = num;
	fraction_part = num - integer_part;

	itoa_base(integer_part, base, file);
	precision = 8;
	fprintf(file, ".");
	recursive_print_ftoa(fraction_part * strlen(base), base, strlen(base), file, precision);
}

