// Copyright (C) 2020 Sirn Nguyen Truong <sonnt174@gmail.com>

#ifndef __TIME_MEASURE_H__
#define __TIME_MEASURE_H__

#include <chrono>
#include <iostream>
#include <string>
#include <ratio>

/**
  Example of how to use class TimeMeasure:

  void test_time_measure() {
    srand(0);
    constexpr int N_SIZE = (int)1e5;
    std::vector<int> arr_nums(N_SIZE);
    for (int i = 0; i < N_SIZE; ++i) {
      auto val = rand();
      arr_nums[i] = val;
    }
    {
      auto arr = arr_nums;
      TimeMeasure<chrono::microseconds> time_mea;
      std::sort(begin(arr), end(arr));
    }
    
    {
      auto arr = arr_nums;
      using myduration = std::chrono::duration<double, std::ratio<1, 69000000000>>;
      TimeMeasure<myduration> time_mea;
      std::sort(begin(arr), end(arr));
    }
  }

*/

template <typename TimeUnit = std::chrono::milliseconds>
class TimeMeasure {
public:
  TimeMeasure() {
    start_t_ = std::chrono::steady_clock::now();
  }

  TimeUnit Elapsed() {
    auto end_t = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<TimeUnit>(end_t - start_t_);
    return elapsed;
  }

  std::string ElapsedStr() {
    std::string str = "";
    auto elap = Elapsed();
    if (DurationExpr() == "") {
      auto num = TimeUnit::period::num;
      auto den = TimeUnit::period::den;
      auto sec_factor = num * 1.0 / den;
      str = std::to_string(elap.count() * sec_factor) + " seconds";
    }
    else {
      str = std::to_string(elap.count()) + " " + DurationExpr();
    }
    str = "\nTime elapsed = " + str + "\n";
    return str;
  }

  ~TimeMeasure() {
    std::cout << ElapsedStr();
  }
private:
  std::string DurationExpr() {
    if (std::ratio_equal<typename TimeUnit::period, std::atto>::value) {
      return "atto seconds";
    }
    else if (std::ratio_equal<typename TimeUnit::period, std::femto>::value) {
      return "femto seconds";
    }
    else if (std::ratio_equal<typename TimeUnit::period, std::pico>::value) {
      return "pico seconds";
    }
    else if (std::ratio_equal<typename TimeUnit::period, std::nano>::value) {
      return "nano seconds";
    }
    else if (std::ratio_equal<typename TimeUnit::period, std::micro>::value) {
      return "micro seconds";
    }
    else if (std::ratio_equal<typename TimeUnit::period, std::milli>::value) {
      return "milli seconds";
    }
    else if (std::ratio_equal<typename TimeUnit::period, std::centi>::value) {
      return "centi seconds";
    }
    else if (std::ratio_equal<typename TimeUnit::period, std::deci>::value) {
      return "deci seconds";
    }
    else if (std::ratio_equal<typename TimeUnit::period, std::deca>::value) {
      return "deca seconds";
    }
    else if (std::ratio_equal<typename TimeUnit::period, std::hecto>::value) {
      return "hecto seconds";
    }
    else if (std::ratio_equal<typename TimeUnit::period, std::kilo>::value) {
      return "kilo seconds";
    }
    else if (std::ratio_equal<typename TimeUnit::period, std::mega>::value) {
      return "mega seconds";
    }
    else if (std::ratio_equal<typename TimeUnit::period, std::giga>::value) {
      return "giga seconds";
    }
    else if (std::ratio_equal<typename TimeUnit::period, std::tera>::value) {
      return "tera seconds";
    }
    else if (std::ratio_equal<typename TimeUnit::period, std::peta>::value) {
      return "peta seconds";
    }
    else if (std::ratio_equal<typename TimeUnit::period, std::exa>::value) {
      return "exa seconds";
    }
    else if (std::ratio_equal<typename TimeUnit::period, std::chrono::minutes::period>::value) {
      return "minutes";
    }
    else if (std::ratio_equal<typename TimeUnit::period, std::chrono::hours::period>::value) {
      return "hours";
    }
    else {
      return "";
    }
  }

  std::chrono::time_point<std::chrono::steady_clock> start_t_;
};

#endif
