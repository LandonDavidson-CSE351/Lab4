# Lab4 Cache Friendly Code
This lab has two parts, both having to do with cache properties and how to best take advantage of it
- The first part contains three functions that can determine the block size, cache size, and associativity of any given cache
- The second part efficiently transposes a 32x32 and 64x64 matrix by taking full advantage of cache size and properties
  - The 32x32 solution works on 8x8 integer "blocks" of the matrix at a time since the cache is direct mapped and can store 32 blocks of 8 integers each at once. That means it can store 8 rows (8 * 32) of a 32x32 matrix without conflict misses. As a bonus, when loading up the Ai array of all the integers we are transposing in that loop, we take full advantage of the cache block size of 8 integers
  - The 64x64 solution is exactly the same except we work on 4x4 integer "blocks" since the cache can only fit 4 rows (4 * 64) of the matrix at once, meaning if we went any bigger we would start getting conflict misses. Unfortunately this solution doesn't take full advantage of the block sizes when loading the Ai array we waste half of the integers pulled up with the block.
