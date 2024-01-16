#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <iterator>
#include <algorithm>


template <typename Key, typename Value>
class HashMap
{
    private:
    std::vector<std::pair<int , std::list<std::pair<Key,Value>>*>> table;

    //HASHING HELPER 
    int Hashing(Key key) const 
    {
        return key % table.size();
    }

    //PRIME HELPER1
    bool is_prime(int num)
    {
        for(int i = 2; i <= num/2; ++i)
        {
            if(num % i == 0)
            {
                return false;
            }
        }
        return true;
    }

    //PRIME HELPER2    
    int next_prime(int current_prime)
    {
        for(int i = current_prime + 1; ;i++)
        {
            if(is_prime(i))
            {
                return i;
            }
        }
        return -1;
    }

    //REHASHING HELPER
    void ReHashing()
    {
        typename std::vector<std::pair<int, std::list<std::pair<Key,Value>>*>> new_table;
        new_table.resize(next_prime(table.size()) , {0,nullptr});
        for(int i = 0; i < table.size(); ++i)
        {
            if(table[i].first)
            {
                typename std::list<std::pair<Key,Value>>::iterator it = table[i].second -> begin();
                
                for(;it != table[i].second -> end() ; it++)
                {
                    new_table[(it -> second % new_table.size())].second -> push_front({it -> first, it -> second});
                    ++new_table[(it -> second % new_table.size())].first;
                }  
            }
        }
        table = std::move(new_table);
    }

    //FIND HELPER(FINDS BY KEY)
    typename std::list<std::pair<Key,Value>>::iterator myFind(const Key& key)
    {
        int index = Hashing(key);
        typename std::list<std::pair<Key,Value>>::iterator curr_list = table[index].second -> begin();
        typename std::list<std::pair<Key,Value>>::iterator curr_list_end = table[index].second -> end();
        while (curr_list != curr_list_end) 
        {
            if ((*curr_list).first == key) 
            {
                return curr_list;
            }
            ++curr_list;
        }
        return curr_list;
    } 

    public:
    HashMap();                                                                          //done
    ~HashMap();                                                                         //done
    void put(const Key& , const Value&);                                                //done
    Value get(const Key&);                                                              //done
    void remove(const Key&);                                                            //done
    bool containsKey(const Key&);                                                       //done
    bool containsValue(const Value&);                                                   //done    
    int size();                                                                         //done
    bool isEmpty();                                                                     //done
    void clear();                                                                       //done
    std::vector<Key> keySet();                                                          //done
    std::vector<Value> valueSet();                                                      //done
    std::vector<std::pair<int , std::list<std::pair<Key,Value>>*>> entrySet();          //done
};

//CONSTRUCTOR
template<typename Key, typename Value>
HashMap<Key, Value>::HashMap()
{
    table.resize(7, {0, nullptr});
}

//DESTRUCTOR
template<typename Key, typename Value>
HashMap<Key, Value>::~HashMap()
{
    clear();
}

//PUT (INSERT)
template<typename Key, typename Value>
void HashMap<Key, Value>::put(const Key& key, const Value& value)
{
    int index = Hashing(key);
    auto& cur_pair = table[index];

    if(cur_pair.second == nullptr)
    {
        cur_pair.second = new std::list<std::pair<Key, Value>>;
        ++table[index].first;
    }

    for (typename std::list<std::pair<Key, Value>>::iterator it = cur_pair.second->begin(); it != cur_pair.second->end(); ++it) 
    {
        if (it->first == key) 
        {
            it->second = value;
            return;
        }
    }

    cur_pair.second -> push_front({key,value});
    ++table[index].first;

    if(table[index].first == table.size())
    {
        ReHashing();
    }
    
}

//GET (RETRIVAL)
template<typename Key, typename Value>
Value HashMap<Key, Value>::get(const Key& key)
{
    int index = Hashing(key);
    auto& cur_list = table[index].second;

    if(cur_list)
    {
        for (auto it = cur_list -> begin(); it != cur_list -> end(); ++it) 
        {
            if (it->first == key) 
            {
                return it->second;
            }
        }
    }

    std::cout << "No key found: " << std::endl;
    exit(0);
}

//SIZE
template<typename Key, typename Value>
int HashMap<Key,Value>::size()
{
    int sum = 0;
    for(int i = 0; i < table.size(); ++i)
    {
        if(table[i].second)
        {
            sum += table[i].second -> size();
        }   
    }
    return sum;
}

//ISEMPTY
template<typename Key,typename Value>
bool HashMap<Key,Value>::isEmpty()
{
    return !(size());
}

//CLEAR
template<typename Key,typename Value>
void HashMap<Key,Value>::clear()
{
    for(int i = 0; i < table.size();++i)
    {
        if(table[i].second)
        {
            table[i].first = 0;
            table[i].second -> clear();
        }    
    }
}

//REMOVE
template<typename Key,typename Value>
void HashMap<Key,Value>::remove(const Key& key)
{
    if(isEmpty())
    {
        return;
    }

    int index = Hashing(key);
    std::list<std::pair<Key,Value>>* curr_list = table[index].second;
    typename std::list<std::pair<Key,Value>>::iterator it = myFind(key);
    if(it != curr_list -> end())
    {
        curr_list -> erase(it);
        --table[index].first;
    }
}

//KEYSET
template<typename Key,typename Value>
std::vector<Key> HashMap<Key,Value>::keySet()
{
    std::vector<Key> keyset;
    for(int i = 0; i < table.size() ; ++i)
    {
        if (table[i].second)
        {
            auto it = table[i].second->begin();
        
            for( ; it != table[i].second->end(); ++it)
            {
                keyset.push_back(it->first);
            }
        }
    }
    return keyset;
}

//VALUESET
template<typename Key,typename Value>
std::vector<Value> HashMap<Key,Value>::valueSet()
{
    std::vector<Value> valueset;
    for(int i = 0; i < table.size() ; ++i)
    {
        if (table[i].second)
        {
            auto it = table[i].second->begin();
        
            for( ; it != table[i].second->end(); ++it)
            {
                valueset.push_back(it->second);
            }
        }
    }
    return valueset;
}


//CONTAINSKEY
template<typename Key,typename Value>
bool HashMap<Key,Value>::containsKey(const Key& key)
{
    std::vector<Key> vec = keySet();
    auto it = std::find(vec.begin(), vec.end(), key);

    return it != vec.end();
}

//CONTAINSVALUE
template<typename Key,typename Value>
bool HashMap<Key,Value>::containsValue(const Value& key)
{
    std::vector<Key> vec = keySet();
    auto it = std::find(vec.begin(), vec.end(), key);

    return it != vec.end();
}

//ENTRYSET
template<typename Key,typename Value>
std::vector<std::pair<int , std::list<std::pair<Key,Value>>*>> HashMap<Key,Value>::entrySet()
{
    std::vector<std::pair<int , std::list<std::pair<Key,Value>>*>> vec;
    vec = table;
    return vec;
}