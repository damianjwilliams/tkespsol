from tkinter import *
from websocket import create_connection
import json

window = Tk()
window.title("Start/Stop Button")
window.geometry('50x50')

ws = create_connection("ws://192.168.4.1:81/")

bits = [0, 0]
#ws.send(bytearray(bits))

def clicked_rf1():
    if btn_rf1['text'] == "Start":
        btn_rf1.configure(text="Stop")
        lbl_rf1.configure(text="  ON  ")
        bits[0] = 1
    else:
        btn_rf1.configure(text="Start")
        lbl_rf1.configure(text="  OFF ")
        bits[0] = 0
    ws.send(bytearray(bits))
    print("send button 1", bits)

    # Converting string to list
    res = json.loads(ws.recv())

    # printing final result and its type
    print("receive ", res)
    #print(type(res))

    if (res[0] == 0):
        lbl_rf1.configure(bg="grey")
    else:
        lbl_rf1.configure(bg="green")



def clicked_rf2():
    if btn_rf2['text'] == "Start":
        btn_rf2.configure(text="Stop")
        lbl_rf2.configure(text=" ON ")
        bits[1] = 1

    else:
        btn_rf2.configure(text="Start")
        lbl_rf2.configure(text=" OFF ")
        bits[1] = 0

    print(bits)
    ws.send(bytearray(bits))
    print("send button 2", bits)

    # Converting string to list
    res = json.loads(ws.recv())

    # printing final result and its type
    print("recieved ", res)
    #print(type(res))

    if(res[1]==0):
        lbl_rf2.configure(bg="grey")
    else:
       lbl_rf2.configure(bg="green")

btn_rf1 = Button(window, text="Start", command=clicked_rf1)
btn_rf1.grid(column=1, row=1)
lbl_rf1 = Label(window, text="  OFF ", bg="red")
lbl_rf1.grid(column=2, row=1)
btn_rf2 = Button(window, text="Start", command=clicked_rf2)
btn_rf2.grid(column=1, row=2)
lbl_rf2 = Label(window, text="  OFF ", bg="red")
lbl_rf2.grid(column=2, row=2)


window.mainloop()