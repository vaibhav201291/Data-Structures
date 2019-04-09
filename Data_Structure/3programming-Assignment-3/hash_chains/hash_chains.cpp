#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

using std::string;
using std::vector;
using std::list;
using std::cin;

struct Query {
    string type, s;
    size_t ind;
};

class QueryProcessor {
    int bucket_count;
    // store all strings in one vector
    vector<list<string>* > bucket_elems;
    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count), 
    bucket_elems(bucket_count, nullptr) 
    {}

    ~QueryProcessor()
    {
        for (auto it = bucket_elems.begin();it!=bucket_elems.end();++it)
        {
            delete *it;
            *it = nullptr;
        }
    }

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }

    void processQuery(const Query& query) {
        if (query.type == "check") {
            // use reverse order, because we append strings to the end
            /*for (int i = static_cast<int>(elems.size()) - 1; i >= 0; --i)
                if (hash_func(elems[i]) == query.ind)
                    std::cout << elems[i] << " ";
            std::cout << "\n";*/

            list<string>* check_list = bucket_elems.at(query.ind);
            if(check_list != nullptr)
            {
                for (auto lt = check_list->begin(); lt!=check_list->end();++lt)
                    std::cout<< *lt << " ";
                
            }
            std::cout<<"\n";

        } else {
            if (query.type == "find")
            {
                size_t hash_value = hash_func(query.s);
                list<string>* find_list = bucket_elems.at(hash_value);
                if(find_list != nullptr)
                {
                    list<string>::iterator ft = std::find(find_list->begin(), find_list->end(), query.s);
                    writeSearchResult(ft != find_list->end());
                }
                else
                    writeSearchResult(false);
            }
            else if (query.type == "add") {
                    //std::cout<<"Calculating hash value for:"<<query.s<<"\n";
                    size_t hash_value = hash_func(query.s);
                    if(bucket_elems.at(hash_value) == nullptr)
                    {
                        //std::cout<<"Creating new list for the bucket with"<< hash_value<<"\n";
                        bucket_elems.at(hash_value) = new list<string>();
                        bucket_elems.at(hash_value)->push_front(query.s);
                    }
                    else
                    {
                        list<string>* same_hash_value = bucket_elems.at(hash_value);
                        list<string>::iterator found_or_not = std::find(same_hash_value->begin(), 
                                same_hash_value->end(), query.s);
                        
                        if (found_or_not == same_hash_value->end())
                            bucket_elems.at(hash_value)->push_front(query.s);
                    }
                    //std::cout<<"hash value= "<<hash_value<<"\n";
            } else if (query.type == "del") {
                size_t hash_value = hash_func(query.s);
                list<string>* del_list = bucket_elems.at(hash_value);
                if(del_list != nullptr)
                {
                    list<string>::iterator del_it, result;
                    del_it = std::find(del_list->begin(),del_list->end(), query.s);
                    if(del_it != del_list->end())
                        result = del_list->erase(del_it);
                }
            }
        }
    }

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
