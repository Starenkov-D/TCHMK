#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LongNumber.h"

int main(int argc, const char * argv[])
{
	if (argc < 5) 
	{
        printf("Warning: Not enough arguments. <first_long_number_filename> [ + | - | * | / | % | ^ ] <second_long_number_filename> <result_long_number_filename>\n");
        return 0;
    }
    
    if (argc > 7) 
	{
        printf("Warning: Too many arguments. <first_long_number_filename> [ + | - | * | / | % | ^ ] <second_long_number_filename> <result_long_number_filename> <module_long_number_filename> <-b>\n");
        return 0;
    }
    
    FILE* firstLongNumFile = fopen(argv[1], "r");
    if (!firstLongNumFile) 
	{
        printf("Warning: Unable to open file: %s \n", argv[1]);
        return 0;
    }
	fclose(firstLongNumFile);

    const char* operation = argv[2];
    if ((strlen(operation) > 1 || operation[0] == '\0') || operation[0] != '+' && operation[0] != '-' && operation[0] != '*' && operation[0] != '/' && operation[0] != '%' && operation[0] != '^') 
	{
        printf("Warning: Invalid operation: %s \n", operation);
        return 0;
    }
    
    FILE* secondLongNumFile = fopen(argv[3], "r");
    if (!secondLongNumFile) 
	{
        printf("Warning: Unable to open file: %s \n", argv[3]);
        return 0;
    }
    fclose(secondLongNumFile);

	FILE* resultLongNumFile = fopen(argv[4], "r");
    if (!resultLongNumFile) 
	{
        printf("Warning: Unable to open file: %s \n", argv[4]);
        return 0;
    }
    fclose(resultLongNumFile);

	////////////////////////////////////////////////////////////////////////////////

	int bin = 0;

	if (argc == 5)
		if (argv[2][0] == '^')
		{
			printf("Warning: Input module file\n");
			return 0;
		}

    if (argc == 6) 
	{
		if (argv[2][0] == '^')
		{
			FILE* moduleLongNumFile = fopen(argv[5], "r");
			if (!moduleLongNumFile) 
			{
				printf("Warning: Unable to open file: %s \n", argv[5]);
				return 0;
			}
			fclose(moduleLongNumFile);
		}
		else
		{
			if (strcmp(argv[5], "-b")) 
			{
				printf("Warning: Invalid flag: %s \n", argv[5]);
				return 0;
			}
			bin = 1;
		}
		
    }

	if (argc == 7) 
	{
		FILE* moduleLongNumFile = fopen(argv[5], "r");
		if (!moduleLongNumFile) 
		{
			printf("Warning: Unable to open file: %s \n", argv[5]);
			return 0;
		}
		fclose(moduleLongNumFile);

        if (strcmp(argv[6], "-b")) 
		{
            printf("Warning: Invalid flag: %s \n", argv[6]);
            return 0;
        }
		bin = 1;
    }
    
	struct LongNumber a,b;

    //загрузка первого БЧ--------------------------------------------------------------------------------------
	if(bin == 1)
		a = ReadBinFile(argv[1]);
	else
		a = ReadTextFile(argv[1]);
    
    //загрузка второго БЧ-------------------------------------------------------------------------------------
	if(bin == 1)
		b = ReadBinFile(argv[3]);
	else
		b = ReadTextFile(argv[3]);
    
    //выполнение операции----------------------------------------------------------------------------------------

    struct LongNumber result;
    
    switch (operation[0]) {
        case '+':
        {
            result = ADD(a, b);
            break;
        }
        case '-':
        {
            result = SUB(a, b);
            break;
        }
        case '*':
        {
            result = MUL(a, b);
            break;
        }
        case '/':
        {
            result = DIV(a, b, 1);
            break;
        }
        case '%':
        {
            result = DIV(a, b, 2);
            break;
        }
        case '^':
        {
			struct LongNumber c;
            if(bin == 1)
				c = ReadBinFile(argv[5]);
			else
				c = ReadTextFile(argv[5]);

			result = DEGREE(a, b, c);
			c = clear(c);
            break;
        }
        default:
            break;
    }
     
    //запись результата----------------------------------------------------------------------------------------
	if (bin == 1)
		WriteBinFile(argv[4], result);
	else
		WriteTextFile(argv[4], result);

    //освободить память, выход---------------------------------------------------------------------------------
    a = clear(a);
    b = clear(b);
    result = clear(result);

	return 0;
}
