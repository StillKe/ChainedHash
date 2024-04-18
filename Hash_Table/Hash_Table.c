#include <stdio.h>

#define HASH_CAPACITY 50000

/**
 * hash_function - Calculates the hash value of a string
 * @str: The input string
 *
 * Return: The hash value
 */
unsigned long hash_function(const char *str)
{
    unsigned long hash = 0;

    while (*str)
    {
        hash += *str++;
    }

    return hash % HASH_CAPACITY;
}

/**
 * main - Entry point of the program
 *
 * Return: Always 0
 */
int main(void)
{
    const char *input_str = "Hello";
    unsigned long hash_value = hash_function(input_str);

    printf("Hash value: %lu\n", hash_value);

    return 0;
}
