#include <iostream>
using namespace std;
#include<fstream>
#include<vector>
#include<cstring>
#include<bits/stdc++.h>


class P
{
	public:
		vector<int> range;// range of process
		int takeRequest;// the amount to take from each process
		int max;
		int min;
		int Distribution;// how the interleaved pattern num of request are take for process
		//Ended up not using order
	int order;//this is for the interleaving pattern; the order that each group is taken. ex:P[0]-P[1]-P[2] or P[1]-P[0]-P[2] or P[2]-P[1]-P[0] etc..
		//in this case 1= sequencial, 2 equals random
		
		
		int pattern;//interleaving pattern- randomly generate the # of request taken from each process  based on the # of request in each process, and store it here
		
};

//things that need to be done
//there is a bug in this function find it
////because it is causing done to come out as 109 instead of 100
vector <int> take (vector<int> s , P pro)//this function will deal with distribution of and interleaving
{
	int u=0;
	int ran=0;
	while(ran<pro.range.size())
	{
		
		

		if(pro.takeRequest < pro.pattern)
		{

			if(pro.range[ran]!=-1)

			{	
				s.push_back(pro.range[ran]);
				u++;	
			}
		}
		else
		{	
			if(pro.Distribution==1)//seqeun
			{
				if(pro.range[ran]!=-1)
				{
					s.push_back(pro.range[ran]);
					pro.range[ran]=-1;
					u++;//checks to see if all require request where taken
				}
			}
			else//random
			{
				int random=rand()%pro.range.size();// getting number for interleaving pattern for each process
			//	cout<<"RAN: "<<random<<" Range size = "<<pro.range.size()<<endl;
			//	cout<<pro.range[random]<<endl;
				if(pro.range[random]!=-1)
                        	{
                        	        
					s.push_back(pro.range[random]);
                        	        pro.range[random]=-1;
                        	        u++;//checks to see if all require request where taken
                        	}

			}	
		}
		ran++;
		if(u==pro.pattern)
		{
			break;
		}
		
	}
	return s;
}



int main(int argc, char*argv[])
{
	vector <P> processes;//double vector created
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
		//cout<<line<<endl;
		//char hold [1000]=line;
		char *token ;
		token = strtok(line,",");
		//line =hold;
		int numOfProcesses= atoi(token);//number of processes in file
		token = strtok(NULL,",");
		int PatternType=atoi(token);
		int loop=0;
		P pro;
		while(loop<numOfProcesses)
		{
			token = strtok(NULL,",");
			int min=atoi(token);
			token = strtok(NULL,",");
			int max=atoi(token);
			int random=(rand()%max+min)%10;// getting number for interleaving pattern for each process
			pro.pattern=random;	
			pro.max=max;	
			pro.min=min;	
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
			//cout<<token<<endl;
			processes.push_back(pro);
			loop++;
			pro.range.clear();
		//cout<<"min= "<<pro.min<<" max= "<<max<<"Distribution:"<<pro.Distribution<<"Request to take: "<<pro.takeRequest<<"Pattern:"<<pro.pattern<<endl;
		}
		vector <int> seq;//1d integer vector
		int done =0;
       		//	numOfProcesses
		//cout<<"taketotal= "<<taketotal<<endl;
		int i =0;
		srand(time(NULL));
		vector<int>  ran;
		vector <int>::iterator it;
		if(PatternType==2)//randomly picked the order of the interleaving pattern
		{
			while (ran.size()<numOfProcesses)
			{
				int rando=rand()%numOfProcesses;// getting number for interleaving pattern for each process

				it = find(ran.begin(),ran.end(),rando);
				if (it==ran.end())
				{
					ran.push_back(rando);
				cout<<"random order"<<rando<<"ran.size()"<<ran.size()<<endl;
				}


			}	
		
		}
		int op=0;
		//while ((done<taketotal)&&(op!=20)) USED FOR TESTING
		while (done<taketotal)
		{
			if(i == numOfProcesses)
			{
				i=0;
			}
			if(((PatternType==1)&&(processes[i].takeRequest==0))||((PatternType==2)&&processes[ran[i]].takeRequest==0))
			{
				//cout<<"DONE PROCCESS ["<<ran[i]<<"]"<<endl;
				//cout<<"PROCESS.REQUEST= "<<processes[ran[i]].takeRequest<<endl;
			}	
			else if(PatternType ==1)//sequencial
			{			
			//forced interleaving pattern to be sequential
			

				if (processes[i].takeRequest<processes[i].pattern)
                        	{
					//cout<<"HELLO :"<<processes[i].takeRequest<<"  i= "<<i<<endl;
					//cout<<"REquest ="<<processes[i].takeRequest<<endl;
					done+=processes[i].takeRequest;
                                        processes[i].pattern=processes[i].takeRequest;
					processes[i].takeRequest=0;
					seq=take(seq,processes[i]);
                        	}	
				else
				{
					done+=processes[i].pattern;
					seq=take(seq,processes[i]);
					processes[i].takeRequest-=processes[i].pattern;
				}


			}
			else// random	
			{

                                if (processes[ran[i]].takeRequest<processes[ran[i]].pattern)
                                {
                          //            cout<<"HELLO :"<<processes[ran[i]].takeRequest<<"  i= "<<ran[i]<<endl;
                          //            cout<<"REquest ="<<processes[ran[i]].takeRequest<<endl;
                                        done+=processes[ran[i]].takeRequest;
                                        processes[ran[i]].pattern=processes[ran[i]].takeRequest;
                                        processes[ran[i]].takeRequest=0;
                               		seq=take(seq,processes[ran[i]]);
                                }
                                else
                                {       done+=processes[ran[i]].pattern;
                                	seq=take(seq,processes[ran[i]]);
					processes[ran[i]].takeRequest-=processes[ran[i]].pattern;
                                }

                                                          

			}

			//cout<<"done= "<<done<<endl;
			op++;	
			i++;
		}
		cout<<"seq= "<<seq.size()<<endl;
		int g=0;
        	while(g<seq.size())
        	{
                	cout<<seq[g]<<"|";
                	g++;
        	}
cout<<endl;/*
		int time=1;
	  while(time<seq.size())
                {
                        cout<<time<<"|";
                        time++;
                }
*/

	}

}





