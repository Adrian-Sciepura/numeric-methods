import matplotlib.pyplot as plt
from numpy import genfromtxt
from datetime import datetime


class MACD:
    def __init__(self, fileName: str):
        self._fileName = fileName
        self._startRow = 1
        self._valueColumnId = 4

        self.__loadDataFromFile()
        self.__calculateMACD()

    def __loadDataFromFile(self) -> None:
        str2date = lambda x: datetime.strptime(x.decode("utf-8"), '%Y-%m-%d')
        self._importData = genfromtxt(self._fileName, delimiter=',', converters={0: str2date})

        self._dates = []
        for i in range(self._startRow, len(self._importData)):
            self._dates.append(self._importData[i][0])

    def __calculateEMA(self, noOfPeriods: int, row: int) -> float:
        alpha = 2 / (noOfPeriods + 1)

        numerator = 0
        denominator = 0

        for i in range(0, noOfPeriods + 1):
            if row - i < self._startRow:
                break

            power = pow((1 - alpha), i)
            numerator += self._importData[row - i][self._valueColumnId] * power
            denominator += power

        return numerator / denominator

    def __calculateMACD(self) -> None:
        self.MACDValues = []

        for i in range(self._startRow, len(self._importData)):
            self.MACDValues.append(self.__calculateEMA(12, i) - self.__calculateEMA(26, i))

    def showPlot(self, startDate: datetime, endDate: datetime) -> None:
        startDateId = -1
        endDateId = -1

        for i in range(self._startRow, len(self._importData)):
            if self._importData[i][0] == startDate:
                startDateId = i
                break

        if startDateId != -1:
            for i in range(startDateId, len(self._importData)):
                if self._importData[i][0] == endDate:
                    endDateId = i
                    break

        if startDateId == -1 or endDateId == -1:
            return

        plt.xticks(rotation=30)
        plt.plot(self._dates[startDateId:endDateId], self.MACDValues[startDateId:endDateId])
        plt.xlabel('dates')
        plt.ylabel('MACD values')
        plt.title('MACD')
        plt.show()
