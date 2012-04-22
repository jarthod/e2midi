#!/usr/bin/python

import socket
import sys
from PyQt4 import QtGui
from PyQt4 import Qt
from PyQt4 import QtCore
from PyQt4.QtNetwork import QTcpSocket
from pygame import mixer
from uic_visualizer import Ui_e2midi

class e2midi(QtGui.QMainWindow, Ui_e2midi):

    def __init__(self, host, nb):
        QtGui.QWidget.__init__(self, None)
        self.setupUi(self)
        mixer.init()
        self.sock = QTcpSocket()
        self.sock.connectToHost(host, 2012)
        self.sock.readyRead.connect(self.listen)
        self.nb = nb
        self.bar = []
        self.central.setSpacing(500/nb)
        for i in range(nb):
            b = QtGui.QProgressBar()
            b.setOrientation(Qt.Qt.Vertical)
            b.setFormat("%d" % i)
            b.setValue(0)
            self.central.addWidget(b)
            self.bar.append(b)

    def handle_data(self, position):
        print position
        bar = self.bar[min(self.nb - 1, int(position * self.nb))]
        bar.setValue(100)
        QtCore.QTimer.singleShot(200, lambda: bar.setValue(0));

    def listen(self):
        data = self.sock.readAll()
        [self.handle_data(float(i)) for i in data.split('\n') if i != '']


if __name__ == "__main__":
    app = QtGui.QApplication(sys.argv)
    midi = e2midi(sys.argv[1], int(sys.argv[2]))
    midi.show()
    app.exec_()
