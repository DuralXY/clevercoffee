/**
 * @file Timer.h
 *
 * @brief A helper class to call a method in regular intervals
 */

#pragma once

#include "Arduino.h"

#include <functional>

class Timer {
    public:
        /** No default constructor */
        Timer() = delete;

        /**
         * @brief COnstructor taking a function pointer and the desired interval
         *
         * @param func Function pointer for the callback to be executed upon timer expiry
         * @param long Desired interval between calls in milliseconds
         */
        Timer(std::function<void()> func, unsigned long interval);

        /**
         * @brief Call operator for timer invocation
         * @details This will check if the timer expired and invoke the callback
         */
        void operator()();

        /**
         * @brief Reset the timer
         * @details This resets the timer such that the callback will be executed directly upon its next invocation
         */
        void reset();

    private:
        // Callback to be executed when timer runs out:
        std::function<void()> callback_;

        // Interval of timer execution
        unsigned long interval_;

        // Next time the timer will run out
        unsigned long next_;
};
