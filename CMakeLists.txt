cmake_minimum_required(VERSION 3.20)
project(ccode C)

set(CMAKE_C_STANDARD 11)


add_executable(isMatch leetcode/isMatch.c)
add_executable(getMinimumTime leetcode/getMinimumTime.c)
add_executable(isSymmetric leetcode/binary_tree/isSymmetric.c)
add_executable(preorderTraversal leetcode/binary_tree/preorderTraversal.c)
add_executable(maxDepth leetcode/binary_tree/maxDepth.c)
add_executable(climbStairs leetcode/climbStairs.c)
add_executable(leetcode121 leetcode/leetcode0121.c)
add_executable(findRepeatNumber leetcode/findRepeatNumber.c)
add_executable(leetcode0136 leetcode/leetcode0136.c)
add_executable(leetcode0141 leetcode/leetcode0141.c)
add_executable(leetcode0141_hashTable leetcode/leetcode0141_hashTable.c)
add_executable(leetcode283 leetcode/leetcode0283.c)
add_executable(leetcode0338 leetcode/leetcode0338.c)