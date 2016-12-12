#!/usr/bin/env python3
"""
Visualize answers
"""
from __future__ import print_function
import argparse
import matplotlib.pyplot as plt


def parse_args(*argument_array):
  parser = argparse.ArgumentParser()
  parser.add_argument('answer_file')
  parser.add_argument('--png', help='save plot to the given file')
  args = parser.parse_args(*argument_array)
  return args


def main(args):
  answer_indices = []
  with open(args.answer_file) as infile:
    answer_indices = [int(line) for line in infile]

  plt.gca().invert_yaxis()
  y = list(range(len(answer_indices)))
  plt.step(answer_indices, y, label='answer')
  plt.plot(y, y, label='diagonal')
  plt.legend()
  if args.png:
    plt.savefig(args.png, dpi=320)
  else:
    plt.show()


if __name__ == '__main__':
  args = parse_args()
  main(args)
