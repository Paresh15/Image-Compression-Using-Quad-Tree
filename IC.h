#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct RGB_Value{
    char r,g,b; 
}RGB_Value;



typedef struct node{
    RGB_Value c;
    int length;
    struct node * top_left,*top_right,*bottom_left,*bottom_right;
}node;

typedef node* QT;



QT new_node(RGB_Value c, int length);
void addnode(QT * root, RGB_Value c, int length);
RGB_Value Average_Color(int x, int y, int l, int width, RGB_Value Input_Matrix[width][width]);
int Comp_level(int x, int y, int l, int width,RGB_Value Input_Matrix[width][width]);
void Compress(QT * root, int x, int y, int l, int width, RGB_Value Input_Matrix[width][width]);


int Is_Leaf(QT root);
void Fill_Matrix(int x, int y, RGB_Value c, int l, int width, RGB_Value Output_Matrix[width][width]);
void Decompress(QT *root, int x, int y, int l, int width, RGB_Value Output_Matrix[width][width]);
void Create_Image(char *fileName, int width, RGB_Value Output_Matrix[width][width]);


void freeTree(QT *root);
void Coversion(char *Input, char *Output);


void swap(RGB_Value *a, RGB_Value *b);
void vertical(char *Input, char *Output);
void horizontal(char *Input, char *Output);

