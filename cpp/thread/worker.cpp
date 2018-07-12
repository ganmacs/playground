#include <deque>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <cassert>

template <typename T> class Queue
{
public:
  Queue(int size)
    : size_(size)
  {}
  bool put(T&& data) {
    if (size_ <= deque_.size()) {
      return false;
    }
    deque_.emplace_back(std::move(data));
    return true;
  }
  bool put(const T& data) {
    if (size_ <= deque_.size()) {
      return false;
    }
    deque_.emplace_back(data);
    return true;
  }
  bool get(T& data) {
    if (deque_.empty()) {
      return false;
    }
    data = std::move(deque_.front());
    deque_.pop_front();
    return true;
  }
  bool empty() const {
    return deque_.empty();
  }
private:
  int size_;
  std::deque<T> deque_;
};

class Runnable
{
public:
  virtual void run() = 0;
};

class ThreadPool
{
public:
  ThreadPool(int threadCount, int queueSize)
    : isTerminationRequested_(false)
    , queue_(queueSize)
  {
    for (int n = 0; n < threadCount; n++) {
      threads_.emplace_back(std::thread(main_));
    }
  }
  ~ThreadPool() {
    {
      std::unique_lock<std::mutex> ul(mutex_);
      isTerminationRequested_ = true;
    }
    cv_.notify_all();
    const int size = threads_.size();
    for (int n = 0; n < size; n++) {
      threads_.at(n).join();
    }
  }
  bool add(std::shared_ptr<Runnable> &&runnable) {
    {
      std::unique_lock<std::mutex> ul(mutex_);
      if (!queue_.put(std::move(runnable))) { return false; }
    }
    cv_.notify_all();
    return true;
  }
  bool add(const std::shared_ptr<Runnable> &runnable) {
    {
      std::unique_lock<std::mutex> ul(mutex_);
      if (!queue_.put(runnable)) { return false; }
    }
    cv_.notify_all();
    return true;
  }
private:
  std::function<void()> main_ = [this]()
  {
    while (1) {
      std::shared_ptr<Runnable> runnable;
      {
        std::unique_lock<std::mutex> ul(mutex_);
        while (queue_.empty()) {
          if (isTerminationRequested_) { return; }
          cv_.wait(ul);
        }
        const bool result = queue_.get(runnable);
        assert(result);
      }
      runnable->run();
    }
  };
  bool isTerminationRequested_;
  Queue<std::shared_ptr<Runnable>> queue_;
  std::mutex mutex_;
  std::condition_variable cv_;
  std::vector<std::thread> threads_;
};



int main(int argc, char *argv[])
{

  return 0;
}
