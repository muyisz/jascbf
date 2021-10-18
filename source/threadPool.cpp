#include "threadPool.h"

threadPool::threadPool(int si) :size(si) {
	_size = si;
	for (int i = 1; i <= size; i++) {
		std::thread a;
		_pool.push_back(std::move(a));
		bool b = true;
		_state.push_back(b);
	}
}

threadPool::~threadPool() {
}

void threadPool::check() {
	if (!_task.empty()) {
		_mutex.lock();
		Task task;
		bool tag = _task.pop(task);
		_mutex.unlock();
		auto ts = [task, this]() {
			task();
			check();
		};
		ts();
	}
	else {
		for (int i = 0; i < size; i++) {
			if (_pool[i].get_id() == std::this_thread::get_id()) {
				_mutex.lock();
				_state[i] = true;
				_pool[i].detach();
				_mutex.unlock();
				return;
			}
		}
	}
}
void threadPool::commit(void(webInit::* conversation)(SOCKET), SOCKET &a, webInit* f) {
	auto ts = [this, f, a]() {
		SOCKET b = a;
		auto task = std::bind(&webInit::conversation, *f, std::forward<SOCKET>(b));
		task();
		check();
	};
	_mutex.lock();
	for (int i = 0; i < size; i++) {
		if (_state[i]) {
			_pool[i] = std::thread(ts);
			_state[i] = false;
			_mutex.unlock();
			return;
		}
	}
	_task.push(ts);
	_mutex.unlock();
}