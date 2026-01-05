import pandas as pd
import matplotlib.pyplot as plt
import os
from plot_utils import save_figure

output_dir = 'output'
filename = 'length_dist.csv'
plot_name = 'length_distribution.png'

def main():
    df = pd.read_csv(os.path.join(output_dir, filename))
    df = df.sort_values('length')

    plt.bar(
        df['length'],
        df['frequency']
    )

    plt.xlabel('Word length')
    plt.ylabel('Frequency')
    plt.title('Word Length Distribution')
    plt.grid(axis='y')

    save_figure(output_dir,plot_name)

if __name__=='__main__':
    main()