#include"IC.c"

int main(int argc, char **argv)
{	
	char *Input;
	char *Output;

	
	if (argc > 1)
	{
		if (strstr(argv[1], "-c"))
		{
			Input = argv[2];
			Output = argv[3];
			Coversion(Input, Output);	
		}    
		else if (strstr(argv[1], "-m"))
		{
			char orientation = argv[2][0];
			
			if(orientation=='v')
			{
				Input = argv[3];
				Output = argv[4];
				vertical(Input, Output);
			}
			else
			{
				Input = argv[3];
				Output = argv[4];
				horizontal(Input, Output);
			}	
		}
		else
		{
			printf("Wrong Input");
		}  
	}
	else
	{
		printf("Wrong Input");
	}
	return 0;
}
