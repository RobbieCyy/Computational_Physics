import numpy as np
# import sys


def generate_b_vector(n):
    # Generate vector b
    b = np.ones(n) * 1.5
    b[0] = b[n - 1] = 2.5
    b[(n // 2) - 1] = b[(n // 2)] = 1.0
    return b


def generate_A_matrix(n):
    # Generate matrix A
    A = np.zeros((n, n))
    for i in range(n):
        A[i, i] = 3
    for i in range(n - 1):
        A[i + 1, i] = -1
        A[i, i + 1] = -1
    for i in range(n):
        A[i, n - 1 - i] = 0.5
    return A


def solve(A, b, epsilon):
    # Solve the equation Ax=b by CG algorithm
    # print("b:")
    # print(b)
    x = np.zeros((np.size(b)))
    # print("x:")
    # print(x)
    r = b - A @ x
    p = r
    k = 0
    while abs(np.linalg.norm(r) / np.linalg.norm(b)) > epsilon:
        alpha = (r.T @ r) / (p.T @ A @ p)
        x = x + alpha * p
        r_0 = r
        r = r - alpha * A @ p
        beta = (r.T @ r) / (r_0.T @ r_0)
        p = r + beta * p
        k = k + 1
    # Return a list, containing the result and number of iteration
    return [x, k]


def showcase(n):
    print("n =", n)
    # Generates the A and b of size n
    b = generate_b_vector(n)
    A = generate_A_matrix(n)
    # Reference answer
    print("Standard result:")
    x_standard = np.linalg.solve(A, b)
    print(x_standard, sep='\n')
    # My result, using modified CG method
    print("My result:")
    result = solve(A, b, 1e-6)
    print(result[0], sep='\n')
    # Number of iteration
    print(result[1])
    # Compare between standard result and my result
    diff = x_standard - result[0]
    print(np.linalg.norm(diff))
    print(np.amax(diff))


def main():
    # sys.stdout = open('result.txt', 'w')
    # Set precision and show all entries of the matrices
    np.set_printoptions(threshold=np.nan, precision=6, floatmode="fixed")
    showcase(100)
    showcase(10000)


if __name__ == "__main__":
    main()
