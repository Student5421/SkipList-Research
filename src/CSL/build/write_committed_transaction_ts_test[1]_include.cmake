if(EXISTS "/home/shin96/workspace_starlab/co-workspace/Compact-SkipList/build/write_committed_transaction_ts_test[1]_tests.cmake")
  include("/home/shin96/workspace_starlab/co-workspace/Compact-SkipList/build/write_committed_transaction_ts_test[1]_tests.cmake")
else()
  add_test(write_committed_transaction_ts_test_NOT_BUILT write_committed_transaction_ts_test_NOT_BUILT)
endif()