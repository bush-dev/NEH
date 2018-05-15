#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int n,m;

class Quest
{
public:
	int task_number;
	int sum_of_times;

	vector<int> time_exec;
	vector<int> start_quest;

	void count_sum();

	bool operator < (const Quest& q) const
	{
	   return sum_of_times > q.sum_of_times;
	}
};

void Quest::count_sum()
{
     int i;
      sum_of_times = 0;

     for(i=0; i< time_exec.size(); i++)
     {
          sum_of_times += time_exec[i];
     }

}

class NEH
{
public:

     vector<Quest> quest1;
     vector<Quest> quest2;

     bool load_file();
     void algorithmNEH();
     void find_Cmax();
     void show(vector<Quest> &quest);
     int Cmax;

};

void NEH::show(vector<Quest> &quest)
{
     int i=0,j=0;
     for( i=0; i<quest.size(); i++)
     {
          for( j=0; j<m; j++)
          {
               cout << quest[i].time_exec[j] << " ";
          }
          if(quest.size() == quest1.size())
               cout << "Suma: " << quest[i].sum_of_times << endl;
          else
               cout << endl;
     }
}


bool NEH::load_file()
{
     int i=0,j=0;
     int time;
     Quest tmp;

	ifstream file;
	file.open("NEH7.DAT", ios::in);
	file >> n >> m;

	for(i=0; i<n; i++)
     {
          tmp.task_number = i+1;
          quest1.push_back(tmp);

          for(j=0; j<m; j++)
          {
               file >> time;
               quest1[i].time_exec.push_back(time);
          }
          quest1[i].count_sum();

     }
     return true;
}

void NEH::find_Cmax()
{
     int bestCmax=INT_MAX;
     int position=0;
     Cmax=INT_MAX;
     int left=0,right=0;
     int i=0;
     int j=0;
     int tmp=0;

     for(tmp=0; tmp<quest2.size(); tmp++)
     {
          quest2[0].start_quest.push_back(0);

          for(i=0; i<m-1; i++)
          {
               quest2[0].start_quest.push_back(quest2[0].start_quest[i] + quest2[0].time_exec[i]);
          }

          for(i=1; i<quest2.size(); i++)
          {
               quest2[i].start_quest.push_back(quest2[i-1].start_quest[0] + quest2[i-1].time_exec[0]);
          }

          for(j=1; j<quest2.size(); j++)
          {
               for(i=1; i<m; i++)
               {
                    quest2[j].start_quest.push_back(max(quest2[j-1].time_exec[i] + quest2[j-1].start_quest[i], quest2[j].time_exec[i-1] + quest2[j].start_quest[i-1]));
               }
          }

          Cmax = (quest2.back().start_quest.back() + quest2.back().time_exec.back());

          cout << "Cmax = " << Cmax << endl;

          for(i=0; i<quest2.size(); i++)
          {
               quest2[i].start_quest.clear();
          }

          if(Cmax < bestCmax)
          {
              bestCmax = Cmax;
              position=0;
          }
          else
          {
               position++;
          }

          right = quest2.size() - tmp -1;
          left = quest2.size() - tmp -2;

          if(tmp < quest2.size()-1)
          {
               swap(quest2[left],quest2[right]);
          }
     }
     for(i=0; i<position; i++)
     {
          swap(quest2[i], quest2[i+1]);
     }

     Cmax = bestCmax;


}

void NEH::algorithmNEH()
{
     int i=0;
     int tmp[2];
     int a=0,b=0;


     sort(quest1.begin(), quest1.end());
     cout << "Posortowane wedlug sumy:" << endl;

     show(quest1);
     quest2.push_back(quest1[0]);
     quest2.push_back(quest1[1]);

          for(a=0; a<quest2.size(); a++)
     {
          quest2[0].start_quest.push_back(0);
          quest2[1].start_quest.push_back(quest2[0].start_quest[0] + quest2[0].time_exec[0]);

          for(b=0; b<m-1; b++)
          {
               quest2[0].start_quest.push_back(quest2[0].start_quest[b] + quest2[0].time_exec[b]);
          }

          for(b=1; b<m; b++)
          {
               quest2[1].start_quest.push_back(max(quest2[1].time_exec[b-1], quest2[0].time_exec[b] + quest2[0].start_quest[b]));
          }

          Cmax= quest2.back().start_quest.back() + quest2.back().time_exec.back();

          tmp[a] = Cmax;

          quest2[0].start_quest.clear();
          quest2[1].start_quest.clear();
          swap(quest2[0],quest2[1]);

     }

     if(tmp[0] > tmp[1])
     {
          Cmax = tmp[1];
          swap(quest2[0],quest2[1]);
     }
     else
     {
          Cmax = tmp[0];
     }

for(i = 2; i<n; i++)
{
     quest2.push_back(quest1[i]);
     find_Cmax();

}
}



int main()
{
     NEH ob;

     ob.load_file();
     ob.show(ob.quest1);
     ob.algorithmNEH();

     cout << "Cmax ostateczny: " << ob.Cmax << endl;

     return 0;
}
