#pragma once
#include "../common.hpp"
#include "../utils/memory_utils.hpp"

namespace data
{
	template<typename val_t>
	class data_map_node
	{
	public:
		data_map_node(byte _key) :
			key(_key),
			next(nullptr),
			value(nullptr),
			first_child(nullptr)
		{

		}

		~data_map_node()
		{
			if(value)
				delete value;

			if(next)
				delete next;

			if(first_child)
				delete first_child;
		}

		data_map_node<val_t>* find_node(unsigned int hash_key, bool create_if_missing, unsigned int search_mask = 0xFF000000)
		{
			byte search_key = hash_key & search_mask;

			if(search_key == key)
			{
				if(search_mask == 0xFF) return this;

				if(!first_child)
				{
					if(!create_if_missing)
						return nullptr;

					first_child = new data_map_node<val_t>(hash_key & (search_mask >> 8));
				}

				return first_child->find_node(hash_key, create_if_missing, search_mask >> 8);
			}

			if(!next)
			{
				if(!create_if_missing) return nullptr;

				next = new data_map_node<val_t>(search_key);
			}

			return next->find_node(hash_key, create_if_missing, search_mask);
		}

		data_map_node<val_t>* set_key(byte new_key)
		{
			key = new_key;
			return this;
		}

		data_map_node<val_t>* set_value(const val_t& new_value)
		{
			if(value)
				delete value;

			value = new val_t(new_value);

			return this;
		}

		const val_t* get_value()
		{
			return value;
		}

	private:
		byte key;
    		val_t* value;
    		data_map_node<val_t>* first_child;
    		data_map_node<val_t>* next;
  	};

	template<typename key_t, typename val_t>
	class data_map {
	public:
		data_map() :
			root_node(new data_map_node<val_t>(0))
		{

		}

		~data_map()
		{
			delete root_node;
		}

		void set(const key_t& key, const val_t& value)
		{
			unsigned int key_hash = utils::memory_utils::djb2_hash<key_t>(key);
			root_node->find_node(key_hash, true)->set_value(value);
		}

		const val_t* get(const key_t& key)
		{
			unsigned int key_hash = utils::memory_utils::djb2_hash<key_t>(key);
			data_map_node<val_t>* target_node = root_node->find_node(key_hash, false);

			if(!target_node) return nullptr;

			return target_node->get_value();
		}

		bool has_key(const key_t& key)
		{
			unsigned int key_hash = utils::memory_utils::djb2_hash<key_t>(key);
			data::data_map_node<val_t>* target_node = root_node->find_node(key_hash, false);

			return target_node && target_node->get_value();
		}

	private:
		data_map_node<val_t>* root_node;
	};

}
