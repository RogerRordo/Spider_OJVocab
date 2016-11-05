#include<fstream>
#include<iostream>
#include<string>
#include<map>
#include<algorithm>
#include<unistd.h>
#define tr(i,l,r) for((i)=(l);(i)<=(r);++i)
using namespace std;
const int maxwords=1000000;
const int delay=1;
const int st=1000;
const int ed=4054;
const string pre="http://poj.org/problem?id=";
const string st1="<p class=\"pst\">Description</p>";
const string st2="<p class=\"pst\">Input</p>";
const string st3="<p class=\"pst\">Output</p>";
const string st4="<p class=\"pst\">Sample Input</p>";
map<string,int> a;
pair<int,string> forout[maxwords];
int words;
string intstr(int x)
{
    char t[10];
    sprintf(t,"%d",x);
    return t;
}
void work()
{
    string buff,buf,text,s;
    ofstream fail("fails.txt");
    int num,t,t1,t2,t3,t4;
    tr(num,st,ed)
    {
        if (num%10==0) cout<<num<<endl;
        system(("wget -q -O temp.txt "+pre+intstr(num)).c_str());
        ifstream fin("temp.txt");
        text=""; buf=""; buff="";
        while(getline(fin,buff)) buf+=buff;
        fin.close();
        t1=buf.find(st1); t2=buf.find(st2); t3=buf.find(st3); t4=buf.find(st4);
        if (t1!=string::npos)
        {
            text+=s.assign(buf,t1+st1.size(),t2-(t1+st1.size()))+" ";
            text+=s.assign(buf,t2+st2.size(),t3-(t2+st2.size()))+" ";
            text+=s.assign(buf,t3+st3.size(),t4-(t3+st3.size()));
            while ((t1=text.find('<'))!=string::npos)
            {
                t2=text.find('>');
                text.replace(t1,t2-t1+1,1,' ');
            }
            tr(t,0,text.size()-1)
                if (!isalpha(text[t])) text[t]=' ';
                else text[t]=tolower(text[t]);
            text+=' ';

            while (!text.empty())
            {
                while (!text.empty()&&text[0]==' ') text.erase(0,1);
                if (!text.empty())
                {
                    a[s.assign(text,0,text.find(' '))]++;
                    text.erase(0,text.find(' '));
                }
            }
        } else fail<<num<<endl;
        sleep(delay);
    }

    for(map<string,int>::iterator it=a.begin();it!=a.end();it++)
    {
        words++;
        forout[words].first=it->second; forout[words].second=it->first;
    }
    sort(forout+1,forout+words+1);

    ofstream fout("res.txt");
    fout<<words<<endl;
    for(t=words;t;t--) fout<<forout[t].second<<' '<<forout[t].first<<endl;
    fout.close(); fail.close();
}

int main()
{
    work();
    return 0;
}
