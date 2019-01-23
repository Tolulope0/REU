#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>




int main(int argc, char*argv[])
{
	int SIZE=100;
	FILE *fp;
	char *token;
	int *len;
	char line[100];
	fp=fopen("request.txt","r");
	//2D MATRIX 
	int **Matrix=malloc(sizeof(int*)*2);
	Matrix[0]=malloc(sizeof(int)*SIZE);
	Matrix[1]=malloc(sizeof(int)*SIZE);
	//2D MATRIX CREATED
	//i created a set number of traces. I am currently thinking of a way to let the number not be set.
	int **R;
	int timestamps=1;
	int j=0;
	int go=0;
	int numR=0;
	while (fgets(line, 100, fp)!=NULL)
	{
		//	printf("%s",line);
		if(j==0)
		{
			token= strtok(line,"\n");
			numR=atoi(token);//number of R in file
			R=malloc(sizeof(int*)*numR);

			j++;

		}
		else
			token= strtok(NULL,":");
			int numNR=atoi(token);//number of items in each R
			int l;
			len=malloc(sizeof(int)*numNR);
			R[go]=malloc(sizeof(int)*numNR);
			for(l=0;l<numNR;l++)
			{
				token= strtok(NULL,",");
				R[go][l]=atoi(token);
			}
			go++;

	}
	//int **Requests=malloc(sizeof(int*)*j);
	fclose(fp);
	j=0;

	for(timestamps=1;timestamps<SIZE+1;timestamps++)
	{
		srand(time(NULL));
		int hold;
		int zero=0;
		int random=(rand()%zero+numR);
		{
			int ran=(rand()%zero+len[random]);
			hold=R[random][ran];//picks 1 item from 1 R	
		}
		Matrix[0][0]=hold;
		Matrix[1][0]=timestamps;
	}

	int k=0;
	while(k<numR)
	{
	free(R[k]);
	k++;
	}
	free(R);
	k=0;
	while(k<SIZE)
	{
	free(Matrix[0]);
	free(Matrix[1]);
	}
	free(Matrix);
	free(len);

}