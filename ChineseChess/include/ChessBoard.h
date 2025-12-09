#pragma once
#include <graphics.h>
#include <vector>
#include "ChessPiece.h" // 【关键】必须包含这个，才能认识 ChessPiece 类

class ChessBoard
{
public:
	ChessBoard();

	// 初始化棋子位置
	void init();

	// 画棋盘和棋子
	void draw();
	// 处理鼠标点击：传入鼠标的像素坐标(x,y)
	void click(int x, int y);
	// 电脑走棋逻辑
	void computerMove();
	// 裁判函数
	// 参数：moveId(移动棋子的ID), row/col(目标位置), killId(目标位置的棋子ID, -1表示空地)
	bool canMove(int moveId, int killId, int row, int col);
	// 提供给外部的接口
	int getGridSize() const { return GRID_SIZE; }
	int getMarginX() const { return MARGIN_X; }
	int getMarginY() const { return MARGIN_Y; }

private:
	// 辅助函数：根据行列坐标找棋子ID
	// 如果这个位置有棋子，返回ID(0-31)；如果没有，返回-1
	int getPieceAt(int row, int col);
	const int GRID_SIZE = 60;
	const int MARGIN_X = 50;
	const int MARGIN_Y = 50;

	// 存储32个棋子
	ChessPiece pieces[32];
	// 当前选中的棋子ID
	// -1 表示没选中任何棋子
	// 0-31 表示选中了对应的棋子
	int selectedId;
	// 记录当前是谁的回合
	// true 代表红方回合，false 代表黑方回合
	bool isRedTurn;
	int getStoneCount(int row1, int col1, int row2, int col2);
};