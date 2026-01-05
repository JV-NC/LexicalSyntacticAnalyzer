import pandas as pd
import matplotlib.pyplot as plt
import os
from plot_utils import save_figure

output_dir = 'output'
filename = 'sort_metrics.csv'
plot_name = 'sort_performance.png'

def main():
    df = pd.read_csv(os.path.join(output_dir, filename))

    df['label'] = df['algorithm'] + ' - ' + df['order']

    for label, group in df.groupby('label'):
        group = group.sort_values('n')

        plt.plot(
            group['n'],
            group['time_s'],
            marker='o',
            label=label
        )
    
    plt.title(f'Sorting Performance')
    plt.xlabel('Input size (n)')
    plt.ylabel('Time (s)')
    plt.legend()
    plt.grid(True)
    
    save_figure(output_dir,plot_name)

if __name__ == '__main__':
    main()