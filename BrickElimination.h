#ifndef _BRICK_ELIMINATION_
#define _BRICK_ELIMINATION_

/* Settings */
#define GRAPH_HEIGHT                    480
#define GRAPH_WIDTH                     720
#define BRICK_NUM                       20
#define BAR_MOVE_SPEED                  15
#define BAR_WIDTH                       (GRAPH_WIDTH/5)
#define BALL_MOVE_SPEED                 1
#define BALL_RADIUS                     20

#define BRICK_EXIST                     1
#define BRICK_NOT_EXIST                 0


/* type define */
typedef enum
{
    Ball_Hit_Wall = 0,
    Ball_Hit_Bar,
    Ball_Hit_Brick,
    Ball_Sill_Moving
}Ball_Hit_Type;

typedef struct
{
    int left;
    int right;
    int top;
    int bottom;
}Brick_Group;


/* class ball define */
class CBall
{
private:
    int m_ball_x, m_ball_y;
    int m_ball_vx, m_ball_vy;
    int m_radius;

public:
    CBall();
    ~CBall();
    void ball_init_v();
    void ball_clean_v();
    void ball_show_v();
    void ball_move_v();
    int get_x() { return m_ball_x; };
    int get_y() { return m_ball_y; };
    int get_r() { return m_radius; };
    int get_vx() { return m_ball_vx; };
    int get_vy() { return m_ball_vy; };
    void set_vx(int vx) { m_ball_vx = vx; };
    void set_vy(int vy) { m_ball_vy = vy; };

};

/* class brick define */
class CBrick
{
private:
    Brick_Group Bricks[BRICK_NUM];
    int m_isBrickExisted[BRICK_NUM];
    int m_brick_height, m_brick_width;

public:
    CBrick();
    ~CBrick();
    void brick_init_v();
    void brick_clean_v();
    void brick_show_v();
    int isBrickExist(int i) { return m_isBrickExisted[i]; };
    void setBrickExist(int i, int state) { m_isBrickExisted[i] = state; };
    int bricks_left(int i) { return Bricks[i].left; };
    int bricks_right(int i) { return Bricks[i].right; };
    int bricks_top(int i) { return Bricks[i].top; };
    int bricks_bottom(int i) { return Bricks[i].bottom; };
};

/* class bar define */
class CBar
{
private:
    int m_bar_x, m_bar_y;
    int m_bar_width, m_bar_height;
    int m_bar_left, m_bar_right, m_bar_top, m_bar_bottom;

public:
    CBar();
    ~CBar();
    void bar_init_v();
    void bar_clean_v();
    void bar_show_v();
    void bar_move_v();
    int get_left() { return m_bar_left; };
    int get_right() { return m_bar_right; };
    int get_top() { return m_bar_top; };
    int get_bottom() { return m_bar_bottom; };
    int get_width() { return m_bar_width; };
    int get_height() { return m_bar_height; };
};

/* class game define */
class GameBrickElimination
{
private:
    CBall ball;
    CBar bar;
    CBrick brick;

public:
    GameBrickElimination();
    ~GameBrickElimination();
    Ball_Hit_Type check_ball_hit(Ball_Hit_Type isHit);
    void game_start();
    void game_run();
    void game_over();
};

#endif