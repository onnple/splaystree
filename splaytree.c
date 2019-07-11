//
// Created by Once on 2019/7/11.
//

#include "splaytree.h"
#include <string.h>
#include <stdlib.h>

SplayTree *splaytree_init(){
    SplayTree *splaytree = (SplayTree*)malloc(sizeof(SplayTree));
    if(!splaytree){
        perror("init splay tree error.");
        return NULL;
    }
    splaytree->root = NULL;
    splaytree->size = 0;
    return splaytree;
}

int splaytree_is_full(SplayTree *splaytree){
    SplayNode *node = (SplayNode*)malloc(sizeof(SplayNode));
    if(!node)
        return 1;
    free(node);
    return 0;
}

int splaytree_is_empty(SplayTree *splaytree){
    if(splaytree == NULL)
        return 1;
    return splaytree->size == 0;
}

// 单旋转：只有父结点（根结点）

// 之字形旋转，双旋转
// LL
static SplayNode *rotate_left_single(SplayNode *root){
    SplayNode *node = root->left;
    root->left = node->right;
    node->right = root;
    return node;
}

// RR
static SplayNode *rotate_right_single(SplayNode *root){
    SplayNode *node = root->right;
    root->right = node->left;
    node->left = root;
    return node;
}

// LR
static SplayNode *rotate_left_double(SplayNode *root){
    root->left = rotate_right_single(root->left);
    return rotate_left_single(root);
}

// RL
static SplayNode *rotate_right_double(SplayNode *root){
    root->right = rotate_left_single(root->right);
    return rotate_right_single(root);
}

// 一字形旋转
static SplayNode *rotate_zig_zig_left(SplayNode *root){
    SplayNode *sun = root->left->left;
    SplayNode *parent = root->left;
    parent->left = sun->right;
    root->left = parent->right;
    sun->right = parent;
    parent->right = root;
    return sun;
}

static SplayNode *rotate_zig_zig_right(SplayNode *root){
    SplayNode *sun = root->right->right;
    SplayNode *parent = root->right;
    parent->right = sun->left;
    root->right = parent->left;
    sun->left = parent;
    parent->left = root;
    return sun;
}

static SplayNode *add_node(SplayTree *splaytree, SplayNode *root, Series *series){
    if(!root){
        root = (SplayNode*)malloc(sizeof(SplayNode));
        if(!root){
            perror("init splay node error.");
            return NULL;
        }
        root->left = root->right = NULL;
        root->series.id = series->id;
        strcpy(root->series.title, series->title);
        strcpy(root->series.introduction, series->introduction);
        splaytree->size++;
        return root;
    }
    else if(root->series.id > series->id){
        root->left = add_node(splaytree, root->left, series);
        if(splaytree->root == root && root->left->series.id == series->id)
            root = rotate_left_single(root);
        else if(root->left->left && root->left->left->series.id == series->id)
            root = rotate_zig_zig_left(root);
        else if(root->left->right && root->left->right->series.id == series->id)
            root = rotate_left_double(root);
        return root;
    }
    else if(root->series.id < series->id){
        root->right = add_node(splaytree, root->right, series);
        if(splaytree->root == root && root->right->series.id == series->id)
            root = rotate_right_single(root);
        else if(root->right->right && root->right->right->series.id == series->id)
            root = rotate_zig_zig_right(root);
        else if(root->right->left && root->right->left->series.id == series->id)
            root = rotate_right_double(root);
        return root;
    }
    else{
        strcpy(root->series.title, series->title);
        strcpy(root->series.introduction, series->introduction);
        return root;
    }
}

int splaytree_add(SplayTree *splaytree, Series *series){
    if(splaytree == NULL || series == NULL)
        return 0;
    splaytree->root = add_node(splaytree, splaytree->root, series);
    return 1;
}

static SplayNode *find_max(SplayNode *root){
    if(root->right)
        return find_max(root);
    else
        return root;
}

static SplayNode *node_rotate_to_root(SplayNode *tree_root, SplayNode *root, unsigned int id){
    if(!root)
        return NULL;
    if(root->series.id == id){
        return root;
    }
    else if(root->series.id > id){
        root->left = node_rotate_to_root(tree_root, root->left, id);
        if(tree_root == root && root->left->series.id == id)
            root = rotate_left_single(root);
        else if(root->left->left && root->left->left->series.id == id)
            root = rotate_zig_zig_left(root);
        else if(root->left->right && root->left->right->series.id == id)
            root = rotate_left_double(root);
    }
    else{
        root->right = node_rotate_to_root(tree_root, root->right, id);
        if(tree_root == root && root->right->series.id == id)
            root = rotate_right_single(root);
        else if(root->right->right && root->right->right->series.id == id)
            root = rotate_zig_zig_right(root);
        else if(root->right->left && root->right->left->series.id == id)
            root = rotate_right_double(root);
    }
    return root;
}

int splaytree_delete_by_id(SplayTree *splaytree, unsigned int id){
    if(splaytree == NULL || splaytree->size == 0)
        return 0;
    SplayNode *root = node_rotate_to_root(splaytree->root, splaytree->root, id);
    if(!root)
        return 0;
    SplayNode *left = root->left;
    SplayNode *right = root->right;
    free(root);
    if(left){
        SplayNode *max = find_max(left);
        SplayNode *left_node = node_rotate_to_root(left, left, max->series.id);
        left_node->right = right;
        splaytree->root = left_node;
    }
    else
        splaytree->root = right;
    splaytree->size--;
    return 1;
}

//static SplayNode *get_node(SplayNode *root, unsigned int id){
//    if(!root)
//        return NULL;
//    if(root->series.id == id)
//        return root;
//    else if(root->series.id > id)
//        return get_node(root->left, id);
//    else
//        return get_node(root->right, id);
//}

SplayNode *splaytree_get_by_id(SplayTree *splaytree, unsigned int id){
    if(splaytree == NULL || splaytree->size == 0)
        return NULL;
    splaytree->root = node_rotate_to_root(splaytree->root, splaytree->root, id);
    return splaytree->root;
}

static void traverse_tree(SplayNode *root, void (*traverse)(SplayNode*)){
    if(!root)
        return;
    traverse_tree(root->left, traverse);
    traverse(root);
    traverse_tree(root->right, traverse);
}

void splaytree_traverse(SplayTree *splaytree, void (*traverse)(SplayNode*)){
    if(splaytree == NULL || splaytree->size == 0 || traverse == NULL)
        return;
    traverse_tree(splaytree->root, traverse);
}

static int clear_node(SplayNode *root){
    if(!root)
        return 0;
    clear_node(root->left);
    clear_node(root->right);
    free(root);
    return 1;
}

int splaytree_clear(SplayTree *splaytree){
    if(splaytree == NULL)
        return 0;
    clear_node(splaytree->root);
    free(splaytree);
    return 1;
}
