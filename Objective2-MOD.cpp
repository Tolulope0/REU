#include<iostream>
#include<fstream>
#include<vector>
#include<cstring>
#include<algorithm>
#include<bits/stdc++.h>
using namespace std;
class Buff
{
	public:
	int value;
	int used=0;
	Buff(int v)
	{
		value=v;
	
	}
};

int miss=0, hit=0;
bool check=false;
class LRU
{
	list<int>buf;
	unordered_map<int,list<int>::iterator>my;
	int csize;

	public:
	LRU(int n)
	{
		csize=n;
	}	
	void refer(int x)
	{
		if(my.find(x) == my.end())
		{
			miss++;
			if(buf.size() ==csize)
			{
				int last=buf.back();
				buf.pop_back();
				my.erase(last);
				


			//	cout<<"MISS"<<endl;
			}

	
		}
		else
		{
			buf.erase(my[x]);
			hit++;

			check=true;

		}
		buf.push_front(x);
		my[x]=buf.begin();
	}

};

int main()
{
        LRU BUFFER(5);
	ifstream infile;
	char *token;	
	char line [10];
       	infile.open("trace-SSS-SRS.txt");
        if(!infile.is_open())
        {
                cout<<"file not found"<<endl;
        }
	else
        {
        	vector<int> sequence;
        	infile>>line;
        	token=strtok(line,"\n");
        	sequence.clear();
        	sequence.push_back(atoi(token));
        	while(!infile.eof())
        	{	infile>>line;
        	   	cout<<"token = "<<token<<endl;
		       	token=strtok(line,"\n");
        	        sequence.push_back(atoi(token));
        	}
		sequence.pop_back();
		//cout<<"S Size = "<<sequence.size();
        	vector <int> Prebuff;
		//vector <int >bufferb;
		int h=0;
        	int counter=0;

		int  cat=0;
			bool PreOn=false;

		vector <int>::iterator it;
        	/*
		while (counter <100)
		{
			int see=sequence[counter];
                	cout<<see<<endl;
			counter++;
		}
		*/
		while (counter <100)
        	{        
                	check=false;
			int see=sequence[counter];
                	cout<<see<<endl;

			if(cat==0)//beginning of sequence
			{
  //              		cout<<"START"<<endl;
				Prebuff.push_back(sequence[counter]);
//				cout<<"Prebuff "<<Prebuff[Prebuff.size()-1]<<endl;
				cat=100;
			}
			else
			{	
				if(PreOn==true)
					BUFFER.refer((Prebuff[h]));
				int g=	Prebuff[Prebuff.size()-1];
				g++;
//				cout<<"sequence[counter]= "<<sequence[counter]<<" Prebuff+1 ="<<g<<endl;
				
				if(sequence[counter]==((Prebuff[(Prebuff.size())-1])+1))
				{
//				
               // 			cout<<"CONTINUE"<<endl;
					Prebuff.push_back(sequence[counter]);
				
				}
				else
				{	
					Prebuff.clear();
			//		Prebuff.push_back(sequence[counter]);
					counter--;
//					cout<<"CLEAR"<<endl;
					cat=0;
				}
				if((Prebuff.size()==5))
				{
//                                	cout<<"Long enough sequence!"<<endl;
			 PreOn=true;
				
					while(h<Prebuff.size())
                        		{

						BUFFER.refer((Prebuff[h]+1));
						BUFFER.refer((Prebuff[h]+2));
					//Prebuff.push_back(Buff(see+2));	//start prefetching for this sequence
					//Prebuff.push_back(Buff(see+3));	//start prefetching for this sequence
					/*if(sequence[counter]== Prebuff[h])
                                	{
                                	     	Prebuff[h].used++;
					     	hit++;
                                	        check =true;
                                	}*/
                                		h++;
                        		}
			
					h=0;
				}	
				else if(PreOn=false)
				{
				miss++;
				}
			//	cout<<"buffer = "<<bufferb[bufferb.size()-1]+1<<endl;
		/*	if(see==bufferb[bufferb.size()-1]+1)
			{	
				bufferb.push_back(see);
				cout<<"see = "<<see<<endl;
			}
			else
			{		if(bufferb.size()==5)

				}
				else
				{	
					bufferb.clear();
				cat=0;
				cout<<"see =n C"<<cat<<endl;
				}
	*/	/*	bufferb.push_back(see-1);
                	bufferb.push_back(see+50);	
                */
	//		}
			}

        	//	bufferb.clear();
	       	//	if(check==false)
        	//	{
        		//	miss++;
        	//	}
			//else
			//	hit++;
			counter++;
//LRU
	/*		if(Prebuff.size()==10)//size of prefetch block is 10
			{
				int fo=0;int hold;
				while(fo<9)
				{
					if(Prebuff[fo].used<Prebuff[fo+1].used)
						hold=fo;
					else
						hold =fo+1;
					fo++;
				}
				Prebuff.erase(Prebuff.begin()+hold);
	
			}	
        	*/
		}
       	
		cout<<"Total number of hits: "<<hit<<" Total number of misses: "<<miss<<endl;
	}

}
