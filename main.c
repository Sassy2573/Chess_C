/*************************************************************************
  > File Name: main.c
  > Author: KrisChou
  > Mail:zhoujx0219@163.com
  > Created Time: Wed 03 Sep 2014 10:04:07 PM CST
 ************************************************************************/
#include "chess.h"
#define B_IP "127.0.0.1"
#define B_PORT 8888
#define W_IP "127.0.0.1"
#define W_PORT 6666
#define POS_TRANS(pos)  (pos -1)
#define IS_OK(row, col) (  row >= 0 && col >= 0 && col <= 18 &&row <= 18 &&strcmp(my_chess[row][col], WHITE_CHESS) != 0 && strcmp(my_chess[row][col], BLACK_CHESS) != 0)
int main(int argc, char* argv[])
{
    char my_chess[ROW][COL][4] = 
    {
        "┌","┬","┬","┬","┬","┬","┬","┬","┬","┬","┬","┬","┬","┬","┬","┬","┬","┬","┐" , 
        "├","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┤" ,
        "├","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┤" ,
        "├","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┤" ,
        "├","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┤" ,
        "├","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┤" ,
        "├","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┤" ,
        "├","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┤" ,
        "├","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┤" ,
        "├","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┤" ,
        "├","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┤" ,
        "├","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┤" ,
        "├","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┤" ,
        "├","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┤" ,
        "├","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┤" ,
        "├","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┤" ,
        "├","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┤" ,
        "├","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┼","┤" ,
        "└","┴","┴","┴","┴","┴","┴","┴","┴","┴","┴","┴","┴","┴","┴","┴","┴","┴","┘"   

    };
    int sfd ;
    pTRACE my_tr, peer_tr, pStep, pTmp ;

    my_tr = NULL ;
    peer_tr = NULL ;
#ifdef FIRST
    my_socket(&sfd, MY_UDP, B_IP, B_PORT);
#else
    my_socket(&sfd, MY_UDP, W_IP, W_PORT);
#endif
    int row, col ;
    MSG my_msg ;
#ifdef FIRST
    chess_show(my_chess, ROW);
    while(1)// 0, 0
    {
        do
        {
            printf(">>");
            scanf("%d%d", &row, &col);
            if(row == 0 || col == 0)
            {
                break ;
            }
        }while( !IS_OK(POS_TRANS(row), POS_TRANS(col))) ;
        if(row !=0 && col != 0)// normal
        {
            my_msg.msg_type = MSG_NORMAL ;
            my_msg.msg_color = CH_BLACK ;
            my_msg.msg_row = POS_TRANS(row) ;
            my_msg.msg_col = POS_TRANS(col) ;
            my_sendto(NULL, sfd, &my_msg, sizeof(MSG), W_IP, W_PORT);

            pStep = (pTRACE)calloc(1, sizeof(TRACE)) ;
            pStep ->tr_row = POS_TRANS(row) ;
            pStep ->tr_col = POS_TRANS(col) ;
            strcpy(pStep ->tr_before, my_chess[POS_TRANS(row)][POS_TRANS(col)]) ;

            pStep -> tr_next = my_tr ;
            my_tr = pStep ;

            strcpy(my_chess[POS_TRANS(row)][POS_TRANS(col)], BLACK_CHESS);


            system("clear");
            chess_show(my_chess, ROW);
            if(chess_win(my_chess, ROW, POS_TRANS(row), POS_TRANS(col), BLACK_CHESS))
            {
                printf("black win !");
                exit(1);
            }
        }else 
        {
            if(my_tr == NULL)
            {
                continue ;
            }else
            {
                memset(&my_msg, 0, sizeof(MSG));
                my_msg.msg_type = MSG_BACK ;
                my_sendto(NULL, sfd, &my_msg, sizeof(MSG), W_IP, W_PORT);
                strcpy(my_chess[my_tr -> tr_row][my_tr -> tr_col], my_tr ->tr_before);
                system("clear");
                chess_show(my_chess, ROW);

                pTmp = my_tr ;
                my_tr = my_tr -> tr_next ;
                free(pTmp);
                pTmp = NULL ;

                /* 本方悔棋后，需要在下一次 */
                do{
                    printf(">>");
                    scanf("%d%d", &row, &col);
                }while( !IS_OK(POS_TRANS(row), POS_TRANS(col))) ;


                my_msg.msg_type = MSG_NORMAL ;
                my_msg.msg_color = CH_BLACK ;
                my_msg.msg_row = POS_TRANS(row) ;
                my_msg.msg_col = POS_TRANS(col) ;
                my_sendto(NULL, sfd, &my_msg, sizeof(MSG), W_IP, W_PORT);

                pStep = (pTRACE)calloc(1, sizeof(TRACE)) ;
                pStep ->tr_row = POS_TRANS(row) ;
                pStep ->tr_col = POS_TRANS(col) ;
                strcpy(pStep ->tr_before, my_chess[POS_TRANS(row)][POS_TRANS(col)]) ;

                pStep -> tr_next = my_tr ;
                my_tr = pStep ;

                strcpy(my_chess[POS_TRANS(row)][POS_TRANS(col)], BLACK_CHESS);


                system("clear");
                chess_show(my_chess, ROW);
                if(chess_win(my_chess, ROW, POS_TRANS(row), POS_TRANS(col), BLACK_CHESS))
                {
                    printf("black win !");
                    exit(1);
                }

            }
        }

        memset(&my_msg, 0, sizeof(MSG));
        my_recvfrom(NULL, sfd, &my_msg, sizeof(MSG), NULL, NULL);    
        if(my_msg.msg_type == MSG_NORMAL)
        {
            pStep = (pTRACE)calloc(1, sizeof(TRACE)) ;
            pStep ->tr_row = my_msg.msg_row ;
            pStep ->tr_col = my_msg.msg_col ;
            strcpy(pStep ->tr_before, my_chess[my_msg.msg_row][my_msg.msg_col]) ;
            pStep -> tr_next = peer_tr; 
            peer_tr = pStep ;


            strcpy(my_chess[my_msg.msg_row][my_msg.msg_col], WHITE_CHESS);
            system("clear");
            chess_show(my_chess, ROW);
            if(chess_win(my_chess, ROW, my_msg.msg_row, my_msg.msg_col, WHITE_CHESS))
            {
                printf("white win !");
                exit(1);
            }
        }else if(my_msg.msg_type == MSG_BACK)
        {
                strcpy(my_chess[peer_tr -> tr_row][peer_tr -> tr_col], peer_tr ->tr_before);
                system("clear");
                chess_show(my_chess, ROW);

                pTmp = peer_tr ;
                peer_tr = peer_tr -> tr_next ;
                free(pTmp);
                pTmp = NULL ;
                
                /* 对方悔棋后，本方需要再收一次 */
                memset(&my_msg, 0, sizeof(MSG));
                my_recvfrom(NULL, sfd, &my_msg, sizeof(MSG), NULL, NULL);    

                pStep = (pTRACE)calloc(1, sizeof(TRACE)) ;
                pStep ->tr_row = my_msg.msg_row ;
                pStep ->tr_col = my_msg.msg_col ;
                strcpy(pStep ->tr_before, my_chess[my_msg.msg_row][my_msg.msg_col]) ;
                pStep -> tr_next = peer_tr; 
                peer_tr = pStep ;

                strcpy(my_chess[my_msg.msg_row][my_msg.msg_col], WHITE_CHESS);
                system("clear");
                chess_show(my_chess, ROW);
                if(chess_win(my_chess, ROW, my_msg.msg_row, my_msg.msg_col, WHITE_CHESS))
                {
                    printf("white win !");
                    exit(1);
                }
        }
    }
#else
    {
        chess_show(my_chess, ROW);
        while(1)
        {
            memset(&my_msg, 0, sizeof(MSG));
            my_recvfrom(NULL, sfd, &my_msg, sizeof(MSG), NULL, NULL);
            if(my_msg.msg_type == MSG_NORMAL)
            {

                pStep = (pTRACE)calloc(1, sizeof(TRACE)) ;
                pStep ->tr_row = my_msg.msg_row ;
                pStep ->tr_col = my_msg.msg_col ;
                strcpy(pStep ->tr_before, my_chess[my_msg.msg_row][my_msg.msg_col]) ;
                pStep -> tr_next = peer_tr; 
                peer_tr = pStep ;



                strcpy(my_chess[my_msg.msg_row][my_msg.msg_col], BLACK_CHESS);
                system("clear");
                chess_show(my_chess, ROW);
                if(chess_win(my_chess, ROW, my_msg.msg_row, my_msg.msg_col, BLACK_CHESS))
                {
                    printf("black win !");
                    exit(1);
                }

            }else if(my_msg.msg_type ==  MSG_BACK)
            {
                strcpy(my_chess[peer_tr -> tr_row][peer_tr -> tr_col], peer_tr ->tr_before);
                system("clear");
                chess_show(my_chess, ROW);

                pTmp = peer_tr ;
                peer_tr = peer_tr -> tr_next ;
                free(pTmp);
                pTmp = NULL ;

                memset(&my_msg, 0, sizeof(MSG));
                my_recvfrom(NULL, sfd, &my_msg, sizeof(MSG), NULL, NULL);    

                pStep = (pTRACE)calloc(1, sizeof(TRACE)) ;
                pStep ->tr_row = my_msg.msg_row ;
                pStep ->tr_col = my_msg.msg_col ;
                strcpy(pStep ->tr_before, my_chess[my_msg.msg_row][my_msg.msg_col]) ;
                pStep -> tr_next = peer_tr; 
                peer_tr = pStep ;

                strcpy(my_chess[my_msg.msg_row][my_msg.msg_col], BLACK_CHESS);
                system("clear");
                chess_show(my_chess, ROW);
                if(chess_win(my_chess, ROW, my_msg.msg_row, my_msg.msg_col, BLACK_CHESS))
                {
                    printf("black win !");
                    exit(1);
                }


            }

                do{
                    printf(">>");
                    scanf("%d%d", &row, &col);
                    if(row == 0 || col == 0)
                    {
                        break ;
                    }
                }while(!IS_OK(POS_TRANS(row), POS_TRANS(col))) ;
                if(row != 0 && col != 0 )//normal
                {
                    my_msg.msg_type = MSG_NORMAL ;
                    my_msg.msg_color = CH_WHITE ;
                    my_msg.msg_row = POS_TRANS(row) ;
                    my_msg.msg_col = POS_TRANS(col) ;
                    my_sendto(NULL, sfd, &my_msg, sizeof(MSG), B_IP, B_PORT);


                    pStep = (pTRACE)calloc(1, sizeof(TRACE)) ;
                    pStep ->tr_row = POS_TRANS(row) ;
                    pStep ->tr_col = POS_TRANS(col) ;
                    strcpy(pStep ->tr_before, my_chess[POS_TRANS(row)][POS_TRANS(col)]) ;

                    pStep -> tr_next = my_tr ;
                    my_tr = pStep ;

                    strcpy(my_chess[POS_TRANS(row)][POS_TRANS(col)], WHITE_CHESS);
                    system("clear");
                    chess_show(my_chess, ROW);
                    if(chess_win(my_chess, ROW, POS_TRANS(row), POS_TRANS(col), WHITE_CHESS))
                    {
                        printf("white win !");
                        exit(1);
                    }

                }else
                {
                    if(my_tr == NULL)
                    {
                        continue ;
                    }else
                    {
                        memset(&my_msg, 0, sizeof(MSG));
                        my_msg.msg_type = MSG_BACK ;
                        my_sendto(NULL, sfd, &my_msg, sizeof(MSG), B_IP, B_PORT);
                        strcpy(my_chess[my_tr -> tr_row][my_tr -> tr_col], my_tr ->tr_before);
                        system("clear");
                        chess_show(my_chess, ROW);

                        pTmp = my_tr ;
                        my_tr = my_tr -> tr_next ;
                        free(pTmp);
                        pTmp = NULL ;
                        
                        do{
                            printf(">>");
                            scanf("%d%d", &row, &col);
                        }while(!IS_OK(POS_TRANS(row), POS_TRANS(col)) );
                            
                    my_msg.msg_type = MSG_NORMAL ;
                    my_msg.msg_color = CH_WHITE ;
                    my_msg.msg_row = POS_TRANS(row) ;
                    my_msg.msg_col = POS_TRANS(col) ;
                    my_sendto(NULL, sfd, &my_msg, sizeof(MSG), B_IP, B_PORT);


                    pStep = (pTRACE)calloc(1, sizeof(TRACE)) ;
                    pStep ->tr_row = POS_TRANS(row) ;
                    pStep ->tr_col = POS_TRANS(col) ;
                    strcpy(pStep ->tr_before, my_chess[POS_TRANS(row)][POS_TRANS(col)]) ;

                    pStep -> tr_next = my_tr ;
                    my_tr = pStep ;

                    strcpy(my_chess[POS_TRANS(row)][POS_TRANS(col)], WHITE_CHESS);
                    system("clear");
                    chess_show(my_chess, ROW);
                    if(chess_win(my_chess, ROW, POS_TRANS(row), POS_TRANS(col), WHITE_CHESS))
                    {
                        printf("white win !");
                        exit(1);
                    }

                    }
                    
                }
        }

    }
#endif
    return 0 ;
}