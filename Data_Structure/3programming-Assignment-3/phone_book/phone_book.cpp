#include <iostream>
#include <vector>
#include <string>
#include <strings.h>

using std::string;
using std::vector;
using std::cin;

struct Query {
    Query():name("N/A"), number(INT32_MAX)
    {}

    string type, name;
    int number;
};

vector<Query> read_queries() {
    int n;
    cin >> n;
    vector<Query> queries(n);
    for (int i = 0; i < n; ++i) {
        cin >> queries[i].type;
        if (queries[i].type == "add")
            cin >> queries[i].number >> queries[i].name;
        else
            cin >> queries[i].number;
    }
    return queries;
}

void write_responses(const vector<string>& result) {
    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}

/*vector<string> process_queries(const vector<Query>& queries) {
    vector<string> result;
    // Keep list of all existing (i.e. not deleted yet) contacts.
    vector<Query> contacts;
    for (size_t i = 0; i < queries.size(); ++i)
        if (queries[i].type == "add") {
            bool was_founded = false;
            // if we already have contact with such number,
            // we should rewrite contact's name
            for (size_t j = 0; j < contacts.size(); ++j)
                if (contacts[j].number == queries[i].number) {
                    contacts[j].name = queries[i].name;
                    was_founded = true;
                    break;
                }
            // otherwise, just add it
            if (!was_founded)
                contacts.push_back(queries[i]);
        } else if (queries[i].type == "del") {
            for (size_t j = 0; j < contacts.size(); ++j)
                if (contacts[j].number == queries[i].number) {
                    contacts.erase(contacts.begin() + j);
                    break;
                }
        } else {
            string response = "not found";
            for (size_t j = 0; j < contacts.size(); ++j)
                if (contacts[j].number == queries[i].number) {
                    response = contacts[j].name;
                    break;
                }
            result.push_back(response);
        }
    return result;
}*/


vector<string> fast_process_queries(const vector<Query>& queries) {
    vector<string> result;
    // Keep list of all existing (i.e. not deleted yet) contacts.
    vector<Query*> contacts(10000000, nullptr);

    for (size_t i = 0; i < queries.size(); ++i)
        if (queries[i].type == "add") {
                if(contacts[queries[i].number] == nullptr)
                    contacts[queries[i].number] = new Query(queries[i]);
                else {
                    if(contacts[queries[i].number]->number == queries[i].number)
                        contacts[queries[i].number]->name = queries[i].name;
                }
        } else if (queries[i].type == "del") {
            if(contacts[queries[i].number] != nullptr)
            {
                if(contacts[queries[i].number]->number == queries[i].number)
                {
                    delete contacts[queries[i].number];
                    contacts[queries[i].number]=nullptr;
                }
            }

        } else {
            string response = "not found";
            if(contacts[queries[i].number] != nullptr)
            {
                if(contacts[queries[i].number]->number == queries[i].number)
                    response = contacts[queries[i].number]->name;
            }
            result.push_back(response);
        }
    contacts.clear();
    return result;
}


int main() {
    //write_responses(process_queries(read_queries()));
    write_responses(fast_process_queries(read_queries()));
    return 0;
}
