#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;
typedef unsigned long long ull;

vector<long long> H;

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

bool AreEqual(const string& t, const string& s, size_t start_point)
{
    size_t i =0;
    while(i < s.length() && start_point < start_point + s.length())
    {
        //std::cout<<"t: "<< t[start_point] <<"\n";
        //std::cout<<"s: "<< s[i]<<"\n";
        if(t[start_point] != s[i])
            return false;
        i++;
        start_point++;
    }

    /*if(i<s.length() || start_point<start_point+s.length())
        return false;*/
    //std::cout<<"\n";
    return true;

    /*std::string subStr = t.substr(start_point, s.length());

    return subStr == s;*/
}

long long hash_func(const string& s){
        static const unsigned long long multiplier = 263;
        static const unsigned long long prime = 1000000007;
        //unsigned long long hash = 0;
        long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash;
    }

const vector<long long>& PreComputeHash(const string& text, const string& pattern)
{
    size_t text_length = text.length();
    size_t pattern_length = pattern.length();

    H.resize(text_length-pattern_length+1);
    std::string S = text.substr(text.length()-pattern.length());
    
    /*std::cout<<"'t' value: "<< static_cast<int>(text[0])<<"\n";
    std::cout<<"'T' value: "<< static_cast<int>(pattern[0])<<"\n";
    std::cout<<"Text: "<<text<<"\n";
    std::cout<<"Text length: "<< text_length<<"\n";
    std::cout<<"\n";
    std::cout<<"Pattern: "<<pattern<<"\n";
    std::cout<<"Pattern length: "<< pattern_length<<"\n";
    std::cout<<"\n";

    std::cout<< "Sample S: "<< S <<"\n";
    std::cout<<"H size: "<<H.size()<<"\n";*/

    //unsigned long long y_const = 1;
    long long y_const = 1;
    const unsigned long long x = 263;
    const unsigned long long p = 1000000007;

    H[text_length-pattern_length] = hash_func(S);
    //std::cout<<"Hash value of last substring: "<< H.at(text_length-pattern_length)<<"\n";
    
    for (auto i=0;i<pattern_length;++i)
    {
        y_const = (y_const*x)%p;
    }
    //std::cout<<"Value of y_const: "<< y_const <<"\n";

    int j =text_length - pattern_length-1;
    while(j>=0)
    {
        //std::string trial_str = text.substr(j, pattern.length());
        //std::cout<< "String under consideration: "<<trial_str<<"\n";
        //std::cout<<"j: "<<j<<"\n";
        //H[j] = (((x*H[j+1]) + text[j] - (y_const*text[j+pattern_length]))%p + p)%p;
        H[j] = ((x*H[j+1] + text[j] - (y_const*text[j+pattern_length])%p) + p)%p;
        //std::cout<<"H[]: "<<H[j]<<"\n";
        //std::cout<<"\n";
        j--;
    }

    /*for (auto k = 0;k<H.size();++k)
        std::cout<<"H[]: "<<H[k]<<"\n";*/
    S.clear();
    return H;
}

void print_occurrences(const std::vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

std::vector<int> get_occurrences(const Data& input) {
    const string& s = input.pattern, t = input.text;
    std::vector<int> ans;
    
    //unsigned long long pHash = hash_func(s);
    long long pHash = hash_func(s);
    //std::cout<<"pHash: "<< pHash<<"\n";
    const vector<long long>& hashes = PreComputeHash(t,s);
    for (size_t i = 0; i <= t.size()-s.size(); ++i)
    {
        if(pHash != H[i])
            continue;
        else if(AreEqual(t,s,i))
            ans.push_back(i);
        //if (t.substr(i, s.size()) == s)
        //    ans.push_back(i);
    }
    return ans;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}
