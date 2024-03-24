from datetime import datetime
from macd import MACD

macd = MACD("data.csv", 4)

startDate1 = datetime(2018, 1, 3)
endDate1 = datetime(2024, 3, 15)

beforeCyberpunk2077short = datetime(2020, 7, 1)
afterCyberpunk7077short = datetime(2021, 4, 1)

beforeCyberpunk2077long = datetime(2020, 7, 1)
afterCyberpunk7077long = datetime(2024, 3, 15)


print("\n\n\n\n--------- Long-term investment Stock growth time ---------")

macd.showPlot(startDate1, endDate1, "MACD i SIGNAL dla inwestycji: okres największego wzrostu - dziś")
macd.playOnTheStockMarket(startDate1, endDate1, "Kapitał dla inwestycji: okres największego wzrostu - dziś")

print("\n\n\n\n--------- Short-term investment CYBERPUNK 2077 ---------")

macd.showPlot(beforeCyberpunk2077short, afterCyberpunk7077short, "MACD i SIGNAL dla inwestycji: przed premierą Cyberpunk 2077 - kilka miesięcy po premierze")
macd.playOnTheStockMarket(beforeCyberpunk2077short, afterCyberpunk7077short, "Kapitał dla inwestycji: przed premierą Cyberpunk 2077 - kilka miesięcy po premierze")

print("\n\n\n\n--------- Long-term investment CYBERPUNK 2077 ---------")

macd.showPlot(beforeCyberpunk2077long, afterCyberpunk7077long, "MACD i SIGNAL dla inwestycji: przed premierą Cyberpunk 2077 - dziś")
macd.playOnTheStockMarket(beforeCyberpunk2077long, afterCyberpunk7077long, "Kapitał dla inwestycji: przed premierą Cyberpunk 2077 - dziś")

macd.showActionsValuesPlot("CD PROJEKT RED")