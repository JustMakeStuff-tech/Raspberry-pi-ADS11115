import matplotlib.pyplot as plt
import numpy as np
import board
import busio
import time
import adafruit_ads1x15.ads1115 as ADS
from adafruit_ads1x15.analog_in import AnalogIn

i2c = busio.I2C(board.SCL, board.SDA)
ads = ADS.ADS1115(i2c)
x = 0
light = AnalogIn(ads, ADS.P0)
temp = AnalogIn(ads, ADS.P1)

X1 = []
X2 = []
Y1 = []
Y2 = []
plt.ylim(-50, 1000)
plt.plot(X1, Y1, label = "light", color = '#0069af')
plt.plot(X2, Y2, label = "Temp", color = '#ff8000')
plt.xlabel('Time(minutes)')
plt.ylabel('Level')
plt.title('Light and temp over time')
plt.legend()

while True:
  x += 5
  Y1.append(light.value/30)
  X1.append(x)
  Y2.append(temp.value/3)
  X2.append(x)
  plt.plot(X1, Y1, label = "light", color = '#0069af')
  plt.plot(X2, Y2, label = "Temp", color = '#ff8000')
  plt.pause(300)
