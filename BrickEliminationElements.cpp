/* BrickEliminationElements.cpp */

#include "BrickElimination.h"
#include <graphics.h>
#include <conio.h>
#include "windows.h"

/* class ball realization */
CBall::CBall()
{
}

CBall::~CBall()
{
}

void CBall::ball_init_v()
{
    m_ball_x = GRAPH_WIDTH / 2;
    m_ball_y = GRAPH_HEIGHT / 2;
    m_ball_vx = BALL_MOVE_SPEED;
    m_ball_vy = BALL_MOVE_SPEED;
    m_radius = BALL_RADIUS;
}

void CBall::ball_clean_v()
{
    setcolor(BLACK);
    setfillcolor(BLACK);
    fillcircle(m_ball_x, m_ball_y, m_radius);
}

void CBall::ball_show_v()
{
    setcolor(YELLOW);
    setfillcolor(GREEN);
    fillcircle(m_ball_x, m_ball_y, m_radius);
}

void CBall::ball_move_v()
{
    m_ball_x += m_ball_vx;
    m_ball_y += m_ball_vy;
}

/* class brick realization */
CBrick::CBrick()
{
}

CBrick::~CBrick()
{
}

void CBrick::brick_init_v()
{
    m_brick_width = GRAPH_WIDTH / BRICK_NUM;
    m_brick_height = GRAPH_HEIGHT / BRICK_NUM;

    for (int i = 0; i < BRICK_NUM; i++)
    {
        Bricks[i].left = i * m_brick_width;
        Bricks[i].right = Bricks[i].left + m_brick_width;
        Bricks[i].top = 0;
        Bricks[i].bottom = m_brick_height;
        m_isBrickExisted[i] = BRICK_EXIST;
    }
}

void CBrick::brick_clean_v()
{
    setcolor(BLACK);
    setfillcolor(BLACK);

    for (int i = 0; i < BRICK_NUM; i++)
    {
        if (m_isBrickExisted[i] == BRICK_NOT_EXIST)
        {
            fillrectangle(Bricks[i].left, Bricks[i].top, Bricks[i].right, Bricks[i].bottom);
        }
        else
        {
            /* do thing */
        }
    }
}

void CBrick::brick_show_v()
{
    for (int i = 0; i < BRICK_NUM; i++)
    {
        if (m_isBrickExisted[i])
        {
            setcolor(WHITE);
            setfillcolor(RED);
            fillrectangle(Bricks[i].left, Bricks[i].top, Bricks[i].right, Bricks[i].bottom);
        }
        else
        {
            /* do thing */
        }
    }
}

/* class bar realization */
CBar::CBar()
{
}

CBar::~CBar()
{
}

void CBar::bar_init_v()
{
    m_bar_width = BAR_WIDTH;
    m_bar_height = GRAPH_HEIGHT / 20;
    m_bar_x = GRAPH_WIDTH / 2;
    m_bar_y = GRAPH_HEIGHT - m_bar_height / 2;
    m_bar_left = m_bar_x - m_bar_width / 2;
    m_bar_right = m_bar_x + m_bar_width / 2;
    m_bar_top = m_bar_y - m_bar_height / 2;
    m_bar_bottom = m_bar_y + m_bar_height / 2;
}

void CBar::bar_clean_v()
{
    setcolor(BLACK);
    setfillcolor(BLACK);
    bar(m_bar_left, m_bar_top, m_bar_right, m_bar_bottom);
}

void CBar::bar_show_v()
{
    setcolor(YELLOW);
    setfillcolor(GREEN);
    bar(m_bar_left, m_bar_top, m_bar_right, m_bar_bottom);
}

void CBar::bar_move_v()
{
    char input;
    if (_kbhit())
    {
        input = _getch();
        if (input == 'a' && m_bar_left > 0)
        {
            m_bar_x -= BAR_MOVE_SPEED;
            m_bar_left = m_bar_x - m_bar_width / 2;
            m_bar_right = m_bar_x + m_bar_width / 2;
        }
        else if (input == 'd' && m_bar_right < GRAPH_WIDTH)
        {
            m_bar_x += BAR_MOVE_SPEED;
            m_bar_left = m_bar_x - m_bar_width / 2;
            m_bar_right = m_bar_x + m_bar_width / 2;
        }
        else
        {
            /* do thing */
        }
    }
    else
    {
        /* do thing */
    }
}

GameBrickElimination::GameBrickElimination()
{
}

GameBrickElimination::~GameBrickElimination()
{
}

Ball_Hit_Type GameBrickElimination::check_ball_hit(Ball_Hit_Type isHit)
{
    switch (isHit)
    {
    case Ball_Hit_Wall:
    {
        //check ball hit wall or not
        if ((ball.get_x() <= ball.get_r()) || (ball.get_x() >= GRAPH_WIDTH - ball.get_r()))
        {
            ball.set_vx(-ball.get_vx());
            return Ball_Hit_Wall;
        }
        else
        {
            /* do nothing */
        }

        if ((ball.get_y() <= ball.get_r()) || (ball.get_y() >= GRAPH_HEIGHT - ball.get_r()))
        {
            ball.set_vy(-ball.get_vy());
            return Ball_Hit_Wall;
        }
        else
        {
            /* do nothing */
        }
        break;
    }
    case Ball_Hit_Bar:
    {
        if (((ball.get_y() + ball.get_r() >= bar.get_top())
            && (ball.get_y() + ball.get_r() < bar.get_bottom() - bar.get_height() / 3))
            || ((ball.get_y() - ball.get_r() <= bar.get_bottom())
                && (ball.get_y() - ball.get_r() > bar.get_top() - bar.get_height() / 3)))
        {
            if ((ball.get_x() > bar.get_left()) && (ball.get_x() < bar.get_right()))
            {
                ball.set_vy(-ball.get_vy());
                return Ball_Hit_Bar;
            }
            else
            {
                /* do nothing */
            }
        }
        else
        {
            /* do nothing */
        }
        break;
    }
    case Ball_Hit_Brick:
    {
        for (int i = 0; i < BRICK_NUM; i++)
        {
            if (brick.isBrickExist(i) == BRICK_EXIST)
            {
                if ((ball.get_y() <= brick.bricks_bottom(i) + ball.get_r())
                    && (ball.get_x() >= brick.bricks_left(i))
                    && (ball.get_x() <= brick.bricks_right(i)))
                {
                    brick.setBrickExist(i, BRICK_NOT_EXIST);
                    ball.set_vy(-ball.get_vy());
                    return Ball_Hit_Brick;
                }
                else
                {
                    /* do nothing */
                }
            }
            else
            {
                /* do nothing */
            }
        }
        break;
    }
    default:
    {
        break;
    }
    }
}

/* class game realization */
void GameBrickElimination::game_start()
{
    ball.ball_init_v();
    bar.bar_init_v();
    brick.brick_init_v();

    initgraph(GRAPH_WIDTH, GRAPH_HEIGHT);
    BeginBatchDraw();
}

void GameBrickElimination::game_run()
{
    while (1)
    {
        ball.ball_clean_v();
        bar.bar_clean_v();
        brick.brick_clean_v();

        check_ball_hit(Ball_Hit_Wall);
        ball.ball_move_v();

        check_ball_hit(Ball_Hit_Bar);
        bar.bar_move_v();

        check_ball_hit(Ball_Hit_Brick);

        ball.ball_show_v();
        bar.bar_show_v();
        brick.brick_show_v();

        FlushBatchDraw();
        Sleep(3);
    }
}

void GameBrickElimination::game_over()
{
    EndBatchDraw();
    closegraph();
}