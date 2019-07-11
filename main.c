#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "splaytree.h"

static void splay_traverse(SplayNode *node){
    printf("%d ", node->series.id);
}

void splaytree(void){
    SplayTree *splaytree = splaytree_init();
    Series s1;
    s1.id = 1;
    strcpy(s1.title, "Game of Thrones");
    strcpy(s1.introduction, "Game of Thrones");
    Series s2;
    s2.id = 2;
    strcpy(s2.title, "The Breaking Bad");
    strcpy(s2.introduction, "The Breaking Bad");
    Series s3;
    s3.id = 3;
    strcpy(s3.title, "One Hundred Years of Solitude");
    strcpy(s3.introduction, "One Hundred Years of Solitude");
    Series s4;
    s4.id = 4;
    strcpy(s4.title, "My Brilliant Friend");
    strcpy(s4.introduction, "My Brilliant Friend");
    Series s5;
    s5.id = 5;
    strcpy(s5.title, "Peaky Blinders");
    strcpy(s5.introduction, "Peaky Blinders");

    splaytree_add(splaytree, &s1);
    splaytree_add(splaytree, &s2);
    splaytree_add(splaytree, &s3);
    splaytree_add(splaytree, &s4);
    splaytree_add(splaytree, &s5);
    splaytree_traverse(splaytree, splay_traverse);
    printf("\n");

    splaytree_delete_by_id(splaytree, 3);
    splaytree_traverse(splaytree, splay_traverse);
    printf("\nroot.id == 2 ? %d", splaytree->root->series.id == 2);
    printf("\n");

    SplayNode *node = splaytree_get_by_id(splaytree, 5);
    splaytree_traverse(splaytree, splay_traverse);
    printf("\n");
    printf("root.id == 5 ? %d\n", splaytree->root->series.id == 5);
    printf("%s\n", node->series.title);

    for (int i = 0; i < 2000; ++i) {
        s5.id = i * i;
        splaytree_add(splaytree, &s5);
    }

    splaytree_traverse(splaytree, splay_traverse);
    printf("\n");

    printf("root.id = %d\n", splaytree->root->series.id);
    printf("************************************\n");

    int id = 0;
    for (int i = 6; i < 2000; ++i) {
        id = i * i;
        splaytree_delete_by_id(splaytree, id);
    }

    splaytree_traverse(splaytree, splay_traverse);
    printf("\n");
    printf("root.id = %d\n", splaytree->root->series.id);

    splaytree_clear(splaytree);
}

int main() {
    splaytree();
    return 0;
}