#!/usr/bin/env python
# Pre-compute sine and cosine values for the pie watchface
# Usage: python precompute.py
# Then copy result into pie.c
# by Wolfram Roesler 2018-07-31

import math
import sys

radius = 200
sys.stdout.write('#define RADIUS %d\n' % radius)

sys.stdout.write('static const int xoffset[] = {\n    ')
for x in range(0,720):
    sys.stdout.write('%d,' % (radius * math.sin(x / 720.0 * 2 * math.pi)))
sys.stdout.write('\n};\n')

sys.stdout.write('static const int yoffset[] = {\n    ')
for x in range(0,720):
    sys.stdout.write('%d,' % (-radius * math.cos(x / 720.0 * 2 * math.pi)))
sys.stdout.write('\n};\n')
