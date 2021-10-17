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
			//	std::cout << _pool[i].get_id()<<"线程被销毁" << std::endl;
				_state[i] = true;
				_pool[i].detach();
				_mutex.unlock();
			//	std::cout << _pool[i].get_id() << "线程被销毁后" << std::this_thread::get_id() << "是调用者" << std:: endl;
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
		//	std::cout << _pool[i].get_id() << "被调用前"<<std::endl;
			_pool[i] = std::thread(ts);
		//	std::cout << _pool[i].get_id() << "被启用后" << std::this_thread::get_id() << "是调用者" << std::endl;
			_state[i] = false;
			_mutex.unlock();
			return;
		}
	}
	_task.push(ts);
	_mutex.unlock();
}

/*
线程死锁了，考虑多加几把锁，有的线程未得到释放，占用锁之后未释放导致剩余的线性也无法进入

*/