#include "pch.h"
#include "CppUnitTest.h"
#include "C:\Users\arabk\source\repos\Huffman\Huffman\Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(Test_makeHuffTree)
		{
			std::string input = "qwertywwwrrtttttt";
			makeHufTree(input);
			Assert::IsTrue(symbols.getSize() == 1);
		}

		TEST_METHOD(Test_makeCodeTable)
		{
			std::string input = "qwertywwwrrtttttt";
			makeHufTree(input);
			makeCodeTable("", symbols[0]);
			Assert::IsTrue(codes['t'] == "0" && codes['q'] == "11110" && codes['e'] == "11111" && codes['r'] == "110" && codes['w'] == "10" && codes['y'] == "1110");
			Assert::IsTrue(decodes["0"] == 't' && decodes["11110"] == 'q' && decodes["11111"] == 'e' && decodes["110"] == 'r' && decodes["10"] == 'w' && decodes["1110"] == 'y');
		}

		TEST_METHOD(Test_code)
		{
			std::string input = "qwertywwwrrtttttt";
			makeHufTree(input);
			makeCodeTable("", symbols[0]);
			std::string coded = code(input);
			Assert::IsTrue(coded == "11110101111111001110101010110110000000");
		}

		TEST_METHOD(Test_decode)
		{
			std::string input = "qwertywwwrrtttttt";
			makeHufTree(input);
			makeCodeTable("", symbols[0]);
			std::string decoded = decode(code(input));
			Assert::IsTrue(decoded == input);
		}
	};
}
