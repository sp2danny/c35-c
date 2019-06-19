
#pragma once

#include <string>
#include <string_view>
#include <map>

template<typename T>
struct RepositoryBase;

template<typename T>
struct Ref
{
	Ref() = default;
	T* operator->() { return T::lookup(m_index); }
	T& operator*() { return *T::lookup(m_index); }
friend
	struct RepositoryBase<T>;
private:
	Ref(int idx) : m_index(idx) {}
	int m_index = 0;
};

template<typename T>
struct RepositoryBase
{
	int index() const { return m_index; }
	Ref<T> ref() { return Ref<T>{m_index}; }

	std::string&     name() { return m_name; }
	std::string_view name() const { return m_name; }

	static T* lookup(int id)
	{
		auto iter = table.find(id);
		if (iter == table.end()) return nullptr;
		return &iter->second;
	}
	static int lookup(std::string name)
	{
		for (auto&& r : table)
			if (r.second.m_name == name) return r.first;
		return 0;
	}
	template<typename... Args>
	static int create(Args&&... args)
	{
		auto [iter, ok] = table.try_emplace(nextIndex, std::forward<Args>(args)...);
		if (ok)
		{
			iter->second.m_index = nextIndex;
			return nextIndex++;
		}
		else
		{
			return 0;
		}
	}

protected:
	static const std::map<int, T>& tab() { return table; }

private:
	inline static int nextIndex = 1;
	inline static std::map<int, T> table;

	int         m_index;
	std::string m_name;
};
