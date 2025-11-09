#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 100

typedef struct Character {
	char character;
	struct Character* next;
	struct Character* pre;
}character;

typedef struct LinkStack {
	character* head;
}linkstack;

typedef struct LinkQueue {
	character* head;
	character* tail;
}linkqueue;


void CreateQueue(linkqueue* OriginalQue) {
	OriginalQue->head = (character*)malloc(sizeof(character));
	OriginalQue->head->character = 'H';
	OriginalQue->head->next = NULL;
	OriginalQue->head->pre = NULL;
	OriginalQue->tail = OriginalQue->head;
}

void CreateOriginalQueue(linkqueue* OriginalQue,char* OriginalLan) {
	printf("请输入要翻译的魔王语言：");
	scanf_s("%s", OriginalLan, MAX_SIZE);

	CreateQueue(OriginalQue);
	int i;
	for (i = 0; OriginalLan[i] != '\0'; i++) {
		character* p = (character*)malloc(sizeof(character));
		p->character = OriginalLan[i];
		p->next = NULL;
		p->pre = OriginalQue->tail;
		OriginalQue->tail->next = p;
		OriginalQue->tail = p;
	}
}

void InsertQueue(linkqueue* OriginalQue, char Char) {
	character* p = (character*)malloc(sizeof(character));
	p->character = Char;
	p->next = NULL;
	p->pre = OriginalQue->tail;
	OriginalQue->tail->next = p;
	OriginalQue->tail = p;
}

char PopQueue(linkqueue* OriginalQue) {
	character* p = OriginalQue->head->next;
	if (p == OriginalQue->tail) {
		OriginalQue->tail = OriginalQue->head;
	}
	OriginalQue->head->next = p->next;
	p->next->pre = OriginalQue->head;
	char popchar = p->character;
	free(p);
	return popchar;
}

void CreateStack(linkstack* Stack) {
	Stack->head = (character*)malloc(sizeof(character));
	Stack->head->character = 'H';
	Stack->head->pre = NULL;
	Stack->head->next = NULL;
}

void InsertStack(linkstack* Stack, char Char) {
	character* p = (character*)malloc(sizeof(character));
	p->character = Char;
	p->next = Stack->head->next;
	Stack->head->next = p;
	p->pre = NULL;
}

char PopStack(linkstack* Stack) {
	character* p = Stack->head->next;
	char a = p->character;
	Stack->head->next = p->next;
	free(p);
	return a;
}

void EqualToA(char* charA) {
	printf("%s", charA);
}

void EqualToB(char* charA, char* charB) {
	for (int i = 0; i < 4; i++) {
		if (charB[i] == 'A') {
			EqualToA(charA);
		}
		else {
			printf("%c", charB[i]);
		}
	}
}

int main() {
	char charA[10] = "sae";
	char charB[10] = "tAdA";
	//存放读取的魔王语言
	char OriginalLan[MAX_SIZE];
	//存放转译后的魔王语言
	char FinalLan[MAX_SIZE];
	//创建队列结构体
	linkqueue OriginalQue;
	

	CreateOriginalQueue(&OriginalQue, OriginalLan);

	linkstack Stack;
	CreateStack(&Stack);

	character* p = OriginalQue.head->next;
	
	while (p != NULL) {
		if (p->character == ')') {
			character* p1 = p;
			p = p->pre;
			while (p->character != '(') {
				character* tempp = p;
				p->pre->next = p->next;
				p->next->pre = p->pre;
				InsertStack(&Stack, p->character);
				p = p->pre;
				free(tempp);
			}
			
			character* p2 = p;
			char sita = PopStack(&Stack);
			linkstack TempStack;
			CreateStack(&TempStack);
			while (Stack.head->next != NULL) {
				InsertStack(&TempStack, PopStack(&Stack));
			}
			
			linkqueue TempQueue;
			CreateQueue(&TempQueue);
			while (TempStack.head->next != NULL) {
				InsertQueue(&TempQueue, sita);
				InsertQueue(&TempQueue, PopStack(&TempStack));
			}
			InsertQueue(&TempQueue, sita);
			
			character* p3 = TempQueue.head->next;
			character* p4 = p2->pre;
			while (p3 != NULL) {
				character* p5 = (character*)malloc(sizeof(character));
				p5->character = p3->character;
				p4->next = p5;
				p5->pre = p4;
				p4 = p5;
				p3 = p3->next;
			}
			p4->next = p1->next;
			if (p1->next != NULL)
				p1->next->pre = p4;
			p = p1->next;	
		}
		else {
			p = p->next;
		}
	}
	
	p = OriginalQue.head->next;
	while (p != NULL) {
		if (p->character == 'B') {
			character* tempp = p->pre;
			for (int i = 0; charB[i] != '\0'; i++) {
				character* p1 = (character*)malloc(sizeof(character));
				p1->character = charB[i];
				tempp->next = p1;
				p1->pre = tempp;
				tempp = p1;
			}
			tempp->next = p->next;
			if (p->next != NULL)
				p->next->pre = tempp;
			free(p);
			p = tempp->next;
		}
		else {
			p = p->next;
		}
	}
	
	p = OriginalQue.head->next;
	while (p != NULL) {
		if (p->character == 'A') {
			character* tempp = p->pre;
			for (int i = 0; charA[i] != '\0'; i++) {
				character* p1 = (character*)malloc(sizeof(character));
				p1->character = charA[i];
				tempp->next = p1;
				p1->pre = tempp;
				tempp = p1;
			}
			tempp->next = p->next;
			if (p->next != NULL)
				p->next->pre = tempp;
			free(p);
			p = tempp->next;
		}
		else {
			p = p->next;
		}
	}
	
	p = OriginalQue.head->next;
	while (p != NULL) {
		printf("%c", p->character);
		p = p->next;
	}
	return;
}
