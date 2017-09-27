#ifndef DICTIONARY_HPP_
#define DICTIONARY_HPP_

template<class Key, class Value>
class Dictionary
{
public:
	virtual ~Dictionary(){};
    virtual bool has(const Key& key) = 0;
    virtual void remove(const Key& key) = 0;
    virtual Value get(const Key& key) = 0;
    virtual void put(const Key& key, const Value& value) = 0;
};
#endif