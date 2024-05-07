/*************************************************************************
    > File Name: chess.c
    > Author: KrisChou
    > Mail:zhoujx0219@163.com 
    > Created Time: Wed 03 Sep 2014 09:35:57 PM CST
 ************************************************************************/
#include "chess.h"

void chess_show(char arr[][COL][4], int row_cnt)
{
    int row, col  ; 
    printf("   ");
    for(col = 0; col < COL ; col ++)
    {
        printf("%2d", col + 1);
    }
    printf("\n");
    for(row = 0; row < row_cnt ; row ++)
    {
        printf("%3d ", row + 1);
        for(col = 0; col < COL ; col ++)
        {
            printf("%s",  arr[row][col]);
            if(col != row_cnt  -1 )
            {
                printf("-");
            }
        }
        printf("\n");
    }
    printf("\n");
    
}
int chess_win(char arr[][COL][4], int row, int pos_x, int pos_y, char* color)
{    
    // level
    int cnt1, cnt2 ;
    int index_x, index_y ;
    for(cnt1 = 0,index_x = pos_x, index_y = pos_y; index_y < COL; index_y ++)
    {
        if(strcmp(arr[index_x][index_y], color) == 0)
        {
            cnt1 ++ ;
        }else
        {
            break ;
        }
    }
    for(cnt2 = 0, index_x = pos_x , index_y = pos_y - 1 ; index_y >= 0; index_y --)
    {
        if(strcmp(arr[index_x][index_y], color) == 0)
        {
            cnt2 ++ ;
        }else
        {
            break ;
        }
    }
    if(cnt1 + cnt2 >= 5)
    {
        return 1 ;
    }
    // vertical
    for(cnt1 = 0,index_x = pos_x, index_y = pos_y; index_x >= 0; index_x --)
    {
        if(strcmp(arr[index_x][index_y], color) == 0)
        {
            cnt1 ++ ;
        }else
        {
            break ;
        }
    }
    for(cnt2 = 0, index_x = pos_x + 1 , index_y = pos_y  ; index_x < row ; index_x ++)
    {
        if(strcmp(arr[index_x][index_y], color) == 0)
        {
            cnt2 ++ ;
        }else
        {
            break ;
        }
    }
    if(cnt1 + cnt2 >= 5)
    {
        return 1 ;
    }
    // + ==
    int sum = pos_x + pos_y ;
    for(cnt1 = 0, index_x = pos_x; index_x >= 0 && sum - index_x < COL; index_x --)
    {
        if(strcmp(arr[index_x][sum - index_x], color) == 0)
        {
            cnt1 ++ ;
        }else
        {
            break ;
        }
    }
    for(cnt2 = 0, index_x = pos_x + 1; index_x < row && index_x <= sum ; index_x ++ )
    {
        if(strcmp(arr[index_x][sum - index_x], color) == 0)
        {
            cnt2 ++ ;
        }else 
        {
            break ;
        }
    }
    if(cnt1 + cnt2 >= 5)
    {
        return 1 ;
    }
    // abs - ==
    int delt ;
    if(pos_x > pos_y)
    {
        delt = pos_x - pos_y ;
        for(cnt1 = 0 , index_x = pos_x; index_x >=0 && index_x >= delt; index_x --)
        {
            if(strcmp(arr[index_x][index_x - delt], color) == 0)
            {
                cnt1 ++ ;
            }else 
            {
                break ;
            }
        }
        for(cnt2 = 0, index_x = pos_x + 1; index_x < row ; index_x ++)
        {
            if(strcmp(arr[index_x][index_x - delt], color) == 0)
            {
                cnt2 ++ ;
            }else 
            {
                break ;
            }
        }
    }else// pos_y >= pos_x 
    {
        delt = pos_y - pos_x ;
        for(cnt1 = 0 , index_x = pos_x; index_x >=0 ; index_x --)
        {
            if(strcmp(arr[index_x][index_x +  delt], color) == 0)
            {
                cnt1 ++ ;
            }else 
            {
                break ;
            }
        }
        for(cnt2 = 0, index_x = pos_x + 1; index_x < row && index_x + delt < COL ; index_x ++)
        {
            if(strcmp(arr[index_x][index_x + delt], color) == 0)
            {
                cnt2 ++ ;
            }else 
            {
                break ;
            }
        }
    }
    if(cnt1 + cnt2 >= 5)
    {
        return 1 ;
    }
    return 0;
}