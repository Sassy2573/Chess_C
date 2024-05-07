/*
 * @Author: Chenyinlin
 * @Date: 2024-05-07 02:18:22
 * @LastEditTime: 2024-05-07 02:21:29
 * @FilePath: /home/chen/Desktop/Project/Chess_C/chess.h
 * @Description: 
 * 
 * @Format: 
 * Copyright (c) 2024 by Sassy, All Rights Reserved. 
 */
#ifndef __MY_CHESS_H__
#define __MY_CHESS_H__
#include "my_socket.h"
#include <pthread.h>

#define MSG_NORMAL 1
#define MSG_BACK  2
#define CH_BLACK 1
#define CH_WHITE 2
#define ROW 19
#define COL 19
#define WHITE_CHESS    "○"
#define BLACK_CHESS     "●"

typedef struct tag_msg
{
    int msg_type ;
    int msg_color ;
    int msg_row ;
    int msg_col ;
}MSG, *pMSG ;

typedef struct tag_trace
{
    int tr_row ;
    int tr_col ;
    char tr_before[4] ;
    struct tag_trace* tr_next ;
}TRACE, *pTRACE;

void chess_show(char ch[][COL][4], int row);
int chess_win(char arr[][COL][4], int row, int pos_x, int pos_y, char* color);

#endif