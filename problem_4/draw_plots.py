import numpy as np
import matplotlib.pyplot as plt


#read data for plots and create plot 'Working time from the number of data'
file_name = ['20.txt', '40.txt', '60.txt', '80.txt', '100.txt']

data = [];

for i in range(5):
    
    with open(file_name[i]) as f:
        for line in f:
            data.append([float(x) for x in line.split()])

x_axis = [1, 2, 3, 4, 5, 6]

fig = plt.figure(figsize=(15, 10))
plot = fig.add_subplot()

plot.plot(x_axis, np.log10(data[8]), 'o', ms = 4, ls = '--', lw = 0.5, label = r'Radix sort     ')
plot.plot(x_axis, np.log10(data[9]), 'o', ms = 4, ls = '--', lw = 0.5, label = r'std::sort (C++)')

plt.grid(ls = ':')

plot.set_xlabel('log$_{10}$(n)')
plot.set_ylabel('log$_{10}$(time)')
plot.legend(loc='best', fontsize=12)

plt.title('Working time from the number of data')

plt.savefig("plot_n.png")
#------------------------------------------------------------------------------


#read data for plots and create plot 'Working time from the randomness of array'
chaos = [20, 40, 60, 80 , 100]

sort_0 = []
sort_1 = []
for i in range(5):

    sort_0.append(data[2 * i + 0][4])
    sort_1.append(data[2 * i + 1][4])

fig = plt.figure(figsize=(15, 10))
plot = fig.add_subplot()

plot.plot(chaos, np.log10(sort_0), 'o', ms = 4, ls = '--', lw = 0.5, label = r'Radix sort     ')
plot.plot(chaos, np.log10(sort_1), 'o', ms = 4, ls = '--', lw = 0.5, label = r'std::sort (C++)')

plt.grid(ls = ':')


plot.set_xlabel('chaos, %')
plot.set_ylabel('log$_{10}$(time)')
plot.legend(loc='best', fontsize=12)

plt.title('Working time from the randomness (chaos) of the array')

plt.savefig("plot_chaos.png")
#------------------------------------------------------------------------------


#read data for plots and create plot 'Working time from the number of digits'
data = []

with open("digits_dep.txt") as f:
    for line in f:
        data.append([float(x) for x in line.split()])

x_axis = []
for x in range(6, 19):
    x_axis.append(x)

fig = plt.figure(figsize=(15, 10))
plot = fig.add_subplot()

plot.plot(x_axis, np.log10(data[0]), 'o', ms = 4, ls = '--', lw = 0.5, label = r'Radix sort     ')
plot.plot(x_axis, np.log10(data[1]), 'o', ms = 4, ls = '--', lw = 0.5, label = r'std::sort (C++)')

plt.grid(ls = ':')

plot.set_xlabel('digits num')
plot.set_ylabel('log$_{10}$(time)')
plot.legend(loc='best', fontsize=12)

plt.title('Working time from the number of digits')

plt.savefig("plot_digit.png")
#------------------------------------------------------------------------------

