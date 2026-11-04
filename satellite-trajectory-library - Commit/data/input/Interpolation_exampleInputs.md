INPUTS USED BY interpolation_example.cpp

Example 1: points on y = x^2 + x + 1
  x-values:       0 1 2
  y-values:       1 3 7
  query x:        1.5

Example 2: satellite on a circular orbit
  orbit radius:   7000 (km)
  orbit period:   96 (minutes)
  known times:    0 8 16 24 (minutes)
  query time:     12 (minutes)
  (x-positions are computed from x(t) = 7000 * cos(2 * pi * t / 96))

Example 3: bad input
  x-values:       0 1 1
  y-values:       0 1 2
  query x:        0.5
