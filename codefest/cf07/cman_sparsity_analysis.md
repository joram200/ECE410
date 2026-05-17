# Sparsity Breakeven Analysis

1. N = 512 and sparsity s
    1. 2N<sup>2</sup> = 524288 FLOPs
    2. 4N<sup>2</sup> = 1048576 Bytes
    3. 2\(1-s\)N<sup>2</sup> = \(1-s\) ⋅ 524288 FLOPs
    4. \{2\[4\(1-s\)N<sup>2</sup>\]\}+\(N+1\) = \[\(1-s\) ⋅ 2097152\] + 513 Bytes
2. Speedup is 524288 FLOPs / \(1-s\) ⋅ 524288 FLOPs or 1 / \(1-s\). Speedup would be 2x when s = 0.5 \[1 / \(1-0.5\) = 1 / 0.5 = 2\].
3. Original Memory equation: 1048576 Bytes = \[\(1-s\) ⋅ 2097152\] + 513 Bytes
    1. 1048576 Bytes - 513 Bytes = \[\(1-s\) ⋅ 2097152\] + 513 Bytes - 513 Bytes => 1048063 Bytes = \(1-s\) ⋅ 2097152 Bytes
    2. 1048063 Bytes / 2097152 Bytes = \(1-s\) ⋅ 2097152 Bytes / 2097152 Bytes => 0.499755382538 = 1 - s
    3. 0.499755382538 + s = 1 - s + s => 0.499755382538 + s = 1
    4. 0.499755382538 + s - 0.499755382538 = 1 - 0.499755382538 => **s = 0.500244617462 ≈ 0.5**
4. 
