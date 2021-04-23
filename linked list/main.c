#include "dll.h"

void main() {
	DLList* dll = dllInit();

	dllInsertTail("tran van A", dll);
	dllInsertTail("tran van A", dll);

	dllInsertHead("tran van A", dll);
	dllInsertHead("tran van A", dll);
	dllInsertHead("tran van A", dll);

//	dllPrint(dll);
	dllSort(dll);
	dllPrint(dll);

	return;
}

 







