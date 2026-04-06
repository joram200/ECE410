# Layers with Highest MAC count
| Layer | Param # | MACs |
|---|---|---|
| `Conv2d (conv1)` — stem | 9,408 | 118,013,952 |
| `layer1 › BasicBlock(0) › Conv2d (conv1)` | 36,864 | 115,605,504 |
| `layer1 › BasicBlock(0) › Conv2d (conv2)` | 36,864 | 115,605,504 |
| `layer1 › BasicBlock(1) › Conv2d (conv1)` | 36,864 | 115,605,504 |
| `layer1 › BasicBlock(1) › Conv2d (conv2)` | 36,864 | 115,605,504 |

## Arithmatic Intensity for Highest MAC Layer
### Assuming FP32 for activation memory
I~Conv2d-stem~ = (2 * 118,013,952 MACs)/(46,760,000 B + (2,685,928 neurons * 4 bytes)) = 4.10 MACs/Byte
