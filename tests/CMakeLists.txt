add_executable(UnitTests
    main.cpp
    TestEmployee.cpp
    TestFileStorage.cpp
    TestFileStorageEdge.cpp
    TestRecordLockManager.cpp
    TestConcurrency.cpp
)

target_include_directories(UnitTests
    PRIVATE
        ${PROJECT_SOURCE_DIR}/Common
        ${PROJECT_SOURCE_DIR}/Server
)

target_link_libraries(UnitTests
    PRIVATE
        gtest
        gtest_main
        Common
)

add_test(NAME AllTests COMMAND UnitTests)
