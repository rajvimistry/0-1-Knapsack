#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(int argc,char *argv[])
{
	FILE *ptr_file;
	char buf[100],total_elements[1];
	int i=0, total_items = 1, capacity = 0;
	char *tok;

	//open and read from file
  	ptr_file =fopen(argv[1],"r");
    	if (!ptr_file)
        	printf("Unable to open a file");

	fscanf(ptr_file,"%[^\n]",total_elements);

	fgets(buf,10,ptr_file);

	total_items = atoi(total_elements);

	int weight[total_items];
	int profit[total_items];
	
	fscanf(ptr_file,"%[^\n]",buf);

	tok = strtok(buf,", ");


	//tokenization of weight and profit and store it into an array
	while(tok!=NULL)
	{
		weight[i] = atoi(tok);
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

	int max_profit = 0, total_weight, max_weight = 0;
	int final_selected_items[total_items], temp_selected_items[total_items];
	int subset = 1,j,k;

	//find a total number of subsets
	for(i=0; i<total_items; i++)
	{
		subset = subset*2;
		final_selected_items[i] = -1;
	}

	//computing all subsets, weight and profit of each subset and comapare it to max_profit
	for(i=0; i<subset; i++)
	{

		for(k=0; k<total_items; k++)
		{
			temp_selected_items[k] = -1;
		}

		int temp = 0, total_profit = 0;
		total_weight = 0;

		for(j=0;j<total_items;j++)
		{
			if(i&(1<<j))
			{
				total_profit = total_profit + profit[j];
				total_weight = total_weight + weight[j];
				for(k=0;k<total_items;k++)
				{
					if(temp_selected_items[k]==-1)
					{
						temp_selected_items[k]=j+1;
						break;
					}
				}

				if(max_profit < total_profit && total_weight <= capacity)
				{
					max_profit = total_profit;max_weight = total_weight;
					for(k=0;k<total_items;k++)
					{
						final_selected_items[k]=temp_selected_items[k];
					}
				}
			}
		}
	}

	printf("Total Profit: %d\nTotal Weight: %d\nSelected Items: ",max_profit,max_weight);

	for(k=0;k<total_items;k++)
	{
		if(final_selected_items[k]!=-1)
		{
			printf("%d ",final_selected_items[k]);
		}
	}

	fclose(ptr_file);
}
