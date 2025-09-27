# EGIER Bag Production Trend Analysis

This project analyzes EGIER’s monthly bag production from **January 2018 to December 2023 (M1–M144)**. The goal is to find the production trend and build a mathematical model using **polynomial regression** (non-linear) to explain the trend accurately.

---

## Dataset
- CSV file format  
- Contains 144 monthly production values (M1–M144)  
- Data is transposed to have columns:  
  - `Month` (1–144)  
  - `Production` (bags)

---

## Steps
1. Load data from CSV  
2. Preprocess data (transpose, rename columns)  
3. Plot original production data  
4. Fit a polynomial regression model (`numpy.polyfit`)  
5. Predict and plot fitted trend (`numpy.polyval`)  
6. Print polynomial coefficients  

---

## Output

* Plot of original vs. fitted production trend
* Polynomial equation coefficients printed in console

---

## Tech Stack
- Python 3  
- Libraries:
  - `numpy`
  - `pandas`
  - `matplotlib`

###
 
<div align="left">
  <img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/python/python-original.svg" height="40" alt="python logo"  />
  <img width="12" />
  <img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/numpy/numpy-original.svg" height="40" alt="numpy logo"  />
  <img width="12" />
  <img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/pandas/pandas-original.svg" height="40" alt="pandas logo"  />
</div>

###
