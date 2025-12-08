#include "ChessPiece.h"

// 默认构造函数：默认设为“死”的，防止空对象被画出来
ChessPiece::ChessPiece()
{
	this->dead = true;
}

// 初始化具体的棋子
ChessPiece::ChessPiece(int id, PieceColor color, PieceType type, int row, int col)
{
	this->id = id;
	this->color = color;
	this->type = type;
	this->row = row;
	this->col = col;
	this->dead = false; // 活着
}

// 绘制函数
void ChessPiece::draw(int gridSize, int marginX, int marginY)
{
	if (dead) return; // 如果死了就不画

	// 算出像素坐标
	int x = marginX + col * gridSize;
	int y = marginY + row * gridSize;
	int r = gridSize / 2 - 2;

	// 画底色（土黄色）
	setfillcolor(RGB(252, 215, 162));
	setlinecolor(RGB(139, 69, 19));
	setlinestyle(PS_SOLID, 2);
	fillcircle(x, y, r);

	// 棋子名字库
	// names[0]是红方名字，names[1]是黑方名字
	const wchar_t* names[][7] = {
		{ L"车", L"马", L"相", L"仕", L"帅", L"炮", L"兵" },
		{ L"车", L"马", L"象", L"士", L"将", L"炮", L"卒" }
	};

	// 设置文字颜色（红方红色，黑方黑色）
	if (color == TEAM_RED) {
		settextcolor(RED);
	}
	else {
		settextcolor(BLACK);
	}

	// 画文字
	setbkmode(TRANSPARENT);
	settextstyle(30, 0, _T("楷体"));

	// 居中输出文字
	outtextxy(x - 15, y - 15, names[color][type]);
}