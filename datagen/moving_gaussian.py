"""
Generates a points from a constant moving Gaussian (in 2d) moving
along x axis in positive direction.
"""
import argparse
import csv
import numpy as np


TWO_PI = 2 * np.pi


def parse_args(*argument_array):
  parser = argparse.ArgumentParser()
  parser.add_argument('-o', '--outfile', type=argparse.FileType('w'),
                      required=True)
  parser.add_argument('--initial-location', type=float, nargs=2,
                      default=[0, 0])
  parser.add_argument('--num-points', type=int, default=10000)
  parser.add_argument('--speed', type=float, default=0.1)
  parser.add_argument('--covariance', type=float, nargs=4, default=[1, 0, 0, 1])
  args = parser.parse_args(*argument_array)
  return args


def generate_moving_gaussian(init_loc, covariance, velocity_per_point, N=1000):
  """
  :param init_loc:
  :param covariance:
  :param velocity_per_point:
  :param N:
  :return array of point:
  """
  points = np.empty(shape=[0, 2])
  center = init_loc
  for i in range(N):
    center = np.add(init_loc, np.multiply(i, velocity_per_point))
    points = np.append(points,
                       np.random.multivariate_normal(center, covariance, 1),
                       axis=0)
  return center, points


def generate_moving_distribution(args):
  header = ['XX', 'YY']
  v = np.multiply(args.speed, [1., 0.])
  cov = np.array([[args.covariance[0], args.covariance[1]],
                  [args.covariance[2], args.covariance[3]]])
  print('cov', cov)

  final_center, points = generate_moving_gaussian(args.initial_location, cov,
                                                  v, N=args.num_points)
  writer = csv.writer(args.outfile)
  writer.writerow(header)
  for x in points:
    writer.writerow(x)
  args.outfile.close()
  return args.outfile.name


if __name__ == '__main__':
  args = parse_args()
  generate_moving_distribution(args)
