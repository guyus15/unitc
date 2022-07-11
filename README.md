# unitc
A unit testing library written in C

## Installation
### Ubuntu Systems
To install *unitc* on Ubuntu and use it as a library without having to specify a link directory, first clone the repository and enter the following 
command from the root of the directory:

`make install`

This command will prompt you to enter your password in order to access the ` /usr/local/lib/` and ` /usr/local/include/` folders and creating the appropriate 
archive and include files.

## Build
### Ubuntu Systems
To build *unitc* on Ubuntu from within the repository's directory, you can use the following commmand:

`make build`

## Usage
### Creating Tests
When writing tests with *unitc*, it is preferable to create a separate file to group together related tests.

A simple test would look like the following:
```c
// Test file

static void test()
{
    /*
     * Specifies the name of the test. This is later used
     * when the tests are run to display the name of the test.
     */
    test_name("test");
    
    // This test will ensure that ...
    
    /*
     * Asserts if the two parameters are equal to each other, will fail if
     * they are not.
     */
    ASSERT_EQUAL(5, 5);
}
```

### Different Assertions
*unitc* provides a few types of assertions for you to use in your tests. These are the following:
- `ASSERT_EQUAL(actual, expected)` - for comparing the equality of integer (32-bit) values
- `ASSERT_LEQUAL(actual, expected)` - for comparing the equality of long integers (64-bit) values
- `ASSERT_FEQUAL(actual, expected)` - for comparing the equality of float values
- `ASSERT_NEQUAL(actual, expected)` - for comparing the inequality of integer (32-bit) values
- `ASSERT_GT(parameter1, parameter2)` - for comparing `parameter1` to be greater than `parameter2`
- `ASSERT_LT(parameter1, parameter2)` - for comparing `parameter1` to be less than than `parameter2`

### Before Each And After Each Test
You can specify functions to be run before and after each test, this can be done with `set_before_each()` and 
`set_after_each()`, respectively.

Each function takes in a void function pointer which points to the function to be called.

Example:
```c
static void before_test()
{
    // Do something before the test ...
}

static void after_test()
{
    // Do something after the test ...
}

int main()
{
    set_before_each(before_test);
    set_after_each(after_test);
    
    // Run tests
}
```

### Running Tests
To run tests in *unitc*, you need to collect them together in a void pointer array. This looks like the following:
```c
void (*tests[])() = 
{
   test_1,
   test_2,
   test_3
   // Etc 
};
```
With this, you can use `run_tests()` to run the tests like this:
```
run_tests(tests, num_tests);
```

### Complete Test File
```c
#include <unitc.h>

static void before_each()
{
    // Do something before test
}

static void after_each()
{
    // Do something after test
}

static void test_1()
{
	test_name("test_1");

	ASSERT_EQUAL(1, 1);
}

static void test_2()
{
	test_name("test_2");

	ASSERT_GT(1, 2);
}


static void test_3()
{
    test_name("test_3");

    ASSERT_EQUAL(5, 5);
}

int main(int argc, char *argv[])
{
    set_before_each(before_each);
    set_after_each(after_each);

	  void (*tests[])() =
	  {
		    test_1,
		    test_2,
        test_3
    };

	  run_tests(tests, 3);

	  return 0;
}
```
### Compiling Tests
When compiling a test with *unitc* you will have to compile the test with any source files referenced for the 
test as well as the *unitc* static library. 
If you ran `make install`, then you will not have to specify the path of the static library

