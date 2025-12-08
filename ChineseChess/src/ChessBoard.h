#pragma once
#pragma once // 防止头文件被重复引用
#include <graphics.h> // 引用图形库

// 定义棋盘类
class ChessBoard
{
public:
	// 构造函数：类创建时自动调用
	ChessBoard();

	// 初始化棋盘数据
	void init();

	// 核心功能：把棋盘画出来
	void draw();

	// 获取格子大小（后续棋子移动需要用到）
	int getGridSize() const { return GRID_SIZE; }

	// 获取左上角偏移量（后续计算坐标需要用到）
	int getMarginX() const { return MARGIN_X; }
	int getMarginY() const { return MARGIN_Y; }

private:
	// 棋盘绘制的参数（常量）
	const int GRID_SIZE = 60; // 每个格子的像素大小
	const int MARGIN_X = 50;  // 棋盘左边的留白宽度
	const int MARGIN_Y = 50;  // 棋盘上边的留白高度
};