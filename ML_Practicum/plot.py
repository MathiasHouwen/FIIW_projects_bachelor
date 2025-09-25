import matplotlib.pyplot as plt
import pandas as pd

# CSV-bestand inlezen
file_path = './doc/training.csv'  # Vervang dit door de juiste pad naar je CSV-bestand
data = pd.read_csv(file_path)

# Kolommen selecteren
columns_to_plot = ["Open", "High", "Low", "Last Close"]

# Controleer of alle kolommen aanwezig zijn
for column in columns_to_plot:
    if column not in data.columns:
        raise ValueError(f"Kolom '{column}' ontbreekt in het CSV-bestand.")

# Meerdere grafieken plotten
plt.figure(figsize=(15, 10))

x_columns = ["Open", "High", "Low"]
y_column = "Last Close"

for i, x_column in enumerate(x_columns):
    plt.subplot(3, 1, i + 1)
    plt.scatter(data[x_column], data[y_column], label=f"{x_column} vs {y_column}")
    plt.title(f"{x_column} vs {y_column}")
    plt.xlabel(x_column)
    plt.ylabel(y_column)
    plt.grid()
    plt.legend()

plt.tight_layout()
plt.show()
