#include "IC.h"


QT new_node(RGB_Value c,int length)
{
    QT n = (node*)malloc(sizeof(node));

    n->c=c; 
    n->length=length;
    n->top_left = NULL;
    n->top_right = NULL;
    n->bottom_left = NULL;
    n->bottom_right = NULL;

    return n;

}

void addnode(QT * root, RGB_Value c, int length)
{
    QT q = new_node(c,length);

    if(*root == NULL) {
        *root = q;
        return;
    }
    
    
    if ((*root )->top_left == NULL){
        (*root )->top_left = q;
        return;
    }
    if ((*root )->top_right == NULL){
        (*root )->top_right = q;
        return;
    }
    if ((*root )->bottom_left == NULL){
        (*root )->bottom_left = q;
        return;
    }
    if ((*root )->bottom_right == NULL){
        (*root )->bottom_right = q;
        return;
    }

}

RGB_Value Average_Color(int x, int y, int l, int width, RGB_Value Input_Matrix[width][width])
{
    RGB_Value c;
    long long int red=0;
    long long int green = 0;
    long long int blue = 0;
    for(int i=x ;i<x+l;i++)
    {
        for(int j=y;j<y+l;j++){
            red += Input_Matrix[i][j].r;
            green += Input_Matrix[i][j].g;
            blue += Input_Matrix[i][j].b;

        }
    }
    
    c.r = red / (l*l);
    c.g = green / (l*l);
    c.b = blue /(l*l);
    return c;
}

int Comp_level(int x,int y,int l,int width,RGB_Value Input_Matrix[width][width])
{
    RGB_Value c= Average_Color(x,y,l,width,Input_Matrix);
    float avg = 0;
    for(int i=x;i<x+l;i++)
        for(int j=y;j<y+l;j++)
		{
            avg += (c.r - Input_Matrix[i][j].r) * (c.r - Input_Matrix[i][j].r);
            avg += (c.g - Input_Matrix[i][j].g) * (c.g - Input_Matrix[i][j].g);
            avg += (c.b - Input_Matrix[i][j].b) * (c.b - Input_Matrix[i][j].b);

        }

    avg /= (3*l*l);
    return (avg <=64);
}

void Compress(QT * root,int x,int y,int l,int width, RGB_Value Input_Matrix[width][width])
{
    if(l<=1) return; 

    addnode(root,Average_Color(x,y,l,width,Input_Matrix),l);

    if(!Comp_level(x,y,l,width,Input_Matrix))
    {
        Compress(&(*root)->top_left, x, y, l / 2, width, Input_Matrix);
		Compress(&(*root)->top_right, x, y + l / 2, l / 2, width, Input_Matrix);
		Compress(&(*root)->bottom_left, x + l / 2, y , l / 2, width, Input_Matrix);
		Compress(&(*root)->bottom_right, x + l / 2, y + l / 2, l / 2, width, Input_Matrix);
    }

}









int Is_Leaf(QT root)
{
    return (root ->top_left == NULL && root-> top_right == NULL && root ->bottom_left == NULL && root->bottom_right == NULL);
}

void Fill_Matrix(int x, int y, RGB_Value c, int l, int width, RGB_Value Output_Matrix[width][width])
{
	for (int i = x; i < x + l; i++)
	{
		for (int j = y; j < y + l; j++)
		{
			Output_Matrix[i][j].r = c.r;
			Output_Matrix[i][j].g = c.g;
			Output_Matrix[i][j].b = c.b;
		}
	}
}


void Decompress(QT *root, int x, int y, int l, int width, RGB_Value Output_Matrix[width][width])
{
	if (*root == NULL)
		return;
	if (Is_Leaf(*root))
	{
		Fill_Matrix(x, y, (*root)->c, l, width, Output_Matrix);
	}

	Decompress(&(*root)->top_left, x, y, l / 2, width, Output_Matrix);
	Decompress(&(*root)->top_right, x, y + l / 2, l / 2, width, Output_Matrix);
	Decompress(&(*root)->bottom_right, x + l / 2, y + l / 2, l / 2, width, Output_Matrix);
	Decompress(&(*root)->bottom_left, x + l / 2, y, l / 2, width, Output_Matrix);
}

void Create_Image(char *fileName, int width, RGB_Value Output_Matrix[width][width])
{
	FILE *fp = fopen(fileName, "wb");

	fprintf(fp, "P6\n");
	fprintf(fp, "%d %d\n", width, width);
	fprintf(fp, "255\n");

	for (int i = 0; i < width; i++)
		fwrite(Output_Matrix[i], sizeof(RGB_Value), width, fp);

	fclose(fp);
}









void freeTree(QT *root)
{
	if(*root == NULL)
	{
    		free(*root);
        	return;
        }
	   
	freeTree(&(*root)->top_right);
	freeTree(&(*root)->top_left);
	freeTree(&(*root)->bottom_right);
	freeTree(&(*root)->bottom_left);

}

void Coversion(char *Input, char *Output)
{
	FILE *fp = fopen(Input, "rb");

	char u[3];
	int width, height, max_value;
	fscanf(fp, "%s%d%d%d%c", u, &width, &height, &max_value, &u[0]);

	RGB_Value Input_Matrix[width][height];
	for (int i = 0; i < width; i++)
	{
		fread(&Input_Matrix[i], sizeof(RGB_Value), width, fp);
	}
	fclose(fp);
	
	QT root = NULL;
	Compress(&root, 0, 0, width, width, Input_Matrix);
	
	RGB_Value Output_Matrix[width][width];
	Decompress(&root, 0, 0, width, width, Output_Matrix);
	
	Create_Image(Output, width, Output_Matrix);

	freeTree(&root);
}







void swap(RGB_Value *a, RGB_Value *b)
{
	RGB_Value temp=*a;
	*a=*b;
	*b=temp;
}

void vertical(char *Input, char *Output)
{
	FILE *fp = fopen(Input, "rb");

	char u[3];
	int width, height, max_value;
	fscanf(fp, "%s%d%d%d%c", u, &width, &height, &max_value, &u[0]);

	RGB_Value Input_Matrix[width][height];
	for (int i = 0; i < width; i++)
	{
		fread(&Input_Matrix[i], sizeof(RGB_Value), width, fp);
	}
	fclose(fp);
	
	FILE *op = fopen(Output, "wb");

	fprintf(op, "P6\n");
	fprintf(op, "%d %d\n", width, width);
	fprintf(op, "255\n");
	
	for (int i = width-1; i >= 0; i--)
		fwrite(Input_Matrix[i], sizeof(RGB_Value), width, op);

	fclose(op);
	
}


void horizontal(char *Input, char *Output)
{
	FILE *fp = fopen(Input, "rb");

	char u[3];
	int width, height, max_value;
	fscanf(fp, "%s%d%d%d%c", u, &width, &height, &max_value, &u[0]);

	RGB_Value Input_Matrix[width][height];
	for (int i = 0; i < width; i++)
	{
		fread(&Input_Matrix[i], sizeof(RGB_Value), width, fp);
	}
	fclose(fp);
	
	
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < width/2; j++)
		{
			swap(&Input_Matrix[i][j],&Input_Matrix[i][width-j-1]);
		}
	}
	
	
	FILE *op = fopen(Output, "wb");

	fprintf(op, "P6\n");
	fprintf(op, "%d %d\n", width, width);
	fprintf(op, "255\n");
	
	
	for (int i = 0; i < width; i++)
		fwrite(Input_Matrix[i], sizeof(RGB_Value), width, op);

	fclose(op);
	
}




















