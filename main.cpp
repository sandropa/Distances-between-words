#include <iostream>
#include <fstream>
#include "graph.h"

using namespace std;


int main()
{
  ifstream wordlist("wordlist.txt");

  Graph G;
  string t_word;
  while(getline(wordlist, t_word))
  {
    G.addWord(t_word);
  }


  char r;
  do
  {
    cout<<"Input the first word."<<endl;
    string a;
    cin>>a;
    cout<<"Input the second word."<<endl;
    string b;
    cin>>b;
    try 
    {
      pair<int, string> path = G.shortestPath(a, b);
      if(path.first == -1)
        cout<<"There is no such path."<<endl;
      else
      {
        cout<<"The distance is "<<path.first<<"."<<endl;
        cout<<"The path: "<<path.second<<endl;
      }
    } 
    catch(const char* msg)
    {
      cout<<msg<<endl;
    }

    cout<<"Do you want to continue? ('y' for yes, 'n' for no)"<<endl;
    cin>>r;
  }
  while(r == 'y');
  
}