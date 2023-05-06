#include "lib.h"
#include <stdio.h>
#include <check.h>

START_TEST (test_calculate_number)
{
    int i = 0;
    char statement[] = "123";
    ck_assert_int_eq(123, calculate_number(statement, &i));

    i = 0;
    char statement2[] = "-123";
    ck_assert_int_eq(-123, calculate_number(statement2, &i));

    i = 0;
    char statement3[] = "(3+4)";
    ck_assert_int_eq(7, calculate_number(statement3, &i));

    i = 0;
    char statement4[] = "2^3";
    ck_assert_int_eq(8, calculate_number(statement4, &i));
}
END_TEST

START_TEST (test_calculate_factor)
{
    int i = 0;
    char statement[] = "2^3";
    ck_assert_int_eq(8, calculate_factor(statement, &i));

    i = 0;
    char statement2[] = "2*3^2";
    ck_assert_int_eq(18, calculate_factor(statement2, &i));

    i = 0;
    char statement3[] = "4%3";
    ck_assert_int_eq(1, calculate_factor(statement3, &i));
}
END_TEST

START_TEST (test_calculate_term)
{
    int i = 0;
    char statement[] = "2*3";
    ck_assert_int_eq(6, calculate_term(statement, &i));

    i = 0;
    char statement2[] = "8/4";
    ck_assert_int_eq(2, calculate_term(statement2, &i));

    i = 0;
    char statement3[] = "10%3";
    ck_assert_int_eq(1, calculate_term(statement3, &i));
}
END_TEST

START_TEST (test_calculate_statement_in_parentheses)
{
    int i = 0;
    char statement[] = "2+3";
    ck_assert_int_eq(5, calculate_statement_in_parentheses(statement, &i));

    i = 0;
    char statement2[] = "2+3-4";
    ck_assert_int_eq(1, calculate_statement_in_parentheses(statement2, &i));

    i = 0;
    char statement3[] = "10/5+3";
    ck_assert_int_eq(5, calculate_statement_in_parentheses(statement3, &i));
}
END_TEST

START_TEST (test_calculate)
{
    char statement[] = "3+5*2-67*3";
    ck_assert_int_eq(-188, calculate(statement));

    char statement2[] = "2*(3+4)";
    ck_assert_int_eq(14, calculate(statement2));

    char statement3[] = "5^2-6*(3+4)";
    ck_assert_int_eq(-17, calculate(statement3));
}
END_TEST

Suite *calculator_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Calculator");

    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_calculate_number);
    tcase_add_test(tc_core, test_calculate_factor);
    tcase_add_test(tc_core, test_calculate_term);
    tcase_add_test(tc_core, test_calculate_statement_in_parentheses);
    tcase_add_test(tc_core, test_calculate);

    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = calculator_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
