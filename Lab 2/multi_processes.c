#include "./utils.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>



int main(int argc, char **argv) {

    pid_t pid;

    int pid = fork();
    if (pid < 0) {
        perror("fork: cannot create child process!");
        exit(1);
    } else if (pid == 0) {
        for (int i = 2; argv[i] != NULL; i+=2) {
            if (is_positive_integer(argv[i]) == 1) {
			    int number = atoi(argv[i]);
			    is_prime(number);
		    }
        }
        
    } else {
        for (int i = 1; argv[i] != NULL; i+=2) {
            if (is_positive_integer(argv[i]) == 1) {
			    int number = atoi(argv[i]);
			    is_prime(number);
		    }
        }
    }
    return 0;
}