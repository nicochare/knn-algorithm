import matplotlib.pyplot as plt
import csv

x_axis = []
y_axis_preENN = []
y_axis_postENN = []

with open('datasets/porcentajes_processed.csv', 'r') as csvfile:
    next(csvfile) # saltar primera linea
    lines = csv.reader(csvfile, delimiter=',')
    for row in lines:
        x_axis.append(int(row[0]))
        y_axis_preENN.append(float(row[1]))
        y_axis_postENN.append(float(row[2]))

plt.plot(x_axis, y_axis_preENN, label = "Antes de ENN", linewidth=3.5)
plt.plot(x_axis, y_axis_postENN, label = "Despues de ENN", linewidth=3.5)
plt.xlim(0, 675)
plt.ylim(0, 105)
plt.xticks([0, 25, 50, 75, 100, 125, 150, 175, 200, 225, 250, 275, 300, 325, 350, 375, 400, 425, 450, 475, 500, 525, 550, 575, 600, 625, 650, 675])
plt.yticks([0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100])
plt.xlabel('k')
plt.ylabel('Porcentajes')
plt.title('Porcentajes dataset diabetes_prediction_dataset2')
plt.grid()
plt.legend(loc='lower right')
plt.show()