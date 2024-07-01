# Terebent Roxana
# Represent the unit ball in RxR for the p-norm with p∈{1.25,1.5,3,8} by random sampling and plotting the points that
# are inside the unit ball.

import random
import matplotlib.pyplot as plt


# compute the p-norm of a point
def p_norm(x, y, p):
    return (abs(x) ** p + abs(y) ** p) ** (1 / p)


# generate n points in the unit square
def generate_points(n):
    points = []
    for i in range(n):
        x = random.uniform(-1, 1)
        y = random.uniform(-1, 1)
        points.append((x, y))
    return points


def main():
    p_values = [1.25, 1.5, 3, 8]
    points_number = 100000
    figure, sub_plot = plt.subplots(1, len(p_values), sharey=True, figsize=(20, 5))

    for i in range(len(p_values)):
        points = generate_points(points_number)
        x_inside = []
        y_inside = []
        p = p_values[i]

        for point in points:
            if p_norm(point[0], point[1], p) <= 1:
                x_inside.append(point[0])
                y_inside.append(point[1])

        sub_plot[i].scatter(x_inside, y_inside, s=1, c='purple')
        sub_plot[i].set_aspect('equal', 'box')
        sub_plot[i].set_title("p=" + str(p))

    plt.show()


main()
