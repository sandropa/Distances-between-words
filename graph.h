#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Graph
{
  // bipartite graph containing words and words in which
  // one letter is replaced by '.'

  public:
  void addWord(string word);
  pair<int, string> shortestPath(string a, string b);
  ~Graph();

  private:
  struct Node
  {
    bool real_word; // string does not contain a '.'
    string str;
    vector<Node*> neighbours;

    Node(string str, bool real_word) : str(str), real_word(real_word) { }
  };

  unordered_map<string, Node*> string_to_node;
  vector<Node*> nodes;
  // both string_to_node and nodes are using pointers to the same nodes
  // this is important for destructor implementation

  // a helper function for addWord, it adds node b to the neighbours of a, and vice versa
  void connect(Node* a, Node* b);

  // a helper function for shortestPath
  string makePath(string a, string b, unordered_map<string, string>& parent_string);
};

#endif // GRAPH_H