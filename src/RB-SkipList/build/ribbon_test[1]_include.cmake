if(EXISTS "/home/shin96/workspace_starlab/co-workspace/LA-SkipList/build/ribbon_test[1]_tests.cmake")
  include("/home/shin96/workspace_starlab/co-workspace/LA-SkipList/build/ribbon_test[1]_tests.cmake")
else()
  add_test(ribbon_test_NOT_BUILT ribbon_test_NOT_BUILT)
endif()