#ifndef UNITC_HEADER
#define UNITC_HEADER

#include <stdint.h>
#include <float.h>

#define ASSERT_EQUAL(a, b)   (assert(a == b, #a, "==", a, __LINE__, __func__))
#define ASSERT_LEQUAL(a, b)   (assert_long(a == b, #a, "==", a, __LINE__, __func__))
#define ASSERT_FEQUAL(a, b)   (assert_float(fabs(a - b) < DBL_EPSILON, #a, "==", a, __LINE__, __func__))
#define ASSERT_NEQUAL(a, b)  (assert(a != b, #a, "!=", a, __LINE__, __func__))
#define ASSERT_GT(a, b)      (assert(a > b, #a, ">", a, __LINE__, __func__))
#define ASSERT_LT(a, b)      (assert(a < b, #a, "<", a, __LINE__, __func__))

int assert(char res, const char *subject, const char *eval, int actual,
		int l_number, const char *func_name);
int assert_long(char res, const char *subject, const char *eval, int64_t actual,
		int l_number, const char *func_name);
int assert_float(char res, const char *subject, const char *eval, float actual,
		int l_number, const char *func_name);

void set_before_each(void (*function)());
void set_after_each(void (*function)());

void test_name(const char *name);

void run_tests(void (*test[])(), int num_tests);

#endif 
