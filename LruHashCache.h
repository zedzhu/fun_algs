#ifndef _LRU_HASH_CACHE_H_
#define _LRU_HASH_CACHE_H_


/**
* @brief 自己实现的一个简单但实用的LruHashCache
* carlzhu
*/

#include <ext/hash_map>
#include <list>
#include <cstddef>
#include <stdexcept>

using namespace __gnu_cxx;

template<typename T>
struct HashFunctor
{
    unsigned int operator()(const T& t)
    {
        return t.hash();
    }
};

struct LongHash
{
    size_t operator()(int64_t i) const
    {
        return size_t(i);
    }
};

//核心hash算法采用djb2
struct StringHash
{
    size_t operator()(const string& s) const
    {
        uint64_t __h = 5381;
        for (size_t i = 0; i < s.length(); ++i)
        {
            bool all_left_digit = true;
            for (size_t j = i; j < s.length(); ++j)
            {
                if (!isdigit(s[j]))
                {
                    all_left_digit = false;
                    break;
                }
            }

            if (all_left_digit)
            {
                for (size_t j = i; j < s.length(); ++j)
                {
                    __h = 10 * __h + s[j] - 48;
                }

                return __h;
            }
            else
            {
                __h = (__h << 5) + __h + s[i]; //djb2: hash * 33 + c
            }
        }

        return __h;
    }
};

/* MurmurHash2, by Austin Appleby
 Note - This code makes a few assumptions about how your machine behaves -
 1. We can read a 4-byte value from any address without crashing
 2. sizeof(int) == 4

 And it has a few limitations -
 1. It will not work incrementally.
 2. It will not produce the same results on little-endian and big-endian machines.
*/
struct MurmurHash2
{
    size_t operator()(const string& s) const
    {
        const void * key = s.c_str();
        int len = (int)s.length();
        unsigned int seed = 13;

        // 'm' and 'r' are mixing constants generated offline.
        // They're not really 'magic', they just happen to work well.
        const unsigned int m = 0x5bd1e995;
        const int r = 24;

        // Initialize the hash to a 'random' value
        unsigned int h = seed ^ len;

        // Mix 4 bytes at a time into the hash
        const unsigned char * data = (const unsigned char *)key;

        while(len >= 4)
        {
            unsigned int k = *(unsigned int *)data;

            k *= m;
            k ^= k >> r;
            k *= m;

            h *= m;
            h ^= k;

            data += 4;
            len -= 4;
        }

        // Handle the last few bytes of the input array
        switch(len)
        {
            case 3: h ^= data[2] << 16;
            case 2: h ^= data[1] << 8;
            case 1: h ^= data[0];
                    h *= m;
        };

        // Do a few final mixes of the hash to ensure the last few
        // bytes are well-incorporated.
        h ^= h >> 13;
        h *= m;
        h ^= h >> 15;

        return h;
    }
};

template<typename key_t, typename value_t>
class KickoutCallBack
{
public:
    virtual ~KickoutCallBack() {}

    /**
     * 注意回调函数里不能含有阻塞式IO等任何可能导致耗时高的操作，否则会极大影响LRU的性能
     */
    virtual void * handleKickout(key_t& k, value_t& v) { return NULL; }
};

template<typename key_t, typename value_t, typename HashFun = HashFunctor<key_t> >
class LruHashCache
{
public:
    typedef std::pair<key_t, value_t> key_value_pair_t;
    //因为使用了::,为了避免与这也可能是一个变量发生歧义，所以用typename强调这是一个类型而不是变量。
    typedef typename std::list<key_value_pair_t>::iterator list_iterator_t;
    typedef HashFun hash_func;
    typedef hash_map<key_t, list_iterator_t, hash_func> LruDataMap;
    typedef KickoutCallBack<key_t, value_t> KickoutCB;

    LruHashCache() :
        _max_size(1024), _get_num(0), _hit_num(0), _kickout_cb(NULL)
    {
    }

    LruHashCache(size_t max_size) :
        _max_size(max_size), _get_num(0), _hit_num(0), _kickout_cb(NULL)
    {
    }

    LruHashCache(size_t max_size, KickoutCB* cb) :
        _max_size(max_size), _get_num(0), _hit_num(0), _kickout_cb(cb)
    {
    }
    
    void put(const key_t& key, const value_t& value)
    {
        typename LruDataMap::iterator it = _cache_items_map.find(key);
        if (it != _cache_items_map.end())
        {
            it->second->second = value;
            _cache_items_list.splice(_cache_items_list.begin(), _cache_items_list, it->second);
        }
        else
        {
            _cache_items_list.push_front(key_value_pair_t(key, value));
            _cache_items_map[key] = _cache_items_list.begin();
        }
        
        if (_cache_items_map.size() > _max_size)
        {
            list_iterator_t last = _cache_items_list.end();
            last--;
            if (_kickout_cb)
            {
                _kickout_cb->handleKickout(last->first, last->second);
            }
            _cache_items_map.erase(last->first);
            _cache_items_list.pop_back();
        }
    }
    
    value_t& get(const key_t& key)
    {
        _get_num++;
        typename LruDataMap::iterator it = _cache_items_map.find(key);
        if (it == _cache_items_map.end())
        {
            throw std::range_error("There is no such key in cache");
        } 
        else
        {
            _hit_num++;
            _cache_items_list.splice(_cache_items_list.begin(), _cache_items_list, it->second);
            return it->second->second;
        }
    }

    value_t& find(const key_t& key)
    {
        typename LruDataMap::iterator it = _cache_items_map.find(key);
        if (it == _cache_items_map.end())
        {
            throw std::range_error("no such key found");
        } 
        else
        {
            return it->second->second;
        }
    }

    void remove(const key_t& key)
    {
        typename LruDataMap::iterator it = _cache_items_map.find(key);
        if (it != _cache_items_map.end())
        {
            _cache_items_list.erase(it->second);
            _cache_items_map.erase(it);
        }
    }

    bool exists(const key_t& key) const
    {
        return _cache_items_map.find(key) != _cache_items_map.end();
    }

    void drain(int m)
    {
        if (m <= 0)
        {
            return;
        }

        while (m-- && size() > 0)
        {
            list_iterator_t last = _cache_items_list.end();
            last--;
            if (_kickout_cb)
            {
                _kickout_cb->handleKickout(last->first, last->second);
            }
            _cache_items_map.erase(last->first);
            _cache_items_list.pop_back();
        }
    }
    
    size_t size() const
    {
        return _cache_items_map.size();
    }

    void swap(LruHashCache& newLruCache)
    {
        _cache_items_list.swap(newLruCache._cache_items_list);
        _cache_items_map.swap(newLruCache._cache_items_map);
        std::swap(_max_size, newLruCache._max_size);
    }

    double hitRatio()
    {
        if (_get_num == 0)
        {
            return 0;
        }
        else
        {
            return double(_hit_num) / double(_get_num);
        }
    }
    
private:
    std::list<key_value_pair_t> _cache_items_list;
    LruDataMap _cache_items_map;
    size_t _max_size;
    int64_t _get_num;
    int64_t _hit_num;
    KickoutCB* _kickout_cb;
};

#endif  /* _LRU_HASH_CACHE_H_ */

