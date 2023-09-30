#ifndef CPP_ALGORITHM_UTIL_SEMAPHORE_HPP
#define CPP_ALGORITHM_UTIL_SEMAPHORE_HPP
#include <condition_variable>
#include <mutex>
namespace my::sync {
class Semaphore {
private:
  size_t m_cnt;
  std::mutex m_mut;
  std::condition_variable m_cv;
public:
  Semaphore(size_t cnt) : m_cnt{cnt}, m_cv{}, m_mut{} {}
  Semaphore() : Semaphore(0) {}
  void post() {
    std::unique_lock lg(m_mut);
    ++m_cnt;
    m_cv.notify_one();
  }
  void wait() {
    std::unique_lock lg(m_mut);
    m_cv.wait(lg, [this] { return m_cnt > 0; });
    --m_cnt;
  }
};
}
#endif //CPP_ALGORITHM_UTIL_SEMAPHORE_HPP