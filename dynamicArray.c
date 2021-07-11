#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	void** pArray;
	int length;
	int size;
} DynamicArray;

DynamicArray* init(int length) {
	if (length <= 0) return NULL;
	DynamicArray* array = (DynamicArray*)malloc(sizeof(DynamicArray));
	if (array == NULL) return NULL;
	array->pArray = (void**)malloc(sizeof(void*) * length);
	if (array->pArray == NULL) return NULL;
	array->length = length;
	array->size = 0;
	return array;
}

void insert(DynamicArray* array, void* data, int index) {
	if (array == NULL) return;
	if (data == NULL) return;
	if (index < 0 || index >(array->size)) index = array->size;
	
	if (array->size >= array->length) {
		int newLength = array->length * 2;
		void** newpArray = (void**)malloc(sizeof(void*) * newLength);
		if (newpArray == NULL) return;
		memcpy(newpArray, array->pArray, sizeof(void*) * array->length);
		free(array->pArray);
		array->pArray = newpArray;
		array->length = newLength;
	}

	for (int i = array->size - 1; i >= index; i--) {
		array->pArray[i + 1] = array->pArray[i];
	}

	array->pArray[index] = data;
	array->size += 1;
}

void travel(DynamicArray * array, void callback(void*)) {
	if (array == NULL)return;
	for (int i = 0; i < array->size; i++) {
		callback(array->pArray[i]);
	}
}

void remove(DynamicArray* array, int index) {
	if (array == NULL) return;
	if (index < 0 || index > array->size) return;
	for (int i = index; i < array->size; i++) {
		array->pArray[i] = array->pArray[i + 1];
	}
	array->size -= 1;
}

void destory(DynamicArray* array) {
	if (array == NULL) return;
	if (array->pArray != NULL) {
		free(array->pArray);
		array->pArray = NULL;
	}
	free(array);
	array = NULL;
}


typedef struct {
	char name[64];
	int age;
} Persion;

void myPrintf(void* data) {
	Persion* persion = (Persion*)data;
	printf("%s,%d\n", persion->name, persion->age);
}

int main() {
	DynamicArray * arr = init(2);
	Persion p1 = {"AA", 11};
	Persion p2 = { "BB", 22 };
	Persion p3 = { "CC", 33 };
	Persion p4 = { "DD", 44 };
	Persion p5 = { "EE", 55 };
	Persion p6 = { "FF", 66 };
	
	insert(arr, &p1, 0);
	insert(arr, &p2, 1);
	insert(arr, &p3, 2);
	insert(arr, &p4, 3);
	insert(arr, &p5, 4);
	insert(arr, &p6, 0);
	travel(arr, myPrintf);

	puts("remove index = 1");
	remove(arr, 1);
	travel(arr, myPrintf);

	puts("insert index = 6 AA");
	insert(arr, &p1, 6);
	travel(arr, myPrintf);
}
