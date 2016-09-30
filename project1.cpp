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
private:
    int pnum;
    int time;
    string activName;
public:
    void setLog(int pNum, int t){
        pnum=pNum;
        time=t;
        
    }
    int getT(){
        return time;}
    
    void printActivName(){
        cout<<activName;
    }
};



void orderAllActivity(vector<Process>& processes)
{
    vector<Log> log;
    //load log
    int len=processes.size();
    for( int i=0;i<len;i++ )
    {
        for(int j=i;j<processes[0].getSize();j++)
        {
            if( processes[i].getTime(j)!= 0)
            {
                Log l;
                l.setLog(processes[i].p_No, processes[i].getTime(j) );
                log.push_back(l);
            }
            else
            {
                processes[i].setName(j,"null");
            }
        }
    }
    
    for(int i=0; i<log.size();i++)
    {   cout<<"befor";
        cout<<log[i].getT()<<"  ";
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
    for(int i=0; i<log.size();i++)
    {   cout<<"after";
        cout<<log[i].getT()<<endl;
    }
    
    
    
    
}
//indepent name queue
queue<string> abc;
//send recieve
queue<string> sendRec;

void initNameQueue(int num)
{
    for(int i=0;i<num; i++)
    {
        string c;
        c=97+num;
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


void  findDependence(){}

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
    processes.push_back(p3);
    
    
    cout<<"init NameQueue starting"<<endl;
    initNameQueue(processes.size()* processes[0].getSize());
    
    
    
    orderAllActivity(processes);
    
    
    findDependence();
    
    
}