#include<iostream>
#include<fstream>
#include<vector>
#include<cstring>
using namespace std;



int main()
{
        
	ifstream infile;
	char *token;	
	char line [10];
	//infile.open("request.txt");
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
		cout<<sequence.size();
        for(int u=0;u<100;u++)
		cout<<sequence[u]<<endl;
		vector <int> bufferb;
		int h=0;
        	int counter=0;
        	bool check=false;
        	int miss=0, hit=0;
        	while (counter <100)
        	{        
                	check=false;
			int see=sequence[counter];
                	cout<<see<<endl;
                	bufferb.push_back(see+1);
                	bufferb.push_back(see-1);
                	bufferb.push_back(see+50);	
                	counter++;
        		while(h<3)
        		{
                		if(sequence[counter]== bufferb[h])
                		{
                        		hit++;
               				check =true;
                		}
        			h++;
        		}
                        h=0;
        		bufferb.clear();
        		if(check==false)
        		{
        			miss++;
        		}
        	}
       		cout<<"Total number of hits: "<<hit<<" Total number of misses: "<<miss<<endl;
	}

}
