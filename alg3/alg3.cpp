#include <iostream>
#include <stdexcept>
using namespace std;
#include "BinaryHeap.h"

int main()
{
    BinaryHeap heap;
	heap.insert(7);
	heap.insert(4);
	heap.insert(9);
	heap.insert(2);
	heap.insert(1);
	heap.insert(3);

	cout << "creating the binary heap\n";

	
		Iterator* b_iterator = heap.create_bft_iterator();
		cout << "\n\n" << "traversing the graph in width: \n";
		while (b_iterator->has_next()) {
			cout << b_iterator->next() << ' ';
		}
		delete b_iterator;
		Iterator* d_iterator = heap.create_dft_iterator();
		cout << "\n\n" << "traversing the graph in depth: \n";
		while (d_iterator->has_next()) {
			cout << d_iterator->next() << ' ';
		}
		delete d_iterator;

		cout << "\n\nis the data 9 in the heap? - " << (heap.contains(4) ? "yes" : "no");
		cout << "\n\nremoving the data 4 from the heap:\n";
		heap.remove(4);
		cout << heap << "\n\nis the data 4 in the heap? - " << (heap.contains(4) ? "yes" : "no");
		cout << "\n\n";
		return 0;
		
}


