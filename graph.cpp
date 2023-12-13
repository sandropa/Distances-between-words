#include "graph.h"
#include <limits>
#include <queue>
#include <utility>

const int inf = numeric_limits<int>::max();


// destructor
Graph::~Graph()
{
  for(Node* node : nodes)
    delete node;
}

// helper function for addWord
void Graph::connect(Node* a, Node* b)
{
  b->neighbours.push_back(a);
  a->neighbours.push_back(b);
}


void Graph::addWord(string word)
{
  // word should be a real word (here we don't check whether this is true or not)
  // this function also adds (to the graph) words that contain '.' instead of one of the letters 

  // return if the word is already in the map
  if(string_to_node.count(word) != 0)
    return;


  // add new node
  Node* new_node = new Node(word, true);
  nodes.push_back(new_node);
  string_to_node.emplace(word, new_node);


  // add fictitious words (words containing '.') and connect them appropriately
  for(int i = 0; i < word.length(); i++) 
  {
    // create the current fictitious word
    string f_word = word;
    f_word[i] = '.';

    if(string_to_node.count(f_word) != 0)
    {
      connect(new_node, string_to_node[f_word]);
    } 
    else
    {
      Node* new_f_node = new Node(f_word, false);
      nodes.push_back(new_f_node);
      
      string_to_node.emplace(f_word, new_f_node); 
      
      connect(new_node, new_f_node);
    }
  }
}


// a helper function for shortestPath, it recreates the path by using 
// the map parent_string 
string Graph::makePath(string a, string b, unordered_map<string, string>& parent_string)
{
  vector<string> words; // words in path
  string current_string = b;
  while(current_string != a)
  {
    if(string_to_node[current_string]->real_word)
      words.push_back(current_string);
    current_string = parent_string[current_string];
  }
  words.push_back(a);

  string path;
  for(int i = words.size() - 1; i > 0; i--)
  {
    path.append(words[i]);
    path.append(" -> ");
  }
  path.append(b);

  return path;
}


pair<int, string> Graph::shortestPath(string a, string b)
{
  // returns (-1, '') if distance is inf
  // we are doing a modified BFS search
  // a and b should be real words

  if(string_to_node.count(a) == 0 || string_to_node.count(b) == 0)
    throw "Words don't exist!";

  unordered_map<string, int> distances; // distances from a
  queue<Node*> q; // nodes to visit
  unordered_map<string, string> parent_string; // is this too expensive?

  //set distances to inf
  for(auto node : nodes)
    distances[node->str] = inf;
  
  distances[a] = 0;
  // string a doesn't have a parent
  q.push(string_to_node[a]);

  while(!q.empty())
  {
    Node* current_node = q.front();
    q.pop();

    // if we found b, return the distance and the path
    if(current_node->str == b)
    {
      int d = distances[b]/2;
      string path = makePath(a, b, parent_string);
      return make_pair(d, path);
    }

    // iterate through the neighbours and add them to the queue
    vector<Node*>& current_neighbours = current_node->neighbours;
    for(Node* neighbour : current_neighbours)
    {
      // check if the node is already vidited
      if(distances[neighbour->str] != inf)
        continue;

      // put the neighbour in the queue
      q.push(neighbour);
      // update the distance
      distances[neighbour->str] = distances[current_node->str] + 1;
      // add the parent
      parent_string[neighbour->str] = current_node->str;
    }
  }
  // if we  haven't found b, return (-1, '')
  return make_pair(-1, "");
}