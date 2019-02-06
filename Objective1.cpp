#include <iostream>
using namespace std;
#include<fstream>
#include<vector>
#include<cstring>
class P
{
	public:
		vector<int> range;
		int takeRequest;

		int Distribution;//
		int order;//this is for the interleaving pattern; the order that each group is taken
		//in this case 1= sequencial, 2 equals random
		
		
		int pattern;//interleaving pattern- randomly generate the # of request taken from each process  based on the # of request in each process, and store it here
		
};


vector <int >take(vector<int>s , P pro )
{


return s;
}
int main(int argc, char*argv[])
{
	vector <P> processes;//double vector created
	//a vector of vectors of integers.
	ifstream infile;
	infile.open("standardrequest.txt");
	if(!infile.is_open())
	{
		cout<<"file not found"<<endl;
	}
	else
	{
		int taketotal=0;//will contain the total number of objects taken from all processes
		char line[1000];
		infile>> line;
		cout<<line<<endl;
		//char hold [1000]=line;
		char *token ;
		token = strtok(line,",");
		//line =hold;
		int numOfProcesses= atoi(token);//number of processes in file
		cout<<"File: "<<line<<"\n Pnum="<<numOfProcesses<<endl;
		int loop=0;
		P pro;
		while(loop<numOfProcesses)
		{
			token = strtok(NULL,",");
			int min=atoi(token);
			token = strtok(NULL,",");
			int max=atoi(token);
			int random=(rand()%max-1+min);// getting number for interleaving pattern
			pro.pattern=random;	
			while (min<=max)
			{
				pro.range.push_back(min);
				min++;
			}
			token = strtok(NULL,",");
			taketotal+=atoi(token);
			pro.takeRequest=atoi(token);
			token = strtok(NULL,",");
			pro.Distribution=atoi(token);
			token = strtok(NULL,",");
			pro.order=atoi(token);
			cout<<token<<endl;
			processes.push_back(pro);
			loop++;
			pro.range.clear();
		}
		vector <int> seq;
		int done =0;
       		//	numOfProcesses
		cout<<"taketotal= "<<taketotal<<endl;
		int i =0;
		while (done<taketotal)
		{
			if(i == numOfProcesses)
			{
				i=0;
			}
			if (processes[i].takeRequest==0)
			{
				//done++;
			}
			else
			{
			//forced interleaving pattern to be sequential
			seq=take(seq,processes[i]);
			done+=processes[i].pattern;
			}	
	
	
			i++;
		}
}















}





