#!/usr/bin/env python3
"""
Generate random walk dataset
Point moves delta distance every time, but in uniformly random direction.
"""
from __future__ import print_function
import argparse
import random
import csv
import numpy as np


def parse_args(*argument_array):
  parser = argparse.ArgumentParser()
  parser.add_argument('--step-size', type=float, default=0.1)
  parser.add_argument('--init-location', type=float, default=[0., 0.])
  parser.add_argument('--num-points', type=int, default=10000)
  parser.add_argument('-o', '--outfile', default='random_walk_2d.csv')
  args = parser.parse_args(*argument_array)
  return args


def main(args):
  loc = np.array(args.init_location)
  points = [loc]
  for i in range(1, args.num_points):
    theta = 2 * np.pi * random.random()
    loc = (loc[0] + args.step_size * np.cos(theta),
           loc[1] + args.step_size * np.sin(theta))
    points.append(loc)

  outfilename = args.outfile
  print('Outputing points to {}..'.format(outfilename))
  header = ['XX', 'YY']
  with open(outfilename, 'w') as outfile:
    writer = csv.writer(outfile)
    writer.writerow(header)
    for row in points:
      writer.writerow(row)
  print('Done.')


if __name__ == '__main__':
  args = parse_args()
  main(args)
