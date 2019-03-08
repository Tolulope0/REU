#include<iostream>
#include<fstream>
#include<vector>
#include<cstring>
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


int main()
{
        
	ifstream infile;
	char *token;	
	char line [10];
       	infile.open("trace-SRS-SRS.txt");
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
		//cout<<sequence.size();
        	vector <Buff> Prebuff;
		vector <int >bufferb;
		int h=0;
        	int counter=0;
        	bool check=false;
		int  cat=0;
        	int miss=0, hit=0;
		vector <int>::iterator it;
        	while (counter <100)
        	{        
                	check=false;
			int see=sequence[counter];
                	cout<<see<<endl;

			if(cat==0)
			{
                		cout<<"HI"<<endl;
				bufferb.push_back(see);
				cat=100;
			}
			if(Prebuff.size()!=0)
			{
			
				while(h<Prebuff.size())
                        	{
                                	cout<<"seq: "<<sequence[counter]<<" Prebuff: "<<Prebuff[h].value<<endl;
					if(sequence[counter]== Prebuff[h].value)
                                	{
                                	     	Prebuff[h].used++;
					     	hit++;
                                	        check =true;
                                	}
                                	h++;
                        	}
			h=0;
			}	
				cout<<"buffer = "<<bufferb[bufferb.size()-1]+1<<endl;
			if(see==bufferb[bufferb.size()-1]+1)
			{	
				bufferb.push_back(see);
				cout<<"see = "<<see<<endl;
			}
			else
			{		if(bufferb.size()==5)
				{
					Prebuff.push_back(Buff(see+1));	//start prefetching for this sequence
					Prebuff.push_back(Buff(see+2));	//start prefetching for this sequence
					Prebuff.push_back(Buff(see+3));	//start prefetching for this sequence
				}
				else
				{	
					bufferb.clear();
				cat=0;
				cout<<"see =n C"<<cat<<endl;
				}
		/*	bufferb.push_back(see-1);
                	bufferb.push_back(see+50);	
                */
			}
			counter++;
        	//	bufferb.clear();
        		if(check==false)
        		{
        			miss++;
        		}

//LRU
			if(Prebuff.size()==10)//size of prefetch block is 10
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
        	}
       		cout<<"Total number of hits: "<<hit<<" Total number of misses: "<<miss<<endl;
	}

}
