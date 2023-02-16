#include "data.h"

extern Mat mapgraphic;
extern Mat HEAD;
extern Mat HEADNOW;
extern int gamemode;
extern int timecounter; //�ý��� �ð� �帧
extern int field[MAPSIZE][MAPSIZE]; //��
extern int snakelong[MAPSIZE * MAPSIZE][6]; //rows - �� �ִ����, cols - ���� ���𸶴� x�� y��ǥ, rows�� 0�̸� ������� 1�̸� ��������
extern int speed; // ���̵��ӵ�1~10�ܰ�� 1���� 10��� 1000 ~ 100
extern int score;// �� ��Ƹ��� ������
extern int direction;
extern int block;
extern int key;
extern int rocknum;

extern void getkey(); //waitKey���
extern void graphic(); //�׷���ó��
extern void logographic(); //���۽� �߰� �׷���
extern void mice(); //���� ���� ����
extern void ROCK(); //��ֹ� ���� ����
extern void fieldcheck();
extern void snakebody(); //�� ���� �� ��ǥ
extern void snakemove();
extern void mouse_callback(int event, int x, int y, int flags, void* userdata); //���콺 Ŭ�� �̺�Ʈ
extern void gameover();
int main()
{
    while (1)
    {
        if (gamemode == 0)
        {
            score = 0;
            rocknum = 0;
            direction = 3;
            fill(&field[0][0], &field[MAPSIZE - 1][MAPSIZE - 1], 0);
            HEADNOW = HEAD;
            snakelong[0][1] = 9;
            snakelong[0][2] = 9;
            snakelong[1][1] = 8;
            snakelong[1][2] = 9;
            snakelong[2][1] = 7;
            snakelong[2][2] = 9;
            snakelong[3][1] = 6;
            snakelong[3][2] = 9;
            fill(&snakelong[4][0], &snakelong[MAPSIZE * MAPSIZE - 1][5], -1);
            field[13][9] = 1;
            gamemode = 1;
        }
        while (gamemode == 1)
        {
            graphic();
            logographic();
            getkey();
            if (key == 27)
                return 0;
        }

        while (gamemode == 2)
        {
            getkey();
            if (key == 27)
                return 0;
            snakemove();
            if (key == 'D') //Dead or score 396(end)
            {
                gamemode = 3;
                break;
            }
            snakebody();
            if (score + 4 + rocknum == MAPSIZE * MAPSIZE)
            {
                gamemode = 3;
                break;
            }
            fieldcheck();
            ROCK();
            mice();
            graphic();
        }


        while (gamemode == 3)
        {
            gameover();
            key = waitKey(0);
            if (key == 27 || key == 'r' || key == 'R')
                break;
        }
        if (key == 27)
            break;
        else if (key == 'r' || key == 'R')
        {
            gamemode = 0;
            continue;
        }
    }
    destroyAllWindows();
}