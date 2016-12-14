#!/usr/bin/env python3
"""
Convert csv file into copy/pastable latex tabular
"""
from __future__ import print_function
import argparse
import csv


def parse_args(*argument_array):
  parser = argparse.ArgumentParser()
  parser.add_argument('csv')
  args = parser.parse_args(*argument_array)
  return args


def main(args):
  with open(args.csv, 'r') as infile:
    reader = csv.reader(infile)
    header = next(reader)
    print('\\begin{tabular}{' + '|'.join(['c' for _ in header]) + '}')
    print('\t' + '\t& '.join(header) + '  \\\\')
    for row in reader:
      print('\\hline')
      print('\t' + '\t& '.join(row) + '  \\\\')
    print('\\end{tabular}')

if __name__ == '__main__':
  args = parse_args()
  main(args)
