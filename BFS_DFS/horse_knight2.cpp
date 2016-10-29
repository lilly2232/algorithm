#include <iostream>
#define MAX 1002
#define QSIZE 1000000
int num;
int visit_arr[MAX][MAX] = { 0, };
int knight_arr[MAX][MAX] = { 0, };	// type : 0 knight 
int ma_arr[MAX][MAX] = { 0, };		// type : 1 ma
using namespace std;
const int DIRECTION[8][2] = {
	-1,0,-1,0,
	1,0,1,0,
	0,-1,0,-1,
	0,1,0,1
};
const int MOVE[8][2] = {
	-2, -1,
	-2, 1,
	2, -1,
	2, 1,
	-1, -2,
	1, -2,
	-1, 2,
	1, 2
};

struct Point
{
	int x;
	int y;
	int cnt;
};
Point queue[QSIZE];
void bfs(int start_x, int start_y, int type, int arr[][MAX])
{
	int front = 0; int rear = 0;
	Point here;
	here.x = start_x; here.y = start_y; here.cnt = 0;
	visit_arr[here.x][here.y] = 1;
	queue[rear++] = here;

	int x, y, cnt;
	while (front != rear)
	{
		here = queue[front];
		front = front + 1;
		x = here.x;  y = here.y; cnt = here.cnt;
		arr[x][y] = cnt;
	
		if (type == 0)
		{
			for (int i = 0; i < 8; i++)
			{
				int point_x, point_y;
				point_x = x + MOVE[i][0];  point_y = y + MOVE[i][1];
				if (point_x > 0 && point_x < num + 1 && point_y > 0 && point_y < num + 1)
					if (arr[point_x][point_y] == 0 && visit_arr[point_x][point_y] == 0)
					{
						visit_arr[point_x][point_y] = 1;
						queue[rear].x = point_x;
						queue[rear].y = point_y;
						queue[rear].cnt = cnt + 1;
						rear++;
					}
			}
		}
		if (type == 1)
		{
			for (int i = 0; i < 8; i++)
			{
				int point_x, point_y;
				point_x = x + DIRECTION[i][0];  point_y = y + DIRECTION[i][1];
				if (arr[point_x][point_y] >= 0)
				{
					point_x = x + MOVE[i][0];  point_y = y + MOVE[i][1];
					if (point_x > 0 && point_x < num + 1 && point_y > 0 && point_y < num + 1) {
						if (arr[point_x][point_y] == 0 && visit_arr[point_x][point_y] == 0)
						{
							visit_arr[point_x][point_y] = 1;
							queue[rear].x = point_x;
							queue[rear].y = point_y;
							queue[rear].cnt = cnt + 1;
							rear++;
						}
					}
				}
			}
		}
	}
}
void init()
{
	for (int i = 1; i <= num; i++) {
		for (int j = 1; j <= num; j++)
			visit_arr[i][j] = 0;
	}
}
int main()
{
	cin >> num;
	int k;
	cin >> k;

	for (int i = 0; i <= num + 1; i++)
		for (int j = 0; j <= num + 1; j++)
		{
			if (i == 0 || j == 0 || i == num + 1 || j == num + 1) {
				knight_arr[i][j] = -2;
				ma_arr[i][j] = -2;
			}
			else {
				int val;
				cin >> val;
				if (val == 1)
				{
					ma_arr[i][j] = knight_arr[i][j] = -1;
				}
			}
		}
	int x, y;
	cin >> x >> y;
	bfs(x, y, 0, knight_arr);
	init();
	bfs(x, y, 1, ma_arr);
	int total = 0;
	for (int i = 1; i <= num; i++)
		for (int j = 1; j <= num; j++)
			if (ma_arr[i][j] == 0 || knight_arr[i][j] < ma_arr[i][j])
			{
				if (knight_arr[i][j] != 0)
					total++;
			}
	cout << total << endl;
}