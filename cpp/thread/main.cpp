#include <thread>
#include <vector>
#include <iostream>

void a() {
  std::cout << " thread id: "<<  std::this_thread::get_id() << std::endl;
}

class Worker {
  int id_;
  std::thread thread_;

  void  _invoke() {
    std::cout << "worker number " << id_ << " thread id: "<<  std::this_thread::get_id() << std::endl;
  }

public:
  Worker(int id) : id_(id) {}

  void invoke() {
     // std::thread t(_invoke);
     // treahd
  }
};

const std::vector<Worker> createWorker(int const n) {
  std::vector<Worker> vec;

  for (int i = 0; i < n; i++) {
    vec.push_back(Worker(i));
  }

  return vec;
}


int main(int argc, char *argv[])
{
  std::vector<Worker> workers = createWorker(5);
  for (auto& w : workers) {
    w.invoke();
  }


  return 0;
}
