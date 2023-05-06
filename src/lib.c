/** 
      @file lib.c 
      
      Модульний контроль. Необхідно створити свій калькулятор математичних виразів. Створити функцію, що приймає строку (напр. `3+5*2-67*3`) та повертає число - результат обчислення.
 
      @author Melnik B. 
*/ 
 
/** 
 Заголовний файл lib.h
*/ 

#include "lib.h"
#include <stdio.h>

/** Дана функція int calculate(char *statement) є головною функцією, яка обчислює математичний вираз, який міститься в рядку statement. Функція викликає допоміжну функцію calculate_statement_in_parentheses з параметрами statement та індексом i, щоб обчислити вираз, який міститься в дужках. Індекс i використовується для визначення поточної позиції в рядку statement.

@param result - це змінна типу int, яка ініціалізується значенням, повернутим функцією calculate_statement_in_parentheses. Вона використовується для зберігання результату обчислень виразу, переданого в аргументі statement.
*/

int calculate(char *statement) {
    int i = 0;
    int result = calculate_statement_in_parentheses(statement, &i);
    while (statement[i] != '\0') {
        i++;
    }
    return result;
}

/** Функція int calculate_statement_in_parentheses(char *statement, int *i) обчислює значення виразу в дужках, що знаходиться в рядку statement. Змінна i вказує на поточну позицію у рядку. Функція обчислює перший множник за допомогою функції calculate_term, а потім перевіряє наявність операцій додавання або віднімання. Якщо такі операції є, то функція обчислює наступний множник за допомогою функції calculate_term і додає чи віднімає його від результату відповідно. Повертає результат обчислення виразу в дужках.

@param result - ціле число, яке містить результат обчислення математичного виразу в дужках.
@param statement - масив символів, який містить математичний вираз.
@param i - вказівник на ціле число, яке містить індекс поточного символу в математичному виразі.
@param operator - символ, який містить оператор додавання або віднімання.
@param term - ціле число, яке містить значення наступного доданка або від'ємника в математичному виразі.
*/

int calculate_statement_in_parentheses(char *statement, int *i) {
    int result = calculate_term(statement, i);
    while (statement[*i] == '+' || statement[*i] == '-') {
        char operator = statement[(*i)++];
        int term = calculate_term(statement, i);
        if (operator == '+') {
            result += term;
        } else {
            result += (-term);
        }
    }
    return result;
}

/** Функція int calculate_term(char *statement, int *i) обчислює та повертає значення терміну в математичному виразі statement, починаючи з позиції *i. Термін - це добуток чи частка факторів.

@param result: змінна типу int, що зберігає результат обчислення.
@param statement: масив символів, що містить математичний вираз.
@param i: вказівник на поточну позицію у масиві statement.
@param operator: змінна типу char, що зберігає поточний оператор (один з символів *, / або %).
@param actor: змінна типу int, що зберігає результат обчислення дочірнього виразу calculate_factor().
*/

int calculate_term(char *statement, int *i) {
    int result = calculate_factor(statement, i);
    while (statement[*i] == '*' || statement[*i] == '/' || statement[*i] == '%') {
        char operator = statement[(*i)++];
        int factor = calculate_factor(statement, i);
        if (operator == '*') {
            result *= factor;
        } else if (operator == '/') {
            result /= factor;
        } else {
            result = result % factor;
        }
    }
    return result;
}

/** Функція int calculate_factor(char *statement, int *i) обчислює фактор - це число або вираз, який складається з числа та можливої операції піднесення до степеня.

@param statement - масив символів, який містить математичний вираз.
@param i - вказівник на ціле число, яке вказує на поточну позицію в масиві statement.
@param result - ціле число, яке містить результат обчислення фактора виразу.
@param operator - символ арифметичної операції, яку потрібно виконати над факторами.
@param factor - ціле число, яке містить значення фактора виразу.
@param exponent - ціле число, яке містить значення показника степеня для фактора.
*/

int calculate_factor(char *statement, int *i) {
    int result = calculate_number(statement, i);
    while (statement[*i] == '*' || statement[*i] == '/' || statement[*i] == '%') {
        char operator = statement[(*i)++];
        int factor = calculate_number(statement, i);
        if (operator == '*') {
            result *= factor;
        } else if (operator == '/') {
            result /= factor;
        } else {
            result = result % factor;
        }
    }
    if (statement[*i] == '^') {
        (*i)++;
        int exponent = calculate_factor(statement, i);
        result = pow(result, exponent);
    }
    return result;
}

/** Функція calculate_number отримує рядок statement та позицію i у рядку. Функція шукає число у рядку, що починається з позиції i. Якщо перший символ на цій позиції - знак мінуса, то функція зберігає цей знак та збільшує позицію i. Далі функція перевіряє, чи на позиції i знаходиться відкриваюча дужка (. Якщо так, то функція обчислює вираз у дужках та збільшує позицію i, щоб перейти до наступного символу після закриваючої дужки ). Якщо перший символ не є дужкою, функція знаходить число, яке складається з послідовності цифр. Функція повертає число, помножене на знак, знайдений на початку, якщо такий був.

@param result: зберігає числове значення під час обчислення числа.
@param sign: зберігає знак числа, що обчислюється (1, якщо додатне, -1, якщо від'ємне).
@param statement: рядок з математичним виразом, з якого витягуються числові значення.
@param i: вказівник на поточну позицію в рядку statement, з якої починається число. Після виконання функції, значення вказівника змінюється на наступну позицію в рядку після числа.
*/

int calculate_number(char *statement, int *i) {
    int result = 0;
    int sign = 1;
    if (statement[*i] == '-') {
        sign = -1;
        (*i)++;
    }
    if (statement[*i] == '(') {
        (*i)++;
        result = calculate_statement_in_parentheses(statement, i);
    } else {
        while (isdigit(statement[*i]) || statement[*i] == ' ') {
            if (isdigit(statement[*i])) {
                result = result * 10 + (statement[(*i)++] - '0');
            } else {
                (*i)++;
            }
        }
    }
    if (statement[*i] == '^') {
        (*i)++;
        int exponent = calculate_number(statement, i);
        result = pow(result, exponent);
    }
    return sign * result;
}


