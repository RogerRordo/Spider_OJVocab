#include<fstream>
#include<iostream>
#include<string>
#include<map>
#include<algorithm>
#include<unistd.h>
#define tr(i,l,r) for((i)=(l);(i)<=(r);++i)
using namespace std;
const int maxwords=1000000;
const int delay=0;
const int st=200;
const int ed=13147;
const string pre="https://uva.onlinejudge.org/external/";
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
    string buff,text,s;
    ofstream fail("fails.txt");
    int num,t;
    tr(num,st,ed)
    {
        cout<<num<<endl;
        system(("wget -q -O temp.pdf "+pre+intstr(num/100)+'/'+intstr(num)+".pdf").c_str());
        system("pdftotext temp.pdf temp.txt");
        ifstream fin("temp.txt");
        if (fin)
        {
            text=""; buff="";
            while(getline(fin,buff))
            {
                if (buff=="Sample Input") break;
                if (!(buff=="Input"||buff=="Output")) text+=buff+' ';
            }
            fin.close(); system("rm temp.txt temp.pdf");
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
