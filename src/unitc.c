#include "unitc.h"

#include <stdio.h>
#include <time.h>
#include <unistd.h>

const char *default_colour = "[0m";
const char *error_colour   = "[0;31m";
const char *success_colour = "[0;32m";

// Every test will be considered to have passed until it is explicitly
// proven to have failed.
static int test_passed = 1;

static void (*before_each_function)();
static void (*after_each_function)();

// The default function to be called before and after each test.
static void default_func()
{
	return;
}

// Called upon initialisation of the library.
void __attribute__((constructor)) init_library()
{
	before_each_function = &default_func;
	after_each_function  = &default_func;
}

int assert(char res, const char *subject, const char *eval, int actual,
		int l_number, const char *func_name)
{
	if (res == 0)
	{
        printf("\033%s", error_colour); // Set the error colour
		printf("Assertion failed (in %s:%d): Actual: %s %s %d\n",
				func_name, l_number, subject, eval, actual);
        printf("\033%s", default_colour); // Set the default colour
		test_passed = 0;
		return -1;
	}

	return 0;
}

int assert_long(char res, const char *subject, const char *eval, int64_t actual,
		int l_number, const char *func_name)
{
    if (res == 0)
    {
        printf("\033%s", error_colour); // Set the error colour
        printf("Assertion failed (in %s:%d): Actual: %s %s %ld\n",
                func_name, l_number, subject, eval, actual);
        printf("\033%s", default_colour); // Set the default colour
        test_passed = 0;
        return -1;
    }

    return 0;
}

int assert_float(char res, const char *subject, const char *eval, float actual,
		int l_number, const char *func_name)
{
    if (res == 0)
    {
        printf("\033%s", error_colour); // Set the error colour
        printf("Assertion failed (in %s:%d): Actual: %s %s %f\n",
                func_name, l_number, subject, eval, actual);
        printf("\033%s", default_colour); // Set the default colour
        test_passed = 0;
        return -1;
    }

    return 0;
}

void set_before_each(void (*function)())
{
	before_each_function = function;
}

void set_after_each(void (*function)())
{
	after_each_function = function;
}

void test_name(const char *name)
{
    printf("\033%s", default_colour); // Set the default colour
	printf("-- Test: %s -- \n", name);	
}

void run_tests(void (*tests[])(), int num_tests)
{
	struct timespec begin, end;

	double elapsed_time = 0;
	int pass_count = 0;

	clock_gettime(CLOCK_REALTIME, &begin);

	// Run each test
	for (int i = 0; i < num_tests; i++)
	{
		// Reset the test pass variable
		test_passed = 1;

		// Call before each function
		(*before_each_function)();

		// Run each test
		(*tests[i])();

		// Call after each function
		(*after_each_function)();

		if (test_passed)
		{   
            printf("\033%s", success_colour); // Set the success colour
			printf("[\U00002713 ] Test PASSED\n");
            printf("\033%s", default_colour); // Set the default colour
			pass_count++;
		} else
		{
            printf("\033%s", error_colour); // Set the error colour
			printf("[\U00002715 ] Test FAILED\n");
            printf("\033%s", default_colour); // Set the default colour
		}

		printf("\n");
	}
	
	clock_gettime(CLOCK_REALTIME, &end);

	elapsed_time = (end.tv_sec - begin.tv_sec);
	elapsed_time += (end.tv_nsec - begin.tv_nsec) / 1000000.0;

	printf("Tests passed: %d/%d\n", pass_count, num_tests);
	printf("Elapsed time: %0.4f seconds\n", elapsed_time);
}
