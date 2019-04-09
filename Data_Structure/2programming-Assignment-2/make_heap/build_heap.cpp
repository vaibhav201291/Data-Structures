#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
 private:
  vector<uint64_t> data_;
  vector< pair<uint64_t, uint64_t> > swaps_;

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }

  void Heapify(vector<uint64_t>& arr, uint64_t idx)
  {
    uint64_t left = (2*idx)+1;
    uint64_t right =  (2*idx)+2;  

    uint64_t smallest = idx;

    if(left <= arr.size()-1 && arr[idx] > arr[left])
      smallest = left;
    
    
    if(right <= arr.size()-1 && arr[right] < arr[smallest])
      smallest=right;
    

    if(smallest!=idx)
    {
          swap(arr[smallest], arr[idx]);
          swaps_.push_back(make_pair(idx, smallest));
          Heapify(arr, smallest);
    }
    

  }

  void GenerateSwaps() {
    swaps_.clear();
    // The following naive implementation just sorts 
    // the given sequence using selection sort algorithm
    // and saves the resulting sequence of swaps.
    // This turns the given array into a heap, 
    // but in the worst case gives a quadratic number of swaps.
    //
    // TODO: replace by a more efficient implementation
    
    /*for (int i = 0; i < data_.size(); ++i)
      for (int j = i + 1; j < data_.size(); ++j) {
        if (data_[i] > data_[j]) {
          swap(data_[i], data_[j]);
          swaps_.push_back(make_pair(i, j));
        }
      }*/

      
      for(int64_t i=(data_.size())/2;i>=0;i--)
        Heapify(data_, i);
      
  }

 public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
