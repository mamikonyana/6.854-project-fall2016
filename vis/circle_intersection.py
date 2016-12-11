#!/usr/bin/env python3
"""
Visualize intersection of unit circles
"""
from __future__ import print_function
import argparse
import pandas as pd
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


def _format(row):
  print(row)
  print(row['XX'], row['YY'])


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
  plt.show()


if __name__ == '__main__':
  args = parse_args()
  main(args)
