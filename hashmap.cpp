#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <list>
#include <vector>
#include <cstdlib>
#include <functional>
#include <stdexcept>
#include <map>
#include <utility>

using namespace std;

template<class KeyType, class ValueType, class Hash = std::hash<KeyType> >

class HashMap {
public:
    using iterator = typename list<pair<const KeyType, ValueType>>::iterator;
    using const_iterator = typename list<pair<const KeyType, ValueType>>:: const_iterator;
    typedef pair<KeyType, ValueType> elem;
    typedef pair<const KeyType, ValueType> celem;
    vector<list<iterator>> v;
    list<celem> ls;
    int lsz;
    Hash hf;
    const int n = 300323;

public:
    HashMap(Hash _hf = Hash()) : hf(_hf) {
        v.resize(n);
        lsz = 0;
    }

    template <typename Iter>
    HashMap(Iter begin, Iter end, Hash _hf = Hash()) {
        v.resize(n);
        lsz = 0;
        hf = _hf;
        for (auto i = begin; i != end; ++i) {
            insert(*i);
        }
    }

    HashMap(initializer_list<elem> l, Hash _hf = Hash()) {
        v.resize(n);
        lsz = 0;
        hf = _hf;
        for (auto i = l.begin(); i != l.end(); ++i) {
            insert((const elem&)(*i));
        }
    }

    HashMap(const HashMap &hm1) {
        v.resize(n);
        lsz = 0;
        hf = hm1.hf;
        for (auto i = hm1.begin(); i != hm1.end(); ++i) {
            insert(*i);
        }
    }

    HashMap& operator =(const HashMap &hm1) {
        if (this == &hm1) return *this;
        v.clear();
        ls.clear();
        v.resize(n);
        lsz = 0;
        hf = hm1.hf;
        for (auto i = hm1.begin(); i != hm1.end(); ++i) {
            insert(*i);
        }
        return *this;
    }

    iterator insert(const elem &p) {
        if (!(find_p(p.first))) {
            int h = (hf(p.first)) % n;
            ls.insert(ls.begin(), p);
            v[h].push_back(ls.begin());
            ++lsz;
            return ls.begin();
        } else {
            return find(p.first);
        }
    }

    void erase(const KeyType &k) {
        int h = (hf(k)) % n;
        for (auto i = v[h].begin(); i != v[h].end(); ++i) {
            if ((*i)->first == k) {
                const auto it = *i;
                ls.erase(it);
                --lsz;
                v[h].erase(i);
                break;
            }
        }
    }

    bool find_p(const KeyType &k) {
        int h = (hf(k)) % n;
        for (auto i = v[h].begin(); i != v[h].end(); ++i) {
            if ((*i)->first == k) {
                return 1;
            }
        }
        return 0;
    }

    iterator find(const KeyType &k) {
        int h = (hf(k)) % n;
        for (auto i = v[h].begin(); i != v[h].end(); ++i) {
            if ((*i)->first == k) {
                return *i;
            }
        }
        return ls.end();
    }

    const_iterator find(const KeyType &k) const {
        int h = (hf(k)) % n;
        for (auto i = v[h].begin(); i != v[h].end(); ++i) {
            if ((*i)->first == k) {
                return *i;
            }
        }
        return ls.end();
    }

    ValueType &operator[](const KeyType &k) {
        auto it = insert(make_pair(k, ValueType()));
        return it->second;
    }

    const ValueType& at(const KeyType& k) const {
        auto it = find(k);
        if (it != ls.end()) return it->second;
        else
            throw std::out_of_range("error");
    }

    void clear() {
        while (lsz > 0) {
            erase(ls.begin()->first);
        }
    }

    size_t size() const {
        return static_cast<size_t>(lsz);
    }

    bool empty() const {
        return lsz == 0;
    }

    Hash hash_function() const {
        return hf;
    }

    iterator begin() {
        return ls.begin();
    }

    iterator end() {
        return ls.end();
    }

    const_iterator begin() const {
        return ls.begin();
    }

    const_iterator end() const {
        return ls.end();
    }
};
