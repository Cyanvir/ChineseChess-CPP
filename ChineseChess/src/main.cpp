#include <graphics.h>
#include <conio.h>
#include "ChessBoard.h" // 引用我们要用的棋盘类

// 链接库配置（和你之前的一样）
#ifdef _WIN64
#pragma comment(lib, "EasyXa.lib")
#pragma comment(lib, "EasyXw.lib")
#else
#pragma comment(lib, "EasyXa.lib")
#pragma comment(lib, "EasyXw.lib")
#endif

int main()
{
	// 1. 创建图形窗口
	// 计算一下窗口大小：棋盘宽(8格) + 左右留白(2*50)，高(9格) + 上下留白
	// 这里直接给一个稍大一点的固定值
	initgraph(580, 700, EX_SHOWCONSOLE);

	// 2. 实例化一个棋盘对象
	ChessBoard board;

	// 3. 绘制棋盘
	board.draw();

	// 4. 暂停，等待用户按键
	_getch();

	// 5. 关闭
	closegraph();
	return 0;
}