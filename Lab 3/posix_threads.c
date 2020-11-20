#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <pthread.h>

struct thread_info {
	pthread_t thread_id;
	char *argv;
};

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

void *prime(void *arg) {
	struct thread_info *tinfo = arg;
	
	if (is_positive_integer(tinfo->argv) == 1) {
		int number = atoi(tinfo->argv);
		
		is_prime(number);
	}
	return NULL;
}

int main(int argc, char *argv[]) {
	int number_of_threads = argc - 1;
	struct thread_info *tinfo;
	
	tinfo = calloc(number_of_threads, sizeof(struct thread_info));
	
	for (int i = 1; i <= number_of_threads; ++i) {
		tinfo[i].argv = argv[i];
		
		int err = pthread_create(&tinfo[i].thread_id, NULL, &prime, &tinfo[i]);
		
		if (err) {
			printf("Thread creation failed: %d\n", err);
			
			return err;
		}
		else printf("Thread created with ID: %lu\n", tinfo[i].thread_id);
	}
	
	for (int i = 1; i <= number_of_threads; ++i) {
		int err = pthread_join(tinfo[i].thread_id, NULL);
		
		if (err) {
			printf("Failed to join thread: %d\n", err);
			return err;
		}
	}
	return 0;
}
