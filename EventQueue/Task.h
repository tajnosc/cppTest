#include <functional>

/*!
 * Common task, can be unix event, JSON processing task or whatever.
 */
using Task = std::function<void()>;