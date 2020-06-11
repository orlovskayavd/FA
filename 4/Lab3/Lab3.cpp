#pragma warning(disable:4996)
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <memory.h>

typedef struct Data {
    int priority;
    char* text;
} Data;

typedef struct QueueNode {
    struct QueueNode* next;
    Data data;
} QueueNode;

QueueNode* tail;
QueueNode* head;

QueueNode* createNode(char* text, int priority) {
    Data data;
    data.text = text;
    data.priority = priority;
    QueueNode* node = (QueueNode*) malloc(sizeof(QueueNode));
    node->data = data;
    node->next = NULL;
    return node;
}

void Enqueue(QueueNode* node) {
    if (tail == NULL) {
        tail = head = node;
    }
    else {
        tail->next = node;
        tail = tail->next;
    }
}
//    head -> node -> node -> node -> node -> tail
QueueNode* Dequeue() {
    if (head == NULL) return NULL;
    QueueNode* result = head;
    head = head->next;
    return result;
}

void EnqueuePriority(QueueNode* node) {
    QueueNode* curNode = head;
    if (head != NULL) {
        if (curNode->data.priority > node->data.priority) {
            node->next = curNode;
            head = node;
        }
        else {
            while (curNode->next && (curNode->next->data.priority <= node->data.priority)) {
                curNode = curNode->next;
            }

            node->next = curNode->next;
            curNode->next = node;
        }
    }
    else Enqueue(node);
}

int main() {
    tail = head = NULL;
    FILE* file;
    char c;
    int n;
    scanf("%d", &n);
    char buf[250], * b = buf;
    char nameBuf[250] = { 0 }, * nameBufPtr = nameBuf;
    char fileName[250] = { 0 };
    for (int i = 0; i < n; ++i) {
        scanf("%s", fileName);
        if (!(file = fopen(fileName, "r"))) {
            printf("Couldn't open %s", fileName);
            continue;
        }

        while (!feof(file)) {
            c = fgetc(file);

            if (c != '\n' && c != EOF) {
                *b++ = c;
            }
            else {
                *b = 0;
                b = buf;

                while (isalpha(*b)) {
                    b++;
                }
                b++;
                int num = 0;
                while (*b != ' ') {
                    num = num * 10 + (*b - '0');
                    b++;
                }
                b++;
                while (*b != '"') {
                    b++;
                }
                b++;
                while (*b != '"') {
                    *nameBufPtr++ = *b++;
                }

                char* name = (char*) malloc(sizeof(char) * (strlen(nameBuf) + 1));
                strcpy(name, nameBuf);
                b = buf;
                while (*b) {
                    *b++ = 0;
                }
                b = buf;

                nameBufPtr = nameBuf;
                while (*nameBufPtr) {
                    *nameBufPtr++ = 0;
                }
                nameBufPtr = nameBuf;

                QueueNode* queueNode = createNode(name, num);
                EnqueuePriority(queueNode);
            }
        }
    }


    QueueNode* queueNode1 = Dequeue();
    while (queueNode1 != NULL) {
        printf("%d %s\n", queueNode1->data.priority, queueNode1->data.text);
        free(queueNode1->data.text);
        free(queueNode1);
        queueNode1 = Dequeue();
    }


}