#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>

#include "cell.h"

/*
Creates a cell group and sets the size to the parameter 'num'
It then passes out a pointer to the new group after it is done 
initialising it
*/
CellGroup* createCellGroup(int newValues[], int newGroupSize)
{
	//Making the new cellgroup in memory and initialising it
	CellGroup* newGroup;
	newGroup = malloc(sizeof(CellGroup));
	newGroup->size = 0;

	//add the cells to the group
	for(int i=0; i<newGroupSize; i++)
	{
		//create a cell
		Cell* newCell = createCell(newValues[i]);
		//add it
		insertCell(newGroup, newCell);
	}
	return newGroup;
}

/*
Creates a cell and sets the data of the cell to the paramater
'null' the passes out a pointer to the new cell after initialising
the variables
*/
Cell* createCell(int num)
{
	Cell* newCell = malloc(sizeof(Cell));
	newCell->data = num;
	newCell->left = NULL;
	newCell->right = NULL;
	return newCell;
}

/*
Inserts a cell into the specified group. 
*/
void insertCell(CellGroup* clgp, Cell* cl){
	//check that the pointers aren't NULL
	assert(clgp != NULL);
	assert(cl != NULL);

	//if the cellgroup is empty
	if( clgp->size == 0 ){
		//make cl the head
		clgp->head = cl;

	} else {
		//start at the head
		Cell* tmpCell = clgp->head;
		
		//loop until the end of the group
		for(int i = 1; i < (clgp->size); i++){
			tmpCell = tmpCell->right;
		}
		//insert the new cell
		tmpCell->right = cl;
		cl->left = tmpCell;
	}	

	//make the list loop round
	cl->right = clgp->head;
	clgp->head->left = cl;

	//increase the size
	clgp->size++;
}

/*
A pointer to a cell in passed in and then that memory address is then free'd
after the memory has been set to 0s. It will return 0 if memory is correctly
deleted and returns 1 otherwise
*/
int deleteCell(Cell* cl)
{
	memset(cl, 0, sizeof(Cell));
	free(cl);
	if(cl!=NULL)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

/*
A pointer to a group is passed in and then that memory address is then free'd if
the group is empty of cells if it not it will loop through the cell group and free
the cells then free the group. It will return 0 if the memory is corretly deleted
and return 1 otherwise
*/
int deleteCellGroup(CellGroup* clgp)
{
	if(clgp->size==0)
	{
		memset(clgp, 0, sizeof(CellGroup));
		free(clgp);
		if(clgp!=NULL)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	else
	{
		Cell* next = clgp->head;
		Cell* current = clgp->head;

		for(int i = 0; i < (clgp->size); i++)
		{
			next = current->right;
			deleteCell(current);
			
			if(next != NULL)
			{
				current = next;
			}

		}

		memset(clgp, 0, sizeof(CellGroup));
		free(clgp);
		if(clgp!=NULL)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}	
}

/*
Takes in an integer number that it assumes it is between 0 and 255 (inclusive)
It then passes out a the binary number
*/
int* binaryConversion(int x)
{
	//Creates an array that will store the binary number backwards
    int backwardBinaryNumber[8];
    
    //Sets all the values to 0
    for(int k=0; k<8; k++){
    	backwardBinaryNumber[k] = 0;
    }
	
	//Creates the binary number using modulus
	int i=0;
    while(x!=0){
    	backwardBinaryNumber[i++]= x % 2;
    	x = x / 2;
    }

	//Creates the binary number in memory
	int *binaryNumber = malloc(sizeof(int)*8);
	
	//Reverses it and saves it to the new malloced memory
	for(int j=7; j>-1; j--)
	{
		binaryNumber[7-j] = backwardBinaryNumber[j];
	}
	
	//Return the int pointer
	return binaryNumber;
}

CellGroup* nextGen(CellGroup* clgp, int* ruleset)
{
	int values[clgp->size];
	for(int i=0; i<clgp->size; i++)
	{
		values[i] = 0;
	}
	Cell* current = clgp->head;
	for(int i=0;i<clgp->size;i++)
	{
		if(current->left->data==1 && current->data==1 && current->right->data==1)
		{
			values[i] = ruleset[0];
		}
		else if(current->left->data==1 && current->data==1 && current->right->data==0)
		{
			values[i] = ruleset[1];
		}
		else if(current->left->data==1 && current->data==0 && current->right->data==1)
		{
			values[i] = ruleset[2];
		}
		else if(current->left->data==1 && current->data==0 && current->right->data==0)
		{
			values[i] = ruleset[3];
		}
		else if(current->left->data==0 && current->data==1 && current->right->data==1)
		{
			values[i] = ruleset[4];
		}
		else if(current->left->data==0 && current->data==1 && current->right->data==0)
		{
			values[i] = ruleset[5];
		}
		else if(current->left->data==0 && current->data==0 && current->right->data==1)
		{
			values[i] = ruleset[6];
		}
		else if(current->left->data==0 && current->data==0 && current->right->data==0)
		{
			values[i] = ruleset[7];
		}
		//move to the next node
		current = current->right;
	}

	//Saving the size before we delete it so we can pass it into the next generation
	int clgpSize = clgp->size;
	
	int test = deleteCellGroup(clgp);
	assert( test == 0 );
	return createCellGroup(values, clgpSize);
}

//Gets the decimal number for the ruleset from the user and validates it
int getUserInput()
{
	bool valid = false;
	int input;
	while(!valid)
	{
		printf("Please enter a number to be used as the ruleset between 0 and 255\n");
		scanf("%d", &input);
		if(input>=0 && input<=255)
		{
			valid = true;
		}
		else
		{
			printf("INVALID NUMBER\n");
		}
	}
	return input;
}

//gets the data in the starting cell group and then returns the cellgroup
CellGroup* getInitialGroup()
{
	bool valid=false;
	int input;
	while(!valid)
	{
		printf("Please enter the length of the first row\n");
		scanf("%d",&input);
		if(input>3)
		{
			valid=true;
		}
		else
		{
			printf("You didnt enter a valid size\n");
		}
	}
	printf("Enter the data in the first row (0 or 1)\n");
	int initialValues[input];
	for(int i=0;i<input;i++)
	{
		bool valid=false;
		while(!valid)
		{
			int currentValue = 0;
			printf("%d: ",(i+1));
			scanf("%d",&currentValue);
			if(currentValue==1||currentValue==0)
			{
				initialValues[i]=currentValue;
				valid=true;
			}
			else
			{
				printf("You did not enter a valid input\n");
			}
		}
	}
	return createCellGroup(initialValues, input);
}

/*
 * Prints a cell group
 */
void printCellGroup(CellGroup* clgp)
{
	//cell to be printed
	Cell* current = clgp->head;

	//loop through
	for(int i = 0; i<(clgp->size); i++){
		//print the correct state
		if(current->data == 0){
			printf(".");
		} else {
			printf("1");
		}
		//move to the next node
		current = current->right;
	}
	//new line for next generation
	printf("\n");
}

//Creates a delay when called
static void delay(unsigned int seconds)
{
	unsigned int wait = time(0)+seconds;
	while(time(0)<wait);
}

//dummy main
int main()
{
	int* ruleset = binaryConversion(getUserInput());
	CellGroup* newCellGroup = getInitialGroup();
	printCellGroup(newCellGroup);
	
	while(true)
	{
		newCellGroup = nextGen(newCellGroup, ruleset);
		printCellGroup(newCellGroup);
		delay(1);
	}
	deleteCellGroup(newCellGroup);
}
