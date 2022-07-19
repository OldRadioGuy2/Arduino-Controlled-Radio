import wx
import serial
import threading
import logging
logger = logging.getLogger(__name__)

NEWLINE_CR = 0
NEWLINE_LF = 1
NEWLINE_CRLF = 2


class SerialIO:
    def __init__(self,window:wx.Window, rx_event):
        self.window=window
        self.rx_event=rx_event
        self.serial=None
        self.thread=None
        self.alive = threading.Event()
        self.alive.set()
        
    def open(self, port:str, baud_rate:int)->bool:
        try:
            self.serial=serial.Serial(port=port, baudrate=(int(baud_rate)),timeout=1)
        except (ValueError,serial.SerialException) as e:
            wx.MessageBox(str(e), style=wx.ICONERROR | Wx.OK)
            return False
        self.start_receive_thread()
        return True
        
    def close(self):
        if self.serial is not None:
            self.stop_receive_thread()
            self.serial.close()
            self.serial = None        

    def write_data(self, data:bytes):
        if self.serial:
            try:
                return self.serial.write(data)
            except serial.SerialException as e:
                wx.MessageBox(str(e), style=wx.ICONERROR | Wx.OK)
                return 0
        
    def write_string(self, data:str) -> int:
        try:
            return self.write_data(bytes(data, 'utf-8'))
        except ValueError as e:        
            wx.MessageBox(str(e), style=wx.ICONERROR | Wx.OK)
            return 0
        
    def start_receive_thread(self):
        if  self.alive.is_set():        
            self.thread = threading.Thread(target=self.receive_thread)
            self.thread.setDaemon(1)
            self.alive.clear()
            self.thread.start()
        pass
    
    def stop_receive_thread(self):
        if not self.alive.is_set():        
            self.alive.set()          # clear alive event for thread
            self.thread.join()        # wait until thread has finished
        pass
    
    def receive_thread(self):
        while not self.alive.is_set():
            b = self.serial.read(self.serial.in_waiting or 1)
            if b:
                wx.PostEvent(self.window, self.rx_event(data=b))
        pass
        
    
