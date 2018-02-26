#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(int argc, char *argv[])
{
	FILE *ptr_file;
	char buf[100],total_elements[1];
	int i=0, total_items = 1, capacity = 0,k,j, max_weight = 0;
	int selected_items[total_items];
	char *tok;

	//open and read from a file
    	ptr_file =fopen(argv[1],"r");
    	if (!ptr_file)
        	printf("Unable to open a file");

	fscanf(ptr_file,"%[^\n]",total_elements);

	fgets(buf,10,ptr_file);
	total_items = atoi(total_elements);

	int weight[total_items];
	int profit[total_items];
	int copy_weight[total_items];
	
	fscanf(ptr_file,"%[^\n]",buf);

	tok = strtok(buf,", ");


	//tokenize and stroing a data
	while(tok!=NULL)
	{
		weight[i] = atoi(tok);
		copy_weight[i] = atoi(tok);
		tok = strtok(NULL,", ");
		i++;
	}

	fgets(buf,10,ptr_file);

	fscanf(ptr_file,"%[^\n]",buf);

	tok = strtok(buf,", ");
	i=0;
	while(tok!=NULL)
	{
		profit[i] = atoi(tok);
		tok = strtok(NULL,", ");
		i++;
	}
	
	fgets(buf,10,ptr_file);

	fscanf(ptr_file,"%[^\n]",buf);

	capacity = atoi(buf);


	//implemetation of knapsack dynamic algorithm
	int matrix[total_items+1][capacity+1];
	
	for(j=0;j<capacity+1;j++)
	{
		matrix[0][j]=0;
	}

	for(k=1;k<total_items+1;k++)
	{
		matrix[k][0] = 0;

		for(i=0;i<total_items;i++)
		{
			selected_items[i] = 0;
		}

		for(j=1;j<capacity+1;j++)
		{

			for(i=0;i<total_items;i++)
			{
				if(selected_items[i] == -2)
				{
					selected_items[i] = 0;
				}
			}

			if((weight[k-1] <= j) && ((matrix[k-1][j-weight[k-1]] + profit[k-1]) > matrix[k-1][j]))
			{
				matrix[k][j] = matrix[k-1][j-weight[k-1]] + profit[k-1];
				if(matrix[k][j-1] != matrix[k][j])
				{
					max_weight = weight[k-1];
					selected_items[k-1]=-1;

					if(j>max_weight && max_weight + weight[j-weight[k-1]] < j)
					{
						max_weight = max_weight + j-weight[k-1];
						for(i=0;i<total_items;i++)
						{
							if(weight[i] == (j-weight[k-1]))
							{
								selected_items[i] = -2;
							}
						}
					}
				}
			}
			else
			{
				matrix[k][j] = matrix[k-1][j];
			}
		}
	}

	printf("Maximum Profit: %d Maximum Weight: %d\nSelected Items:\n",matrix[total_items][capacity],max_weight);


	for(i=0;i<total_items;i++)
	{
		if(selected_items[i] == -1 || selected_items[i] == -2)
		{
			printf("Item No. %d\n",i+1);
		}
	}

	fclose(ptr_file);
}
