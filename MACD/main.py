from datetime import datetime
from macd import MACD

macd = MACD("data.csv")

startDate = datetime(2018, 1, 3)
endDate = datetime(2024, 3, 15)

macd.showPlot(startDate, endDate)
macd.playOnTheStockMarket(startDate, endDate)
macd.showActionsValuesPlot("CD PROJEKT RED")