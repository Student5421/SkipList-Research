if(EXISTS "/home/shin96/workspace_starlab/co-workspace/Compact-SkipList/build/env_basic_test[1]_tests.cmake")
  include("/home/shin96/workspace_starlab/co-workspace/Compact-SkipList/build/env_basic_test[1]_tests.cmake")
else()
  add_test(env_basic_test_NOT_BUILT env_basic_test_NOT_BUILT)
endif()