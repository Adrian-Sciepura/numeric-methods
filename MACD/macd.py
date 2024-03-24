import matplotlib.pyplot as plt
from numpy import genfromtxt
from datetime import datetime


class MACD:
    def __init__(self, fileName: str, valueColumnId: int):
        self._fileName = fileName
        self._startRow = 1
        self._valueColumnId = valueColumnId
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

    def __getActionPriceIndexByDate(self, date: datetime) -> int:
        for i in range(0, len(self._importData)):
            if self._importData[i][0] == date:
                return i
        return -1

    def showPlot(self, startDate: datetime, endDate: datetime, plotName: str) -> None:
        startDateId: int = 0
        endDateId: int = 0
        datesSize = len(self._dates)

        while startDateId < datesSize and self._dates[startDateId] < startDate:
            startDateId += 1

        endDateId = startDateId

        while endDateId < datesSize and self._dates[endDateId] < endDate:
            endDateId += 1

        plt.rcParams['figure.figsize'] = [12, 5]
        plt.plot(self._dates[startDateId:endDateId], self.MACDValues[startDateId:endDateId], label='MACD', color='b')
        plt.plot(self._dates[startDateId:endDateId], self.SIGNALValues[startDateId:endDateId], label='SIGNAL', color='r')

        intersect = list(filter(lambda a: startDate <= a[0] <= endDate, self.intersectPoints))

        for i in intersect:
            plt.plot(i[0], i[1], 'yo' if i[2] else 'go', markersize=4)

        plt.xlabel('data')
        plt.ylabel('wartość')
        plt.title(plotName)
        plt.legend()
        plt.show()

    def playOnTheStockMarket(self, startDate: datetime, endDate: datetime, plotName: str) -> None:
        datesInRange = list(filter(lambda a: startDate <= a <= endDate, self._dates))
        capitalByDate: list[int] = []
        shares = 1000
        money = 0

        indexOfSharesValue = self.__getActionPriceIndexByDate(datesInRange[0])

        lastActionIndex = 0
        takeActionSize = len(self.intersectPoints)
        iterator = 0
        for date in datesInRange:
            sharesValue = self._importData[indexOfSharesValue + iterator][self._valueColumnId]

            while lastActionIndex < takeActionSize and self.intersectPoints[lastActionIndex][0] < date:
                lastActionIndex += 1

            # Found
            if lastActionIndex < takeActionSize and self.intersectPoints[lastActionIndex][0] == date:
                action = self.intersectPoints[lastActionIndex]
                formattedDate = action[0].strftime("%Y-%m-%d")

                if sharesValue >= 0:
                    if action[2]:
                        # Sell all
                        money += sharesValue * shares
                        shares = 0
                        print("DATE:", formattedDate, ", ACTION: SELL ALL, MONEY:", money, ", SHARES:", shares)
                    else:
                        # Buy as many as possible
                        howManyToBuy = int(money / sharesValue)
                        money -= howManyToBuy * sharesValue
                        shares += howManyToBuy
                        if shares == 0 and howManyToBuy == 0:
                            print("DATE:", formattedDate, ", STATUS: YOU ARE BROKE :(")
                        else:
                            print("DATE:", formattedDate, ", ACTION: BUY, MONEY:", money, ", SHARES:", shares)

            capitalByDate.append(money + shares * sharesValue)
            iterator += 1

        plt.xlabel('Data')
        plt.ylabel('Wartość')
        plt.title(plotName)
        plt.plot(datesInRange, capitalByDate, label='CENA')
        plt.legend()
        plt.show()

    def showActionsValuesPlot(self, companyName: str):
        actionValues = []

        for i in range(0, len(self._importData)-1):
            actionValues.append(self._importData[i][self._valueColumnId])

        plt.xlabel("Data")
        plt.ylabel("Wartość")
        plt.title("Wartość akcji firmy " + companyName)
        plt.plot(self._dates, actionValues)
        plt.show()