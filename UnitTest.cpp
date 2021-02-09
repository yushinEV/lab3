#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab3Aistrd_Ushin/main.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(insert_and_bft)
		{
			BSTREE T;
			T.insert(7);
			T.insert(3);
			T.insert(1);
			T.insert(5);
			T.insert(11);
			T.insert(12);
			T.insert(8);
			Iterator* BFT = T.create_bft_iterator();
			Assert::AreEqual(BFT->next(), 7);
			Assert::AreEqual(BFT->next(), 3);
			Assert::AreEqual(BFT->next(), 11);
			Assert::AreEqual(BFT->next(), 1);
			Assert::AreEqual(BFT->next(), 5);
			Assert::AreEqual(BFT->next(), 8);
			Assert::AreEqual(BFT->next(), 12);
		}
		TEST_METHOD(bft_except)
		{
			BSTREE T;
			Iterator* BFT = T.create_bft_iterator();
			bool indicator = 0;
			try
			{
				BFT->next();
			}
			catch (exception& exception)
			{
				indicator = 1;
			}
			Assert::IsTrue(indicator);
		}
		TEST_METHOD(insert_and_dft)
		{
			BSTREE T;
			T.insert(9);
			T.insert(5);
			T.insert(3);
			T.insert(7);
			T.insert(14);
			T.insert(16);
			T.insert(10);
			Iterator* BFT = T.create_dft_iterator();
			Assert::AreEqual(BFT->next(), 9);
			Assert::AreEqual(BFT->next(), 5);
			Assert::AreEqual(BFT->next(), 3);
			Assert::AreEqual(BFT->next(), 7);
			Assert::AreEqual(BFT->next(), 14);
			Assert::AreEqual(BFT->next(), 10);
			Assert::AreEqual(BFT->next(), 16);
		}
		TEST_METHOD(dft_except)
		{
			BSTREE T;
			Iterator* DFT = T.create_dft_iterator();
			bool indicator = 0;
			try
			{
				DFT->next();
			}
			catch (exception& exception)
			{
				indicator = 1;
			}
			Assert::IsTrue(indicator);
		}
		TEST_METHOD(contains)
		{
			BSTREE T;
			T.insert(7);
			T.insert(3);
			T.insert(17);
			Assert::IsTrue(T.contains(17));
			Assert::IsFalse(T.contains(1));
		}
		TEST_METHOD(remove)
		{
			BSTREE T;
			T.insert(7);
			T.insert(3);
			T.insert(1);
			T.insert(5);
			T.insert(10);
			T.insert(12);
			T.insert(8);
			T.remove(1);
			Iterator* BFT = T.create_bft_iterator();
			Assert::AreEqual(BFT->next(), 7);
			Assert::AreEqual(BFT->next(), 3);
			Assert::AreEqual(BFT->next(), 10);
			Assert::AreEqual(BFT->next(), 5);
			Assert::AreEqual(BFT->next(), 8);
			Assert::AreEqual(BFT->next(), 12);
		}
	};
}