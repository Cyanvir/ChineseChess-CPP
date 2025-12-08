#include "ChessBoard.h"

// 构造函数
ChessBoard::ChessBoard()
{
	// 可以在这里设置一些默认值，目前留空
}

// 初始化
void init()
{
	// 暂时没数据需要初始化，留个接口
}

// 【核心】绘制棋盘的逻辑
void ChessBoard::draw()
{
	// 1. 设置棋盘背景色（一种接近木质的颜色）
	setbkcolor(RGB(230, 195, 120));
	cleardevice();

	// 2. 准备画线，设置线条颜色为黑色
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2); // 实线，线宽2像素

	// 3. 画横线 (共10条)
	for (int i = 0; i < 10; i++) {
		// 计算线条的起点(x1, y1) 和 终点(x2, y2)
		// y坐标随 i 增加向下移动
		int y = MARGIN_Y + i * GRID_SIZE;

		// 起点x 和 终点x
		int x1 = MARGIN_X;
		int x2 = MARGIN_X + 8 * GRID_SIZE;

		line(x1, y, x2, y);
	}

	// 4. 画竖线 (共9条)
	// 这里的逻辑有点特殊：中间有楚河汉界，竖线是断开的
	for (int i = 0; i < 9; i++) {
		int x = MARGIN_X + i * GRID_SIZE;

		// 上半部分竖线 (第0行到第4行)
		line(x, MARGIN_Y, x, MARGIN_Y + 4 * GRID_SIZE);

		// 下半部分竖线 (第5行到第9行)
		line(x, MARGIN_Y + 5 * GRID_SIZE, x, MARGIN_Y + 9 * GRID_SIZE);
	}

	// 5. 补上楚河汉界两边的外边框竖线（防止刚才断开导致两边没有封口）
	int x_left = MARGIN_X;
	int x_right = MARGIN_X + 8 * GRID_SIZE;
	// 补第4行到第5行之间的左边框
	line(x_left, MARGIN_Y + 4 * GRID_SIZE, x_left, MARGIN_Y + 5 * GRID_SIZE);
	// 补第4行到第5行之间的右边框
	line(x_right, MARGIN_Y + 4 * GRID_SIZE, x_right, MARGIN_Y + 5 * GRID_SIZE);

	// 6. 画九宫格的斜线（士走的路线）
	// 上方九宫格
	line(MARGIN_X + 3 * GRID_SIZE, MARGIN_Y, MARGIN_X + 5 * GRID_SIZE, MARGIN_Y + 2 * GRID_SIZE);
	line(MARGIN_X + 5 * GRID_SIZE, MARGIN_Y, MARGIN_X + 3 * GRID_SIZE, MARGIN_Y + 2 * GRID_SIZE);

	// 下方九宫格
	line(MARGIN_X + 3 * GRID_SIZE, MARGIN_Y + 7 * GRID_SIZE, MARGIN_X + 5 * GRID_SIZE, MARGIN_Y + 9 * GRID_SIZE);
	line(MARGIN_X + 5 * GRID_SIZE, MARGIN_Y + 7 * GRID_SIZE, MARGIN_X + 3 * GRID_SIZE, MARGIN_Y + 9 * GRID_SIZE);

	// 7. 写字：“楚河 汉界”
	settextcolor(BLACK);
	setbkmode(TRANSPARENT); // 文字背景透明
	// 设置字体：高50，宽0(自适应)，字体名"楷体"
	settextstyle(40, 0, _T("楷体"));

	// 算出位置居中
	outtextxy(MARGIN_X + 1 * GRID_SIZE + 10, MARGIN_Y + 4 * GRID_SIZE + 10, _T("楚河"));
	outtextxy(MARGIN_X + 5 * GRID_SIZE + 10, MARGIN_Y + 4 * GRID_SIZE + 10, _T("汉界"));
}