import matplotlib.pyplot as plt
from numpy import genfromtxt
from datetime import datetime


class MACD:
    def __init__(self, fileName: str):
        self._fileName = fileName
        self._startRow = 1
        self._valueColumnId = 4
        self.MACDValues = []
        self.SIGNALValues = []
        self.intersectPoints = []

        self.__loadDataFromFile()
        self.__calculateMACD()
        self.__calculateSIGNAL()
        self.__checkIntersections()

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

    def __calculateSIGNAL(self):
        alpha = 2 / (9 + 1)
        for i in range(0, len(self.MACDValues)):
            numerator = 0
            denominator = 0
            for j in range(0, 9 + 1):
                if i - j < 0:
                    break

                power = pow((1 - alpha), j)
                numerator += self.MACDValues[i - j] * power
                denominator += power
            self.SIGNALValues.append(numerator / denominator)

    def __calculateMACD(self) -> None:
        for i in range(self._startRow, len(self._importData)):
            self.MACDValues.append(self.__calculateEMA(12, i) - self.__calculateEMA(26, i))

    # returns:
    # 1 - from above
    # 0 - don't intersect
    # -1 -> from below
    def __checkIfMACDcrossesSIGNAL(self, m1: int, m2: int, s1: int, s2: int) -> int:
        if m1 > s1 and m2 < s2:
            return 1
        elif m1 < s1 and m2 > s2:
            return -1
        else:
            return 0

    def __checkIntersections(self):
        for i in range(0, len(self.MACDValues) - 1):
            cross = self.__checkIfMACDcrossesSIGNAL(
                self.MACDValues[i],
                self.MACDValues[i + 1],
                self.SIGNALValues[i],
                self.SIGNALValues[i + 1])

            if cross != 0:
                self.intersectPoints.append([self._dates[i + 1], self.MACDValues[i + 1], True if cross == 1 else False])

    def __getActionPriceByDate(self, date: datetime) -> int:
        for entry in self._importData:
            if entry[0] == date:
                return entry[self._valueColumnId]

        return -1

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
        plt.plot(self._dates[startDateId:endDateId], self.MACDValues[startDateId:endDateId], label='MACD', color='b')
        plt.plot(self._dates[startDateId:endDateId], self.SIGNALValues[startDateId:endDateId], label='SIGNAL',
                 color='r')

        intersect = list(filter(lambda a: startDate <= a[0] <= endDate, self.intersectPoints))

        for i in intersect:
            plt.plot(i[0], i[1], 'yo' if i[2] else 'go', markersize=4)

        plt.xlabel('dates')
        plt.ylabel('MACD values')
        plt.title('MACD')
        plt.legend()
        plt.show()

    def playOnTheStockMarket(self, startDate: datetime, endDate: datetime) -> None:
        shares = 1000
        money = 0

        takeAction = list(filter(lambda a: startDate <= a[0] <= endDate, self.intersectPoints))

        for action in takeAction:
            sharesValue = self.__getActionPriceByDate(action[0])
            formatedDate = action[0].strftime("%Y-%m-%d")

            if sharesValue >= 0:
                if action[2]:
                    # Sell all
                    money += sharesValue * shares
                    shares = 0
                    print("DATE:", formatedDate, ", ACTION: SELL ALL, MONEY:", money, ", SHARES:", shares)
                else:
                    # Buy as many as possible
                    howManyToBuy = int(money / sharesValue)
                    money -= howManyToBuy * sharesValue
                    shares = howManyToBuy
                    if shares == 0 and howManyToBuy == 0:
                        print("DATE:", formatedDate, ", STATUS: YOU ARE BROKE :(")
                    else:
                        print("DATE:", formatedDate, ", ACTION: BUY, MONEY:", money, ", SHARES:", shares)
