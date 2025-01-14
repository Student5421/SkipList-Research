//  Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).
//
// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#include "memtable/skiplist.h"
#include <set>
#include "memory/arena.h"
#include "rocksdb/env.h"
#include "test_util/testharness.h"
#include "util/hash.h"
#include "util/random.h"

#include <chrono>
typedef std::chrono::high_resolution_clock Clock;
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Zipfian pattern generator from util directory - Signal.Jin
#include "util/zipf.h"
#include "util/latest-generator.h"

namespace ROCKSDB_NAMESPACE {

typedef uint64_t Key;

struct TestComparator {
  int operator()(const Key& a, const Key& b) const {
    if (a < b) {
      return -1;
    } else if (a > b) {
      return +1;
    } else {
      return 0;
    }
  }
};

class SkipTest : public testing::Test {};
/*
TEST_F(SkipTest, NodeCompareTest) {
  const int N = 100000; // Write Count - Signal.Jin
  const int R = 6000;
  Random rnd(1000);
  std::set<Key> keys;
  Arena arena;
  TestComparator cmp;
  SkipList<Key, TestComparator> list(cmp, &arena);

  float *lat = (float *)malloc(sizeof(float)*R);
  //float *system_s = (float *)malloc(sizeof(float)*R);
  //float *system_e = (float *)malloc(sizeof(float)*R);
  int j = 0;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distr(0, N);

  uint64_t *rnd_val = (uint64_t *)malloc(sizeof(uint64_t)*R);

  //uint64_t *zipf_val = (uint64_t *)malloc(sizeof(uint64_t)*R);

  FILE *fp_sk_test;
  fp_sk_test = fopen("NodeCompare.csv", "at");

  // Insert key sequential pattern in skiplist
  for (int i = 0; i < N; i++) {
    Key key = i;
    if (keys.insert(key).second) {
      list.Insert(key);
    }
  }

  // Init Zipfian Generator - Signal.Jin
  //init_latestgen(N);
  //init_zipf_generator(0, N);

  for(int i = 0; i < R; i++) {
    //rnd_val[i] = rnd.Next() % N;
    rnd_val[i] = distr(gen);
  } // Generate Random Key - Signal.Jin

  for(int i = 0; i < R; i++) {
    zipf_val[i] = nextValue() % N;
  } // Zipfian Key Pattern - Signal.Jin

  //sleep(10);
  for(int i = 0; i < R; i++) {
    Key Gkey = rnd_val[i];
    //Key Zkey = zipf_val[i];
    //std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    auto start_time = Clock::now();
    if (list.Contains(Gkey)) { // Maybe estimate time in here - Signal.Jin
      ASSERT_EQ(keys.count(Gkey), 1U);
    } else {
      ASSERT_EQ(keys.count(Gkey), 0U);
    }
    auto end_time = Clock::now();
    //auto dur_s = start_time.time_since_epoch();
    //auto dur_e = end_time.time_since_epoch();
    //std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
    lat[j] = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count() * 0.001;
    //system_s[j] = std::chrono::duration_cast<std::chrono::nanoseconds>(dur_s);
    //system_s[j] = start_time.time_since_epoch().count();
    //system_e[j] = std::chrono::duration_cast<std::chrono::nanoseconds>(dur_e);
    j++;
  }

  for(int i = 0; i < R; i++) {
    //fprintf(fp_sk_test, "%.2f\n", system_s[i]); // Signal.Jin  
    fprintf(fp_sk_test, "%.2f\n", lat[i]); // Signal.Jin  
    //fprintf(fp_sk_test, "%.2f\n\n", system_e[i]); // Signal.Jin  
  }

  fclose(fp_sk_test);
  //free(zipf_val);
  free(rnd_val);
  free(lat);
  //free(system_s);
  //free(system_e);
  //fprintf(stdout, "Time (us) = %.2f\n", r_time); // Signal.Jin
  //fprintf(stdout, "Count = %d\n", count);
}
*/
/*
TEST_F(SkipTest, SeqInsertAndLookupX) { // Skiplist test for Sequential Pattern (Find nothing) - Signal.Jin
  const int N = 100000; // Write Count - Signal.Jin
  const int R = 50000; // Read Count - Signal.Jin
  std::set<Key> keys;
  Arena arena;
  TestComparator cmp;
  SkipList<Key, TestComparator> list(cmp, &arena);

  FILE *fp_sk_test;
  float *lat = (float *)malloc(sizeof(float)*R);
  int j = 0;

  fp_sk_test = fopen("Xseq_test_skiplist.txt", "at");
  struct timespec s_time, e_time;
  double r_time;

  // Insert key sequential pattern in skiplist
  for (int i = 0; i < N; i++) {
    Key key = i;
    if (keys.insert(key).second) {
      list.Insert(key);
    }
  }

  for (int i = N; i < R+N; i++) { 
    clock_gettime(CLOCK_MONOTONIC, &s_time);
    if (list.Contains(i)) { // Maybe estimate time in here - Signal.Jin
      ASSERT_EQ(keys.count(i), 1U);
    } else {
      ASSERT_EQ(keys.count(i), 0U);
    }
    clock_gettime(CLOCK_MONOTONIC, &e_time);
    r_time = (e_time.tv_sec - s_time.tv_sec) + (e_time.tv_nsec - s_time.tv_nsec)*0.001;
    lat[j] = r_time;
    j++;  
  }

  for(int i = 0; i < R; i++) {
    fprintf(fp_sk_test, "%.2f\n", lat[i]); // Signal.Jin  
  }
  fclose(fp_sk_test);
  free(lat);
}
*/
/*
TEST_F(SkipTest, SeqInsertAndLookup) { // Skiplist test for Sequential Pattern (Find all keys) - Signal.Jin
  const int N = 1000000; // Write Count - Signal.Jin
  const int R = 1000000; // Read Count - Signal.Jin
  std::set<Key> keys;
  Arena arena;
  TestComparator cmp;
  SkipList<Key, TestComparator> list(cmp, &arena);

  //FILE *fp_sk_test;
  //float *lat = (float *)malloc(sizeof(float)*R);
  //int j = 0;

  //fp_sk_test = fopen("./opt_sc_exp/seq/100k/sc_seq_100k.csv", "at");

  // Insert key sequential pattern in skiplist
  auto w_start = Clock::now();
  for (int i = 0; i < N; i++) {
    Key key = i;
    if (keys.insert(key).second) {
      list.Insert_On(key);
    }
  }
  auto w_end = Clock::now();

  int start_p = rand() % (N/2);
  
  auto r_start = Clock::now();
  for (int i = start_p; i < R + start_p; i++) { 
    //auto start_time = Clock::now();
    if (list.Contains_On(i)) { // Maybe estimate time in here - Signal.Jin
      ASSERT_EQ(keys.count(i), 1U);
    } else {
      ASSERT_EQ(keys.count(i), 0U);
    }
    //auto end_time = Clock::now();
    //r_time = (e_time.tv_sec - s_time.tv_sec) + (e_time.tv_nsec - s_time.tv_nsec)*0.001;
    // lat[j] = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count() * 0.001;
    // j++;
  }
  auto r_end = Clock::now();

  float r_time, w_time;
  r_time = std::chrono::duration_cast<std::chrono::nanoseconds>(r_end - r_start).count() * 0.001;
  w_time = std::chrono::duration_cast<std::chrono::nanoseconds>(w_end - w_start).count() * 0.001;
  printf("\nW = %.lf, R = %.lf\n", w_time, r_time);


  // for(int k = 0; k < R; k++) {
  //   fprintf(fp_sk_test, "%.2f\n", lat[k]); // Signal.Jin  
  // }
  // fclose(fp_sk_test);
  // free(lat);
}
*/
/*
TEST_F(SkipTest, YCSBWorkloadA) { // Skiplist test for Random Pattern - Signal.Jin
  const int N = 16000000; // Write Count - Signal.Jin
  const int run_cnt = 16000000; // Read Count - Signal.Jin
  
  Random rnd(5326);
  std::set<Key> keys;
  Arena arena;
  TestComparator cmp;
  SkipList<Key, TestComparator> list(cmp, &arena);

  // Init Zipfian Generator - Signal.Jin
  init_latestgen(N);
  init_zipf_generator(0, N);

  float r_time, w_time;

  // Insert key Random pattern in skiplist
  auto w_start = Clock::now();
  for (int i = 0; i < N; i++) {
    Key key = (nextValue() % (N)) + 1;
    if (keys.insert(key).second) {
      list.Insert_Buf(key);
    }
  }
  auto w_end = Clock::now();
  w_time = std::chrono::duration_cast<std::chrono::nanoseconds>(w_end - w_start).count() * 0.001;
  printf("\n YCSB load time = %.lf\n", w_time);
  
  auto r_start = Clock::now();
  for (int i = 0; i < run_cnt; i++) {
    Key Zkey = (nextValue() % (run_cnt)) + 1;

    int next_op = rand() % 100;

    if (next_op < 50) {
      if (list.Contains_Buf(Zkey)) {
        ASSERT_EQ(keys.count(Zkey), 1U);
      } else {
        ASSERT_EQ(keys.count(Zkey), 0U);
      }
    } else {
      if (keys.insert(Zkey).second) {
        list.Insert_Buf(Zkey);
      }
    }
  }
  auto r_end = Clock::now();
  r_time = std::chrono::duration_cast<std::chrono::nanoseconds>(r_end - r_start).count() * 0.001;
  printf("\n YCSB A run time = %.lf\n", r_time);
}
*/
/*
TEST_F(SkipTest, YCSBWorkloadB) { // Skiplist test for Random Pattern - Signal.Jin
  const int N = 16000000; // Write Count - Signal.Jin
  const int run_cnt = 16000000; // Read Count - Signal.Jin
  
  Random rnd(5326);
  std::set<Key> keys;
  Arena arena;
  TestComparator cmp;
  SkipList<Key, TestComparator> list(cmp, &arena);

  // Init Zipfian Generator - Signal.Jin
  init_latestgen(N);
  init_zipf_generator(0, N);

  float r_time, w_time;

  // Insert key Random pattern in skiplist
  auto w_start = Clock::now();
  for (int i = 0; i < N; i++) {
    Key key = (nextValue() % (N)) + 1;
    if (keys.insert(key).second) {
      list.Insert_Buf(key);
    }
  }
  auto w_end = Clock::now();
  w_time = std::chrono::duration_cast<std::chrono::nanoseconds>(w_end - w_start).count() * 0.001;
  printf("\n YCSB load time = %.lf\n", w_time);
  
  auto r_start = Clock::now();
  for (int i = 0; i < run_cnt; i++) {
    Key Zkey = (nextValue() % (run_cnt)) + 1;

    int next_op = rand() % 100;

    if (next_op < 95) {
      if (list.Contains_Buf(Zkey)) {
        ASSERT_EQ(keys.count(Zkey), 1U);
      } else {
        ASSERT_EQ(keys.count(Zkey), 0U);
      }
    } else {
      if (keys.insert(Zkey).second) {
        list.Insert_Buf(Zkey);
      }
    }
  }
  auto r_end = Clock::now();
  r_time = std::chrono::duration_cast<std::chrono::nanoseconds>(r_end - r_start).count() * 0.001;
  printf("\n YCSB B run time = %.lf\n", r_time);
}
*/
/*
TEST_F(SkipTest, YCSBWorkloadC) { // Skiplist test for Random Pattern - Signal.Jin
  const int N = 16000000; // Write Count - Signal.Jin
  const int run_cnt = 16000000; // Read Count - Signal.Jin
  
  Random rnd(5326);
  std::set<Key> keys;
  Arena arena;
  TestComparator cmp;
  SkipList<Key, TestComparator> list(cmp, &arena);

  // Init Zipfian Generator - Signal.Jin
  init_latestgen(N);
  init_zipf_generator(0, N);

  float r_time, w_time;

  // Insert key Random pattern in skiplist
  auto w_start = Clock::now();
  for (int i = 0; i < N; i++) {
    Key key = (nextValue() % (N)) + 1;
    if (keys.insert(key).second) {
      list.Insert_Buf(key);
    }
  }
  auto w_end = Clock::now();
  w_time = std::chrono::duration_cast<std::chrono::nanoseconds>(w_end - w_start).count() * 0.001;
  printf("\n YCSB load time = %.lf\n", w_time);
  
  auto r_start = Clock::now();
  for (int i = 0; i < run_cnt; i++) {
    Key Zkey = (nextValue() % (run_cnt)) + 1;
    if (list.Contains_Buf(Zkey)) {
      ASSERT_EQ(keys.count(Zkey), 1U);
    } else {
      ASSERT_EQ(keys.count(Zkey), 0U);
    }
  }
  auto r_end = Clock::now();
  r_time = std::chrono::duration_cast<std::chrono::nanoseconds>(r_end - r_start).count() * 0.001;
  printf("\n YCSB C run time = %.lf\n", r_time);
}
*/
/*
TEST_F(SkipTest, YCSBWorkloadD) { // Skiplist test for Random Pattern - Signal.Jin
  const int N = 16000000; // Write Count - Signal.Jin
  const int run_cnt = 16000000; // Read Count - Signal.Jin
  
  Random rnd(5326);
  std::set<Key> keys;
  Arena arena;
  TestComparator cmp;
  SkipList<Key, TestComparator> list(cmp, &arena);

  // Init Zipfian Generator - Signal.Jin
  init_latestgen(N);
  init_zipf_generator(0, N);

  float r_time, w_time;

  // Insert key Random pattern in skiplist
  auto w_start = Clock::now();
  for (int i = 0; i < N; i++) {
    Key key = (nextValue() % (N)) + 1;
    if (keys.insert(key).second) {
      list.Insert_Buf(key);
    }
  }
  auto w_end = Clock::now();
  w_time = std::chrono::duration_cast<std::chrono::nanoseconds>(w_end - w_start).count() * 0.001;
  printf("\n YCSB load time = %.lf\n", w_time);
  
  auto r_start = Clock::now();
  for (int i = 0; i < run_cnt; i++) {
    Key Zkey = (nextValue() % (run_cnt)) + 1;

    int next_op = rand() % 100;

    if (next_op < 95) {
      if (list.Contains_Buf(Zkey)) {
        ASSERT_EQ(keys.count(Zkey), 1U);
      } else {
        ASSERT_EQ(keys.count(Zkey), 0U);
      }
    } else {
      if (keys.insert(Zkey).second) {
        list.Insert_Buf(Zkey);
      }
    }
  }
  auto r_end = Clock::now();
  r_time = std::chrono::duration_cast<std::chrono::nanoseconds>(r_end - r_start).count() * 0.001;
  printf("\n YCSB D run time = %.lf\n", r_time);
}
*/
/*
TEST_F(SkipTest, YCSBWorkloadE) { // Skiplist test for Random Pattern - Signal.Jin
  const int N = 16000000; // Write Count - Signal.Jin
  const int run_cnt = 16000000; // Read Count - Signal.Jin
  
  Random rnd(5326);
  std::set<Key> keys;
  Arena arena;
  TestComparator cmp;
  SkipList<Key, TestComparator> list(cmp, &arena);

  // Init Zipfian Generator - Signal.Jin
  init_latestgen(N);
  init_zipf_generator(0, N);

  float r_time, w_time;

  // Insert key Random pattern in skiplist
  auto w_start = Clock::now();
  for (int i = 0; i < N; i++) {
    Key key = (nextValue() % (N)) + 1;
    if (keys.insert(key).second) {
      list.Insert_Buf(key);
    }
  }
  auto w_end = Clock::now();
  w_time = std::chrono::duration_cast<std::chrono::nanoseconds>(w_end - w_start).count() * 0.001;
  printf("\n YCSB load time = %.lf\n", w_time);
  
  auto r_start = Clock::now();
  for (int i = 0; i < run_cnt; i++) {
    Key Zkey = (nextValue() % (run_cnt)) + 1;

    int next_op = rand() % 100;

    if (next_op < 95) {
      if (list.Contains_Scan(Zkey, 100)) {
        ASSERT_EQ(keys.count(Zkey), 1U);
      } else {
        ASSERT_EQ(keys.count(Zkey), 0U);
      }
    } else {
      if (keys.insert(Zkey).second) {
        list.Insert_Buf(Zkey);
      }
    }
  }
  auto r_end = Clock::now();
  r_time = std::chrono::duration_cast<std::chrono::nanoseconds>(r_end - r_start).count() * 0.001;
  printf("\n YCSB E run time = %.lf\n", r_time);
}
*/
/*
TEST_F(SkipTest, YCSBWorkloadF) { // Skiplist test for Random Pattern - Signal.Jin
  const int N = 16000000; // Write Count - Signal.Jin
  const int run_cnt = 16000000; // Read Count - Signal.Jin
  
  Random rnd(5326);
  std::set<Key> keys;
  Arena arena;
  TestComparator cmp;
  SkipList<Key, TestComparator> list(cmp, &arena);

  // Init Zipfian Generator - Signal.Jin
  init_latestgen(N);
  init_zipf_generator(0, N);

  float r_time, w_time;

  // Insert key Random pattern in skiplist
  auto w_start = Clock::now();
  for (int i = 0; i < N; i++) {
    Key key = (nextValue() % (N)) + 1;
    if (keys.insert(key).second) {
      list.Insert_Buf(key);
    }
  }
  auto w_end = Clock::now();
  w_time = std::chrono::duration_cast<std::chrono::nanoseconds>(w_end - w_start).count() * 0.001;
  printf("\n YCSB load time = %.lf\n", w_time);
  
  auto r_start = Clock::now();
  for (int i = 0; i < run_cnt; i++) {
    Key Zkey = (nextValue() % (run_cnt)) + 1;

    int next_op = rand() % 100;

    if (next_op < 50) {
      if (list.Contains_Buf(Zkey)) {
        ASSERT_EQ(keys.count(Zkey), 1U);
      } else {
        ASSERT_EQ(keys.count(Zkey), 0U);
      }
    } else {
      if (list.Contains_Buf(Zkey)) {
        ASSERT_EQ(keys.count(Zkey), 1U);
      } else {
        ASSERT_EQ(keys.count(Zkey), 0U);
      }
      if (keys.insert(Zkey).second) {
        list.Insert_Buf(Zkey);
      }
    }
  }
  auto r_end = Clock::now();
  r_time = std::chrono::duration_cast<std::chrono::nanoseconds>(r_end - r_start).count() * 0.001;
  printf("\n YCSB F run time = %.lf\n", r_time);
}
*/

TEST_F(SkipTest, UniRandInsertAndLookup) { // Skiplist test for Random Pattern - Signal.Jin
  //const int N = 1000000; // Write Count - Signal.Jin
  const int R = 1; // Read Count - Signal.Jin
  //uint64_t scan_op = 100; // Scan Count - Signal.Jin
  Random rnd(5326);
  std::set<Key> keys;
  Arena arena;
  TestComparator cmp;
  SkipList<Key, TestComparator> list(cmp, &arena);

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distr(0, 500);
  
  //FILE *fp_sk_test;
  float *lat = (float *)malloc(sizeof(float)*R);
  //uint64_t *rnd_val = (uint64_t *)malloc(sizeof(uint64_t)*N);
  //for(int i = 0; i < N; i++) {
    //rnd_val[i] = rnd.Next() % N;
  //  rnd_val[i] = distr(gen);
  //} // Generate Random Key - Signal.Jin

  //fp_sk_test = fopen("./rbtree/default_uni_4m.csv", "at");
  //printf("\nBefore Insert\n");

  for (int i = 0; i < 64; i++) {
    //printf("%d ", distr(gen));
  }
  printf("\nEnd\n");

  auto w_start = Clock::now();
  for (int i = 0; i < 1000000; i++) {
    Key key = i+1;
    if (keys.insert(key).second) {
      list.Insert(key);
    }
  }
  auto w_end = Clock::now();
  printf("\nEnd-W\n");
  auto r_start = Clock::now();
  int j = 0;
  for (int i = 0; i < R-1; i++) { 
    Key Gkey = distr(gen)+1;
    auto start_time = Clock::now();
    if (list.Contains(Gkey)) { // Maybe estimate time in here - Signal.Jin
     ASSERT_EQ(keys.count(Gkey), 1U);
    } else {
     ASSERT_EQ(keys.count(Gkey), 0U);
    }
    auto end_time = Clock::now();
    lat[j] = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count() * 0.001;
    j++;
  }
  auto r_end = Clock::now();

  float r_time, w_time;
  r_time = std::chrono::duration_cast<std::chrono::nanoseconds>(r_end - r_start).count() * 0.001;
  w_time = std::chrono::duration_cast<std::chrono::nanoseconds>(w_end - w_start).count() * 0.001;
  printf("\nW = %.lf, R = %.lf\n", w_time, r_time);

  // Output height now  - zhao
  //int height_now = list.GetHeight_now();
  //printf("now %d \n",height_now);

  float sum = 0;
  for(int i = 0; i < R; i++) {
    sum += lat[i];
  }
  float avg = sum / R;
  printf("Avg [%d] = %lf\n", R, avg);
  int count = list.EstimateNode();
  printf("Node = %d\n", count);

  //for(int k = 0; k < R; k++) {
  //  fprintf(fp_sk_test, "%.2f\n", lat[k]);
  //}

  //fclose(fp_sk_test);
  free(lat);
  //free(rnd_val);
}

/*
TEST_F(SkipTest, ZipRandInsertAndLookup) { // Skiplist test for Random Pattern - Signal.Jin
  const int N = 1000000; // Write Count - Signal.Jin
  const int R = 1000000; // Read Count - Signal.Jin
  //uint64_t scan_op = 500; // Scan Count - Signal.Jin
  Random rnd(5326);
  std::set<Key> keys;
  Arena arena;
  TestComparator cmp;
  SkipList<Key, TestComparator> list(cmp, &arena);

  // Init Zipfian Generator - Signal.Jin
  init_zipf_generator(0, N);

  //FILE *fp_sk_test;
  //fp_sk_test = fopen("./rbtree/default_zipf_4m.csv", "at");

  //float *lat = (float *)malloc(sizeof(float)*R);
  //uint64_t *zipf_val = (uint64_t *)malloc(sizeof(uint64_t)*R);

  //for(int i = 0; i < R; i++) {
  //  zipf_val[i] = nextValue() % N;
  //} // Zipfian Key Pattern - Signal.Jin

  for (int i = 0; i < 64; i++) {
    printf("%lu ", nextValue() % 500);
  }
  printf("\nEnd\n");

  // Insert key Random pattern in skiplist
  auto w_start = Clock::now();
  for (int i = 0; i < N; i++) {
    Key key = (nextValue() % (N)) + 1;
    if (keys.insert(key).second) {
      list.Insert_Buf(key);
    }
  }
  auto w_end = Clock::now();
  //int j = 0;
  printf("read\n");
  auto r_start = Clock::now();
  for (int i = 0; i < R; i++) {
    Key Zkey = (nextValue() % (R)) + 1;
    //auto start_time = Clock::now();
    if (list.Contains_Buf(Zkey)) { // Maybe estimate time in here - Signal.Jin
      ASSERT_EQ(keys.count(Zkey), 1U);
    } else {
      ASSERT_EQ(keys.count(Zkey), 0U);
    }
    //auto end_time = Clock::now();
    //lat[j] = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count() * 0.001;
    //j++;
  }
  auto r_end = Clock::now();

  float r_time, w_time;
  r_time = std::chrono::duration_cast<std::chrono::nanoseconds>(r_end - r_start).count() * 0.001;
  w_time = std::chrono::duration_cast<std::chrono::nanoseconds>(w_end - w_start).count() * 0.001;

  printf("\nw=%.lf, r=%.lf\n", w_time, r_time);

  //printf("Node = %lu\n", list.EstimateNode());
  //list.Estimate_Max();
  //printf("height = %d\n", list.GetHeight_now());
  // float sum = 0;
  // for(int i = 0; i < R; i++) {
  //   sum += lat[i];
  // }
  // float avg = sum / R;

  // printf("Avg [%d] = %lf\n", R, avg);

  //for(int k = 0; k < R; k++) {
    //fprintf(fp_sk_test, "%.2f\n", lat[k]);
    //printf("%.2f\n", lat[k]);
  //}
  //fclose(fp_sk_test);
  //free(zipf_val);
  //free(lat);
}
*/
/*
TEST_F(SkipTest, RealWorldWorkloadTest) { // Skiplist test for Random Pattern - Signal.Jin
  const int N = 200000000;

  std::set<Key> keys;
  Arena arena;
  TestComparator cmp;
  SkipList<Key, TestComparator> list(cmp, &arena);

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distr(0, N);

  std::string file_path = "../dataset/keys/fb.txt";
  std::ifstream file(file_path);

  if (!file.is_open()) {
    std::cerr << "Failed to open file: " << file_path << std::endl;
  }

  std::vector<uint64_t> numbers;
  std::string line;

  while(std::getline(file, line)) {
    uint64_t number = std::stoull(line);
    numbers.push_back(number); 
  }

  file.close();

  auto w_start = Clock::now();
  for (std::size_t i = 0; i < numbers.size(); i++) {
    Key key = numbers[i];
    //Key key = numbers[distr(gen)];
    if (keys.insert(key).second) {
      list.Insert_Buf(key);
    }
  }
  auto w_end = Clock::now();

  auto r_start = Clock::now();
  for (std::size_t i = 0; i < numbers.size(); i++) { 
    Key Gkey = numbers[i];
    //Key Gkey = numbers[distr(gen)];
    if (list.Contains_Buf(Gkey)) { // Maybe estimate time in here - Signal.Jin
     ASSERT_EQ(keys.count(Gkey), 1U);
    } else {
     ASSERT_EQ(keys.count(Gkey), 0U);
    }
  }
  auto r_end = Clock::now();

  float r_time, w_time;
  r_time = std::chrono::duration_cast<std::chrono::nanoseconds>(r_end - r_start).count() * 0.001;
  w_time = std::chrono::duration_cast<std::chrono::nanoseconds>(w_end - w_start).count() * 0.001;
  printf("\nW = %.lf, R = %.lf\n", w_time, r_time);
  printf("\nData length = %lu\n", numbers.size());
}
*/
// We want to make sure that with a single writer and multiple
// concurrent readers (with no synchronization other than when a
// reader's iterator is created), the reader always observes all the
// data that was present in the skip list when the iterator was
// constructor.  Because insertions are happening concurrently, we may
// also observe new values that were inserted since the iterator was
// constructed, but we should never miss any values that were present
// at iterator construction time.
//
// We generate multi-part keys:
//     <key,gen,hash>
// where:
//     key is in range [0..K-1]
//     gen is a generation number for key
//     hash is hash(key,gen)
//
// The insertion code picks a random key, sets gen to be 1 + the last
// generation number inserted for that key, and sets hash to Hash(key,gen).
//
// At the beginning of a read, we snapshot the last inserted
// generation number for each key.  We then iterate, including random
// calls to Next() and Seek().  For every key we encounter, we
// check that it is either expected given the initial snapshot or has
// been concurrently added since the iterator started.
class ConcurrentTest {
 private:
  static const uint32_t K = 4;

  static uint64_t key(Key key) { return (key >> 40); }
  static uint64_t gen(Key key) { return (key >> 8) & 0xffffffffu; }
  static uint64_t hash(Key key) { return key & 0xff; }

  static uint64_t HashNumbers(uint64_t k, uint64_t g) {
    uint64_t data[2] = { k, g };
    return Hash(reinterpret_cast<char*>(data), sizeof(data), 0);
  }

  static Key MakeKey(uint64_t k, uint64_t g) {
    assert(sizeof(Key) == sizeof(uint64_t));
    assert(k <= K);  // We sometimes pass K to seek to the end of the skiplist
    assert(g <= 0xffffffffu);
    return ((k << 40) | (g << 8) | (HashNumbers(k, g) & 0xff));
  }

  static bool IsValidKey(Key k) {
    return hash(k) == (HashNumbers(key(k), gen(k)) & 0xff);
  }

  static Key RandomTarget(Random* rnd) {
    switch (rnd->Next() % 10) {
      case 0:
        // Seek to beginning
        return MakeKey(0, 0);
      case 1:
        // Seek to end
        return MakeKey(K, 0);
      default:
        // Seek to middle
        return MakeKey(rnd->Next() % K, 0);
    }
  }

  // Per-key generation
  struct State {
    std::atomic<int> generation[K];
    void Set(int k, int v) {
      generation[k].store(v, std::memory_order_release);
    }
    int Get(int k) { return generation[k].load(std::memory_order_acquire); }

    State() {
      for (unsigned int k = 0; k < K; k++) {
        Set(k, 0);
      }
    }
  };

  // Current state of the test
  State current_;

  Arena arena_;

  // SkipList is not protected by mu_.  We just use a single writer
  // thread to modify it.
  SkipList<Key, TestComparator> list_;

 public:
  ConcurrentTest() : list_(TestComparator(), &arena_) {}

  // REQUIRES: External synchronization
  void WriteStep(Random* rnd) {
    const uint32_t k = rnd->Next() % K;
    const int g = current_.Get(k) + 1;
    const Key new_key = MakeKey(k, g);
    list_.Insert(new_key);
    current_.Set(k, g);
  }

  void ReadStep(Random* rnd) {
    // Remember the initial committed state of the skiplist.
    State initial_state;
    for (unsigned int k = 0; k < K; k++) {
      initial_state.Set(k, current_.Get(k));
    }

    Key pos = RandomTarget(rnd);
    SkipList<Key, TestComparator>::Iterator iter(&list_);
    iter.Seek(pos);
    while (true) {
      Key current;
      if (!iter.Valid()) {
        current = MakeKey(K, 0);
      } else {
        current = iter.key();
        ASSERT_TRUE(IsValidKey(current)) << current;
      }
      ASSERT_LE(pos, current) << "should not go backwards";

      // Verify that everything in [pos,current) was not present in
      // initial_state.
      while (pos < current) {
        ASSERT_LT(key(pos), K) << pos;

        // Note that generation 0 is never inserted, so it is ok if
        // <*,0,*> is missing.
        ASSERT_TRUE((gen(pos) == 0U) ||
                    (gen(pos) > static_cast<uint64_t>(initial_state.Get(
                                    static_cast<int>(key(pos))))))
            << "key: " << key(pos) << "; gen: " << gen(pos)
            << "; initgen: " << initial_state.Get(static_cast<int>(key(pos)));

        // Advance to next key in the valid key space
        if (key(pos) < key(current)) {
          pos = MakeKey(key(pos) + 1, 0);
        } else {
          pos = MakeKey(key(pos), gen(pos) + 1);
        }
      }

      if (!iter.Valid()) {
        break;
      }

      if (rnd->Next() % 2) {
        iter.Next();
        pos = MakeKey(key(pos), gen(pos) + 1);
      } else {
        Key new_target = RandomTarget(rnd);
        if (new_target > pos) {
          pos = new_target;
          iter.Seek(new_target);
        }
      }
    }
  }
};
const uint32_t ConcurrentTest::K;

// Simple test that does single-threaded testing of the ConcurrentTest
// scaffolding.
/*
TEST_F(SkipTest, ConcurrentWithoutThreads) {
  ConcurrentTest test;
  Random rnd(test::RandomSeed());
  for (int i = 0; i < 1; i++) {
    test.ReadStep(&rnd);
    test.WriteStep(&rnd);
  }
}
*/
class TestState {
 public:
  ConcurrentTest t_;
  int seed_;
  std::atomic<bool> quit_flag_;

  enum ReaderState {
    STARTING,
    RUNNING,
    DONE
  };

  explicit TestState(int s)
      : seed_(s), quit_flag_(false), state_(STARTING), state_cv_(&mu_) {}

  void Wait(ReaderState s) {
    mu_.Lock();
    while (state_ != s) {
      state_cv_.Wait();
    }
    mu_.Unlock();
  }

  void Change(ReaderState s) {
    mu_.Lock();
    state_ = s;
    state_cv_.Signal();
    mu_.Unlock();
  }

 private:
  port::Mutex mu_;
  ReaderState state_;
  port::CondVar state_cv_;
};
/*
static void ConcurrentReader(void* arg) {
  TestState* state = reinterpret_cast<TestState*>(arg);
  Random rnd(state->seed_);
  int64_t reads = 0;
  state->Change(TestState::RUNNING);
  while (!state->quit_flag_.load(std::memory_order_acquire)) {
    state->t_.ReadStep(&rnd);
    ++reads;
  }
  state->Change(TestState::DONE);
}
*/
/*
static void RunConcurrent(int run) { // In here, Main step for Skiplist_test (WriteStep) - Signal.Jin
  const int seed = test::RandomSeed() + (run * 100);
  Random rnd(seed);
  const int N = 1;
  //const int kSize = 250000;
  for (int i = 0; i < N; i++) {
    TestState state(seed + 1);
    Env::Default()->SetBackgroundThreads(4);
    //Env::Default()->Schedule(ConcurrentReader, &state);
    Env::Default()->Schedule(ConcurrentWriter, &state);
    
    state.Wait(TestState::RUNNING);
    for (int k = 0; k < kSize; k++) {
      state.t_.WriteStep(&rnd);
    }
    state.quit_flag_.store(true, std::memory_order_release);
    state.Wait(TestState::DONE);
    
  }
}
*/
//TEST_F(SkipTest, Concurrent1) { RunConcurrent(1); }
//TEST_F(SkipTest, Concurrent2) { RunConcurrent(2); }
//TEST_F(SkipTest, Concurrent3) { RunConcurrent(3); }
//TEST_F(SkipTest, Concurrent4) { RunConcurrent(4); }
//TEST_F(SkipTest, Concurrent5) { RunConcurrent(5); }

}  // namespace ROCKSDB_NAMESPACE

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
