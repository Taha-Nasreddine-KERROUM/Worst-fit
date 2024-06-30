#include<stdio.h>

typedef struct {
    int size;
    int rank;
    int alloc;
} modint;


void BestFit ( int *p, int pn, modint *b, int bn ) {
    for ( int i = 0; i < pn; ++i )
        for ( int j = 0; j < bn; ++j )
            if ( b[j].size >= p[i] && b[j].alloc == -1 ) {
                b[j].size -= p[i];
                b[j].alloc = i;
                break;
            }
}

void swap ( modint *b, modint *baby ) {
    modint temp = *b;
    *b = *baby;
    *baby = temp;
}

void sort ( modint *b, int bn ) {
    for ( int i = 0; i < bn - 1; ++i )
        for ( int j = 0; j < bn - 1; ++j )
            if ( b[j].size < b[j+1].size )
                swap( b + j, b + j + 1 );
}

void anti_sort ( modint *b, int bn ) {
    for ( int i = 0; i < bn - 1; ++i )
        for ( int j = 0; j < bn - 1; ++j )
            if ( b[j].rank > b[j+1].rank )
                swap( b + j, b + j + 1 );
}

int internal_Frag ( modint *b, int bn ) {
    int frag = 0;
    for ( int i = 0; i < bn; ++i )
            frag += b[i].size;
    return frag;
}

int main() {
    modint b[10] = {0};
    int p[10] = {0},
        pnum, bnum;
        
    for(int i = 0; i < 10; i++)
        b[i].alloc = -1;
        
    printf("- no of process: ");
    scanf("%d", &pnum);
    
    printf("- no of blocks: ");
    scanf("%d", &bnum);
    
    printf("- Size of each process:\n");
    for(int i = 0; i < pnum; i++) {
        printf("\tProcess %d: ", i);
        scanf("%d", p + i);
    }
    
    printf("- block sizes:\n");
    for(int i = 0; i < bnum; i++) {
        printf("\tBlock %d: ", i);
        scanf("%d", &b[i].size);
        b[i].rank = i;
    }
    
    sort(b, bnum);
    BestFit(p, pnum, b, bnum);
    anti_sort(b, bnum);
    
    printf("\nBlock Allocation:");
    for(int i = 0; i < bnum; i++) {
        printf("\nBlock %d -> ", i, b[i].rank);
        if(b[i].alloc != -1) {
            printf("Process %d", b[i].alloc);
        } else {
            printf("free");
        }
    }
    
    printf("\n\nInternal Fragmentation: %d\n", internal_Frag(b, bnum));
    
    return 0;
}
