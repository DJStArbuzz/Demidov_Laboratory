#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main()
{
    // SET
    set<int> st;
    st.size();          // Размер
    st.empty();         // На пустоту проверку
    st.insert(5);       // Вставка элемента
    st.erase(5);        // Удаление
    st.begin(); 
    st.end();           // Самый большой элемент
    st.rbegin();        // Самый большой элемент
    st.rend();
    st.find(10);        // Указатель на элемент, на узел. Иначе st.end
    st.lower_bound(5); 
    st.upper_bound(5);

    // MULTISET - SET, ХРАНЯЩИЙ ПОВТОРЫ
    multiset<int> mst = { 1, 2, 3, 6 , 6, 8, 9 };
    mst.erase(6);           // Удаление всех 6
    mst.erase(mst.find(6)); // Удаление одной 6 по узлу
    mst.erase(mst.begin()); // Удаление самого левого узла

    pair<int, int> tmp;
    // MAP
    map<int, int> mp;
    mp.size();
    mp.empty();
    mp.insert(tmp);
    mp.erase(10);
    mp.begin();
    mp.rbegin();
    mp.end();
    mp.rend();
    mp.find(10);
    mp.lower_bound(10);
    mp.upper_bound(10);
    mp[5]++; // Ищем узел == 5, и к нему добавляем ++. mp.find(5) -> second++

    multimap<int, int> mmp;
    // Может быть много одинаковых ключей с разными значениями
}
