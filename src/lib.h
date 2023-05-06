/** 
     @file lib.h
     
     Модульний контроль. Необхідно створити свій калькулятор математичних виразів. Створити функцію, що приймає строку (напр. `3+5*2-67*3`) та повертає число - результат обчислення.
     
     @author Melnyk B. 
*/ 

#ifndef LIB_H
#define LIB_H

/** Бібліотеки які використовуються у програмі
*/

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/** MAX_STATEMENT_LENGTH - це константа, яка вказує на максимальну довжину математичного виразу, який може бути збережений у змінній statement. Це число використовується для визначення розміру масиву statement.
*/

#define MAX_STATEMENT_LENGTH 1000

/** Функції які використовуються у програмі
*/

int calculate(char *statement);
int calculate_statement_in_parentheses(char *statement, int *i);
int calculate_term(char *statement, int *i);
int calculate_factor(char *statement, int *i);
int calculate_number(char *statement, int *i);

#endif
