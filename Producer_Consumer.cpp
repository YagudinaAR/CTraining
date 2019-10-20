#include <iostream>
#include <thread>
#include <deque>
#include <mutex>
#include <chrono>
#include <condition_variable>

using namespace std;

mutex cout_mu;

class Buffer
{
	deque<int> buffer_;
	const unsigned int size_ = 10;
	mutex mu;
	condition_variable cond;
public:
	Buffer() {}
	void add(int num)
	{
		while (true)
		{
			unique_lock<mutex> locker(mu);
			cond.wait(locker, [this]() {return buffer_.size() < size_; });
			buffer_.push_back(num);
			locker.unlock();
			cond.notify_all();
			return;
		}
	}
	int remove() 
	{
		while (true)
		{
			unique_lock<mutex> locker(mu);
			cond.wait(locker, [this]() {return buffer_.size() > 0; });
			int back = buffer_.back();
			buffer_.pop_back();
			locker.unlock();
			cond.notify_all();
			return back;
		}
	}
};

class Producer
{
	Buffer& buffer_;

public:
	Producer(Buffer& buffer) : buffer_(buffer) {};
	void run() 
	{
		while (true) 
		{
			int num = rand() % 100;
			buffer_.add(num);
			cout_mu.lock();
			cout << "Produced: " << num << endl;
			this_thread::sleep_for(chrono::milliseconds(50));
			cout_mu.unlock();
		}
	}
};

class Consumer
{
	Buffer& buffer_;

public:
	Consumer(Buffer& buffer) : buffer_(buffer) {};
	void run() 
	{
		while (true) 
		{
			int num = buffer_.remove();
			cout_mu.lock();
			cout << "Consumed: " << num << endl;
			this_thread::sleep_for(chrono::milliseconds(50));
			cout_mu.unlock();
		}
	}

};

int main() 
{
	Buffer b;
	Producer p(b);
	Consumer c(b);

	thread producer_thread(&Producer::run, &p);
	thread consumer_thread(&Consumer::run, &c);

	producer_thread.join();
	consumer_thread.join();
	return 0;
}