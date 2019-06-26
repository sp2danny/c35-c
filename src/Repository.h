
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
	operator T*() { return T::lookup(m_index); }
	operator bool() const { return T::lookup(m_index) != nullptr; }
	friend struct RepositoryBase<T>;
	friend T;

	bool operator <(const Ref& other) const { return m_index  < other.m_index; }
	bool operator==(const Ref& other) const { return m_index == other.m_index; }

private:
	Ref(int idx) : m_index(idx) {}
	int m_index = 0;
};

template<typename T>
struct CRef
{
	CRef() = default;
	const T* operator->() { return T::lookup(m_index); }
	const T& operator*() { return *T::lookup(m_index); }
	operator const T*() { return T::lookup(m_index); }
	operator bool() const { return T::lookup(m_index) != nullptr; }
	friend struct RepositoryBase<T>;

	bool operator <(const CRef& other) const { return m_index  < other.m_index; }
	bool operator==(const CRef& other) const { return m_index == other.m_index; }

private:
	CRef(int idx) : m_index(idx) {}
	int m_index = 0;
};

template<typename T>
struct RepositoryBase
{
	int index() const { return m_index; }
	Ref<T> ref() { return Ref<T>{m_index}; }
	CRef<T> ref() const { return CRef<T>{m_index}; }
	CRef<T> cref() const { return CRef<T>{m_index}; }

	std::string&     name() { return m_name; }
	std::string_view name() const { return m_name; }

	static T* lookup(int id)
	{
		auto iter = table.find(id);
		if (iter == table.end()) return nullptr;
		return &iter->second;
	}
	static int lookup(std::string_view name)
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
	static void clear()
	{
		table.clear();
		nextIndex = 1;
	}

protected:
	static const std::map<int, T>& tab() { return table; }

	struct iterator
	{
		iterator operator++() { ++underlying; return *this; }
		bool operator!=(iterator other) { return underlying != other.underlying; }
		T& operator*() { return underlying->second; }
		T* operator->() { return &underlying->second; }
		typename std::map<int, T>::iterator underlying;
	};

	static const iterator begin() { return {table.begin()}; }
	static const iterator end()   { return {table.end()  }; }

private:
	inline static int nextIndex = 1;
	inline static std::map<int, T> table;

	int m_index;
	std::string m_name;
};
