#include <iostream>
#include <vector>
#include <algorithm>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using std::vector;
using std::ios_base;
using std::cin;
using std::cout;

class TreeOrders {
  int n;
  vector <int> key;
  vector <int> left;
  vector <int> right;
  
public:
vector<int> order_result;
  void read() {
    cin >> n;
    key.resize(n);
    left.resize(n);
    right.resize(n);
    for (int i = 0; i < n; i++) {
      cin >> key[i] >> left[i] >> right[i];
    }
  }


  //vector <int> in_order(size_t idx) {
    void in_order(size_t idx) {
    //vector<int> result;
    // Finish the implementation
    // You may need to add a new recursive method to do that
    // left
    // root
    // right

    if (idx == -1)
      return;

    in_order(left.at(idx));
    order_result.push_back(key.at(idx));
    in_order(right.at(idx));

    //return result;
  }

  //vector <int> pre_order() {
  void pre_order(size_t idx) {
    vector<int> result;    
    // Finish the implementation
    // You may need to add a new recursive method to do that
    
    if(idx==-1)
      return;

    order_result.push_back(key.at(idx));
    pre_order(left.at(idx));
    pre_order(right.at(idx));
    

    //return result;
  }

  //vector <int> post_order() {
  void post_order(size_t idx){
    //vector<int> result;
    // Finish the implementation
    // You may need to add a new recursive method to do that
    // left 
    // right 
    // root

    if(idx==-1)
      return;

    post_order(left.at(idx));
    post_order(right.at(idx));
    order_result.push_back(key.at(idx));
    

    //return result;
  }
};

void print(vector <int> a) {
  for (size_t i = 0; i < a.size(); i++) {
    if (i > 0) {
      cout << ' ';
    }
    cout << a[i];
  }
  cout << '\n';
}

int main_with_large_stack_space() {
  ios_base::sync_with_stdio(0);
  TreeOrders t;
  t.read();

  t.in_order(0);
  print(t.order_result);
  t.order_result.clear();

  t.pre_order(0);
  print(t.order_result);
  t.order_result.clear();

  t.post_order(0);
  print(t.order_result);
  t.order_result.clear();
  //print(t.in_order(0));
  //print(t.pre_order());
  //print(t.post_order());
  return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }
#endif

  return main_with_large_stack_space();
}

