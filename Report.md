# Best threads count

```
| Num Threads  | file size | result |
|1|100mb|1010955 ms|
|2|100mb|1085080 ms|
|4|100mb|70595 ms|
|8|100mb|102016 ms|
|16|100mb|227942 ms|

```

# Optimaized version
| Num Threads  | file size | result |
|1|100mb| 86825 ms|
|2|100mb| 87806 ms|
|4|100mb| 5864 ms|
|8|100mb| 9984 ms|
|16|100mb| 20743 ms|

# Hardware
```bash
machdep.cpu.core_count: 8
machdep.cpu.thread_count: 8
machdep.cpu.brand_string: Apple M1
```