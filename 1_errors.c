#include "shell.h"

/**
* _errrs2i - Convert a string to an integer.
* @str: The string to be converted.
*
* Return: 0 converted number if successful.
*  -1 on error.
*/
int _errrs2i(char *str)
{
int i = 0;
unsigned long int ret = 0;

if (*str == '+')
str++;  /* NOTE: Removing '+' to prevent unexpected behavior in main. */
for (i = 0; str[i] != '\0'; i++)
{
if (str[i] >= '0' && str[i] <= '9')
{
ret *= 10;
ret += (str[i] - '0');
if (ret > INT_MAX)
return (-1);
}
else
return (-1);
}
return (ret);
}

/**
* print_error -The function prints an error message.
* @info: The parameter and return info struct.
* @errstr: String with the specified error type.
*
* This function prints an error message including the file name, line number,
*  command, and the specified error type.
*/
void print_error(info_t *info, char *errstr)
{
_eputs(info->fname);
_eputs(": ");
print_d(info->line_count, STDERR_FILENO);
_eputs(": ");
_eputs(info->argv[0]);
_eputs(": ");
_eputs(errstr);
}

/**
* print_d - Print a decimal (integer) number (base 10).
* @data: The input number.
* @fd: The file descriptor for output.
*
* Return: The number of characters printed.
*/
int print_d(int data, int fd)
{
int (*__putchar)(char) = _putchar;
int i, c = 0;
unsigned int _abs_, current;

if (fd == STDERR_FILENO)
__putchar = _eputchar;
if (data < 0)
{
_abs_ = -data;
__putchar('-');
c++;
}
else
_abs_ = data;
current = _abs_;
for (i = 1000000000; i > 1; i /= 10)
{
if (_abs_ / i)
{
__putchar('0' + current / i);
c++;
}
current %= i;
}
__putchar('0' + current);
c++;

return (c);
}

/**
* convert_num2base - Convert a number to a string with a given base.
* @digit: The number.
* @b: The base.
* @f: Argument flags.
*
* Return: A string representing the number.
*/
char *convert_num2base(long int digit, int b, int f)
{
static char *array;
static char buf[50];
char sign = 0;
char *ptr;
unsigned long n = digit;

if (!(f & CONVERT_UNSIGNED) && digit < 0)
{
n = -digit;
sign = '-';
}
array = f & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
ptr = &buf[49];
*ptr = '\0';

do {
*--ptr = array[n % b];
n /= b;
} while (n != 0);

if (sign)
*--ptr = sign;
return (ptr);
}

/**
* remove_comms - Replace the first instance of '#' with '\0'.
* @buffer: The address of the string to modify.
*
* This function modifies the input string by replacing the first instance
*  of '#' with '\0'.
*/
void remove_comms(char *buffer)
{
int i;

for (i = 0; buffer[i] != '\0'; i++)
if (buffer[i] == '#' && (!i || buffer[i - 1] == ' '))
{
buffer[i] = '\0';
break;
}
}
