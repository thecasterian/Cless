#ifndef CLESS_CORE_BASE_BASE_H
#define CLESS_CORE_BASE_BASE_H

namespace cless::core::base {

template <typename... Fs>
struct Overloaded : Fs... {
    using Fs::operator()...;
};

}  // namespace cless::core::base

#endif
