#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>




int main(int argc, char*argv[])
{
	
	int SIZE=0;
	printf("Enter size of matrix:");
	scanf("%d",&SIZE);

	FILE *fp;
	char *token;
	int *len;
	char line[100];
	fp=fopen("request.txt","r");
	//2D MATRIX 
	int **Matrix=malloc(sizeof(int*)*2);//2
	Matrix[0]=malloc(sizeof(int)*SIZE);//1
	Matrix[1]=malloc(sizeof(int)*SIZE);//1
	//Matrix=4
	//2D MATRIX CREATED
	//i created a set number of traces. I am currently thinking of a way to let the number not be set.
	int **R;
	int timestamps=1;
	int j=0;
	int go=0;
	int numR=4;
	while (fgets(line, 100, fp)!=NULL)
	{
		if(j==0)
		{
			token= strtok(line,"\n");
			numR=atoi(token);//number of R in file
			R=malloc(sizeof(int*)*numR);
			len=malloc(sizeof(int)*numR);
			j++;

		}
		else
		{	
			token= strtok(line,":");
			int numNR=atoi(token);//number of items in each R
			int l;
			len[go]=numNR;
			R[go]=malloc(sizeof(int)*numNR);
			for(l=0;l<numNR-1;l++)
			{
				token= strtok(NULL,",");
			 	R[go][l]=atoi(token);
			}
				token= strtok(NULL,"\n");
				R[go][l]=atoi(token);
			go++;
		}
	}
	fclose(fp);
	j=0;
	int ran=0;
	int random=10;
	int zero=1;
	int hold=0;
	srand(time(NULL));
	for(timestamps=0;timestamps<SIZE;timestamps++)
	{
		zero=1;
		random=(rand()%numR-1+zero);
		//printf("random:0-3: %d\n",random);
		ran=(rand()%len[random]-1+zero);
		//printf("ran:0-9: %d\n",ran);
		hold=R[random][ran];//picks 1 item from 1 R	
		//printf("hold: %d\n",hold);
		
		Matrix[0][timestamps]=hold;
		Matrix[1][timestamps]=timestamps+1;
	}
	int h=0;
	int k=0;
	printf("Requests	|");
	for(j=0;j<2;j++)
	{
		for(k=0;k<SIZE;k++)
		{
			printf("%2d|",Matrix[j][k]);
		}
		if(h==0)
			printf("\nTimestamps	|");
		h++;
	}	
	printf("\n");
	k=0;
	while(k<numR)
	{
		free(R[k]);
		k++;
	}
	free(R);
	k=0;
	free(Matrix[0]);
	free(Matrix[1]);
	free(Matrix);
	free(len);

}
