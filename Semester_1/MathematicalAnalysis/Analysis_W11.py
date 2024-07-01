# Terebent Roxana

import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import minimize


# Define the quadratic function
def f(x, A):
    xt = np.transpose(x)
    return 0.5 * np.dot(xt, np.dot(A, x))


# (a) Matrix A for a unique minimum
A_min = np.array([[2, 0],
                  [0, 2]])    # positive eigenvalues -> 2, 2

# (b) Matrix A for a unique maximum
A_max = np.array([[-2, 0],
                  [0, -2]])     # negative eigenvalues -> -2, -2

# (c) Matrix A for a unique saddle point
A_saddle = np.array([[1, 0],
                     [0, -1]])   # positive and negative eigenvalues -> 1, -1


# Plotting
def plot_surface_contour_gradient(A, title):
    x = np.linspace(-5, 5, 100)
    y = np.linspace(-5, 5, 100)
    X, Y = np.meshgrid(x, y)

    # Z contains the values of the function for all the points in the grid
    Z = np.zeros((len(y), len(x)))
    for i, yi in enumerate(y):
        for j, xi in enumerate(x):
            point = np.array([xi, yi])
            Z[i, j] = f(point, A)

    fig = plt.figure(figsize=(24, 12))

    # Surface plot
    ax = fig.add_subplot(121, projection='3d')
    ax.plot_surface(X, Y, Z, cmap='viridis', alpha=0.75)
    ax.set_title(title + ' - 3D Surface')

    # Contour plot
    ax = fig.add_subplot(122)
    contour = ax.contour(X, Y, Z, levels=20, cmap='viridis')
    ax.set_title(title + ' - Contour Lines')
    plt.colorbar(contour)

    # Gradient plot
    x_points = np.array([1, -2, -3])
    y_points = np.array([2, 1, -3])

    for i in range(len(x_points)):
        point = np.array([x_points[i], y_points[i]])
        result = minimize(lambda x: f(x, A), point, jac=lambda x: np.dot(A, x), method='L-BFGS-B')
        gradient = np.dot(A, result.x)

        ax.quiver(point[0], point[1], gradient[0], gradient[1],
                  angles='xy', scale_units='xy', scale=0.2, color='purple')

    ax.scatter(x_points, y_points, c='purple', marker='o')
    plt.show()


# Plot for unique minimum
plot_surface_contour_gradient(A_min, "Unique minimum")


# Plot for unique maximum
plot_surface_contour_gradient(A_max, "Unique maximum")


# Plot for unique saddle point
plot_surface_contour_gradient(A_saddle, "Unique saddle point")
