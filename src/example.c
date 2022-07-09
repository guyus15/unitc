#include <unitc.h>

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
	void (*tests[])() =
	{
		test_1,
		test_2,
        test_3
    };

	run_tests(tests, 3);

	return 0;
}
