#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 100

typedef struct {
	int number;
	char name[MAX_SIZE];
	char introduction[MAX_SIZE];
} vertex;

typedef struct {
	int n;
	int m;
	vertex v[10];
	int edgs[10][10];
} Map;

void Menu() {
	printf("\n");
	printf("       ********************************************************\n");
	printf("       ************   杭州电子科技大学导游咨询系统 ************\n");
	printf("       ************   1.杭电景点信息查询           ************\n");
	printf("       ************   2.两景点之间最短路查询       ************\n");
	printf("       ************   3.退出系统                   ************\n");
	printf("       ********************************************************\n");
	return;
}

void CreatVertex(Map* map) {
	map->v[0].number = 1;
	strcpy(map->v[0].name, "西北田径场");
	strcpy(map->v[0].introduction, "这是学生进行体育活动的场地，有真正的草地");
	map->v[1].number = 2;
	strcpy(map->v[1].name, "大学生活动中心");
	strcpy(map->v[1].introduction, "这是举办文艺活动的场所");
	map->v[2].number = 3;
	strcpy(map->v[2].name, "梅花饮食广场");
	strcpy(map->v[2].introduction, "这里是学校最受欢迎的餐饮区，物美价廉");
	map->v[3].number = 4;
	strcpy(map->v[3].name, "实验楼");
	strcpy(map->v[3].introduction, "这里是学校实验室所在的楼层");
	map->v[4].number = 5;
	strcpy(map->v[4].name, "六教");
	strcpy(map->v[4].introduction, "这是学校的教学楼");
	map->v[5].number = 6;
	strcpy(map->v[5].name, "七教");
	strcpy(map->v[5].introduction, "这是学校的教学楼");
	map->v[6].number = 7;
	strcpy(map->v[6].name, "一教");
	strcpy(map->v[6].introduction, "这是学校的教学楼，属计算机学院与通信工程学院");
	map->v[7].number = 8;
	strcpy(map->v[7].name, "图书馆");
	strcpy(map->v[7].introduction, "这是学校的图书馆，藏书丰富，是同学们阅读自习的好去处");
	map->v[8].number = 9;
	strcpy(map->v[8].name, "三教");
	strcpy(map->v[8].introduction, "这是学校的教学楼");
	map->v[9].number = 10;
	strcpy(map->v[9].name, "体育馆");
	strcpy(map->v[9].introduction, "这是学生进行室内比赛和体育活动的场所");
	return;
}

void CreatMap(Map* map) {
	int i, j;
	map->n = 10;
	map->m = 55;
	for (i = 0; i < map->n; i++) ///初始化邻接矩阵
	{
		for (j = 0; j < map->n; j++)
		{
			map->edgs[i][j] = 99999;
		}
	}
	map->edgs[0][1] = map->edgs[1][0] = 500;///写入边的信息
	map->edgs[0][2] = map->edgs[2][0] = 1000;
	map->edgs[0][7] = map->edgs[7][0] = 500;
	map->edgs[1][3] = map->edgs[3][1] = 200;
	map->edgs[1][4] = map->edgs[4][1] = 200;
	map->edgs[2][7] = map->edgs[7][2] = 400;
	map->edgs[3][4] = map->edgs[4][3] = 300;
	map->edgs[4][5] = map->edgs[5][4] = 300;
	map->edgs[4][6] = map->edgs[6][4] = 100;
	map->edgs[5][6] = map->edgs[6][5] = 300;
	map->edgs[5][8] = map->edgs[8][5] = 200;
	map->edgs[6][8] = map->edgs[8][6] = 200;
	map->edgs[6][7] = map->edgs[7][6] = 200;
	map->edgs[8][9] = map->edgs[9][8] = 500;
	return;
}

void SearchInfo(Map* map) {
	int i, n;
	printf("杭州电子科技大学的景点有：\n");
	for (i = 0; i < map->n; i++)
	{
		printf("%d:%s\n", map->v[i].number, map->v[i].name);
	}

	while (1)
	{
		printf("请输入你想要查询的景点编号（按0退出查询）：\n");
		scanf_s("%d", &n);
		getchar();
		if (n == 0) {
			break;
		}
		if (n < 0 || n>10) {
			printf("输入有误，请重新输入！！！\n");
			continue;
		}
		else {
			printf("%d:%s\n", map->v[n - 1].number, map->v[n - 1].name);
			printf("%s\n", map->v[n - 1].introduction);
		}
	}
	return;
}

void Floyd(Map map,int dist[10][10], int path[10][10]) {
	int i, j, k;
	for (i = 0; i < map.n; i++) ///初始化距离与路径矩阵
	{
		for (j = 0; j < map.n; j++)
		{
			dist[i][j] = map.edgs[i][j];
			if (i != j && dist[i][j] < 99999)
			{
				path[i][j] = i;
			}
			else
			{
				path[i][j] = -1;///-1代表不可达
			}
		}
	}

	for (k = 0; k < map.n; k++)
	{
		for (i = 0; i < map.n; i++)
		{
			for (j = 0; j < map.n; j++)
			{
				if (dist[i][j] > (dist[i][k] + dist[k][j]))
				{
					dist[i][j] = dist[i][k] + dist[k][j];///更新
					path[i][j] = k;         ///path用于记录最短路径上的结点*/
				}
			}
		}
	}
	return;
}

void Floyd_print(int s, int e, int path[10][10], Map map)
{
	if (path[s][e] == -1 || path[s][e] == e || path[s][e] == s)///递归终止条件
	{
		return;
	}
	else
	{
		Floyd_print(s, path[s][e], path, map);
		printf("%s->", map.v[path[s][e]].name);
		Floyd_print(path[s][e], e, path, map);
	}
}

int main() {
	Map map;
	int n;
	int dist[10][10];
	int path[10][10];
	int start;
	int ends;
	
	while (1) {
		CreatVertex(&map);
		CreatMap(&map);
		
		Menu();
		printf("请输入需要操作的命令：\n");
		scanf_s("%d", &n);
		getchar();
		
		switch (n) {
		case 1:
			system("cls");
			SearchInfo(&map);
			system("cls");
			break;
		
		case 2:
			system("cls");
			printf("杭州电子科技大学的景点有：\n");
			for (int i = 0; i < map.n; i++)
			{
				printf("%d:%s\n", map.v[i].number, map.v[i].name);
			}
			printf("请输入起点的景点：\n");
			scanf_s("%d", &start);
			printf("请输入终点的景点：\n");
			scanf_s("%d", &ends);

			Floyd(map, dist, path);

			printf("从%s到%s最短距离是：%d\n", map.v[start - 1].name, map.v[ends - 1].name, dist[start - 1][ends - 1]);
			printf("%s->", map.v[start - 1].name);
			Floyd_print(start - 1, ends - 1, path, map);
			printf("%s\n", map.v[ends - 1].name);
			system("pause");
			system("cls");

			break;
		
		case 3:
			return 0;
		
		default:
			system("cls");
			printf("输入无效。\n");
			system("pause");
			system("cls");
			break;
		}
	}
	return 0;
}
