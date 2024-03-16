from numpy import genfromtxt
from datetime import datetime

str2date = lambda x: datetime.strptime(x.decode("utf-8"), '%Y-%m-%d')
my_data = genfromtxt('data.csv', delimiter=',', converters={0: str2date})


