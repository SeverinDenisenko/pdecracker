import matplotlib.pyplot as plt
import pandas as pd

start = pd.read_csv("initial.dat", sep=" ")
solution = pd.read_csv("solution.dat", sep=" ")

plt.plot(start["t"], start["x"], label="Initial")
plt.plot(solution["t"], solution["x"], label="Numeric solution")
plt.legend()
plt.show()
