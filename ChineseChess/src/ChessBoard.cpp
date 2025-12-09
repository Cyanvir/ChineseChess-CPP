#include "ChessBoard.h"
#include <cmath>
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
// 辅助函数：计算两个点之间（不包含起点和终点）有几个棋子？
// 用于“车”和“炮”的判断
int ChessBoard::getStoneCount(int row1, int col1, int row2, int col2)
{
	int ret = 0;
	// 情况1：在同一行
	if (row1 == row2) {
		int min = (col1 < col2) ? col1 : col2;
		int max = (col1 < col2) ? col2 : col1;
		for (int i = min + 1; i < max; i++) {
			if (getPieceAt(row1, i) != -1) ret++; // 如果有子，计数+1
		}
	}
	// 情况2：在同一列
	else if (col1 == col2) {
		int min = (row1 < row2) ? row1 : row2;
		int max = (row1 < row2) ? row2 : row1;
		for (int i = min + 1; i < max; i++) {
			if (getPieceAt(i, col1) != -1) ret++;
		}
	}
	return ret;
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

		// --- 1. 先判断是不是想“移动”或者“吃子” ---
		// (Day 3 的裁判逻辑放在这里)
		// 注意：如果只是点击自己取消，不需要经过裁判，所以裁判逻辑要稍微往后放一点，或者特判一下

		if (clickId != -1) {
			// 点了棋子

			// 【新增逻辑】如果点的是自己 -> 取消选中
			if (clickId == selectedId) {
				selectedId = -1; // 放下棋子
				return;          // 操作结束，直接返回
			}

			if (pieces[clickId].getColor() == pieces[selectedId].getColor()) {
				// 点了其他队友 -> 换选
				selectedId = clickId;
				return; // 换完就走，不需要后续判断
			}

			// --- 下面是“吃子”逻辑 ---
			// 只有吃子才需要问裁判
			if (canMove(selectedId, clickId, row, col)) {
				pieces[clickId].die();
				pieces[selectedId].setPosition(row, col);
				selectedId = -1;
			}
		}
		else {
			// --- 下面是“移动到空地”逻辑 ---
			// 只有移动才需要问裁判
			if (canMove(selectedId, clickId, row, col)) {
				pieces[selectedId].setPosition(row, col);
				selectedId = -1;
			}
		}
	}
}
bool ChessBoard::canMove(int moveId, int killId, int row, int col)
{
	// 1. 如果目标位置有棋子，且是队友，绝对不能走（不能吃自己人）
	if (killId != -1) {
		if (pieces[moveId].getColor() == pieces[killId].getColor()) {
			return false; // 队友，禁止误伤
		}
	}

	// 获取当前棋子的信息
	int row1 = pieces[moveId].getRow();
	int col1 = pieces[moveId].getCol();
	PieceType type = pieces[moveId].getType();
	PieceColor color = pieces[moveId].getColor(); // 红/黑

	// 2. 根据棋子类型，逐个判断
	switch (type)
	{
	case ROOK: // 【车】：横冲直撞
		// 必须在同一行 或 同一列
		if (row1 != row && col1 != col) return false;
		// 中间不能有障碍物
		if (getStoneCount(row1, col1, row, col) > 0) return false;
		break;

	case HORSE: // 【马】：走日字，要注意“撇脚”
	{
		// 算出横向和纵向的距离
		int dr = row - row1; // 纵向距离
		int dc = col - col1; // 横向距离
		int absDr = abs(dr);
		int absDc = abs(dc);

		// 必须是“日”字：一边走1格，一边走2格
		if (!((absDr == 1 && absDc == 2) || (absDr == 2 && absDc == 1))) return false;

		// --- 撇脚马判断 ---
		if (absDc == 2) {
			// 也就是横着走2格，那“马脚”就在横着走1格的位置
			int legCol = (col + col1) / 2;
			if (getPieceAt(row1, legCol) != -1) return false; // 绊马脚了
		}
		else {
			// 竖着走2格，“马脚”在竖着走1格的位置
			int legRow = (row + row1) / 2;
			if (getPieceAt(legRow, col1) != -1) return false;
		}
		break;
	}

	case CANNON: // 【炮】：隔山打牛
		if (row1 != row && col1 != col) return false; // 必须直线

		if (killId == -1) {
			// 如果是移动（不吃子）：中间必须没障碍
			if (getStoneCount(row1, col1, row, col) > 0) return false;
		}
		else {
			// 如果是吃子：中间必须正好有1个障碍（炮架子）
			if (getStoneCount(row1, col1, row, col) != 1) return false;
		}
		break;

	case ELEPHANT: // 【相/象】：走田字，不能过河
		// 1. 必须走“田”：横纵距离都是2
		if (abs(row - row1) != 2 || abs(col - col1) != 2) return false;

		// 2. 堵象眼判断：田字中心不能有子
		if (getPieceAt((row + row1) / 2, (col + col1) / 2) != -1) return false;

		// 3. 不能过河
		if (color == TEAM_RED) {
			if (row < 5) return false; // 红相不能去上半区(0-4行)
		}
		else {
			if (row > 4) return false; // 黑象不能去下半区(5-9行)
		}
		break;

	case ADVISOR: // 【仕/士】：走斜线，不出九宫格
		// 1. 必须走斜线（横纵各动1格）
		if (abs(row - row1) != 1 || abs(col - col1) != 1) return false;

		// 2. 不能出九宫格
		if (col < 3 || col > 5) return false; // 左右边界
		if (color == TEAM_RED) {
			if (row < 7) return false; // 红仕只能在下三路
		}
		else {
			if (row > 2) return false; // 黑士只能在上三路
		}
		break;

	case KING: // 【帅/将】：走直线，不出九宫格，王不见王
		// 1. 走直线，每次1格
		if ((abs(row - row1) + abs(col - col1)) != 1) return false;

		// 2. 不能出九宫格
		if (col < 3 || col > 5) return false;
		if (color == TEAM_RED) {
			if (row < 7) return false;
		}
		else {
			if (row > 2) return false;
		}
		// TODO: 王不见王的规则比较复杂，先不做，如果你想拿满分可以后面补
		break;

	case SOLDIER: // 【兵/卒】：过河前只能冲，过河后能横着走，决不能回头
		// 1. 纵向距离：红兵只能向上(-1)，黑卒只能向下(+1)
		int dr = row - row1;
		int dc = col - col1;

		if (color == TEAM_RED) {
			// 红兵：没过河(row1 > 4)只能向前；过河后可以向前或左右
			if (row1 > 4) {
				// 没过河：只能向前1格，横向不能动
				if (dr != -1 || dc != 0) return false;
			}
			else {
				// 过河了：向前1格 或者 横向1格
				// 逻辑：总步数必须是1，且不能后退(dr不能是正数)
				if (abs(dr) + abs(dc) != 1) return false;
				if (dr > 0) return false; // 绝不回头
			}
		}
		else {
			// 黑卒逻辑相反
			if (row1 <= 4) {
				if (dr != 1 || dc != 0) return false;
			}
			else {
				if (abs(dr) + abs(dc) != 1) return false;
				if (dr < 0) return false;
			}
		}
		break;
	}

	return true; // 如果上面都没拦住，那就是合法移动
}