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
	int Process_Max_Num;
	int Process_Min_Num;
	int Process_Distribution;// how the interleaved pattern num of request are take for process
	int Pattern_Distribution;//Pattern Distribution
	//in this case 1= sequencial, 2 equals random
	int Pattern_Min_Num, Pattern_Max_Num, Start;
	int pattern;//interleaving pattern- randomly generate the # of request taken from each process  based on the # of request in each process, and store it here

};

//things that need to be done
//there is a bug in this function find it
////because it is causing done to come out as 109 instead of 100
vector <int> take(vector<int> s, P pro)//this function will deal with Process_Distribution of and interleaving
{
	int ran = pro.Start;
	int u = 0;
	if(ran>pro.sequence.size())
		ran=0;
	while (ran < pro.sequence.size())//endless loop
	{

		{
			if (pro.Process_Distribution == 1)//seqeun
			{
					s.push_back(pro.sequence[ran]);
					u++;//checks to see if all required request where taken
			}
			else//random
			{
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
		while (!infile.eof())
		{
			numOfProcesses++;
			token = strtok(line, ",");
			int Process_Min_Num = atoi(token);
			//cout<<"Process_Min_Num"<<Process_Min_Num<<endl;
			token = strtok(NULL, ",");
			int Process_Max_Num = atoi(token);
			pro.pattern = 0;
			//cout<<"Pattern"<<random<<endl;
			pro.Process_Max_Num = Process_Max_Num;
			pro.Process_Min_Num = Process_Min_Num;
			while (Process_Min_Num <= Process_Max_Num)
			{
				pro.sequence.push_back(Process_Min_Num);
				Process_Min_Num++;
			}
			token = strtok(NULL, ",");
			//cout<<"taketotal"<<token<<endl;
			pro.takeRequest = atoi(token);
			taketotal += atoi(token);
			//token = strtok(NULL, ",");
			//cout << "Start= " << token << endl;
			pro.Start = pro.Process_Min_Num;
			//token = strtok(NULL,",");
			token = strtok(NULL, ",");
			//cout<<"Process_Distribution"<<token<<endl;
			pro.Process_Distribution = atoi(token);
			token = strtok(NULL, ",");
			//cout<<"Pattern_Min_Num"<<token<<endl;
			pro.Pattern_Min_Num = atoi(token);
			token = strtok(NULL, ",");
			//cout<<"Pattern_Max_Num"<<token<<endl;
			pro.Pattern_Max_Num = atoi(token);
			token = strtok(NULL, "\n");
			//cout<<"Pattern_Distribution"<<token<<endl;
			pro.Pattern_Distribution = atoi(token);
			processes.push_back(pro);
			loop++;
			pro.sequence.clear();
			infile >> line;

			//cout<<"Process_Min_Num= "<<pro.Pattern_Min_Num<<" Process_Max_Num= "<<pro.Pattern_Max_Num<<"Process_Distribution:"<<pro.Process_Distribution<<"Request to take: "<<pro.takeRequest<<"Pattern range: ["<<pro.Pattern_Min_Num<<":"<<pro.Pattern_Max_Num<<"]"<<" Pattern Pattern_Distribution: "<<pro.Pattern_Distribution<<endl;
		}

		infile.close();
		int done = 0;
		int i = 0;
		srand(time(NULL));
		vector<int>  ran;
		vector <int>::iterator it;
		while (ran.size() < numOfProcesses)//forcing processes to run in sequence
		{//(P[0]-P[1]-P[2])

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
			if (i == numOfProcesses)//makes sure index i does not go out of bounds
			{
				i = 0;
			}
			if (opi < numOfProcesses)//make sure sequ will start from order
			{
					processes[i].Start = processes[i].Process_Min_Num;
					opi++;
			}
			if (processes[i].Pattern_Distribution == 1)
			{

				if(processes[i].pattern>processes[i].Pattern_Max_Num||processes[i].pattern==0)//keeps sequencial pattern in bounds of pattern limits
					processes[i].pattern=processes[i].Pattern_Min_Num;


			}
			if (processes[i].Pattern_Distribution == 2)
			{
				processes[i].pattern = processes[i].Pattern_Min_Num+(rand() % ((processes[i].Pattern_Max_Num+1)-processes[i].Pattern_Min_Num));// getting number for interleaving pattern for each process
			}
			if (processes[i].takeRequest < processes[i].pattern||((processes[i].takeRequest==0)&&(processes[i].pattern==0)))
			{
	//			cout << "Request :" << processes[i].takeRequest << "  pattern= " << processes[i].pattern << endl;
				if (processes[i].takeRequest == 0)
					io = 9;
					//take remainder of request
				done += processes[i].takeRequest;
				processes[i].pattern = processes[i].takeRequest;
				processes[i].Start += processes[i].pattern;
				//cout << "Start = " << processes[i].Start << endl;

				if (processes[i].Start > processes[i].Process_Max_Num)
					processes[i].Start = processes[i].Process_Min_Num;
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
				//cout << "Start = " << processes[i].Start << endl;
				if (processes[i].Start > processes[i].Process_Max_Num)
					processes[i].Start = processes[i].Process_Min_Num;
				if(processes[i].pattern!=0)
				{
					seq = take(seq, processes[i]);
	//			cout<<"BLUEBERRY PIE"<<endl;
				}//processes[i].Start+=processes[i].takeRequest;
				processes[i].Start += processes[i].pattern;

				processes[i].takeRequest -= processes[i].pattern;
	//		cout<<"1seq= "<<seq.size()<<endl;
			}
			io = 0;
			processes[i].pattern++;//used for sequencial interleaving Pattern
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
			cout << seq[g] << "\n";
			g++;
		}
		outFile.close();
	}
}
