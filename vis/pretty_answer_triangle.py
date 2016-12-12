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
  parser.add_argument('--label')
  parser.add_argument('--title')
  args = parser.parse_args(*argument_array)
  return args


def main(args):
  answer_indices = []
  with open(args.answer_file) as infile:
    answer_indices = [int(line) for line in infile]

  y = list(range(len(answer_indices)))
  plt.step(answer_indices, y, label=args.label)

  plt.plot(y, y, label='diagonal')
  plt.gca().invert_yaxis()
  plt.xlabel('j*(index)')
  plt.ylabel('index')
  plt.title(args.title)
  plt.legend(loc='lower left')
  if args.png:
    plt.savefig(args.png, dpi=320)
  else:
    plt.show()


if __name__ == '__main__':
  args = parse_args()
  main(args)
