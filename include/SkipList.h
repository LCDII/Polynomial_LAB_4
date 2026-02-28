#pragma once
#include<vector>
#include <cstdlib>
#include <ctime>
using namespace std;


#define LEVEL 5 // log 32 = 5, 32 ammount of monoms; Its enough;


template<class T, class Compare>
class SkipList
{
	struct Node
	{
		T value;
		vector<Node*> next;
		Node(const T& v, int _level) : value(v), next(_level, nullptr) {}
	};


	Node* head;
	int level = 1;
	size_t sz = 0;
	Compare comp;


	bool equal(const T& a, const T& b) const {
		return !comp(a, b) && !comp(b, a);
	}


	int getRandomLevel()
	{
		int level = 1;
		srand(static_cast<unsigned>(time(nullptr)));

		for (int i = 0; i < LEVEL-1; i++)
		{
			int res = rand() % 2;
			if (res)
				level++;
		}
		return level;
	}
public:

	class Iterator
	{
	public:
		Node* node;
		Iterator(Node* n = nullptr) : node(n) {}

		T& operator*() { return node->value; }
		T* operator->() { return &node->value; }

		Iterator& operator++() {
			node = node->next[0];
			return *this;
		}

		bool operator==(const Iterator& other) const {
			return node == other.node;
		}

		bool operator!=(const Iterator& other) const {
			return node != other.node;
		}
	};

	SkipList() {
		head = new Node(T{}, LEVEL);
	}

	SkipList(const SkipList& other) : SkipList()
	{
		comp = other.comp;
		for (auto it = other.begin(); it != other.end(); ++it)
			insert(*it);
	}


	SkipList(SkipList&& other) noexcept : head(other.head), level(other.level), sz(other.sz), comp(move(other.comp))
	{
		other.head = nullptr;
		other.sz = 0;
	}


	~SkipList() {
		Node* cur = head;
		while (cur) {
			Node* next = cur->next[0];
			delete cur;
			cur = next;
		}
	}
	size_t size() const 
	{ 
		return sz; 
	}
	bool empty() const 
	{ 
		return sz == 0; 
	}
	Iterator begin() const
	{ 
		return Iterator(head->next[0]);
	}
	Iterator end() const
	{ 
		return Iterator(nullptr);
	}

	SkipList& operator=(const SkipList& other) {
		if (this == &other)
			return *this;

		clear();

		comp = other.comp;

		for (auto it = other.begin(); it != other.end(); ++it)
			insert(*it);

		return *this;
	}

	void insert(const T& value) {
		vector<Node*> update(LEVEL);
		Node* cur = head;

		for (int i = level - 1; i >= 0; --i) {
			while (cur->next[i] && comp(cur->next[i]->value, value))
				cur = cur->next[i];
			update[i] = cur;
		}

		int newLevel = getRandomLevel();

		if (newLevel > level)
		{
			for (int i = level; i < newLevel; ++i)
				update[i] = head;
			level = newLevel;
		}

		Node* node = new Node(value, newLevel);

		for (int i = 0; i < newLevel; ++i)
		{
			node->next[i] = update[i]->next[i];
			update[i]->next[i] = node;
		}

		sz++;
	}

	Iterator erase(Iterator it)
	{
		Node* target = it.node;
		if (!target) return end();

		std::vector<Node*> update(LEVEL);
		Node* cur = head;

		for (int i = level - 1; i >= 0; --i)
		{
			while (cur->next[i] && cur->next[i] != target &&
				comp(cur->next[i]->value, target->value))
			{
				cur = cur->next[i];
			}
			update[i] = cur;
		}

		for (int i = 0; i < level; ++i)
		{
			if (update[i]->next[i] == target)
				update[i]->next[i] = target->next[i];
		}

		Node* nextNode = target->next[0];

		delete target;
		--sz;

		
		while (level > 1 && head->next[level - 1] == nullptr)
			--level;

		return Iterator(nextNode);
	}

	void clear() {
		Node* cur = head->next[0];

		while (cur) {
			Node* nxt = cur->next[0];
			delete cur;
			cur = nxt;
		}

		for (int i = 0; i < LEVEL; ++i)
			head->next[i] = nullptr;

		level = 1;
		sz = 0;
	}

	Iterator find(const T& value) {
		Node* cur = head;

		for (int i = level - 1; i >= 0; --i)
			while (cur->next[i] && comp(cur->next[i]->value, value))
				cur = cur->next[i];

		cur = cur->next[0];

		if (cur && equal(cur->value, value))
			return Iterator(cur);

		return end();
	}

	//works only if both lists sorted
	SkipList operator+(const SkipList& other) const
	{
		SkipList result;

		vector<Node*> tails(LEVEL, result.head);

		auto it1 = begin();
		auto it2 = other.begin();

		auto addLast = [&](const T& val)
			{
				//Level rebalance for new List
				int newLevel = result.getRandomLevel();
				Node* node = new Node(val, newLevel);

				for (int i = 0; i < newLevel; ++i)
				{
					tails[i]->next[i] = node;
					tails[i] = node;
				}

				result.sz++;
				result.level = std::max(result.level, newLevel);
			};

		while (it1 != end() && it2 != other.end())
		{
			if (comp(*it1, *it2))
			{
				addLast(*it1);
				++it1;
			}
			else if (comp(*it2, *it1))
			{
				addLast(*it2);
				++it2;
			}
			else {
				addLast((*it1) + (*it2));
				++it1; ++it2;
			}
		}

		while (it1 != end()) 
		{
			addLast(*it1);
			++it1;
		}
		while (it2 != other.end()) 
		{
			addLast(*it2);
			++it2;
		}

		return result;
	}
};