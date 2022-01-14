#define BOOST_TEST_MODULE numeric_tests
#include <boost/test/included/unit_test.hpp>
#include <iostream>
#include <string>
#include <regex>
#include <vector>
#define MAX 100

//数値をアルファベットに置き換える
std::string replaceA(std::string Formula, std::vector<std::string> &stuckA) {
	
	std::regex check{ "([0-9]{1,})|(-[0-9]{1,})" };
	std::sregex_iterator end, ite{ Formula.begin(), Formula.end(), check };

	
	for (; ite != end; ++ite) {
		stuckA.push_back(ite->str());
	}

	return std::regex_replace(Formula, check, "A");
}

bool parse(std::string Formula) {
	std::string answer[MAX] = {};
	std::vector<std::string> stuckA = {};

	//入力された数式がすべて半角文字であるかどうか
	try {
		std::string check_HarfSize = Formula;
		while (!check_HarfSize.empty())
		{
			if (IsDBCSLeadByte(check_HarfSize[0]) == 0) {
				check_HarfSize.erase(0, 1);
			}
			else {
				throw "Only Harf size";
			}
		}
	}
	catch (char* e) { std::cout << "Exception : " << e << "\n"; return false; }

	Formula = replaceA(Formula, stuckA);
	
	for (int i = 0; i < Formula.size(); i++) {
		answer[i] = Formula[i];
	}

	for (int i = 0; i < MAX; i++) {
		if (answer[i] == "A") {
			answer[i] = stuckA[0];
			stuckA.erase(stuckA.begin());
		}
	}

	for (int i = 0; i < MAX; i++) {
		std::cout << answer[i] << "\n";
		if (answer[i] == "")break;
	}

	return true;
}


/*
 テストコード部分。
 これ以降に、上記に書いたプログラムに対するテストコードを記述します。
*/

/*
 単純な足し算の文字列式を指定した時のテストを行う関数です。
 このテストでは、"1+2" と言う文字列を正常に分割できるかどうかをテストします。
 */
BOOST_AUTO_TEST_CASE(test_plus)
{
	BOOST_REQUIRE(parse("1+2"));
}

/*
 2 桁の数値文字列が含まれる場合のテストを行う関数です。
 このテストでは、"1-2" と言う 2 桁の数値が含まれる文字列を正常に分割
 できるかどうかをテストします。
 */

BOOST_AUTO_TEST_CASE(test_negative)
{
	BOOST_REQUIRE(parse("1-2"));
}

/*
 2 桁の数値文字列が含まれる場合のテストを行う関数です。
 このテストでは、"1*2" と言う 2 桁の数値が含まれる文字列を正常に分割
 できるかどうかをテストします。
 */

BOOST_AUTO_TEST_CASE(test_multiplication)
{
	BOOST_REQUIRE(parse("1*2"));
}

/*
 2 桁の数値文字列が含まれる場合のテストを行う関数です。
 このテストでは、"1/2" と言う 2 桁の数値が含まれる文字列を正常に分割
 できるかどうかをテストします。
 */

BOOST_AUTO_TEST_CASE(test_division)
{
	BOOST_REQUIRE(parse("1/2"));
}

BOOST_AUTO_TEST_CASE(test_HarfSize)
{
	BOOST_REQUIRE(parse("１+2"));
}
