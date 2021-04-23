#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printArr(int *arr, int sz) {
	for(int i = 0; i < sz; i++) 
		printf("%d  ", arr[i]);
	printf("\n");
	return;
}

void swapArr(int *a, int *b) {
	int t = *a;
	
	*a = *b;
	*b = t;
	return;
}

/* ========== Selection Sort =========== */

void selectionSort(int *arr, int sz) {
	int i, j, iMin;

	for(i = 0; i < sz - 1; i++) {
		iMin = i;
		for(j = i+1; j < sz; j++) {
			if(arr[j] < arr[iMin])
				iMin = j;
		}
		swapArr(&arr[i], &arr[iMin]);
	}
	return;
}

/* ========== Insertion Sort ========== */

void insertionSort(int *arr, int sz) {
	int i, j;

	for(i = 1; i < sz; i++) {
		for(j = i-1; j >= 0; j--) {
			if(arr[i] < arr[j]) {
				swapArr(&arr[i], &arr[j]);
				i = j;
			}
		}
	}
	return;
}

/* ========== Bubble Sort =========== */

void bubbleSort(int *arr, int sz) {
	int i, j, sorted;

	for(i = sz - 1; i > 0; i--) {
		sorted = 1;
		for(j = 0; j < i; j++) {
			if(arr[j] > arr[j+1]) {
				swapArr(&arr[j], &arr[j+1]);
				sorted = 0;
			}
		}
		if(sorted) {
			break;
		}
	}
	return;
}

/* ========== QuickSort ========== */

int partition(int *arr, int start, int end) {
	int i = start,
	    pivot = end,
	    j = pivot - 1;
	
	while(i <= j) {
		if(arr[i] < arr[pivot]) i++;
		else {
			swapArr(&arr[i], &arr[j]);
			j--;
		}
	}
	swapArr(&arr[i], &arr[pivot]);
	return i;
}

void quickSort(int *arr, int start, int end) {
	int pivot;

	if(start < end){	
		pivot = partition(arr, start, end);
		quickSort(arr, start, pivot - 1);
		quickSort(arr, pivot + 1, end);
	}
	return;
}

/* ========== Heap Sort ========== */

void maxHeap(int *arr, int sz, int i) {
	int m = i,
	    left = 2 * i + 1,
	    right = left + 1;

	if(left < sz && arr[m] < arr[left]) m = left;
	if(right < sz && arr[m] < arr[right]) m = right;
	
	if(m != i) {
		swapArr(&arr[i], &arr[m]);
		maxHeap(arr, sz, m);
	}
	return;
}

void minHeap(int *arr, int sz, int i) {
	int m = i,
	    left = 2 * i + 1,
	    right = left + 1;

	if(left < sz && arr[m] > arr[left]) m = left;
	if(right < sz && arr[m] > arr[right]) m = right;
	
	if(m != i) {
		swapArr(&arr[i], &arr[m]);
		minHeap(arr, sz, m);
	}
}

void buildHeapTree(int *arr, int sz) {
	for(int i = (sz - 2) / 2; i >= 0; i--) {
		maxHeap(arr, sz, i);
//		minHeap(arr, sz, i);
	}
	return;
}

void heapSort(int *arr, int sz) {
	if(sz < 2) return;

	buildHeapTree(arr, sz);
	swapArr(&arr[0], &arr[sz-1]);
	heapSort(arr, sz - 1);
	return;
}

/* ========== Merge Sort ========== */

void merge(int *a, int start, int mid, int end) {
	int nLeft = mid - start + 1,
	    nRight = end - mid,
	    *left = (int*)malloc(sizeof(int) * nLeft),
	    *right = (int*)malloc(sizeof(int) * nRight);
	int i, j, k;

	for(i = start, k = 0; i <= mid; i++, k++) {
		left[k] = a[i];
	}
	for(k = 0; i <= end; i++, k++) {
		right[k] = a[i];
	}

	i = 0;
	j = 0;
	k = start;	
	
	while(i < nLeft && j < nRight) {
		if(left[i] < right[j]) {
			a[k] = left[i];
			i++;
		} else {
			a[k] = right[j];
			j++;
		}
		k++;	
	}

	while(i < nLeft) {
		a[k] = left[i];
		k++;
		i++;
	}

	while(j < nRight) {
		a[k] = right[j];
		k++;
		j++;
	}	

	free(left);
	free(right);
	return;
}

void mergeSort(int *a, int start, int end) {
	int mid;
	
	if(start < end) {
		mid = (start + end) / 2;		
		
		mergeSort(a, start, mid);
		mergeSort(a, mid + 1, end);
		merge(a, start, mid, end);
	}
	return;
}

void main() {
	int arr[] = {0, 3, 3, 4, 2, 4, 7, 8, 9, 5, 20, 14, 20, 19, 2, 0, 2, 0};
	int sz = sizeof(arr) / sizeof(arr[0]);

	printf("Array : ");
	printArr(arr, sz);
	printf("\nQuickSort : 	 ");
	quickSort(arr, 0, sz - 1);
	printArr(arr, sz);

	printf("Heap Sort :	 ");	
	heapSort(arr, sz);
	printArr(arr, sz);

	printf("Merge Sort : 	 ");
	mergeSort(arr, 0, sz - 1);
	printArr(arr, sz);

	printf("Insertion Sort : ");
	mergeSort(arr, 0, sz - 1);
	printArr(arr, sz);

	printf("Selection Sort : ");
	mergeSort(arr, 0, sz - 1);
	printArr(arr, sz);

	printf("Bubble Sort : 	 ");
	mergeSort(arr, 0, sz - 1);
	printArr(arr, sz);		

	return;
}







