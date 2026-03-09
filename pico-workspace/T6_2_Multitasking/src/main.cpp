/**
 * @file main.cpp
 * @brief Template implementation for basic multithreading with std::thread.
 *
 * DISCLAIMER:
 * This file is the task template file for ELEC C7222
 * Module 6 Task 6.2: Multitasking.
 * Students are expected to complete and/or modify this template according to
 * the assignment instructions.
 */

#include <algorithm>
#include <chrono>
#include <iostream>
#include <thread>

/**
 * Task Description (Module 6 Task 6.2: Multitasking)
 *
 * Goal:
 * - Create and run two worker threads using ``std::thread``.
 * - Practice deterministic thread execution without synchronization objects.
 *
 * Requirements:
 * 1. Implement ``run_simulation(int producer_period_ms, int consumer_period_ms,
 *    int duration_ms)``.
 * 2. Start two worker threads inside that function:
 *    - producer: increments producer counter periodically
 *    - consumer: increments sample counter periodically
 * 3. Do not use ``std::mutex``, ``std::atomic``, condition variables, or
 *    semaphores in this task, just use ``std::this_thread::sleep_for`` to adjust timing.
 * 4. Both workers must measure elapsed time since startup and each worker runs
 *    until its own elapsed time reaches ``duration_ms``.
 * 5. Join both threads and return counters in ``SimulationResult``.
 * 6. In ``main()``, call ``run_simulation(20, 30, 200)`` and keep the summary
 *    output line unchanged.
 *
 * Timing hint:
 * - ``std::chrono::steady_clock::now()``
 * - ``std::chrono::milliseconds(...)``
 * - ``std::this_thread::sleep_for(...)``
 * Reference: https://cplusplus.com/reference/chrono/
 */

/**
 * @brief Result bundle returned by run_simulation().
 * @details Stores deterministic counters collected from both worker threads.
 */
struct SimulationResult {
	/** Number of producer-loop iterations completed during the run window. */
	int produced_count;
	/** Number of consumer-loop iterations completed during the run window. */
	int consumed_samples;
	/** Combined value computed as produced_count + consumed_samples. */
	int final_value;
};

/**
 * @brief Run a fixed-time two-thread simulation without synchronization objects.
 * @param producer_period_ms Sleep period of the producer worker in milliseconds.
 * @param consumer_period_ms Sleep period of the consumer worker in milliseconds.
 * @param duration_ms Total simulation duration in milliseconds.
 * @return SimulationResult with producer count, consumer count, and their sum.
 * @details
 * This function must:
 * - clamp period values to at least 1 ms,
 * - clamp duration to [1, 500] ms,
 * - start two workers (producer and consumer),
 * - join both workers before returning.
 */
SimulationResult run_simulation(int producer_period_ms, int consumer_period_ms, int duration_ms) {
	// TODO: validate periods and duration to avoid non-positive sleep durations. Make sure duration
	// is at least 1ms to avoid zero-duration edge case but also it must be less than 500 ms.
	producer_period_ms = std::max(1, producer_period_ms);
    consumer_period_ms = std::max(1, consumer_period_ms);
    duration_ms = std::clamp(duration_ms, 1, 500);

	// TODO: declare producer and consumer counters
	int produced_count = 0;
    int consumed_samples = 0;

	auto worker_task = [](int& counter, int period, int max_duration) {
        auto start_time = std::chrono::steady_clock::now();
        auto duration_limit = std::chrono::milliseconds(max_duration);
        auto sleep_time = std::chrono::milliseconds(period);

        while ((std::chrono::steady_clock::now() - start_time) < duration_limit) {
            counter++;
            std::this_thread::sleep_for(sleep_time);
        }
    };

	// TODO: create producer worker threa
	// TODO: create consumer worker thread
	std::thread producer(worker_task, std::ref(produced_count), producer_period_ms, duration_ms);
    std::thread consumer(worker_task, std::ref(consumed_samples), consumer_period_ms, duration_ms);

	// TODO: join both threads before computing return value
	producer.join();
    consumer.join();

	// TODO: compute final_value and return SimulationResult
	
	int final_value = produced_count + consumed_samples;
    
    return SimulationResult{produced_count, consumed_samples, final_value};
}
	

/**
 * @brief Program entry point for the grading harness.
 * @return 0 on successful execution.
 * @details Calls run_simulation() with fixed arguments and prints one required
 * summary line that must remain unchanged for automatic I/O grading.
 */
int main() {
	// TODO: call run_simulation with required arguments
	SimulationResult result = run_simulation(20, 30, 200);

	// IMPORTANT: keep the std::cout output line and text unchanged.
	// The automatic grader validates exact stdout output.
	std::cout << "summary produced=" << result.produced_count << " consumed=" << result.consumed_samples
			  << " final=" << result.final_value << std::endl;

	return 0;
}
