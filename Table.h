//
// Created by mikhail on 27.12.2022.
//

#ifndef CPPLAB3_3_TABLE_H
#define CPPLAB3_3_TABLE_H
template<class T1, class T2>
class pair
{
public:
    T1 key;
    T2 value;
    pair() = default;
    pair(T1 key, T2 value) : key(key), value(value) {};
};
template<class T1, class T2>
class Table {
public:
    std::vector<pair<T1, T2>> pairs;
    Table(std::initializer_list<pair<T1, T2>> list);
    const T2 &at(const T1& a) const;
    T2 &at(const T1& a);
    bool find(const T1 &a) const;
    void add(const pair<T1, T2>& p);
    std::vector<T1> getKeys() const;
};


template<class T1, class T2>
Table<T1, T2>::Table(std::initializer_list<pair<T1, T2>> list) {
    pairs = list;
}

template<class T1, class T2>
T2 &Table<T1, T2>::at(const T1 &a) {
    for(int i = 0; i < pairs.size(); ++i)
    {
        if(pairs[i].key == a)
        {
            return pairs[i].value;
        }
    }
    throw std::out_of_range("could not find element");
}
template<class T1, class T2>
const T2 &Table<T1, T2>::at(const T1 &a) const {
    for(int i = 0; i < pairs.size(); ++i)
    {
        if(pairs[i].key == a)
        {
            return pairs[i].value;
        }
    }
    throw std::out_of_range("could not find element");
}

template<class T1, class T2>
bool Table<T1, T2>::find(const T1 &a) const {
    for(int i = 0; i < pairs.size(); ++i)
    {
        if(pairs[i].key == a)
        {
            return true;
        }
    }
    return false;
}

template<class T1, class T2>
void Table<T1, T2>::add(const pair<T1, T2>& p) {
    if(find(p.key))
        return;
    pairs.push_back(p);
}

template<class T1, class T2>
std::vector<T1> Table<T1, T2>::getKeys() const {
    std::vector<T1> result;
    result.reserve(pairs.size());
    for(int i = 0; i < pairs.size(); ++i)
    {
        result.push_back(pairs[i].key);
    }
    return result;
}


#endif //CPPLAB3_3_TABLE_H
