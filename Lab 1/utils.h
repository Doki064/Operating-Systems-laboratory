#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int is_positive_integer(char *str) {
	if (isdigit(str[0]) == 0) {
			printf("INPUT ERROR: %s is not a positive integer!\n", str);
			return 0;
	}
	return 1;
}

int is_prime(int number) {
	int i;
	for (i = 2; i * i <= number; ++i) {
		if (number % i == 0) {
			printf("%d is not a prime\n", number);
			return 0;
		}
	}
	printf("%d is a prime\n", number);
	return 1;
}

void prime(char **argv) {
	int i;
	for (i = 1; argv[i] != NULL; ++i) {
		if (is_positive_integer(argv[i]) == 1) {
			int number = atoi(argv[i]);
			is_prime(number);
		}
	}
}

int has_pythagorean(int number) {
	int i, j;
	for (i = 1; i * i <= number; ++i) {
		for (j = i; j * j <= number; ++j) {
			if (i * i + j * j == number) {
				printf("%d satifies a Pythagorean triplet\t\t\t", number);
				printf("%d^2 + %d^2 = %d\n", i, j, number);
				return 1;
			}
		}
	}
	printf("%d does not satifies Pythagorean triplet\n", number);
	return 0;
}

void pythago(char **argv) {
	int i;
	for (i = 1; argv[i] != NULL; ++i) {
		if (is_positive_integer(argv[i]) == 1) {
			int number = atoi(argv[i]);
			has_pythagorean(number);	
		}
	}
}
