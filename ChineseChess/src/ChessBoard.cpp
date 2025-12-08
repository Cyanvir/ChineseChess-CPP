#include "ChessBoard.h"

ChessBoard::ChessBoard()
{
	selectedId = -1; // 一开始什么都没选中
}

// 初始化32个棋子
void ChessBoard::init()
{
	// 【核心修改】全部换成 TEAM_RED 和 TEAM_BLACK

	// --- 红方 (0-15) ---
	pieces[0] = ChessPiece(0, TEAM_RED, ROOK, 9, 0);
	pieces[1] = ChessPiece(1, TEAM_RED, HORSE, 9, 1);
	pieces[2] = ChessPiece(2, TEAM_RED, ELEPHANT, 9, 2);
	pieces[3] = ChessPiece(3, TEAM_RED, ADVISOR, 9, 3);
	pieces[4] = ChessPiece(4, TEAM_RED, KING, 9, 4);
	pieces[5] = ChessPiece(5, TEAM_RED, ADVISOR, 9, 5);
	pieces[6] = ChessPiece(6, TEAM_RED, ELEPHANT, 9, 6);
	pieces[7] = ChessPiece(7, TEAM_RED, HORSE, 9, 7);
	pieces[8] = ChessPiece(8, TEAM_RED, ROOK, 9, 8);

	pieces[9] = ChessPiece(9, TEAM_RED, CANNON, 7, 1);
	pieces[10] = ChessPiece(10, TEAM_RED, CANNON, 7, 7);

	pieces[11] = ChessPiece(11, TEAM_RED, SOLDIER, 6, 0);
	pieces[12] = ChessPiece(12, TEAM_RED, SOLDIER, 6, 2);
	pieces[13] = ChessPiece(13, TEAM_RED, SOLDIER, 6, 4);
	pieces[14] = ChessPiece(14, TEAM_RED, SOLDIER, 6, 6);
	pieces[15] = ChessPiece(15, TEAM_RED, SOLDIER, 6, 8);

	// --- 黑方 (16-31) ---
	pieces[16] = ChessPiece(16, TEAM_BLACK, ROOK, 0, 0);
	pieces[17] = ChessPiece(17, TEAM_BLACK, HORSE, 0, 1);
	pieces[18] = ChessPiece(18, TEAM_BLACK, ELEPHANT, 0, 2);
	pieces[19] = ChessPiece(19, TEAM_BLACK, ADVISOR, 0, 3);
	pieces[20] = ChessPiece(20, TEAM_BLACK, KING, 0, 4);
	pieces[21] = ChessPiece(21, TEAM_BLACK, ADVISOR, 0, 5);
	pieces[22] = ChessPiece(22, TEAM_BLACK, ELEPHANT, 0, 6);
	pieces[23] = ChessPiece(23, TEAM_BLACK, HORSE, 0, 7);
	pieces[24] = ChessPiece(24, TEAM_BLACK, ROOK, 0, 8);

	pieces[25] = ChessPiece(25, TEAM_BLACK, CANNON, 2, 1);
	pieces[26] = ChessPiece(26, TEAM_BLACK, CANNON, 2, 7);

	pieces[27] = ChessPiece(27, TEAM_BLACK, SOLDIER, 3, 0);
	pieces[28] = ChessPiece(28, TEAM_BLACK, SOLDIER, 3, 2);
	pieces[29] = ChessPiece(29, TEAM_BLACK, SOLDIER, 3, 4);
	pieces[30] = ChessPiece(30, TEAM_BLACK, SOLDIER, 3, 6);
	pieces[31] = ChessPiece(31, TEAM_BLACK, SOLDIER, 3, 8);
}
void ChessBoard::draw()
{
	// 1. 设置背景
	setbkcolor(RGB(230, 195, 120));
	cleardevice();

	// 2. 画网格线
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);

	// 横线
	for (int i = 0; i < 10; i++) {
		int y = MARGIN_Y + i * GRID_SIZE;
		line(MARGIN_X, y, MARGIN_X + 8 * GRID_SIZE, y);
	}

	// 竖线
	for (int i = 0; i < 9; i++) {
		int x = MARGIN_X + i * GRID_SIZE;
		line(x, MARGIN_Y, x, MARGIN_Y + 4 * GRID_SIZE); // 上半
		line(x, MARGIN_Y + 5 * GRID_SIZE, x, MARGIN_Y + 9 * GRID_SIZE); // 下半
	}

	// 补左右边框
	line(MARGIN_X, MARGIN_Y + 4 * GRID_SIZE, MARGIN_X, MARGIN_Y + 5 * GRID_SIZE);
	line(MARGIN_X + 8 * GRID_SIZE, MARGIN_Y + 4 * GRID_SIZE, MARGIN_X + 8 * GRID_SIZE, MARGIN_Y + 5 * GRID_SIZE);

	// 九宫格斜线
	line(MARGIN_X + 3 * GRID_SIZE, MARGIN_Y, MARGIN_X + 5 * GRID_SIZE, MARGIN_Y + 2 * GRID_SIZE);
	line(MARGIN_X + 5 * GRID_SIZE, MARGIN_Y, MARGIN_X + 3 * GRID_SIZE, MARGIN_Y + 2 * GRID_SIZE);
	line(MARGIN_X + 3 * GRID_SIZE, MARGIN_Y + 7 * GRID_SIZE, MARGIN_X + 5 * GRID_SIZE, MARGIN_Y + 9 * GRID_SIZE);
	line(MARGIN_X + 5 * GRID_SIZE, MARGIN_Y + 7 * GRID_SIZE, MARGIN_X + 3 * GRID_SIZE, MARGIN_Y + 9 * GRID_SIZE);

	// 3. 写字
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(40, 0, _T("楷体"));
	outtextxy(MARGIN_X + 1 * GRID_SIZE + 10, MARGIN_Y + 4 * GRID_SIZE + 10, _T("楚河"));
	outtextxy(MARGIN_X + 5 * GRID_SIZE + 10, MARGIN_Y + 4 * GRID_SIZE + 10, _T("汉界"));

	// 4. 画所有棋子
	for (int i = 0; i < 32; i++) {
		pieces[i].draw(GRID_SIZE, MARGIN_X, MARGIN_Y);
	}
	// 5. 如果有选中的棋子，画个框提示一下
	if (selectedId != -1) {
		int r = pieces[selectedId].getRow();
		int c = pieces[selectedId].getCol();
		int x = MARGIN_X + c * GRID_SIZE;
		int y = MARGIN_Y + r * GRID_SIZE;

		setlinecolor(BLUE); // 选个显眼的蓝色
		setlinestyle(PS_SOLID, 2);
		// 画个矩形框住棋子
		rectangle(x - 30, y - 30, x + 30, y + 30);
	}
}
// 辅助功能：看看 row, col 这个格子里有没有活着的棋子
int ChessBoard::getPieceAt(int row, int col)
{
	for (int i = 0; i < 32; i++) {
		if (!pieces[i].isDead() && pieces[i].getRow() == row && pieces[i].getCol() == col) {
			return i; // 找到了，返回棋子ID
		}
	}
	return -1; // 没找到
}
void ChessBoard::click(int x, int y)
{
	// 1. 像素坐标转网格坐标 (记得要把边距减掉)
	// 比如点击了 (115, 115)，边距50，格子60
	// (115-50)/60 = 1，说明点在了第1列
	// 这里的 + GRID_SIZE / 2 是为了四舍五入，让点击容错率更高（点格子边缘也能识别）
	int col = (x - MARGIN_X + GRID_SIZE / 2) / GRID_SIZE;
	int row = (y - MARGIN_Y + GRID_SIZE / 2) / GRID_SIZE;

	// 2. 越界检查（点到棋盘外面去了就忽略）
	if (col < 0 || col > 8 || row < 0 || row > 9) return;

	// 3. 看看刚才点的这个地方有没有棋子
	int clickId = getPieceAt(row, col);

	// --- 状态机逻辑 ---

	if (selectedId == -1) {
		// 【情况A：当前没选中棋子】
		if (clickId != -1) {
			// 如果点到了棋子，就选中它！
			selectedId = clickId;
			// 播放个音效或者打印个日志（这里先留空）
		}
	}
	else {
		// 【情况B：手里已经拿着一个棋子了】
		if (clickId != -1) {
			// 如果又点了一个棋子
			// 这里暂时简化处理：如果是队友就换人，如果是敌人就吃掉（今天先做换人）
			if (pieces[clickId].getColor() == pieces[selectedId].getColor()) {
				// 点了队友，换选这个队友
				selectedId = clickId;
			}
			else {
				// 点了敌人 -> 吃子！(先把敌人弄死，再走过去)
				pieces[clickId].die(); // 敌人去世
				pieces[selectedId].setPosition(row, col); // 我走过去
				selectedId = -1; // 行动结束，取消选中
			}
		}
		else {
			// 点了空地 -> 移动
			// 暂时不判断规则，想去哪去哪（瞬移）
			pieces[selectedId].setPosition(row, col);
			selectedId = -1; // 移动完毕，取消选中
		}
	}
}