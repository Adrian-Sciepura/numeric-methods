from datetime import datetime

from macd import MACD

macd = MACD("data.csv")
macd.showPlot(datetime(2023, 1, 2), datetime(2024, 3, 15))