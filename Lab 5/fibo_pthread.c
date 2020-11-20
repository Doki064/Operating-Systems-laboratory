#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <pthread.h>

int *fibo_seq; // array of fibonacci sequence
int fibo_term; // size of fibonacci sequence
int fibo_count; // counter of fibonacci sequence

int is_positive_integer(char *arg) {
	if (isdigit(arg[0]) == 0) {
			printf("Input error: %s not an integer!\n", arg);
			return -1;
	}

  if (atoi(arg) < 0) {
    printf("Input error: %s not a non-negative integer!\n", arg);
    return -1;
  }

	return 0;
}

void *fibonacci(void *arg) {
  if (fibo_count == 0) {
    fibo_seq[fibo_count] = 0;
    pthread_exit(0);
  }

  if (fibo_count == 1) {
    fibo_seq[fibo_count] = 1;
    pthread_exit(0);
  }

  fibo_seq[fibo_count] = fibo_seq[fibo_count - 1] + fibo_seq[fibo_count - 2];
  pthread_exit(0);
}

int main(int argc, char *argv[]) {

  if (argc != 2) {
    printf("Input error: must specify a fibonacci term!\n");
    return -1;
  }
	int err = is_positive_integer(argv[1]);
	if (err != 0) return err;

  fibo_term = atoi(argv[1]);
	fibo_seq = (int *) malloc((fibo_term+1) * sizeof(int));
  pthread_t *thread_id = (pthread_t *) malloc((fibo_term+1) * sizeof(pthread_t));

  pthread_attr_t attr;
  pthread_attr_init(&attr);

	for (fibo_count = 0; fibo_count <= fibo_term; ++fibo_count) {
		err = pthread_create(&thread_id[fibo_count], &attr, &fibonacci, NULL);

		if (err) {
			printf("Thread creation failed: %d\n", err);
			return err;
		}
		// else printf("Thread created with ID: %lu\n", thread_id[fibo_count]);
	}

	for (int i = 0; i <= fibo_term; ++i) {
		err = pthread_join(thread_id[i], NULL);

		if (err) {
			printf("Failed to join thread: %d\n", err);
			return err;
		}
	}

  printf("Fibonacci sequence: ");
  for (int i = 0; i <= fibo_term; ++i) {
    printf("%d ", fibo_seq[i]);
  }
  printf("\n");
	return 0;
}
