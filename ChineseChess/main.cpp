#include <graphics.h>  // 引用 EasyX 图形库头文件
#include <conio.h>     // 引用控制台输入库

// 【核心修改点】
// 告诉连接器我们要用 EasyX 的库文件
// 这里的文件名必须和你在 lib 文件夹里看到的一模一样！
#ifdef _WIN64
#pragma comment(lib, "EasyXa.lib")   // 对应 ASCII 版本
#pragma comment(lib, "EasyXw.lib")   // 对应 Unicode 版本
#else
#pragma comment(lib, "EasyXa.lib")
#pragma comment(lib, "EasyXw.lib")
#endif

int main()
{
	// 1. 初始化图形窗口
	// 宽 640, 高 720 (这大约是一个标准象棋程序的尺寸)
	initgraph(640, 720, EX_SHOWCONSOLE);

	// 2. 设置背景颜色 (模拟象棋棋盘的木纹黄颜色)
	setbkcolor(RGB(230, 195, 120));

	// 3. 清空屏幕，让背景色生效
	cleardevice();

	// 4. 画一个简单的“棋子”测试一下
	// 设置填充颜色为红色
	setfillcolor(RED);
	// 设置线条颜色为红色（去掉黑边）
	setlinecolor(RED);
	// 画一个实心圆 (圆心坐标 x=320, y=360, 半径=40)
	fillcircle(320, 360, 40);

	// 5. 在圆中间写个字 (测试文字输出)
	setbkmode(TRANSPARENT); // 文字背景透明
	settextcolor(WHITE);    // 文字白色
	settextstyle(40, 0, _T("黑体")); // 设置字体大小

	// 居中显示一个“帅”字
	outtextxy(320 - 20, 360 - 20, _T("帅"));

	// 6. 等待用户按任意键，否则窗口会一闪而过
	_getch();

	// 7. 关闭图形窗口
	closegraph();

	return 0;
}