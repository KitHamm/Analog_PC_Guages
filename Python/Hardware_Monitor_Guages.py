import time, os, threading
import serial
from serial.tools import list_ports
import psutil
import GPUtil
import pystray
import PIL.Image

SLEEP_SECONDS = 0.5
image = PIL.Image.open("hwm.ico")
ports = list(list_ports.comports())
for port in ports:
    if "CP210x" in port.description:
        com = port.name
ser = serial.Serial(com, 115200)
GPU = ""


def on_clicked(icon, item):
    if str(item) == "Exit":
        ser.write(bytes("N/A" + "\n" + "N/A" + "\n" +
                  "N/A" + "\n", encoding="utf-8"))
        os._exit(1)


icon = pystray.Icon("Icon", image, menu=pystray.Menu(
    pystray.MenuItem("Exit", on_clicked)
))


def monitor():
    if (ser.isOpen() == True):
        while True:
            CPUPercent = str(round(psutil.cpu_percent()))
            GPUPercent = str(round(GPUtil.getGPUs()[0].load*100))
            RAM = str(round(psutil.virtual_memory().percent))
            print(
                f"\rMonitor running - CPU: {CPUPercent}% | GPU: {GPUPercent}% | RAM: {RAM}%", end="")
            ser.write(bytes(CPUPercent + "\n" + GPUPercent + "\n" +
                            RAM + "\n", encoding="utf-8"))
            time.sleep(SLEEP_SECONDS)
    else:
        print(f"Error")


threading.Thread(target=icon.run).start()
threading.Thread(target=monitor).start()
