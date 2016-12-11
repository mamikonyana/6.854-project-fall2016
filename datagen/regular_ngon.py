#!/usr/bin/env python3
"""
Generate points that are vertices of regualar n-gon
"""
from __future__ import print_function
import argparse
import numpy as np
import csv


def parse_args(*argument_array):
  parser = argparse.ArgumentParser()
  parser.add_argument('-n', '--n', type=int, default=10)
  parser.add_argument('-o', '--outfile')
  parser.add_argument('--radius', type=float, default=1.)
  args = parser.parse_args(*argument_array)
  return args


def main(args):
  points = [(args.radius * np.cos(2 * np.pi * i / args.n),
             args.radius * np.sin(2 * np.pi * i / args.n))
            for i in range(args.n)]
  outfilename = args.outfile or '{}-gon.csv'.format(args.n)
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
