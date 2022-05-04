import matplotlib.pyplot as plt
import pandas as pandas

if __name__ == '__main__':

    data = pandas.read_csv('stats.csv')
    p_list = [2, 4, 8, 16]
    d_list = [1, 2, 3, 4, 5, 6]

    # Speedup vs number of processors.
    s1_list = []
    s2_list = []
    s3_list = []
    for p_n in p_list:
        for i in range(5, len(data), 6):   # If correct num processors.
            if data['p'][i] == p_n and data['d'][i] == 6:
                t0 = float(data['time'][i - 5]) if float(data['time'][i - 5]) > 0 else 1
                t1 = float(data['time'][i - 4]) if float(data['time'][i - 4]) > 0 else 1
                t2 = float(data['time'][i - 3]) if float(data['time'][i - 3]) > 0 else 1
                t3 = float(data['time'][i - 2]) if float(data['time'][i - 2]) > 0 else 1
                t4 = float(data['time'][i - 1]) if float(data['time'][i - 1]) > 0 else 1
                t5 = float(data['time'][i - 0]) if float(data['time'][i - 0]) > 0 else 1

                # Calculate speedup and append.
                s1_list.append(t3 / t0)
                s2_list.append(t4 / t1)
                s3_list.append(t5 / t2)

    # Plot graph.
    plt.plot(p_list, s1_list, label='MinMax Search')
    plt.plot(p_list, s2_list, label='MinMax Search with AB Pruning')
    plt.plot(p_list, s3_list, label='MinMax Search with AB Pruning and Move Ordering')

    plt.legend()
    plt.xlabel('Number of Processors')
    plt.ylabel('Speedup')
    plt.show()

    # Speedup vs depth.
    s1_list = []
    s2_list = []
    s3_list = []
    for d_n in d_list:
        for i in range(5, len(data), 6):  # If correct num processors.
            if data['d'][i] == d_n and data['p'][i] == 4:
                t0 = float(data['time'][i - 5]) if float(data['time'][i - 5]) > 0 else 1
                t1 = float(data['time'][i - 4]) if float(data['time'][i - 4]) > 0 else 1
                t2 = float(data['time'][i - 3]) if float(data['time'][i - 3]) > 0 else 1
                t3 = float(data['time'][i - 2]) if float(data['time'][i - 2]) > 0 else 1
                t4 = float(data['time'][i - 1]) if float(data['time'][i - 1]) > 0 else 1
                t5 = float(data['time'][i - 0]) if float(data['time'][i - 0]) > 0 else 1

                # Calculate speedup and append.
                s1_list.append(t3 / t0)
                s2_list.append(t4 / t1)
                s3_list.append(t5 / t2)

    # Plot graph.
    plt.plot(d_list, s1_list, label='MinMax Search')
    plt.plot(d_list, s2_list, label='MinMax Search with AB Pruning')
    plt.plot(d_list, s3_list, label='MinMax Search with AB Pruning and Move Ordering')

    plt.legend()
    plt.xlabel('Depth')
    plt.ylabel('Speedup')
    plt.show()

    # Efficiency vs number of processors.
    s1_list = []
    s2_list = []
    s3_list = []
    for p_n in p_list:
        for i in range(5, len(data), 6):  # If correct num processors.
            if data['p'][i] == p_n and data['d'][i] == 6:
                t0 = float(data['time'][i - 5]) if float(data['time'][i - 5]) > 0 else 1
                t1 = float(data['time'][i - 4]) if float(data['time'][i - 4]) > 0 else 1
                t2 = float(data['time'][i - 3]) if float(data['time'][i - 3]) > 0 else 1
                t3 = float(data['time'][i - 2]) if float(data['time'][i - 2]) > 0 else 1
                t4 = float(data['time'][i - 1]) if float(data['time'][i - 1]) > 0 else 1
                t5 = float(data['time'][i - 0]) if float(data['time'][i - 0]) > 0 else 1

                # Calculate speedup and append.
                s1_list.append(t3 / t0 / p_n)
                s2_list.append(t4 / t1 / p_n)
                s3_list.append(t5 / t2 / p_n)

    # # Plot graph.
    plt.plot(p_list, s1_list, label='MinMax Search')
    plt.plot(p_list, s2_list, label='MinMax Search with AB Pruning')
    plt.plot(p_list, s3_list, label='MinMax Search with AB Pruning and Move Ordering')

    plt.legend()
    plt.xlabel('Number of Processors')
    plt.ylabel('Efficiency')
    plt.show()

    # Efficiency vs depth.
    s1_list = []
    s2_list = []
    s3_list = []
    for d_n in d_list:
        for i in range(5, len(data), 6):  # If correct num processors.
            if data['d'][i] == d_n and data['p'][i] == 4:
                t0 = float(data['time'][i - 5]) if float(data['time'][i - 5]) > 0 else 1
                t1 = float(data['time'][i - 4]) if float(data['time'][i - 4]) > 0 else 1
                t2 = float(data['time'][i - 3]) if float(data['time'][i - 3]) > 0 else 1
                t3 = float(data['time'][i - 2]) if float(data['time'][i - 2]) > 0 else 1
                t4 = float(data['time'][i - 1]) if float(data['time'][i - 1]) > 0 else 1
                t5 = float(data['time'][i - 0]) if float(data['time'][i - 0]) > 0 else 1

                # Calculate speedup and append.
                s1_list.append(t3 / t0 / 4)
                s2_list.append(t4 / t1 / 4)
                s3_list.append(t5 / t2 / 4)

    # Plot graph.
    plt.plot(d_list, s1_list, label='MinMax Search')
    plt.plot(d_list, s2_list, label='MinMax Search with AB Pruning')
    plt.plot(d_list, s3_list, label='MinMax Search with AB Pruning and Move Ordering')

    plt.legend()
    plt.xlabel('Depth')
    plt.ylabel('Efficiency')
    plt.show()
