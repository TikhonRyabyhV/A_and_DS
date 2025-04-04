import numpy as np
import matplotlib.pyplot as plt



file_name = ['20.txt', '40.txt', '60.txt', '80.txt', '100.txt']
plot_name = ['20.png', '40.png', '60.png', '80.png', '100.png']

data = [];

for i in range(5):
    
    with open(file_name[i]) as f:
        for line in f:
            data.append([float(x) for x in line.split()])

x_axis = [1, 2, 3, 4, 5]

fig = plt.figure(figsize=(15, 10))
plot = fig.add_subplot()

plot.plot(x_axis, np.log10(data[12]), 'o', ms = 4, ls = '--', lw = 0.5, label = r'Bubble sort           ')
plot.plot(x_axis, np.log10(data[13]), 'o', ms = 4, ls = '--', lw = 0.5, label = r'Bubble sort with check')
plot.plot(x_axis, np.log10(data[14]), 'o', ms = 4, ls = '--', lw = 0.5, label = r'Shaker sort           ')
plot.plot(x_axis, np.log10(data[15]), 'o', ms = 4, ls = '--', lw = 0.5, label = r'Comb sort             ')

plt.grid(ls = ':')

plot.set_xlabel('log$_{10}$(n)')
plot.set_ylabel('log$_{10}$(time)')
plot.legend(loc='best', fontsize=12)

plt.title('Working time from the number of data')

plt.savefig("plot_n.png")


chaos = [20, 40, 60, 80 , 100]

sort_0 = []
sort_1 = []
sort_2 = []
sort_3 = []
for i in range(5):

    sort_0.append(data[4 * i + 0][4])
    sort_1.append(data[4 * i + 1][4])
    sort_2.append(data[4 * i + 2][4])
    sort_3.append(data[4 * i + 3][4])

fig = plt.figure(figsize=(15, 10))
plot = fig.add_subplot()

plot.plot(chaos, np.log10(sort_0), 'o', ms = 4, ls = '--', lw = 0.5, label = r'Bubble sort           ')
plot.plot(chaos, np.log10(sort_1), 'o', ms = 4, ls = '--', lw = 0.5, label = r'Bubble sort with check')
plot.plot(chaos, np.log10(sort_2), 'o', ms = 4, ls = '--', lw = 0.5, label = r'Shaker sort           ')
plot.plot(chaos, np.log10(sort_3), 'o', ms = 4, ls = '--', lw = 0.5, label = r'Comb sort             ')

plt.grid(ls = ':')


plot.set_xlabel('chaos, %')
plot.set_ylabel('log$_{10}$(time)')
plot.legend(loc='best', fontsize=12)

plt.title('Working time from the randomness (chaos) of the array')

plt.savefig("plot_chaos.png")

"""
    fig = plt.figure(figsize=(7, 10))
    plot = fig.add_subplot()

    plot.plot(x_axis, data[0], 'o', ms = 4, ls = '--', lw = 0.5, label = r'$Bubble      $')
    plot.plot(x_axis, data[1], 'o', ms = 4, ls = '--', lw = 0.5, label = r'$Bubble-check$')
    plot.plot(x_axis, data[2], 'o', ms = 4, ls = '--', lw = 0.5, label = r'$Shaker-sort $')

    plot.set_xlabel(' log10(n) ')
    plot.set_ylabel('log10(time)')
    plot.legend(loc='best', fontsize=12)

    p1, v1 = np.polyfit(x_axis, np.log10(data[0]), deg=1, cov=True)
    pf1 = np.poly1d(p1)
    print("Sort bubble: k =", p1[0])

    p2, v2 = np.polyfit(x_axis, np.log10(data[1]), deg=1, cov=True)
    pf2 = np.poly1d(p2)
    print("Sort bubble with check: k =", p2[0])

    p3, v3 = np.polyfit(x_axis, np.log10(data[2]), deg=1, cov=True)
    pf3 = np.poly1d(p3)
    print("Sort shaker: k =", p3[0])

    print("-----------------------------------")

    plt.savefig(plot_name[i])
"""
