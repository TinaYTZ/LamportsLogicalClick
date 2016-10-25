//
//  main.cpp
//  Assignment1
//
//
//
//  project1.cpp
//  Project1
//
//written by: Yunting Zhang (dropped class)
//modified by: Eric Simmons
//does not allow multiple receives to one send.

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <sstream>
#include <string>
#include <cstring>
#include <stdlib.h>

using namespace std;

class Activity{
    private:
    string name;
    int time;
    public:
    void setname(string n){
        name=n;
    }
    string getname(){
        return name;
    }
    int gettime(){
        return time;
    }
    void settime(int t){
         time=t;
    }

};



class Process{
    private:
    vector<Activity> activities;
    int p_No;
    public:
    void pushActivity(string s){
        istringstream iss(s);
        while (iss){
            string sub;
            iss >> sub;
            if(sub!=""){
                Activity n;
                n.settime(atoi(sub.c_str()));
                activities.push_back(n);
            }
        }
    }
    void setPno(int i){
        p_No=i;
    }
    int getPno(){
    return p_No;
    }
    int getSize(){
        return (int)activities.size();
    }
    int  getTime(int j){
        return activities[j].gettime();
    }
    void setName(int j, string name){
        
        activities[j].setname(name);
    }
    string getName(int j){
        return  activities[j].getname();
    }
    void printActivityTime(ofstream& out){
        int len=getSize();
        for(int i=0;i<len;i++){
            cout<<activities[i].gettime()<<"  ";
            out<<activities[i].gettime()<<"  ";
        }
        cout<<endl;
        out << endl;
    }
    void printAName(ofstream& out)
    { for(int i=0; i<getSize();i++)
         {
            cout<<getName(i)<<"   ";
	    out<<getName(i)<<"   ";
         }
        cout<<endl;
    	out << endl;
    }
    
    
};


class Log{
    int pnum;
    int anum;
    int time;
    int dtag; //0 independ 1 depend
public:
    void setLog(int pNum, int t, int aNum ){
        pnum=pNum;
        time=t;
        anum=aNum;
        dtag=-1;   //default
    }
    void setDtag(int d){
        dtag=d;
    }
    int getT(){
        return time;}
    int getP(){
        return pnum;}
    int getA(){
        return anum;}
    int getD(){
        return dtag;}
    
};

queue<string> abc;
//send recieve
queue<string> sendRec;

void initNameQueue(int num)
{
    for(int i=0;i<num; i++)
    {  string c;
        c=97+i;
        abc.push(c);
    }
    sendRec.push("s1");
    sendRec.push("r1");
    sendRec.push("s2");
    sendRec.push("r2");
    sendRec.push("s3");
    sendRec.push("r3");
    sendRec.push("s4");
    sendRec.push("r4");
    sendRec.push("s5");
    sendRec.push("r5");
    sendRec.push("s6");
    sendRec.push("r6");
    sendRec.push("s7");
    sendRec.push("r7");
    sendRec.push("s8");
    sendRec.push("r8");
    sendRec.push("s9");
    sendRec.push("r9");
    sendRec.push("s10");
    sendRec.push("r10");
    sendRec.push("s11");
    sendRec.push("r11");
    sendRec.push("s12");
    sendRec.push("r13");
    sendRec.push("s13");
    sendRec.push("r14");
    sendRec.push("s14");
    sendRec.push("r15");
    sendRec.push("s15");
    sendRec.push("r16");
    sendRec.push("s16");
    sendRec.push("r17");
    sendRec.push("s17");
    sendRec.push("r18");
    sendRec.push("s18");
    sendRec.push("r19");
    sendRec.push("s19");
    sendRec.push("r20");
    sendRec.push("s20");
}

/*created by Eric to fix the error that wouldn't allow for multiple receives
searches the log for any activies who occur before i and their depedency = 1, if their time = i's time return true else if we make it to the end without finding a match return false*/
bool duplicateReceives(int i, vector<Log> log)
{
  for(int j=i-1; j>=0;j--)
	{
		if(log[j].getD() == 1 && log[i].getT()==log[j].getT())
			return true;
	}
	return false;
}

void orderAllActivity(vector<Process> processes, ofstream& out)
{   vector<Log> log;
    //create the queue, log, it is composed of activities with their time and process number
    int len=(int)processes.size();
    for( int i=0;i<len;i++ )
    {
        for(int j=0;j<processes[i].getSize();j++)
        {
            if( processes[i].getTime(j)!= 0)
            {
                Log l;
                l.setLog(processes[i].getPno(), processes[i].getTime(j),j );
                log.push_back(l);
            }
            else
            {
                processes[i].setName(j,"null");

            }
        }
    }
    
    //order the queue, if the queue is out of order throw up an error
    int seq=1;
    for(int i=0; i<log.size();i++)
    {
        for(int j=i; j<log.size();j++)
            {    if (log[i].getT()>log[j].getT())
                    {
                        Log tem=log[i];
                        log[i]=log[j];
                        log[j]=tem;
                    }
            }
        if(log[i].getT()<=seq)
        {   if(log[i].getT()==seq)
        {seq+=1;
        }
        }
        else{
	     out << "incorrect\n";
   	     cout<<"incorrect\n";
            out.close();
            exit(0);
        }

    }
   //error will be here downward
   //p stands for process
    int p;
    for(int i=0; i<log.size();i++)
    {
            p=log[i].getP();
		//if the activity time is 1, the dTag will be 0
            if(log[i].getT()==1)
            {
                log[i].setDtag(0);
                continue;
            }

            for (int j=0; j<i;j++)
            {   if(log[j].getP()==p)
		//check if there is multiple times in the same process if so, throw an error
                {   if(log[j].getT()==log[i].getT())
                    {
                        
			out <<"incorrect"<<endl;
		        cout<<"incorrect"<<endl;
			out.close();
                        exit(0);
                    }
			//if at anytime a consectutve numbering of time occurs on the same process set their dependency tag to 0
                    if( log[j].getT()+1==log[i].getT())
                    {
                        log[i].setDtag(0);
                        break;
                    }
                }
            }
		//if the depency tag is still not 0
            if(log[i].getD()==-1)
                {  for(int j=i-1; j>=0;j--)
                    {   
			//here is the error that doesn't allow multiple receives
			if(log[j].getT()+1==log[i].getT())
                            {   //if(log[j].getD()==0)
                                  //{
                                   log[j].setDtag(1);
                                   log[i].setDtag(1);
                                   break;
                                   //}
                            }
                    }
                    if(log[i].getD()==-1)
                    {
		     out <<"incorrect";
		     cout<<"incorrect"<<endl;
		     out.close();
                     exit(0);
                    }
                }
    }
    
    
    
    int a;
	//used to keep track of the lastReceive outputed
    string lastRec;
    for(int i=0; i<log.size();i++)
    {
	p=log[i].getP();
        a=log[i].getA();
            if(log[i].getD()==0)
            {   string ab=abc.front();
                processes[p-1].setName(a, ab);
                abc.pop();
            }
            else
		{
		//this part needs to be changed to allow for correct labeling of multiple of receives. FIXED
		if(duplicateReceives(i,log))
		{
				processes[p-1].setName(a, lastRec);
		}
		else
		{
               	 	string sr=sendRec.front();
			lastRec = sr;
                	processes[p-1].setName(a, sr);
               		 sendRec.pop();
		}
		}
      }

    for(int i=0; i<processes.size();i++)
    {
        processes[i].printAName(out);
        
    }
    

}





int main(){
    
    
    vector<Process> processes;
    
    
   // ifstream in(*argv);
    ifstream in("input.txt");
    ofstream out("output.txt");
    string temp;
    string str;
    int count=1;
    while(getline(in,temp))
    {
        Process px;
        px.pushActivity(temp);
        px.setPno(count);
        processes.push_back(px);
        count++;
    }
    
    initNameQueue(20);
    
    orderAllActivity(processes, out);
}
