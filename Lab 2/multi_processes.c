#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void is_positive_integer(char *str) {
	if (isdigit(str[0]) == 0) {
			printf("INPUT ERROR: %s is not a positive integer!\n", str);
	}
}

void is_prime(int number) {
	int i;
	for (i = 2; i * i <= number; ++i) {
		if (number % i == 0) {
			printf("%d is not a prime\n", number);
			return;
		}
	}
	printf("%d is a prime\n", number);
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		perror("input: not found!");
		return 1;
	}
	
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork: cannot create child process!");
        exit(1);
	
    } else if (pid == 0) {
        for (int i = 2; i < argc; i+=2) {
            if (is_positive_integer(argv[i]) == 1) {
			    int number = atoi(argv[i]);
			    is_prime(number);
		    }
        }
        
    } else {
        for (int i = 1; i < argc; i+=2) {
            if (is_positive_integer(argv[i]) == 1) {
			    int number = atoi(argv[i]);
			    is_prime(number);
		    }
        }
    }
	
    return 0;
}