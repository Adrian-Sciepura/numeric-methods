from datetime import datetime

from macd import MACD

macd = MACD("data.csv")
macd.showPlot(datetime(2020, 5, 4), datetime(2024, 3, 15))