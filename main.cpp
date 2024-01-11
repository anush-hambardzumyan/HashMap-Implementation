#include "hashmap_pro.hpp"

int main()
{
    HashMap<int , char> MyMap;                          //creating <int,char> map
    MyMap.put(1, 'I');                                  //inserting values for integer - roman numbers
    MyMap.put(5 , 'V');     
    MyMap.put(10 , 'X');
    MyMap.put(50 , 'L');     
    MyMap.put(100 , 'C');       

    std::cout << "Size of map is: ";                      //size of map
    std::cout << MyMap.size() << std::endl;
    std::cout << std::endl;

    std::cout << "Value Associated with key 1 is ";    
    std::cout << MyMap.get(1) << std::endl;               //value of key 1
    std::cout << std::endl;

    std::cout << "Keys of map: ";                           //keyset
    std::vector<int> vec1 = MyMap.keySet();
    for(int i = 0; i < vec1.size() ; ++i)
    {
        std::cout << vec1[i] << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "Values of map: ";                         //valueset
    std::vector<char> vec = MyMap.valueSet();
    for(int i = 0; i < vec.size() ; ++i)
    {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;


    int findkey = 10;                                                   //containsKey
    std::cout << "The key " << findkey;
    if(MyMap.containsKey(findkey))
    {
        std::cout << " exists. " << std::endl;
    } 
    else
    {
        std::cout << " doesn't exist. " << std::endl;
    }
    std::cout << std::endl;


    char findvalue = 'A';                                                   //containsValue
    std::cout << "The value " << findvalue;
    if(MyMap.containsValue(findvalue))
    {
        std::cout << " exists. " << std::endl;
    } 
    else
    {
        std::cout << " doesn't exist. " << std::endl;
    }
    std::cout << std::endl;
}