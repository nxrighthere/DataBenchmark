# DataBenchmark

Performance on AMD FX-4300 with `-DNDEBUG` using GCC 8.1.0:

| DOD     | OOD     | OOD (Fragmented) | OOP (Inheritance) |
|---------|---------|------------------|-------------------|
| 107.224 | 102.277 | 2027.3           | 1850.76           |

Performance on AMD Ryzen 5 1400:

| DOD     | OOD     | OOD (Fragmented) | OOP (Inheritance) |
|---------|---------|------------------|-------------------|
| 81.57   | 69.8499 | 1453.79          | 1378.33           |

Optimized compilation beyond `-O0` improves performance equally well except _OOD (Fragmented)_.

[DataBenchmark.exe](https://drive.google.com/open?id=1s2NZjKCtdQkIPdsHdnlU2Ta-wDtA25uG) (Windows x64)
