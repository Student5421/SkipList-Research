if(EXISTS "/home/shin96/workspace_starlab/co-workspace/Compact-SkipList/build/ldb_cmd_test[1]_tests.cmake")
  include("/home/shin96/workspace_starlab/co-workspace/Compact-SkipList/build/ldb_cmd_test[1]_tests.cmake")
else()
  add_test(ldb_cmd_test_NOT_BUILT ldb_cmd_test_NOT_BUILT)
endif()