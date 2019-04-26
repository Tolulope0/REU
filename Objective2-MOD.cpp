#include<iostream>
#include<fstream>
#include<vector>
#include<cstring>
#include<algorithm>
#include<list>
#include<bits/stdc++.h>
using namespace std;








	



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

	void display()
	{
		cout<<"Prefetch buffer: ";	
		for( list<int>::iterator it =buf.begin();it != buf.end();++it)
			cout<<(*it)<<" ";
		cout<<endl;	
	}
	void refer(int x)
	{

		if(my.find(x) == my.end())
		{

				miss++;
		if(check!=true){
			if(buf.size() ==csize)
			{

				int last=buf.back();
				buf.pop_back();
				my.erase(last);
			//	cout<<"MISS"<<endl;
			}
		}
	
		}
		else
		{
			buf.erase(my[x]);
			hit++;
			check=false;
		//	miss--;

		}

		if(check!=true){
		buf.push_front(x);
		my[x]=buf.begin();
		}
		check=false;
		display();
	}

};

int main()
{
	int LIMIT=4;
        LRU BUFFER(5);
	ifstream infile;
	char *token;	
	char line [10];
       	infile.open("trace-SRR-SRS.txt");
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
        	   	//cout<<"token = "<<token<<endl;
		       	token=strtok(line,"\n");
        	        sequence.push_back(atoi(token));
        	}
		sequence.pop_back();
		//cout<<"S Size = "<<sequence.size();
        	vector <int> Prebuff;
		//vector <int >bufferb;
		int h=0;
		int hi=0;
        	int counter=0;

		int  cat=0;
			bool PreOn=false;
                	check=false;

		vector <int>::iterator it;
        	/*
		while (counter <100)
		{
			int see=sequence[counter];
                	cout<<see<<endl;
			counter++;
		}
		*/

		miss++;
		while (counter <100)
        	{        

				if(Prebuff.size()>=LIMIT)
					hi=0;
				else
					hi=1;
			int see=sequence[counter];
                	cout<<see<<" MISS= "<<miss<<endl;

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
				{
					check=true;// do not prefetch for this
					BUFFER.refer((Prebuff[Prebuff.size()-1]));
				}
				else
					miss++;
				int g=	Prebuff[Prebuff.size()-1];
				g++;
//				cout<<"sequence[counter]= "<<sequence[counter]<<" Prebuff+1 ="<<g<<endl;
				
				if(sequence[counter]==((Prebuff[(Prebuff.size())-1])+1))
				{
//				
               // 			cout<<"CONTINUE"<<endl;
					Prebuff.push_back(sequence[counter]);
				
				}
				else if(Prebuff.size()<LIMIT)
				//else
				{
					Prebuff.clear();
					counter--;				//				cout<<"CLEAR"<<endl;
					cat=0;				
				}
				
				if((Prebuff.size()>=LIMIT))
				{
                                	cout<<"Long enough sequence!- MISS= "<<miss<<endl;
			//		cout<<"g = "<<g<<"see= "<<see<<endl;
					if(g!=see){
					PreOn=true;
					BUFFER.refer((Prebuff[Prebuff.size()-1]+1));
					BUFFER.refer((Prebuff[Prebuff.size()-1]+2));
					if(hi==0)
					{
					Prebuff.clear();
					counter--;				//				cout<<"CLEAR"<<endl;
					
					cat=0;				
					hi=1;
					}
					
					if(h==0)
					{
						miss-=2;
						h++;
					}
				h=0;
					}
				}

                	//	cout<<see<<" MISS= "<<miss<<endl;

			}

			counter++;
//LRU
		}
       	
		cout<<"Total number of hits: "<<hit<<" Total number of misses: "<<miss<<endl;
	float ratio =hit/miss;
		//cout<<"Hit/Mess ratio: "<<(float)(hit/miss)<<endl;
	//	cout<<"Hit/Mess ratio: "<<ratio<<endl;
	}

}
