#!/usr/bin/env python3
"""
Visualize intersection of unit circles
"""
from __future__ import print_function
import argparse
import itertools
import pandas as pd
import numpy as np
from matplotlib import patches
import matplotlib.pyplot as plt


def parse_args(*argument_array):
  parser = argparse.ArgumentParser()
  parser.add_argument('--csv', required=True,
                      help='CSV file with circle centers.')
  parser.add_argument('--circles', nargs='+', type=int,
                      help='Indices of circles to include.')
  args = parser.parse_args(*argument_array)
  return args


def intersect(c1, c2):
  c_x = c2[0] - c1[0]
  c_y = c2[1] - c1[1]
  s = c_x ** 2 + c_y ** 2
  if c_x < 1e-10:
    y = s / (2 * c_y)
    x = np.sqrt(1 - y ** 2)
    return (x + c1[0], y + c1[1]), (-x + c1[0], y + c1[1])
  print('c_x', c_x)
  r = c_y / c_x
  u = s / (2 * c_x)
  a = 1 + r ** 2
  b = 2 * r * u
  c = u ** 2 - 1
  det = b ** 2 - 4 * a * c

  y1 = (b + np.sqrt(det)) / (2 * a)
  x1 = u - r * y1
  print('x1', x1)
  print('u', u)
  y2 = (b - np.sqrt(det)) / (2 * a)
  x2 = u - r * y2
  return (x1 + c1[0], y1), (x2 + c1[0], y2)


def main(args):
  df = pd.read_csv(args.csv)
  centers = df.loc[args.circles]
  fig = plt.figure()
  plt.axis('equal')
  ax = fig.add_subplot(111)
  # ax.set_xlim([-1 + min(df['XX']), 1 + max(df['XX'])])
  # ax.set_ylim([-1 + min(df['YY']), 1 + max(df['YY'])])
  ax.set_xlim([-3, 3])
  ax.set_ylim([-2, 2])
  for i, (x, y) in centers.iterrows():
    e = patches.Circle((x, y), radius=1., linestyle=':', fill=False)
    ax.add_artist(e)

  intersects = []
  for (i1, c1), (i2, c2) in itertools.combinations(centers.iterrows(), 2):
    intersects.extend(intersect(c1, c2))
  print('centers', centers)
  print('intersects', intersects)
  good_intersects = []
  for x, y in intersects:
    _add = True
    print('xy', x, y)
    for i, (c_x, c_y) in centers.iterrows():
      if (x - c_x) ** 2 + (y - c_y) ** 2 > 1.1:
        print(i, c_x, c_y)
        print(i, (x - c_x) ** 2 + (y - c_y) ** 2)
        _add = False
        break
    if _add:
      good_intersects.append((x, y))
  print('good_intersects', good_intersects)
  plt.show()


if __name__ == '__main__':
  args = parse_args()
  print(intersect((0, 0), (1, 1)))
  print(intersect((2, 2), (1, 1)))
  main(args)
