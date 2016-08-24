#include <iostream>
#include "calculator.h"

using namespace std;
#define BOOST_TEST_MODULE test_calculator
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(TechnicalTaskTest)
    BOOST_AUTO_TEST_CASE(test0){
        string expression = "-1 + 5 - 3";
        double result_expression = 1;
        ExpressionParser ep(expression);
        BOOST_TEST( ep.Result() == result_expression);
    }
    BOOST_AUTO_TEST_CASE(test1){
        string expression = "-10 + (8*2.5) - (3/1.5)";
        double result_expression = 8;
        ExpressionParser ep(expression);
        BOOST_TEST( ep.Result() == result_expression);
    }
    BOOST_AUTO_TEST_CASE(test2){
        string expression = "1 + (2 * (2.5 + 2.5 + (3-2))) - (3/1.5)";
        double result_expression = 11;
        ExpressionParser ep(expression);
        BOOST_TEST( ep.Result() == result_expression);
    }
    BOOST_AUTO_TEST_CASE(test3){
    setlocale(LC_CTYPE,"Russian");
    string expression = "1.1 + 2.1 + abc";
    string result_expression = "некорректный ввод, строка содержит недопустимое выражение abc";
    ExpressionParser ep(expression);
    try
    {
        ep.Result();
    }
    catch(const runtime_error&  ex)
    {
        BOOST_TEST(result_expression.compare(ex.what()) == 0);
    }
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(SimpleTests)
    BOOST_AUTO_TEST_CASE(test0){
        string expression = "2 + 2";
        double result_expression = 4;
        ExpressionParser ep(expression);
        BOOST_TEST( ep.Result() == result_expression);
    }
    BOOST_AUTO_TEST_CASE(test1){
        string expression = "2 * 2";
        double result_expression = 4;
        ExpressionParser ep(expression);
        BOOST_TEST( ep.Result() == result_expression);
    }
    BOOST_AUTO_TEST_CASE(test2){
        string expression = "2 / 2";
        double result_expression = 1;
        ExpressionParser ep(expression);
        BOOST_TEST( ep.Result() == result_expression);
    }
    BOOST_AUTO_TEST_CASE(test3){
        string expression = "2 + 2 * 2";
        double result_expression = 6;
        ExpressionParser ep(expression);
        BOOST_TEST( ep.Result() == result_expression);
    }
    BOOST_AUTO_TEST_CASE(test4){
        string expression = "(2 + 2) * 2";
        double result_expression = 8;
        ExpressionParser ep(expression);
        BOOST_TEST( ep.Result() == result_expression);
    }
    BOOST_AUTO_TEST_CASE(test5){
        string expression = "37.75*64.1"; //2419,775
        double result_expression = 2419.78;
        ExpressionParser ep(expression);
        BOOST_TEST( ep.Result() == result_expression);
    }
    BOOST_AUTO_TEST_CASE(test6){
        string expression = "-19.61/(29.94*(-18.9/-19.75*40.26)+11.83)/81.46";
        double result_expression = 0;
        ExpressionParser ep(expression);
        BOOST_TEST( ep.Result() == result_expression);
    }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(BracketTest)
    BOOST_AUTO_TEST_CASE(test0){
        string expression = "60 + ((43,5 + 56.3)*(6) + 34.5)";
        double result_expression = 693.3;
        ExpressionParser ep(expression);
        BOOST_TEST( ep.Result() == result_expression);
    }
    BOOST_AUTO_TEST_CASE(test1){
        string expression = "60 + (45.6 + 54";
        string result_expression = "не хватает закрывающей скобки : index 15";
        ExpressionParser ep(expression);
        try
        {
            ep.Result();
        }
        catch(const runtime_error&  ex)
        {
            BOOST_TEST(result_expression.compare(ex.what()) == 0);
        }
    }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(UnknownSymbolsTest)
    BOOST_AUTO_TEST_CASE(test0_end){
        setlocale(LC_CTYPE,"Russian");
        string expression = "1.1 + 2.1 + a%bc";
        string result_expression = "некорректный ввод, строка содержит недопустимое выражение a%bc";
        ExpressionParser ep(expression);
        try
        {
            ep.Result();
        }
        catch(const runtime_error&  ex)
        {
            BOOST_TEST(result_expression.compare(ex.what()) == 0);
        }
    }
    BOOST_AUTO_TEST_CASE(test1_middle){
        setlocale(LC_CTYPE,"Russian");
        string expression = "1.1 + a%bc + 2.1";
        string result_expression = "некорректный ввод, строка содержит недопустимое выражение a%bc";
        ExpressionParser ep(expression);
        try
        {
            ep.Result();
        }
        catch(const runtime_error&  ex)
        {
            BOOST_TEST(result_expression.compare(ex.what()) == 0);
        }
    }
    BOOST_AUTO_TEST_CASE(test2_begin){
        setlocale(LC_CTYPE,"Russian");
        string expression = "a%bc + 1.1 + 2.1";
        string result_expression = "некорректный ввод, строка содержит недопустимое выражение a%bc";
        ExpressionParser ep(expression);
        try
        {
            ep.Result();
        }
        catch(const runtime_error&  ex)
        {
            BOOST_TEST(result_expression.compare(ex.what()) == 0);
        }
    }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(SpaceTest)
    BOOST_AUTO_TEST_CASE(test0_begin){
        string expression = "                           2 + 2";
        double result_expression = 4;
        ExpressionParser ep(expression);
        BOOST_TEST( ep.Result() == result_expression);
    }
    BOOST_AUTO_TEST_CASE(test1_middle){
        string expression = "2                         +                                    2";
        double result_expression = 4;
        ExpressionParser ep(expression);
        BOOST_TEST( ep.Result() == result_expression);
    }
    BOOST_AUTO_TEST_CASE(test1_end){
        string expression = "2 + 2                                             ";
        double result_expression = 4;
        ExpressionParser ep(expression);
        BOOST_TEST( ep.Result() == result_expression);
    }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(AbsTenMillionTest)
    BOOST_AUTO_TEST_CASE(test0){
        string expression = "9999999 + 1111111";
        string result_expression = "результат вычисления по модулю больше 10 000 000";
        ExpressionParser ep(expression);
        try
        {
            ep.Result();
        }
        catch(const runtime_error&  ex)
        {
            BOOST_TEST(result_expression.compare(ex.what()) == 0);
        }
    }
    BOOST_AUTO_TEST_CASE(test1){
        string expression = "-9999999 - 1111111";
        string result_expression = "результат вычисления по модулю больше 10 000 000";
        ExpressionParser ep(expression);
        try
        {
            ep.Result();
        }
        catch(const runtime_error&  ex)
        {
            BOOST_TEST(result_expression.compare(ex.what()) == 0);
        }
    }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(IncorrectNumberTest)
    BOOST_AUTO_TEST_CASE(test0){
        string expression = "12.9999999 + 35.6";
        string result_expression = "введено некорректное число: 12.9999999";
        ExpressionParser ep(expression);
        try
        {
            ep.Result();
        }
        catch(const runtime_error&  ex)
        {
            BOOST_TEST(result_expression.compare(ex.what()) == 0);
        }
    }
    BOOST_AUTO_TEST_CASE(test1){
        string expression = "123456789.1 + 35.6";
        string result_expression = "введено некорректное число: 123456789.1";
        ExpressionParser ep(expression);
        try
        {
            ep.Result();
        }
        catch(const runtime_error&  ex)
        {
            BOOST_TEST(result_expression.compare(ex.what()) == 0);
        }
    }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(IncorrectExpressionTest)
    BOOST_AUTO_TEST_CASE(test0){
        string expression = "";
        string result_expression = "пустое выражение";

        try
        {
            ExpressionParser ep(expression);
            ep.Result();
        }
        catch(const runtime_error&  ex)
        {
            BOOST_TEST(result_expression.compare(ex.what()) == 0);
        }
    }
    BOOST_AUTO_TEST_CASE(test1){
        string expression = "5+";
        string result_expression = "неожиданный конец выражения";

        try
        {
            ExpressionParser ep(expression);
            ep.Result();
        }
        catch(const runtime_error&  ex)
        {
            BOOST_TEST(result_expression.compare(ex.what()) == 0);
        }
    }
    BOOST_AUTO_TEST_CASE(test2){
        string expression = "         ";
        string result_expression = "неожиданный конец выражения";
        try
        {
            ExpressionParser ep(expression);
            ep.Result();
        }
        catch(const runtime_error&  ex)
        {
            BOOST_TEST(result_expression.compare(ex.what()) == 0);
        }
    }
    BOOST_AUTO_TEST_CASE(test3){
        string expression = "molodets";
        string result_expression = "некорректный ввод, строка содержит недопустимое выражение molodets";
        try
        {
            ExpressionParser ep(expression);
            ep.Result();
        }
        catch(const runtime_error&  ex)
        {
            BOOST_TEST(result_expression.compare(ex.what()) == 0);
        }
    }
BOOST_AUTO_TEST_SUITE_END()
