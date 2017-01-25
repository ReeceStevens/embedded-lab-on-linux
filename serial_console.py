import sys
import serial

def main(tty):
    with serial.Serial(tty, 115200) as port:
        while True:
            try:
                data = port.readline().decode('ascii').strip()
                # data_buffer = addNewData(data_buffer, data)
                print(data)
            except UnicodeDecodeError:
                continue

if __name__ == '__main__':
    if (len(sys.argv) > 1):
        main(sys.argv[1])
    else:
        print("Please supply a serial tty")
