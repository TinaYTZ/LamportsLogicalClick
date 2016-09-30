//
//  project1.cpp
//  Project1
//
//  Created by Tina Zhang on 9/27/16.
//
//

#include <iostream>
#include <queue>
#include <vector>
#include <sstream>

using namespace std;

class Activity{
public:
    string name;
    int time;
    void setName(string x){
        name=x;
    }
    string getname(){
        return name;
    }
    int gettime(){
        return time;
    }
};


class Process{
public:
    vector<Activity> activities;
    int p_No;
    
    void pushActivity(string s){
        istringstream iss(s);
        while (iss){
            string sub;
            iss >> sub;
            if(sub!=""){
                Activity n;
                n.time = atoi(sub.c_str());
                activities.push_back(n);
            }
        }
    }
    int getSize(){
        return activities.size();
    }
    int  getTime(int j){
        return activities[j].gettime();
    }
    void setName(int j, string name){
        
        activities[j].setName(name);
    }
    string getName(int j){
        return          activities[j].getname();
    }
    void printActivityTime(){
        int len=getSize();
        cout<<p_No<<" length: "<<len<<endl;
        for(int i=0;i<len;i++){
            cout<<activities[i].time<<"  ";
        }
        cout<<endl;
    }
    
    
    
};


class Log{
    int pnum;
    int anum;
    int time;
public:
    void setLog(int pNum, int t, int aNum ){
        pnum=pNum;
        time=t;
        anum=aNum;
    }
    int getT(){
        return time;}
    int getP(){
        return pnum;}
    int getA(){
        return anum;}
    
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
}



void orderAllActivity(vector<Process>& processes)
{   vector<Log> log;
    //load log
    int len=processes.size();
    for( int i=0;i<len;i++ )
    {
        for(int j=0;j<processes[i].getSize();j++)
        {
            if( processes[i].getTime(j)!= 0)
            {
                Log l;
                l.setLog(processes[i].p_No, processes[i].getTime(j),j );
                log.push_back(l);
            }
            else
            {
                processes[i].setName(j,"null");
            }
        }
    }
    
    //order it and verify
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
    }
    
    
    //valid
    for(int i=0; i<log.size();i++)
    {  if(log[i].getT()<=seq)
    {   if(log[i].getT()==seq)
    {seq+=1;
    }
    }
    else{cout<<"incorect";
        exit(0);
    }
        
    }
    int deptag=1;
    
    for(int i=0; i<log.size();i++)
    {   cout<<"after valid";
        cout<<log[i].getT()<<"   "<<log[i].getP()<<endl;
        int p=log[i].getP();
        int a=log[i].getA();
        cout<<p<<"  "<<a;
        if(log[i].getT()==1)
        {
            processes[p].setName(a , abc.front());
            cout<<"seting name"<<processes[p].getName(a)<<"  ";
        }
        else{
            for (int j=i-1; j>0 && log[j].getT()+1==log[i].getT();j--)
            {
                if(log[j].getP()==p)
                {   abc.pop();
                    processes[p].setName(a, abc.front());
                    int tag=0;
                    break;
                }
            }
            if(deptag==1)
            {
                for(int j=i-1;j>0 && log[j].getT()+1==log[i].getT();j--)
                {   int pp=log[j].getP();
                    int aa=log[j].getA();
                    processes[pp].setName(aa, sendRec.front());
                    sendRec.pop();
                    processes[p].setName(a, sendRec.front());
                    sendRec.pop();
                    
                }
            }
        }
    }
    
}









int main(){
    
    
    vector<Process> processes;
    
    Process p1;
    
    p1.pushActivity("1 2 8 9");
    p1.p_No=1;
    p1.printActivityTime();
    processes.push_back(p1);
    
    
    Process p2;
    p2.pushActivity("1 6 7 0");
    p2.p_No=2;
    p2.printActivityTime();
    processes.push_back(p2);
    
    Process p3;
    p3.pushActivity("3 4 5 6");
    p3.p_No=3;
    p3.printActivityTime();
    processes.push_back(p3);
    
    initNameQueue(20);
    
    orderAllActivity(processes);
    
    for(int i=0;i< processes.size();i++)
    {   cout<<"P"<<i<<": ";
        for(int j=0; j<processes[0].getSize(); j++)
        {cout<<processes[i].getName(j)<<"  ";
        }
        cout<<endl;
    }
    
    
    
    
}