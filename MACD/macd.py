from numpy import genfromtxt
from datetime import datetime


class MACD:
    def __init__(self, fileName):
        self._fileName = fileName
        self._startRow = 1
        self._valueColumnId = 4

        self.__loadDataFromFile()
        self.__calculateMACD()

    def __loadDataFromFile(self):
        str2date = lambda x: datetime.strptime(x.decode("utf-8"), '%Y-%m-%d')
        self._importData = genfromtxt(self._fileName, delimiter=',', converters={0: str2date})

    def __calculateEMA(self, noOfPeriods, row):
        alpha = 2 / (noOfPeriods + 1)

        numerator = 0
        denominator = 0

        for i in range(0, noOfPeriods + 1):
            if row - i < self._startRow:
                break

            power = pow((1 - alpha),i)
            numerator += self._importData[row - i][self._valueColumnId] * power
            denominator += power

        return numerator / denominator

    def __calculateMACD(self):
        self.MACDValues = []

        for i in range(self._startRow, len(self._importData)):
            self.MACDValues.append(self.__calculateEMA(12, i) - self.__calculateEMA(26, i))
