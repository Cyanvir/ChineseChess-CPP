#include <graphics.h>
#include "ChessBoard.h"
#include <time.h>
#ifdef _WIN64
#pragma comment(lib, "EasyXa.lib")
#pragma comment(lib, "EasyXw.lib")
#else
#pragma comment(lib, "EasyXa.lib")
#pragma comment(lib, "EasyXw.lib")
#endif

int main()
{
	srand((unsigned int)time(NULL)); // 设置随机种子
	// 初始化窗口
	initgraph(580, 700, EX_SHOWCONSOLE); // 这里保留控制台方便调试

	ChessBoard board;
	board.init();

	// 开始绘制循环
	// 每次循环：处理输入 -> 更新数据 -> 绘制画面
	BeginBatchDraw(); // 开启双缓冲，防止画面闪烁（很重要！）

	while (true) {
		// 1. 处理鼠标交互
		MOUSEMSG msg;
		if (MouseHit()) { // 如果有鼠标消息
			msg = GetMouseMsg();
			if (msg.uMsg == WM_LBUTTONDOWN) { //如果是左键按下
				// 把坐标传给棋盘去处理
				board.click(msg.x, msg.y);
			}
		}

		// 2. 绘制
		board.draw();

		// 3. 显示
		FlushBatchDraw();

		// 稍微延时一下，降低CPU占用
		Sleep(10);
	}

	EndBatchDraw();
	closegraph();
	return 0;
}