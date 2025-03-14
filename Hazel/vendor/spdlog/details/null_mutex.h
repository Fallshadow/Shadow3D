#pragma once

#include <atomic>
// #include <atomic> 是 C++ 标准库中的一个头文件，提供了对原子操作的支持。原子操作是指在多线程环境中可以安全地进行而不需要使用锁的操作。使用原子操作可以避免数据竞争，提高程序的并发性能。
// 原子类型（如 std::atomic<int>）允许在多个线程之间安全地共享数据，而不需要显式的锁机制。
// 这些操作是不可分割的，即在一个线程中执行的原子操作不会被其他线程的操作中断。
// 
// null, no cost dummy "mutex" and dummy "atomic" int
// 在 C++ 中，有时我们需要使用一些占位符或“虚拟”实现来满足接口要求或进行性能优化。
// 在这种情况下，注释提到的 “dummy mutex” 和 “dummy atomic int” 是指没有实际同步开销的占位符实现。
// Dummy Mutex
// 一个 “dummy mutex” 是一个不执行任何操作的互斥锁实现。它通常用于模板编程中，当你希望在某些情况下避免实际的锁开销时使用。
// 在多线程代码中，如果你确定某些代码路径不需要实际的同步（例如，因为它们只在单线程环境中运行），可以使用 “dummy mutex” 来避免不必要的性能开销。
// 
// Dummy Atomic Int
// 一个 “dummy atomic int” 是一个不具备原子性操作特性的整数实现。它在逻辑上表现为原子类型，但实际上不提供任何同步机制。
// 类似于 “dummy mutex” ，在某些情况下，你可能希望避免使用真正的原子操作（例如，在单线程环境中），以减少性能开销。
// 
// class DummyMutex {  
// public:
//     void lock() {}
//     void unlock() {}
//     bool try_lock() { return true; }
// };
// 
// template<typename T>
// 
// class DummyAtomic {
// public:
//     DummyAtomic(T value = T()) : value_(value) {}
// 
//     T load() const { return value_; }
//     void store(T value) { value_ = value; }
// 
//     // Other atomic operations can be similarly defined as no-ops  
// private:
//     T value_;
// };
// 
// 使用场景
// 模板编程：在模板类中，你可以根据编译时条件选择使用真正的互斥锁或原子类型，或者使用这些“dummy”实现。
// 性能优化：在性能关键的代码中，避免不必要的同步开销。

namespace spdlog {
	namespace details {

        struct null_mutex {
            void lock() {}
            void unlock() {}
            bool try_lock() {
                return true;
            }
        };

        struct null_atomic_int {
            int value;
            null_atomic_int() = default;

            // 在 C++ 中，explicit 关键字用于构造函数，以防止隐式类型转换。
            // 它的主要作用是避免在对象初始化时发生意外的隐式转换，从而提高代码的安全性和可读性。
            explicit null_atomic_int(int val) : value(val) {

            }

            int load(std::memory_order) const {
                return value;
            }

            void store(int val) {
                value = val;
            }
        };
	}
}