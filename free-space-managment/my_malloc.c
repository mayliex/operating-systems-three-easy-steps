#include <stdlib.h>
#include <assert.h>
#include <sys/mman.h>
#include <stdio.h>

typedef struct __node_t {
    int              size;
    struct __node_t *next;
} node_t;

typedef struct __header_t {
    int size;
    int magic;
} header_t;

const int heap_size = 4096;
const int magic = 123123;
node_t* head;

void free(void *ptr) {
    header_t *hptr = ptr - sizeof(header_t);
    assert(hptr->magic == magic);
}

void* malloc(size_t size) {
    header_t* new_header = (header_t*) head;

    head->size -= size + sizeof(header_t);
    node_t* next_head = (node_t*)((uintptr_t) head + sizeof(header_t) + size);
    *next_head = *head;
    head = next_head;

    new_header->size = size;
    new_header->magic = magic;
    return (void*)((uintptr_t) new_header) + sizeof(header_t);
}

int main() {
    head = mmap(NULL, heap_size, PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);
    uintptr_t from = (uintptr_t) head;
    head->size   = heap_size - sizeof(node_t);
    printf("sizeof(node_t) = %d\n", sizeof(node_t));
    printf("sizeof(header_t) = %d\n", sizeof(header_t));
    printf("sizeof(int) = %d\n", sizeof(int));
    head->next   = NULL;

    int* b = malloc(sizeof(int));
    uintptr_t to = (uintptr_t) head;
    *b = 7;
    printf("*b = %d\n", *b);
    printf("difference = %lu", to - from);
    return 0;
}