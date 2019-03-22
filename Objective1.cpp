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
	int minP, maxP, start;
	int pattern;//interleaving pattern- randomly generate the # of request taken from each process  based on the # of request in each process, and store it here

};

//things that need to be done
//there is a bug in this function find it
////because it is causing done to come out as 109 instead of 100
vector <int> take(vector<int> s, P pro)//this function will deal with distribution of and interleaving
{
	int ran = pro.start;
	int u = 0;
	if(ran>pro.sequence.size())
		ran=0;	
	while (ran < pro.sequence.size())
	{

	//	if (pro.takeRequest < pro.pattern)
	//	{
	//			s.push_back(pro.sequence[ran]);// range of process
	//			u++;
	//	}
	//	else
		{
			if (pro.Distribution == 1)//seqeun
			{
					s.push_back(pro.sequence[ran]);
					u++;//checks to see if all require request where taken
	//		cout<<"KKKKLL  u= "<<u<<"ran= "<<ran<<"SIZE"<<pro.sequence.size()<<endl;
			}
			else//random
			{
	//		cout<<"UUUUUUUUKKKKLL"<<endl;
				int random = rand() % pro.sequence.size();// getting number for interleaving pattern for each process
					s.push_back(pro.sequence[random]);
					u++;
			}
		}
		ran++;
		if(ran==pro.sequence.size())
		{
			ran=0;	
		}
		if (u == pro.pattern)
		{
	//				cout<<"u= "<<u<<endl;
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
	if (!infile.is_open())
	{
		cout << "file not found" << endl;
	}
	else
	{
		int taketotal = 0;//will contain the total number of objects taken from all processes
		char line[1000];
		infile >> line;
		char *token;
		int numOfProcesses = 0;
		int loop = 0;
		P pro;
		//while(loop<numOfProcesses)
		while (!infile.eof())
		{
			numOfProcesses++;
			token = strtok(line, ",");
			int min = atoi(token);
			//cout<<"Min"<<min<<endl;
			token = strtok(NULL, ",");
			int max = atoi(token);
			//cout<<"Max"<<max<<endl;
			//token = strtok(NULL,",");
			//pro.start=atoi(token);
			int random = (rand() % max + min) % 10;// getting number for interleaving pattern for each process
			pro.pattern = random;
			//cout<<"Pattern"<<random<<endl;
			pro.max = max;
			pro.min = min;
			while (min <= max)
			{
				pro.sequence.push_back(min);
				min++;
			}
			token = strtok(NULL, ",");
			//cout<<"taketotal"<<token<<endl;
			pro.takeRequest = atoi(token);
			taketotal += atoi(token);
			token = strtok(NULL, ",");
			//cout << "start= " << token << endl;
			pro.start = atoi(token);
			//token = strtok(NULL,",");
			token = strtok(NULL, ",");
			//cout<<"Distribution"<<token<<endl;
			pro.Distribution = atoi(token);
			token = strtok(NULL, ",");
			//cout<<"MinP"<<token<<endl;
			pro.minP = atoi(token);
			token = strtok(NULL, ",");
			//cout<<"MaxP"<<token<<endl;
			pro.maxP = atoi(token);
			token = strtok(NULL, "\n");
			//cout<<"Order"<<token<<endl;
			pro.order = atoi(token);
			processes.push_back(pro);
			loop++;
			pro.sequence.clear();
			infile >> line;

			//cout<<"min= "<<pro.minP<<" max= "<<pro.maxP<<"Distribution:"<<pro.Distribution<<"Request to take: "<<pro.takeRequest<<"Pattern range: ["<<pro.minP<<":"<<pro.maxP<<"]"<<" Pattern order: "<<pro.order<<endl;
		}

		infile.close();
		int done = 0;
		int i = 0;
		srand(time(NULL));
		vector<int>  ran;
		vector <int>::iterator it;
		while (ran.size() < numOfProcesses)//forcing processes to run in sequence
		{
			int rando = 0;
			ran.push_back(rando);
			rando++;
		}
		int gp = 0;
		vector <int> seq;//1d integer vector
	//	cout<<"TakeTotal: "<<taketotal<<endl;
		vector<int>hol;
		int opi = 0;
		int op = 0;
		int io = 0;
	//		while ((done<taketotal)&&(op!=20)) //USED FOR TESTING
		while (done < taketotal)
		{
			if (i == numOfProcesses)
			{
				i = 0;
			}
			if (opi < numOfProcesses)
			{
				int go = processes[i].minP;
				processes[i].start = (find(processes[i].sequence.begin(),processes[i].sequence.end(),processes[i].start)-processes[i].sequence.begin());
				while (go < processes[i].maxP)
				{
					hol.push_back(go);
					go++;
				}
				opi++;
			}
			if (processes[i].order == 1)
			{
				if (gp == hol.size())
				{
					gp = 0;
				}
				processes[i].pattern = hol[gp];
				gp++;
		//	cout<<"Pattern of "<<"P"<<i<<" "<<processes[i].pattern<<endl;
			}
			if (processes[i].order == 2)
			{
				processes[i].pattern = rand() % processes[i].maxP;// getting number for interleaving pattern for each process	
		//	cout<<"Pattern of "<<"P"<<i<<" "<<processes[i].pattern<<endl;
			}
			if (processes[i].takeRequest < processes[i].pattern||((processes[i].takeRequest==0)&&(processes[i].pattern==0)))
			{
	//			cout << "Request :" << processes[i].takeRequest << "  pattern= " << processes[i].pattern << endl;
				if (processes[i].takeRequest == 0)
					io = 9;
				done += processes[i].takeRequest;
				processes[i].pattern = processes[i].takeRequest;
				processes[i].start += processes[i].pattern;
				//cout << "START = " << processes[i].start << endl;

				if (processes[i].start > processes[i].max)
					processes[i].start = processes[i].min;
				processes[i].takeRequest = 0;
				if (io != 9)//if request are zero than dont call function
					seq = take(seq, processes[i]);
	//				cout<<"seq= "<<seq.size()<<endl;
			}
			else
			{
	//			cout << "Request :" << processes[i].takeRequest << "  pattern= " << processes[i].pattern << endl;
				//				cout<<"Done ="<<done<<endl;
				done += processes[i].pattern;
				//cout << "START = " << processes[i].start << endl;
				if (processes[i].start > processes[i].max)
					processes[i].start = processes[i].min;
				if(processes[i].pattern!=0)
				{
					seq = take(seq, processes[i]);
	//			cout<<"BLUEBERRY PIE"<<endl;
				}//processes[i].start+=processes[i].takeRequest;
				processes[i].start += processes[i].pattern;

				processes[i].takeRequest -= processes[i].pattern;
	//		cout<<"1seq= "<<seq.size()<<endl;
			}
			io = 0;
	//		cout<<"Ddone= "<<done<<endl;
			op++;
			i++;
		}
	//		cout<<"Seq= "<<seq.size()<<endl;

		int g = 0;
		ofstream outFile;
		outFile.open("trace-SRR-SRS.txt");
		while (g < seq.size())
		{
			outFile<<seq[g]<<"\n";
			//cout << seq[g] << "\n";
			g++;
		}
		outFile.close();
	}
}





