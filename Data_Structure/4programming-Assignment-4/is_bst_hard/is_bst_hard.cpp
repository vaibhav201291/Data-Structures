#include <algorithm>
#include <iostream>
#include <vector>
#include <limits.h>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
  long long key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(long long key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

bool IsBinary(const vector<Node>& tree, Node i, long long min, long long max)
{
    //if(i == -1)
    //  return true;
    /*cout<<"Key: "<< i.key<<"\n";
    cout<<"Min: "<< min<<"\n";
    cout<<"Max: "<< max<<"\n";
    cout<<"\n";*/

    if(i.key < min || i.key > max)
    {
      //cout<<"Duplicate"<<"\n";
      return false;
    }

    bool left_binary = true, right_binary = true;
    if(i.left != -1)
        left_binary = IsBinary(tree, tree.at(i.left), min, i.key-1);
      //left_binary = IsBinary(tree, tree.at(i.left), min, i.key);

    if(i.right != -1)
      right_binary = IsBinary(tree, tree.at(i.right), i.key, max);
    //if(i.left==-1 || )

    //cout<<"Ans: "<<left_binary && right_binary<<"\n";
    return ( left_binary && right_binary);
}

bool IsBinarySearchTree(const vector<Node>& tree) {
  // Implement correct algorithm here
  return (IsBinary(tree, tree.at(0), INT_MIN, INT_MAX));
  //return true;
}

int main() {
  int nodes;
  cin >> nodes;
  
  if (nodes == 0)
  {
    cout << "CORRECT" << endl;
    return 0;  
  }

  vector<Node> tree;
  for (int i = 0; i < nodes; ++i) {
    int key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
  if (IsBinarySearchTree(tree)) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
