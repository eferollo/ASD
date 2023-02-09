#include <stdio.h>
#include <stdlib.h>
#define filename "tiles.txt"
#define filename1 "board.txt"

typedef struct{
    char c1, c2;
    int v1,v2;
}tiles_t;

typedef struct{
    int tile;
    int rot;
}board_t;

tiles_t *readTiles(int *N);
board_t *readBoard(int *nr, int *nc, int *mark);
void disp_sempl(int pos, tiles_t *t, board_t *board, board_t *sol, int *mark, int n, int nr, int nc, int j, int *max);
void alg_wrapper(tiles_t *tiles, board_t *board, int n_t, int nr, int nc, int *mark);
int calc_maxBoard(board_t *b, tiles_t *t, int nr, int nc);
void printSol(tiles_t *t, board_t *b, int nr, int nc);

int main() {
    int n_t, nr,nc;
    tiles_t *tiles= readTiles(&n_t);
    int *mark=(int *)calloc(n_t,sizeof(int));
    board_t *board=readBoard(&nr,&nc, mark);
    alg_wrapper(tiles,board,n_t,nc,nr, mark);
    return 0;
}

int calc_maxBoard(board_t *b, tiles_t *t, int nr, int nc){
    int i,j,val_r, val_c, sum=0;
    char c;
    for(i=0; i<nr*nc; i=i+nc){
        if(b[i].rot==0) {
            c = t[b[i].tile].c1;
            val_r = t[b[i].tile].v1;
        }
        else{
            c=t[b[i].tile].c2;
            val_r=t[b[i].tile].v2;
        }
        for(j=i+1; j<i+nc; j++){
            if(b[j].rot==0){
                if(t[b[j].tile].c1 == c)
                    val_r+=t[b[j].tile].v1;
                else break;
            }else{
                if(t[b[j].tile].c2 == c)
                    val_r+=t[b[j].tile].v2;
                else break;
            }
        }
        if(j==nr) sum+=val_r;
    }
    for(i=0; i<nc; i++){
        if(b[i].rot==0) {
            c = t[b[i].tile].c2;
            val_c = t[b[i].tile].v2;
        }
        else{
            c=t[b[i].tile].c1;
            val_c=t[b[i].tile].v1;
        }
        for(j=i+nc; j<nr*nc; j=j+nc){
            if(b[j].rot==0){
                if(t[b[j].tile].c2 == c)
                    val_c+=t[b[j].tile].v2;
                else break;
            }else{
                if(t[b[j].tile].c1 == c)
                    val_c+=t[b[j].tile].v1;
                else break;
            }
        }
        if(j/nc==nc) sum+=val_c;
    }
    return sum;
}

void disp_sempl(int pos, tiles_t *t, board_t *board, board_t *sol, int *mark, int n, int nr, int nc , int j, int *max){
    int i, max_tmp;
    if(pos >= nr*nc){
        max_tmp=calc_maxBoard(board,t, nr, nc);
        if(max_tmp>*max){
            *max=max_tmp;
            for(i=0;i<nr*nc;i++)
                sol[i]=board[i];
        }
        return;
    }
    if(board[j].tile==-1){
        for(i=0; i<n; i++){
            if(!mark[i]){
                mark[i]=1;
                board[j].tile=i;
                board[j].rot=0;
                disp_sempl(pos+1, t,board,sol,mark,n,nr, nc,j+1,max);
                board[j].rot=1;
                disp_sempl(pos+1, t,board,sol,mark,n,nr, nc,j+1,max);
                board[j].tile=-1;
                mark[i]=0;
            }
        }
    }else
        disp_sempl(pos+1, t,board,sol,mark,n,nr, nc,j+1,max);
}

void printSol(tiles_t *t, board_t *b, int nr, int nc){
    int i;
    for(i=0;i<nr*nc; i++){
        if(i%nc==0 && i!=0) printf("\n");
        if(b[i].rot==0) printf("(%c %d) (%c %d) | ", t[b[i].tile].c1, t[b[i].tile].v1, t[b[i].tile].c2, t[b[i].tile].v2);
        else printf("(%c %d) (%c %d) | ", t[b[i].tile].c2, t[b[i].tile].v2, t[b[i].tile].c1, t[b[i].tile].v1);
    }
}

void alg_wrapper(tiles_t *tiles, board_t *board, int n_t, int nr, int nc, int *mark){
    board_t *sol=malloc(nr*nc* sizeof(board_t));
    int max=0;
    disp_sempl(0, tiles, board, sol, mark, n_t, nr, nc, 0, &max);
    printSol(tiles,sol,nr,nc);
    free(sol);
    free(board);
    free(tiles);
    free(mark);
}

tiles_t *readTiles(int *N){
    FILE *fp;
    fp= fopen(filename, "r");
    if(fp==NULL){
        printf("Error while opening file\n");
        exit(-1);
    }
    int i,n;
    fscanf(fp,"%d", &n);
    *N=n;
    tiles_t *tiles=(tiles_t *)malloc(n* sizeof(tiles_t));
    for(i=0;i<n;i++)
        fscanf(fp," %c %d %c %d", &tiles[i].c1, &tiles[i].v1, &tiles[i].c2, &tiles[i].v2);

    fclose(fp);
    return tiles;
}

board_t *readBoard(int *nr, int *nc, int *mark){
    FILE *fp;
    fp= fopen(filename1,"r");
    if(fp==NULL){
        printf("Error while opening file\n");
        exit(-1);
    }
    int i,r,c;
    fscanf(fp,"%d %d", &r,&c);
    *nr=r; *nc=c;
    board_t *board=(board_t *)malloc(r*c*sizeof(board_t));
    for(i=0; i<r*c; i++){
        fscanf(fp, "%d/%d", &board[i].tile, &board[i].rot);
        if(board[i].tile!=-1)
            mark[board[i].tile]=1;
    }
    fclose(fp);
    return board;
}