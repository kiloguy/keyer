## keyer

keyer is a simple program to deal with keyer effects (去背). It simply replaces all the pixels with the color you specified with transparent color (0, 0, 0, 0).

### Usage
```
Usage: keyer <input file> <output file> {png|jpg|bmp} <r> <g> <b> [a]
```
If the input image has 4 channels (rgba), "a" should be specified.
Value of r, g, b, a are integer 0 ~ 255.
**Currently only support output PNG format.**