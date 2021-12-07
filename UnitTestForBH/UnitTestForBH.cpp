#include "pch.h"
#include "CppUnitTest.h"
#include "..\alg3\BinaryHeap.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestForBH
{
	TEST_CLASS(UnitTestForBH)
	{
	public:
		
		TEST_METHOD(containsTest)
		{
			BinaryHeap heap;
			heap.insert(9);
			heap.insert(6);
			heap.insert(0);
			heap.insert(-3);

			Assert::IsTrue(heap.contains(-3));
			Assert::IsTrue(heap.contains(0));
			Assert::IsTrue(heap.contains(6));
			Assert::IsTrue(heap.contains(9));
			Assert::IsTrue(!heap.contains(1));
			Assert::IsTrue(!heap.contains(10));
		}

		TEST_METHOD(insertTest)
		{
			BinaryHeap heap;
			heap.insert(2);
			heap.insert(3);
			heap.insert(0);
			heap.insert(-1);


			Iterator* bft_iterator = heap.create_bft_iterator();
			Assert::IsTrue(bft_iterator->next() == 3);
			int next_data = bft_iterator->next();
			Assert::IsTrue(next_data == 0 || next_data == 2);
			next_data = bft_iterator->next();
			Assert::IsTrue(next_data == 0 || next_data == 2);
			Assert::IsTrue(next_data >= bft_iterator->next());

		}

		TEST_METHOD(removeTest)
		{
			BinaryHeap heap;
			try {
				heap.remove(1);
			}
			catch (const invalid_argument error) {
				Assert::AreEqual("No such element", error.what());
			}
			
			heap.insert(2);
			heap.insert(5);
			heap.insert(9);
			heap.insert(1);

			Assert::IsTrue(heap.contains(1));
			Assert::IsTrue(heap.contains(9));
			Assert::IsTrue(heap.contains(5));
			Assert::IsTrue(heap.contains(2));

			heap.remove(1);
			Assert::IsTrue(!heap.contains(1));
			Assert::IsTrue(heap.contains(9));
			Assert::IsTrue(heap.contains(5));
			Assert::IsTrue(heap.contains(2));

		}

		TEST_METHOD(create_bft_iteratorTest)
		{
			BinaryHeap heap;
			heap.insert(5);
			heap.insert(4);
			heap.insert(3);
			heap.insert(2);
			heap.insert(1);
			heap.insert(0);

			Iterator* bft_iterator = heap.create_bft_iterator();

			int i = 5;
			while (bft_iterator->has_next()) {
				Assert::IsTrue(bft_iterator->next() == i--);
			}
			Assert::IsTrue(i == -1);
		}

		TEST_METHOD(create_dft_iteratorTest) {
			BinaryHeap heap;
			heap.insert(5);
			heap.insert(4);
			heap.insert(3);
			heap.insert(2);
			heap.insert(1);
			heap.insert(0);

			Iterator* dft_iterator = heap.create_dft_iterator();
			Assert::IsTrue(dft_iterator->has_next());
			Assert::IsTrue(dft_iterator->next() == 5);
			Assert::IsTrue(dft_iterator->has_next());
			Assert::IsTrue(dft_iterator->next() == 4);
			Assert::IsTrue(dft_iterator->has_next());
			Assert::IsTrue(dft_iterator->next() == 2);
			Assert::IsTrue(dft_iterator->has_next());
			Assert::IsTrue(dft_iterator->next() == 1);
			Assert::IsTrue(dft_iterator->has_next());
			Assert::IsTrue(dft_iterator->next() == 3);
			Assert::IsTrue(dft_iterator->has_next());
			Assert::IsTrue(dft_iterator->next() == 0);
			Assert::IsTrue(!dft_iterator->has_next());

		}
		
	};
}
