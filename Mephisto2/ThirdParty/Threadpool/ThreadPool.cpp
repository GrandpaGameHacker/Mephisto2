/*
MIT License

Copyright (c) 2019 Felipe Bastos

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "ThreadPool.h"

thread_pool::thread_pool(size_t thread_count) {
	for (size_t i = 0; i < thread_count; ++i) {
		// start waiting threads. Workers listen for changes through
		//  the thread_pool member condition_variable
		_threads.emplace_back(std::thread([&]() {
			std::unique_lock<std::mutex> queue_lock(_task_mutex, std::defer_lock);

			while (true) {
				queue_lock.lock();
				_task_cv.wait(queue_lock, [&]() -> bool {
					return !_tasks.empty() || _stop_threads;
					});

				// used by dtor to stop all threads without having to
				//  unceremoniously stop tasks. The tasks must all be
				//  finished, lest we break a promise and risk a `future`
				//  object throwing an exception.
				if (_stop_threads && _tasks.empty())
					return;

				// to initialize temp_task, we must move the unique_ptr
				//  from the queue to the local stack. Since a unique_ptr
				//  cannot be copied (obviously), it must be explicitly
				//  moved. This transfers ownership of the pointed-to
				//  object to *this, as specified in 20.11.1.2.1
				//  [unique.ptr.single.ctor].
				auto temp_task = std::move(_tasks.front());

				_tasks.pop();
				queue_lock.unlock();

				(*temp_task)();
			}
			}));
	}
}

thread_pool::~thread_pool() {
	_stop_threads = true;
	_task_cv.notify_all();

	for (std::thread& thread : _threads) {
		thread.join();
	}
}