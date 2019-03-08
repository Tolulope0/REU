#include <iostream>
using namespace std;
#include<fstream>
#include<vector>
#include<cstring>
#include<bits/stdc++.h>


class P
{
	public:
		vector<int> sequence;// range of process
		int takeRequest;// the amount to take from each process
		int max;
		int min;
		int Distribution;// how the interleaved pattern num of request are take for process
		//Ended up not using order
		int order;//this is for the interleaving pattern; the order that each group is taken. ex:P[0]-P[1]-P[2] or P[1]-P[0]-P[2] or P[2]-P[1]-P[0] etc..
		//in this case 1= sequencial, 2 equals random
		int minP,maxP;
		
		int pattern;//interleaving pattern- randomly generate the # of request taken from each process  based on the # of request in each process, and store it here
		
};

//things that need to be done
//there is a bug in this function find it
////because it is causing done to come out as 109 instead of 100
vector <int> take (vector<int> s , P pro)//this function will deal with distribution of and interleaving
{
	int u=0;
	int ran=0;
	while(ran<pro.sequence.size())
	{
		if(pro.takeRequest < pro.pattern)
		{

			if(pro.sequence[ran]!=-1)

			{	
				s.push_back(pro.sequence[ran]);// range of process
					pro.sequence[ran]=-1;
				u++;	
			}
		}
		else
		{	
			if(pro.Distribution==1)//seqeun
			{
				
				if(pro.sequence[ran]!=-1)
				{
					s.push_back(pro.sequence[ran]);
					u++;//checks to see if all require request where taken
					pro.sequence[ran]=-1;
				}
			}
			else//random
			{
				int random=rand()%pro.sequence.size();// getting number for interleaving pattern for each process
			//	cout<<"RAN: "<<random<<" Range size = "<<pro.range.size()<<endl;
                        	        
					if(pro.sequence[ran]!=-1)
					{	
						s.push_back(pro.sequence[random]);
                        	        	u++;//checks to see if all require request where taken
					}

			}	
		}
		ran++;
		if(u==pro.pattern)
		{
	//		cout<<"u="<<u<<endl;
			break;
		}
		
	}
	return s;
}



int main(int argc, char*argv[])
{
	vector <P> processes;//double vector created
	ifstream infile;
	infile.open("input.txt");
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
		//token = strtok(line,",");
		//line =hold;
		int numOfProcesses=0;
		//= atoi(token);//number of processes in file
		//token = strtok(NULL,",");
		//int PatternType=0;
		//	atoi(token);
		int loop=0;
		P pro;
		//while(loop<numOfProcesses)
		while (!infile.eof())
		{
			numOfProcesses++;
			token = strtok(line,",");
			int min=atoi(token);
			token = strtok(NULL,",");
			int max=atoi(token);
			int random=(rand()%max+min)%10;// getting number for interleaving pattern for each process
			pro.pattern=random;	
			pro.max=max;	
			pro.min=min;	
			while (min<=max)
			{
				pro.sequence.push_back(min);
				min++;
			}
			token = strtok(NULL,",");
			taketotal+=atoi(token);
			pro.takeRequest=atoi(token);
			token = strtok(NULL,",");
			pro.Distribution=atoi(token);
			token = strtok(NULL,",");
			pro.minP=atoi(token);
			token = strtok(NULL,",");
			pro.maxP=atoi(token);
			token = strtok(NULL,"\n");
			pro.order=atoi(token);
			//cout<<token<<endl;
			processes.push_back(pro);
			loop++;
			pro.sequence.clear();
			infile>>line;
	//	cout<<"min= "<<pro.min<<" max= "<<max<<"Distribution:"<<pro.Distribution<<"Request to take: "<<pro.takeRequest<<"Pattern range: ["<<pro.minP<<":"<<pro.maxP<<"]"<<" Pattern order: "<<pro.order<<endl;
		}
		
		infile.close();
		
		

		int done =0;
       		//	numOfProcesses
		//cout<<"taketotal= "<<taketotal<<endl;
		int i =0;
		srand(time(NULL));
		vector<int>  ran;
		vector <int>::iterator it;
		while (ran.size()<numOfProcesses)//forcing processes to run in sequence
		{
			int rando =0;
			ran.push_back(rando);
			rando++;
					//		cout<<"random order"<<rando<<"ran.size()"<<ran.size()<<endl;
		}


			
		int gp=0;
//		vector<int>seq;	
		vector <int> seq;//1d integer vector

		vector<int>hol;	
		int opi=0;
		int op=0;
                int io=0;
	//	while ((done<taketotal)&&(op!=20)) //USED FOR TESTING
		while (done<taketotal)
		{
			 if(i == numOfProcesses)
                        {
                                i=0;
                                opi++;
                        }

			 
                	if(opi==0)
			{
        			int go=processes[i].minP;
				while(go<processes[i].maxP)
				{
                			hol.push_back(go);
                			go++;
		
				}

			}
      			if(processes[i].order == 1)
        		{
				if(gp==hol.size())
				{
					gp=0;
				}
                        
              			processes[i].pattern=hol[gp];
				gp++;

        		}
        		if(processes[i].order == 2)
        		{
				processes[i].pattern=rand()%processes[i].maxP;// getting number for interleaving pattern for each process	
			}
			if (processes[i].takeRequest<processes[i].pattern)
                 	{
          //                	        cout<<"Request :"<<processes[i].takeRequest<<"  pattern= "<<processes[i].pattern<<endl;
				if(processes[i].takeRequest==0)
					io=9;
				done+=processes[i].takeRequest;
                                processes[i].pattern=processes[i].takeRequest;
				processes[i].takeRequest=0;
				if(io!=9)//if request are zero than dont call function
					seq=take(seq,processes[i]);
	//	cout<<"seq= "<<seq.size()<<endl;
                        }	
			else
			{
        //                  	        cout<<"Request :"<<processes[i].takeRequest<<"  pattern= "<<processes[i].pattern<<endl;
					//cout<<"Done ="<<done<<endl;
				done+=processes[i].pattern;
				seq=take(seq,processes[i]);
		
				processes[i].takeRequest-=processes[i].pattern;
	//	cout<<"seq= "<<seq.size()<<endl;
			}

		
		io=0;
	//		cout<<"done= "<<done<<endl;
		op++;	
		i++;
	}
	//	cout<<"seq= "<<seq.size()<<endl;
	int g=0;
       ofstream outFile;
       outFile.open("trace-SRS-SRS.txt");
       	while(g<seq.size())
        {
               outFile<<seq[g]<<"\n";
               	//cout<<seq[g]<<"\n";
                g++;
        }
	outFile.close();
	
	
	
	}

}





