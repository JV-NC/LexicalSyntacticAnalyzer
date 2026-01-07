"""
@file plot_utils.py
@brief Utility functions for saving Matplotlib figures.

This module provides helper functions shared across plotting scripts,
centralizing file handling and output configuration.
"""

import os
import matplotlib.pyplot as plt

def save_figure(output_dir: str, filename: str)->None:
    """
    @brief Saves the current Matplotlib figure to disk.

    Ensures the output directory exists, saves the active figure
    with high resolution, and closes the figure to free memory.

    @param output_dir Directory where the image will be saved.
    @param filename Name of the output image file.
    @return None
    """
    os.makedirs(output_dir, exist_ok=True)

    full_path = os.path.join(output_dir, filename)
    plt.savefig(full_path, dpi=300, bbox_inches='tight')
    plt.close()