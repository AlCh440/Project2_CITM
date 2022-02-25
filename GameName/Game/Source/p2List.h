#ifndef __p2List_H__
#define __p2List_H__

#include "Defs.h"

/**
* Contains items from double linked list
*/
template<class tdata>
struct p2ListItem
{
	tdata                 data;
	p2ListItem<tdata>*   next;
	p2ListItem<tdata>*   prev;

	inline p2ListItem(const tdata& _data)
	{
		data = _data;
		next = prev = NULL;
	}

	~p2ListItem()
	{}
};

/**
* Manages a double linked list
*/
template<class tdata>
class p2List
{

public:

	p2ListItem<tdata>*   start;
	p2ListItem<tdata>*   end;
	unsigned int  size;

public:

	/**
	* Constructor
	*/
	inline p2List()
	{
		start = end = NULL;
		size = 0;
	}

	/**
	* Destructor
	*/
	~p2List()
	{
		clear();
	}

	p2ListItem<tdata>* getFirst() const
	{
		return start;
	}

	p2ListItem<tdata>* getLast() const
	{
		return end;
	}

	/**
	* Get Size
	*/
	unsigned int count() const
	{
		return size;
	}

	/**
	* Add new item
	*/
	p2ListItem<tdata>* add(const tdata& item)
	{
		p2ListItem<tdata>*   p_data_item;
		p_data_item = new p2ListItem < tdata >(item);

		if(start == NULL)
		{
			start = end = p_data_item;
		}
		else
		{
			p_data_item->prev = end;
			end->next = p_data_item;
			end = p_data_item;
		}
		++size;
		return(p_data_item);
	}

	/**
	* Find by index
	*/
	bool at(unsigned int index, tdata& data) const
	{
		bool ret = false;
		unsigned int i = 0;
		p2ListItem<tdata>*   p_data = start;

		for(unsigned int i = 0; i < index && p_data != NULL; ++i)
			p_data = p_data->next;

		if(p_data != NULL)
		{
			ret = true;
			data = p_data->data;
		}

		return ret;
	}

	/**
	* Deletes an item from the list
	*/
	bool del(p2ListItem<tdata>* item)
	{
		if(item == NULL)
		{
			return (false);
		}

		// Now reconstruct the list
		if(item->prev != NULL)
		{
			item->prev->next = item->next;

			if(item->next != NULL)
			{
				item->next->prev = item->prev;
			}
			else
			{
				end = item->prev;
			}
		}
		else
		{
			if(item->next)
			{
				item->next->prev = NULL;
				start = item->next;
			}
			else
			{
				start = end = NULL;
			}
		}

		delete item;
		--size;
		return(true);
	}

	/**
	* Destroy and free all mem
	*/
	void clear()
	{
		p2ListItem<tdata>*   p_data;
		p2ListItem<tdata>*   p_next;
		p_data = start;

		while(p_data != NULL)
		{
			p_next = p_data->next;
			delete (p_data);
			p_data = p_next;
		}

		start = end = NULL;
		size = 0;
	}

	/**
	* returns the first apperance of data as index (-1 if not found)
	*/
	bool find(const tdata& data)
	{
		p2ListItem<tdata>* tmp = start;
		int index = 0;

		while(tmp != NULL)
		{
			if(tmp->data == data)
				return true;

			++index;
			tmp = tmp->next;
		}
		return false;
	}


	/**
	* returns the first apperance of data as index (-1 if not found)
	*/
	p2ListItem<tdata>* findNode(const tdata& data)
	{
		p2ListItem<tdata>* tmp = start;

		while(tmp != NULL)
		{
			if(tmp->data == data)
				return(tmp);
			tmp = tmp->next;
		}

		return (NULL);
	}

	// Read/write operator access directly to a position in the list
	tdata& operator [](const unsigned int index)
	{
		long pos;
		p2ListItem<tdata>* pItem;
		pos = 0;
		pItem = start;

		while (pItem != NULL)
		{
			if (pos == index)
			{
				break;
			}

			++pos;
			pItem = pItem->next;
		}

		return(pItem->data);
	}

};
#endif /*__p2List_H__*/