#include <vector>
#include <queue>
#include <atomic>
#include <future>
#include <iostream>
#include <stdexcept>
#include <WinSock2.h>
#include "webInit.h"

template <typename T>
class muqueue {
public:
	bool empty() {
		std::unique_lock<std::mutex> lock(m_mutex);
		return m_queue.empty();
	}
	int size() {
		std::unique_lock<std::mutex> lock(m_mutex);
		return m_queue.size();
	}
	void push(T t) {
		std::unique_lock<std::mutex> lock(m_mutex);
		m_queue.push(t);
	}
	bool pop(T& t) {
		std::unique_lock<std::mutex> lock(m_mutex);
		if (m_queue.empty()) {
			return false;
		}
		t = std::move(m_queue.front());
		m_queue.pop();
		return true;
	}
private:
	std::queue<T> m_queue;
	std::mutex  m_mutex;
};


class threadPool {
public:
	threadPool(int si);
	~threadPool();
	void check();
	void commit(void(webInit::* conversation)(SOCKET), SOCKET&, webInit*);
private:
	const int size;
	using Task = std::function<void()>;
	muqueue<Task> _task;
	std::vector<std::thread> _pool;
	std::vector<bool> _state;
	std::atomic<int> _size{ 0 };
	std::mutex _mutex;
};

/*

json("",asd,"",cad)

*/