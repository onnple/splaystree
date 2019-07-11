#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "basic.h"
#include "sort.h"
#include "seqlist.h"
#include "polynomial.h"
#include "stack.h"
#include "queue.h"
#include "fs.h"
#include "stree.h"
#include "mathematica.h"
#include "avltree.h"
#include "splaytree.h"

void seqlist(void){
    SeqList *seqList = seqlist_init();
    printf("size: %u, max size: %u\n", seqList->size, seqList->max_size);
    Book b1;
    b1.id = 5;
    strcpy(b1.title, "The Price of Salt");
    strcpy(b1.author, "Highsmith");
    Book b2;
    b2.id = 6;
    strcpy(b2.title, "The Old Man and The Sea");
    strcpy(b2.author, "Hemingway");
    Book b3;
    b3.id = 3;
    strcpy(b3.title, "One Hundred Years of Solitude");
    strcpy(b3.author, "Garcia");
    seqlist_add(seqList, &b1, 0);
    seqlist_add(seqList, &b2, 3);
    seqlist_add(seqList, &b3, 1);
    for (int i = 0; i < seqList->size; ++i) {
        printf("%s\n", seqList->books[i]->title);
    }
    putchar('\n');
    printf("%s\n", seqlist_get(seqList, 3)->title);
    seqlist_delete(seqList, 5);
    putchar('\n');
    for (int i = 0; i < seqList->size; ++i) {
        printf("%s\n", seqList->books[i]->title);
    }
    seqlist_clear(seqList);
}

void print_expression(Polynomial *poly, char *message){
    char *expression1 = poly_algebraic_expression(poly);
    printf("%s%s\n", message, expression1);
    free(expression1);
}

void polynomial(void){
    // -6X^2 + 2X + 5
    Polynomial *poly1 = poly_init();
    Expression exp1;
    exp1.coefficient = 5;
    exp1.exponent = 0;
    Expression exp2;
    exp2.coefficient = -6;
    exp2.exponent = 3;
    Expression exp3;
    exp3.coefficient = 2;
    exp3.exponent = 1;
    poly_add(poly1, &exp1);
    poly_add(poly1, &exp2);
    poly_add(poly1, &exp3);

    // 18X^5 - 3X^2 - 9X + 7
    Polynomial *poly2 = poly_init();
    Expression exp4;
    exp4.coefficient = -3;
    exp4.exponent = 2;
    Expression exp5;
    exp5.coefficient = 18;
    exp5.exponent = 5;
    Expression exp6;
    exp6.coefficient = -8;
    exp6.exponent = 1;
    Expression exp7;
    exp7.coefficient = 7;
    exp7.exponent = 0;
    poly_add(poly2, &exp4);
    poly_add(poly2, &exp5);
    poly_add(poly2, &exp6);
    poly_add(poly2, &exp7);

    // 按字符串输出多项式代数表达式
    print_expression(poly1, "A:     ");
    print_expression(poly2, "B:     ");

    // 代数值
    float value1 = poly_algebraic_value(poly1, 3);
    float value2 = poly_algebraic_value(poly2, 2);
    printf("%f %f\n", value1, value2);

    // 加减乘
    Polynomial *plus = poly_plus(poly1, poly2);
    print_expression(plus, "A + B: ");
    Polynomial *sub = poly_subtract(poly1, poly2);
    print_expression(sub, "A - B: ");
    Polynomial *multiply = poly_multiply(poly1, poly2);
    print_expression(multiply, "A x B: ");

    // 导数/微商、不定积分、定积分
    Polynomial *diff = poly_differential(poly1);
    print_expression(diff, "D[A]:  ");
    Polynomial *in_inte = poly_in_integral(poly2);
    print_expression(in_inte, "In[B]: ");
    float result = poly_integral(poly2, -5, 15);
    printf("In[B, -5, 15]: %.0f\n", result);

    poly_clear(plus);
    poly_clear(sub);
    poly_clear(multiply);
    poly_clear(diff);
    poly_clear(in_inte);
    poly_clear(poly1);
    poly_clear(poly2);
}

void stack(void){
    // 文本语法检查
    char *text = "{}[]{()[]}[]{}";
    int auth = syntax_auth(text, strlen(text));
    if(auth == 1)
        printf("syntax correct.\n");
    else
        printf("syntax error.\n");

    // 进制转换
    char *str = to_base_str(78, 2);
    if(str)
        printf("%s\n", str);
    else
        printf("error.\n");
}

void task1(void){
    printf("01 processing the result of ajax......\n");
}

void task2(void){
    printf("02 rendering the data of elements......\n");
}

void task3(void){
    printf("03 execute the task of timeout......\n");
}

void queue(void){
    Queue *queue = queue_init();
    queue_enqueue(queue, task3);
    queue_enqueue(queue, task1);
    queue_enqueue(queue, task2);
    Task task = queue_dequeue(queue);
    task();
    queue_execute_tasks(queue);
    queue_clear(queue);

}

// 数据对象，一般业务数据
typedef struct post{
    unsigned int id;
    char *title;
    char *content;
} Post;

// 结点，包括数据域（可包含关键字），指针域
typedef struct pnode{
    int key; // 可自定义创建一个无关的关键字
    Post post; // 数据域（这里已包含关键字域）
    struct pnode *left; // 指针域，儿子结点
    struct pnode *right;
    struct pnode *parent;
    struct pnode *sblings;
} PNode;

// 树ADT对外接口
typedef struct ptree{
    PNode *root;
    unsigned int size;
} PTree;

void fs(void){
    FTree *ftree = ftree_init();
    File d1;
    strcpy(d1.file_name, "/");
    d1.is_directory = 1;
    strcpy(d1.file_content, "root");

    File d2;
    strcpy(d2.file_name, "bin");
    d2.is_directory = 1;
    strcpy(d2.file_content, "bin");

    File d3;
    strcpy(d3.file_name, "etc");
    d3.is_directory = 1;
    strcpy(d3.file_content, "etc");

    File d4;
    strcpy(d4.file_name, "man");
    d4.is_directory = 0;
    strcpy(d4.file_content, "man");

    File d5;
    strcpy(d5.file_name, "mysql");
    d5.is_directory = 0;
    strcpy(d5.file_content, "mysql");

    File d6;
    strcpy(d6.file_name, "mongodb");
    d6.is_directory = 0;
    strcpy(d6.file_content, "mongodb");

    ftree_add(ftree, "/", &d1);
    ftree_add(ftree, "/", &d2);
    ftree_add(ftree, "/", &d3);
    ftree_add(ftree, "/bin", &d4);
    ftree_add(ftree, "/usr/db", &d5);
    ftree_add(ftree, "/usr/db", &d6);
    ftree_traverse(ftree);
    printf("%d\n", ftree->size);
    if(ftree_is_exist(ftree, "/bin/man"))
        printf("/bin/man exists.\n");
    if(ftree_is_exist(ftree, "/bin/mount"))
        printf("/bin/mount exists.\n");
    else
        printf("/bin/mount does not exist.\n");
    ftree_clear(ftree);
}

static void process_name(MNode *node){
    printf("%06d %s\n", node->movie.id, node->movie.name);
}

static void process_id(MNode *node){
    printf("%d ", node->movie.id);
}

void stree(){
    STree *stree = stree_init();
    Movie m1;
    m1.id = 98;
    strcpy(m1.name, "Once Upon A Time In Hollywood");
    strcpy(m1.about, "Once Upon A Time In Hollywood");

    Movie m2;
    m2.id = 34;
    strcpy(m2.name, "The Price of Salt");
    strcpy(m2.about, "The Price of Salt");

    Movie m3;
    m3.id = 69;
    strcpy(m3.name, "Mad Man");
    strcpy(m3.about, "Mad Man");

    Movie m4;
    m4.id = 112;
    strcpy(m4.name, "Breaking Bad");
    strcpy(m4.about, "Breaking Bad");

    Movie m5;
    m5.id = 21;
    strcpy(m5.name, "The Name of Rose");
    strcpy(m5.about, "The Name of Rose");

    Movie m6;
    m6.id = 100;
    strcpy(m6.name, "You Belong to Me");
    strcpy(m6.about, "You Belong to Me");

    stree_add(stree, &m1);
    stree_add(stree, &m2);
    stree_add(stree, &m3);
    stree_add(stree, &m4);
    stree_add(stree, &m5);
    stree_add(stree, &m6);

    // 获取二叉树中id的最大最小值
    printf("Max: %d, Min: %d\n\n", stree_get_max(stree)->movie.id, stree_get_min(stree)->movie.id);

    stree_process(stree, process_name); // 升序输出
    printf("\n");

    stree_process(stree, process_id);
    printf("\n");

    stree_delete_by_id(stree, 100); // 删除树叶
    stree_process(stree, process_id);
    printf("\n");
    stree_delete_by_id(stree, 98); // 删除有两个儿子的结点
    stree_process(stree, process_id);
    printf("\n");
    stree_delete_by_id(stree, 34); // 删除有两个儿子的结点
    stree_process(stree, process_id);
    printf("\n");
    stree_delete_by_id(stree, 69); // 删除只有一个儿子的结点
    stree_process(stree, process_id);
    printf("\n");

    stree_clear(stree);
}

void expression_tree(void){
    char str[] = "a^h - 3.14^e + b - (2.5x - 3^c) - 8xy + 3x^2z - yz";
    char str1[] = "a + b * c + (d * e + f) * g";
    Exp *exp = exp_init();
    exp_load(exp, str);
    exp_traverse(exp);
    exp_clear(exp);
}

static int height(AVLNode *node){
    if(!node)
        return -1; // 空树为-1
    return node->height;
}

void traverse_tree(AVLNode *node){
    printf("(%d) - ", height(node->left) - height(node->right));
}

void avltree(void){
    AVLTree *avltree = avltree_init();
    for (int i = 0; i < 8; ++i) {
        User user;
        user.id = i + 1;
        strcpy(user.username, "AVL");
        strcpy(user.password, "AVL");
        avltree_add(avltree, &user);
    }
    avltree_traverse(avltree, traverse_tree);
    printf("\n");

    avltree_delete_by_id(avltree, 5); // 删除树叶，RR单旋转
    avltree_traverse(avltree, traverse_tree);
    printf("\n");

    User u1;
    u1.id = 10;
    strcpy(u1.username, "AVL");
    strcpy(u1.password, "AVL");
    avltree_add(avltree, &u1);
    User u2;
    u2.id = 5;
    strcpy(u2.username, "AVL");
    strcpy(u2.password, "AVL");
    avltree_add(avltree, &u2);
    User u3;
    u3.id = 0;
    strcpy(u3.username, "AVL");
    strcpy(u3.password, "AVL");
    avltree_add(avltree, &u3); // LL单旋转
    avltree_traverse(avltree, traverse_tree);
    printf("\n");

    avltree_delete_by_id(avltree, 7); // 删除有两个儿子的结点
    avltree_traverse(avltree, traverse_tree);
    printf("\n");

    avltree_delete_by_id(avltree, 4); // 删除有两个儿子的结点
    avltree_traverse(avltree, traverse_tree);
    printf("\n");

    avltree_delete_by_id(avltree, 6);
    avltree_delete_by_id(avltree, 5);
    avltree_traverse(avltree, traverse_tree);
    printf("\n");

    u1.id = 6;
    avltree_add(avltree, &u1);
    u1.id = 7;
    avltree_add(avltree, &u1);
    u1.id = 5;
    avltree_add(avltree, &u1);
    avltree_traverse(avltree, traverse_tree);
    printf("\n");

    avltree_delete_by_id(avltree, 1);
    avltree_delete_by_id(avltree, 2);
    avltree_delete_by_id(avltree, 8);
    avltree_traverse(avltree, traverse_tree);
    printf("\n");

    for (int i = 0; i < 2000; ++i) {
        if(i % 2 == 0)
            u1.id = i * i / 2;
        else
            u1.id = i * i / 3;
        avltree_add(avltree, &u1);
    }
    avltree_traverse(avltree, traverse_tree);
    printf("\n");

    int id = 0;
    for (int i = 0; i < 2000; ++i) {
        if(i % 2 == 0)
            id = i * i / 2;
        else
            id = i * i / 3;
        avltree_delete_by_id(avltree, id);
    }

    avltree_clear(avltree);
}

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