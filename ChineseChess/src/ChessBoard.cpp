#include "ChessBoard.h"
#include <cmath>
#include<graphics.h>
// 兵的价值表 (这是针对红兵的，越往上走分越高)
// 0分表示家里，20分表示过河，50分表示逼近九宫格
const int SOLDIER_TABLE[10][9] = {
	{ 0,  0,  0,  0,  0,  0,  0,  0,  0}, // 0行 (对面底线)
	{40, 60, 80, 80, 80, 80, 80, 60, 40}, // 1行 (九宫格顶) - 高分！
	{20, 40, 60, 80, 80, 80, 60, 40, 20}, // 2行
	{20, 20, 40, 40, 40, 40, 40, 20, 20}, // 3行 (卒林线)
	{20, 20, 20, 20, 20, 20, 20, 20, 20}, // 4行 (河岸)
	{ 0,  0,  0,  0,  0,  0,  0,  0,  0}, // 5行 (自己河岸)
	{ 0,  0,  0,  0,  0,  0,  0,  0,  0}, // 6行
	{ 0,  0,  0,  0,  0,  0,  0,  0,  0}, // 7行
	{ 0,  0,  0,  0,  0,  0,  0,  0,  0}, // 8行
	{ 0,  0,  0,  0,  0,  0,  0,  0,  0}, // 9行 (自己底线)
};
ChessBoard::ChessBoard()
{
	selectedId = -1; // 一开始什么都没选中
}

// 初始化32个棋子
void ChessBoard::init()
{
	// 1. 弹窗询问玩家
	int ret = MessageBox(GetHWnd(), _T("你想执红先行吗？\n(按'是'执红，按'否'执黑)"), _T("选择阵营"), MB_YESNO | MB_ICONQUESTION);

	if (ret == IDYES) {
		playerColor = TEAM_RED;
	}
	else {
		playerColor = TEAM_BLACK;
	}

	// 2. 初始化所有变量
	selectedId = -1;
	isRedTurn = true; // 永远是红方先行
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
	// 4. 【核心逻辑】如果玩家选了黑方，那电脑(红方)得先走一步！
	if (playerColor == TEAM_BLACK) {
		// 先画出来棋盘让玩家看一眼
		draw();
		Sleep(500);
		// 电脑走红方第一步
		computerMove();
	}
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
	// 提示当前回合
	settextstyle(30, 0, _T("黑体"));
	setbkmode(TRANSPARENT);

	LPCTSTR tipText; // 定义一个字符串变量
	if (isRedTurn) {
		settextcolor(RED);
		tipText = _T("轮到红方走棋");
	}
	else {
		settextcolor(BLACK);
		tipText = _T("轮到黑方走棋");
	}

	// 1. 自动居中计算
	// 窗口宽度是 580 (main函数里设的)，也可以用 getwidth() 获取
	int textWidth = textwidth(tipText);
	int x = (580 - textWidth) / 2;

	// 2. 位置下移，不挡住棋子
	// 棋盘底部是 MARGIN_Y + 9 * GRID_SIZE
	// 我们再往下多加 70 像素，给最下面的棋子留出位置
	int y = MARGIN_Y + 9 * GRID_SIZE + 70;

	outtextxy(x, y, tipText);
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
	// 1. 如果当前不是玩家的回合，禁止操作（防止电脑思考时玩家乱点）
	if (isRedTurn && playerColor == TEAM_BLACK) return;
	if (!isRedTurn && playerColor == TEAM_RED) return;
	// 必须点“当前回合”颜色的棋子
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
		// 【情况A：手里空空】
		if (clickId != -1) {
			// 必须点“当前回合”颜色的棋子
			// 如果是红方回合(true)，必须点 RED 颜色的棋子
			// 如果是黑方回合(false)，必须点 BLACK 颜色的棋子
			if (isRedTurn == true && pieces[clickId].getColor() != TEAM_RED) return;
			if (isRedTurn == false && pieces[clickId].getColor() != TEAM_BLACK) return;

			selectedId = clickId;
		}
	}
	else {
		// 【情况B：手里已经拿着一个棋子了】
		// 1. 点自己 -> 取消选中
		if (clickId == selectedId) {
			selectedId = -1;
			return;
		}

		// 2. 点队友 -> 换选
		if (clickId != -1 && pieces[clickId].getColor() == pieces[selectedId].getColor()) {
			selectedId = clickId;
			return;
		}

		// 3. 点敌人 或 点空地 -> 尝试移动
		// 问裁判：能不能走？
		if (canMove(selectedId, clickId, row, col)) {
			if (clickId != -1) {
				// 吃子逻辑
				if (pieces[clickId].getType() == KING) {
					// 1. 先把老将吃了，画面更新
					pieces[clickId].die();
					pieces[selectedId].setPosition(row, col);
					draw();

					// 2. 【修改】直接调用统一接口
					if (isRedTurn) gameOver(TEAM_RED);
					else gameOver(TEAM_BLACK);
					return; // 结束
				}
				pieces[clickId].die();
			}

			pieces[selectedId].setPosition(row, col);
			selectedId = -1;

			// 【关键修改】玩家走完了，交换回合给电脑
			isRedTurn = !isRedTurn;

			draw();           // 在后台画图
			FlushBatchDraw(); // 【新增】立刻把这一帧显示出来！让玩家看到自己走的棋

			// 呼叫电脑
			Sleep(500);       // 现在暂停，玩家就能盯着自己刚走的那步棋看了
			computerMove();

			draw();           // 电脑走完了，再画一次
			FlushBatchDraw(); // 【新增】立刻显示电脑走的棋
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
// 辅助结构体：记录一步棋的信息
struct MoveStep {
	int moveId; // 哪个棋子动
	int killId; // 吃了谁（-1表示没吃）
	int row;    // 去哪里（行）
	int col;    // 去哪里（列）
	int score;  // 这步棋多少分
};

void ChessBoard::computerMove()
{
	// 1. 动态决定电脑该动哪边的棋子
	int startId = 0;
	int endId = 0;

	if (isRedTurn) {
		// 轮到红方走（电脑执红）
		startId = 0;
		endId = 16; // 遍历 0-15
	}
	else {
		// 轮到黑方走（电脑执黑）
		startId = 16;
		endId = 32; // 遍历 16-31
	}

	std::vector<MoveStep> moves;

	// 2. 遍历指定范围的棋子
	for (int i = startId; i < endId; i++) {
		if (pieces[i].isDead()) continue;

		for (int row = 0; row <= 9; row++) {
			for (int col = 0; col <= 8; col++) {
				int killId = getPieceAt(row, col);

				if (canMove(i, killId, row, col)) {
					MoveStep step;
					step.moveId = i;
					step.killId = killId;
					step.row = row;
					step.col = col;
					step.score = 0;

					// --- 评分规则 ---
					if (killId != -1) {
						switch (pieces[killId].getType()) {
						case KING: step.score += 10000; break;
						case ROOK: step.score += 500; break;
						case HORSE: step.score += 300; break;
						case CANNON: step.score += 300; break;
						case ADVISOR: step.score += 200; break;
						case ELEPHANT: step.score += 200; break;
						default: step.score += 100; break;
						}
					}

					// 位置分计算
					if (pieces[i].getType() == SOLDIER) {
						// 注意：SOLDIER_TABLE 是基于红方视角的
						if (isRedTurn) {
							// 电脑执红，直接查表
							step.score += SOLDIER_TABLE[row][col];
						}
						else {
							// 电脑执黑，倒过来查
							step.score += SOLDIER_TABLE[9 - row][col];
						}
					}
					moves.push_back(step);
				}
			}
		}
	}

	if (moves.empty()) return; // 无路可走

	// 3. 挑选分数最高的
	int maxScore = -1;
	std::vector<MoveStep> bestMoves;

	for (const auto& step : moves) {
		if (step.score > maxScore) {
			maxScore = step.score;
			bestMoves.clear();
			bestMoves.push_back(step);
		}
		else if (step.score == maxScore) {
			bestMoves.push_back(step);
		}
	}

	int index = rand() % bestMoves.size();
	MoveStep best = bestMoves[index];

	// 4. 执行这步棋
	if (best.killId != -1) {
		if (pieces[best.killId].getType() == KING) {
			// 吃老帅
			pieces[best.killId].die();
			pieces[best.moveId].setPosition(best.row, best.col);
			draw(); // 必须重绘，让玩家看到最后这一步
			FlushBatchDraw(); // 记得这里也要刷新一下让玩家死个明白
			// 电脑赢了（注意：进入这里说明是当前行动方赢了）
			// 如果 isRedTurn 是 true，说明是红方(电脑)走的这一步赢了
			if (isRedTurn) gameOver(TEAM_RED);
			else gameOver(TEAM_BLACK);

			return;
		}
		pieces[best.killId].die();
	}
	pieces[best.moveId].setPosition(best.row, best.col);
	// 5. 【关键修改】走完后，把回合反转给对面（玩家）
	isRedTurn = !isRedTurn;
}
// 统一的游戏结束处理函数
void ChessBoard::gameOver(PieceColor winner)
{
	// 1. 构造提示语
	LPCTSTR msgContent;
	if (winner == TEAM_RED) {
		msgContent = _T("红方获胜！\n\n是否再来一局？");
	}
	else {
		msgContent = _T("黑方获胜！\n\n是否再来一局？");
	}

	// 2. 弹出选择框
	int ret = MessageBox(GetHWnd(), msgContent, _T("游戏结束"), MB_YESNO | MB_ICONQUESTION);

	// 3. 根据用户选择执行
	if (ret == IDYES) {
		// 选“是” -> 重开
		init();
	}
	else {
		// 选“否” -> 彻底退出程序
		exit(0);
	}
}