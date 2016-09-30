//
//  main.cpp
//  Assignment1
//
//  Created by Tina Zhang on 9/27/16.
//  Copyright © 2016 Tina Zhang. All rights reserved.
//

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
#include <string>

using namespace std;

class Activity{

    string aname;
    int time;
public:
    void setname(string n){
        aname=n;
    }
    string getname(){
        return aname;
    }
    int gettime(){
        return time;
    }
    void settime(int t){
         time=t;
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
                n.settime(atoi(sub.c_str()));
                activities.push_back(n);
            }
        }
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
    void printActivityTime(){
        int len=getSize();
        cout<<p_No<<" length: "<<len<<endl;
        for(int i=0;i<len;i++){
            cout<<activities[i].gettime()<<"  ";
        }
        cout<<endl;
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
        dtag=1;
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
}



void orderAllActivity(vector<Process> processes)
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
                cout<<i<<"  "<<processes[i].getName(j);
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
    
    for(int i=0; i<log.size();i++)
    {   //cout<<"after valid";
        //cout<<log[i].getT()<<"   "<<log[i].getP()<<endl;
        int p=log[i].getP();
        int a=log[i].getA();
        if(log[i].getT()==1)
        {
            log[i].setDtag(0);
        }
        else{
            for (int j=i-1; j>0 && log[j].getT()+1==log[i].getT();j--)
            {
                if(log[j].getP()==p)
                {
                    log[i].setDtag(0);
                    break;
                }
            }
        }
        cout<<log[i].getD()<<endl;
    
    }
    
    for(int i=0; i<log.size();i++)
        {
            int p=log[i].getP();
            int a=log[i].getA();
            cout<<"P"<<p<<"A"<<a;
            if(log[i].getD()==0)
            {   string ab=abc.front();
                processes[p].setName(a, ab);
                abc.pop();
            }
            else{
             string sr=sendRec.front();
             processes[p].setName(a, sr);
             sendRec.pop();
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
    
    
   
    
    
    
}