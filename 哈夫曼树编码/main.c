#include<stdio.h>
#include<stdlib.h>
#include <errno.h>
#include <io.h>

#define MAX_SIZE 100

typedef struct Element {
	char character;
	int weight;
	int parent, lch, rch;
};

void Encoding(struct Element* Huffman, int j, FILE* fp3) {
	if (Huffman[j].parent == 0) {
		return;
	}
	Encoding(Huffman, Huffman[j].parent, fp3);
	int number = j;
	j = Huffman[j].parent;
	if (Huffman[j].lch == number) {
		fprintf(fp3, "0");
	}
	if (Huffman[j].rch == number) {
		fprintf(fp3, "1");
	}
}

void TreePrint(struct Element* Huffman, int num, int depth, FILE* fp7) {
	for (int i = 0; i < depth; i++) {
		printf("   ");  
		fprintf(fp7, "   ");
	}
	printf("%d\n", Huffman[num].weight);
	fprintf(fp7, "%d\n", Huffman[num].weight);
	if (Huffman[num].lch == 0 && Huffman[num].rch == 0) {
		return;
	}
	TreePrint(Huffman, Huffman[num].lch, depth + 1, fp7);
	TreePrint(Huffman, Huffman[num].rch, depth + 1, fp7);
}

int main() {
	struct Element Huffman[MAX_SIZE];
	char chars[MAX_SIZE];
	int count, weight;
	
	const char* filename = "hfmTree.text";

	if (_access(filename, 0) != -1) {
		FILE* fp1 = fopen("hfmTree.text", "r");
		if (fp1 == NULL) {
			perror("无法打开文件");
			return 1;
		}
		
		int i = 0;
		int a;
		while (fscanf_s(fp1, " %c %d %d %d %d %d", &Huffman[i].character, &a, &Huffman[i].weight, &Huffman[i].parent, &Huffman[i].lch, &Huffman[i].rch) == 5) {
			printf("\t%c\t%d\t%d\t%d\t%d\n", Huffman[i].character, Huffman[i].weight, Huffman[i].parent, Huffman[i].lch, Huffman[i].rch);
			i++;
		}
		fclose(fp1);
	}
	else {
		//初始化
		for (int i = 0; i < MAX_SIZE; i++) {
			Huffman[i].weight = 999;
			Huffman[i].parent = 0;
			Huffman[i].lch = 0;
			Huffman[i].rch = 0;
			Huffman[i].character = 'N';
		}

		printf("请输入要输入的数据个数：");
		scanf_s("%d", &count);

		for (int i = 0; i < count; i++) {
			printf("请输入字母：");
			scanf_s(" %c", &Huffman[i].character);
			printf("请输入对应权值：");
			scanf_s("%d", &Huffman[i].weight);
		}

		while (1) {
			int a[2] = { 999,999 };
			int b[2] = { -1,-1 };
			for (int i = 0; i < count; i++) {
				int weight = Huffman[i].weight;
				int number = i;
				if (weight < a[0] && Huffman[i].parent == 0) {
					int tempw = a[0];
					a[0] = weight;
					weight = tempw;
					int tempn = b[0];
					b[0] = number;
					number = tempn;
				}
				if (weight < a[1] && Huffman[i].parent == 0) {
					int tempw = a[1];
					a[1] = weight;
					weight = tempw;
					int tempn = b[1];
					b[1] = number;
					number = tempn;
				}
				if (a[0] > a[1]) {
					int tempw = a[0];
					a[0] = a[1];
					a[1] = tempw;
					int tempn = b[0];
					b[0] = b[1];
					b[1] = tempn;
				}
			}

			if (a[0] != 999 && a[1] != 999) {
				Huffman[count].weight = Huffman[b[0]].weight + Huffman[b[1]].weight;
				Huffman[count].lch = b[0];
				Huffman[count].rch = b[1];
				Huffman[b[0]].parent = count;
				Huffman[b[1]].parent = count;
				count++;
			}
			else {
				break;
			}
		}

		FILE* fp1;
		errno_t err1 = fopen_s(&fp1, "hfmTree.text", "w");
		if (err1 != 0) {
			perror("无法打开文件"); // 注意：perror可能不会显示fopen_s的错误，因为它通常用于打印errno的值
			// 可以使用fprintf(stderr, "无法打开文件，错误码：%d\n", err); 来打印错误码
			return 1;
		}

		// 写入一些文本到文件
		for (int i = 0; i < count; i++) {
			fprintf(fp1, "\t%c\t%d\t%d\t%d\t%d\n", Huffman[i].character, Huffman[i].weight, Huffman[i].parent, Huffman[i].lch, Huffman[i].rch);
		}
		fclose(fp1);
	}

	FILE* fp2 = fopen("ToBeTran.text", "r");
	if (fp2 == NULL) {
		perror("无法打开文件");
		return 1;
	}
	
	FILE* fp3;
	errno_t err3 = fopen_s(&fp3, "CodeFile.text", "w");
	if (err3 != 0) {
		perror("无法打开文件"); 
		return 1;
	}
	
	for (int i = 0; fscanf_s(fp2, "%c", &chars[i], 1) == 1; i++) {
		int j;
		for (j = 0; chars[i] != Huffman[j].character; j++);
		Encoding(Huffman, j, fp3);
	}

	fclose(fp2);
	fclose(fp3);

	int parentnum;
	for (parentnum = 0; Huffman[parentnum].parent != 0; parentnum++);
	char flag = '2';
	int num = parentnum;

	FILE* fp4;
	errno_t err4 = fopen_s(&fp4, "TextFile.text", "w");
	if (err4 != 0) {
		perror("无法打开文件");
		return 1;
	}
	
	FILE* fp5 = fopen("CodeFile.text", "r");
	if (fp5 == NULL) {
		perror("无法打开文件");
		return 1;
	}

	FILE* fp6;
	errno_t err6 = fopen_s(&fp6, "CodePrin.text", "w");
	if (err6 != 0) {
		perror("无法打开文件");
		return 1;
	}

	int count1 = 1;
	while (fscanf_s(fp5, "%c", &flag, 1) == 1) {
		printf("%c", flag);
		fprintf(fp6, "%c", flag);
		if (count1 == 50) {
			printf("\n");
			fprintf(fp6, "\n");
			count1 = 1;
		}
		if (flag == '0') {
			num = Huffman[num].lch;
			if (Huffman[num].lch == 0 && Huffman[num].rch == 0) {
				fprintf(fp4, "%c", Huffman[num].character);
				num = parentnum;
			}
		}
		if (flag == '1') {
			num = Huffman[num].rch;
			if (Huffman[num].lch == 0 && Huffman[num].rch == 0) {
				fprintf(fp4, "%c", Huffman[num].character);
				num = parentnum;
			}
		}
		count1++;
	}
	printf("\n");
	
	fclose(fp4);
	fclose(fp5);
	fclose(fp6);

	FILE* fp7;
	errno_t err7 = fopen_s(&fp7, "TreePrint.text", "w");
	if (err7 != 0) {
		perror("无法打开文件");
		return 1;
	}
	
	TreePrint(Huffman, parentnum, 0, fp7);
	
	return 0;
}
