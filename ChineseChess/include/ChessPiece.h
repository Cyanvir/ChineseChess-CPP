#pragma once
#include <graphics.h>

// 1. 定义棋子颜色的枚举（放在这里，不要放 ChessBoard 里）
enum PieceColor {
	TEAM_RED,    // 红方队伍
	TEAM_BLACK,  // 黑方队伍
	NONE    // 无
};

// 2. 定义棋子类型的枚举
enum PieceType {
	ROOK,     // 车
	HORSE,    // 马
	ELEPHANT, // 相/象
	ADVISOR,  // 仕/士
	KING,     // 帅/将
	CANNON,   // 炮
	SOLDIER   // 兵/卒
};

// 3. 定义棋子类
class ChessPiece
{
public:
	// 默认构造函数
	ChessPiece();

	// 带参数的构造函数
	ChessPiece(int id, PieceColor color, PieceType type, int row, int col);

	// 画棋子
	void draw(int gridSize, int marginX, int marginY);

	// 获取属性的函数
	int getRow() const { return row; }
	int getCol() const { return col; }
	int getId() const { return id; }
	PieceColor getColor() const { return color; }
	PieceType getType() const { return type; }
	bool isDead() const { return dead; }

	// 设置位置
	void setPosition(int r, int c) { row = r; col = c; }
	// 棋子被吃掉
	void die() { dead = true; }

private:
	int id;          // ID
	PieceColor color;// 颜色
	PieceType type;  // 类型
	int row, col;    // 行列坐标
	bool dead;       // 是否存活
};