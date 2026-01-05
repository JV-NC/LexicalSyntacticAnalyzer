import os
import matplotlib.pyplot as plt

def save_figure(output_dir: str, filename: str)->None:
    os.makedirs(output_dir, exist_ok=True)

    full_path = os.path.join(output_dir, filename)
    plt.savefig(full_path, dpi=300, bbox_inches='tight')
    plt.close()