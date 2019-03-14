import struct
import binascii
from math import pi,sin,cos,exp
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import time

from cmath import phase

def update_line(num, data, line, robot):
    
    if num == len(data[0])-1:
        update_line.done = True
    
    if not update_line.done:
        line.set_data(data[0:2,:num])
    
    robotSize = 0.35
    
#    xT = [-robotSize/2,-robotSize/2,robotSize/2]
#    yT = [-robotSize/2,robotSize/2,0]
    
    xT = [2*robotSize/3, -robotSize/3, -robotSize/3, 2*robotSize/3]
    yT = [            0, -robotSize/4,  robotSize/4,      0]
    
    xc = data[0,num]
    yc = data[1,num]
    theta = data[2,num]
    
    xT1 = []
    yT1 = []
    
    
    for n in range(len(xT)):
        xn,yn = xT[n],yT[n]
        xT1.append(xc+xn*cos(theta)-yn*sin(theta))
        yT1.append(yc+yn*cos(theta)+xn*sin(theta))
        
    robot.set_data([xT1,yT1])
    
    return line,robot
# End update_line
update_line.done = False;

def readDataFromBinary(filename,T=0.05):
    f = open(filename,"rb")
    
    data = []
    
    keepGoing = True
    while keepGoing:
        try:
            str = f.read(16);
            (t1,x1,y1,h1) = struct.unpack("ffff",str)
            # If data is empty
            if not data:
                # write unpacked entry into data
                data.append((t1,x1,y1,h1))
            else:
                # Get last position from data
                (t0,x0,y0,h0) = data[-1];
                
                # Make sure angle is interpolated correctly
                dh = h1-h0
                while dh < -pi:
                    dh += 2*pi
                while dh > +pi:
                    dh -= 2*pi
                
                # For t from t0 to t1 in increments of T
                t = t0
                while t <= t1-T:
                    t += T
                    x = (x1-x0)*(t-t0)/(t1-t0)+x0
                    y = (y1-y0)*(t-t0)/(t1-t0)+y0
                    h = dh*(t-t0)/(t1-t0)+h0
                    # Append (t,x,y,h) to data
                    data.append((t,x,y,h))
                # End while
                
                if t < t1:
                    data.append((t1,x1,y1,h1))
            # End else
        except Exception:
            keepGoing = False
    # End while
    
    X = []
    Y = []
    H = []
    
    for (t,x,y,h) in data:
        X.append(x)
        Y.append(y)
        H.append(h)
    
    data = np.array([X,Y,H])
    
    return data
# End readDataFromBinary

def animate(data,T = 0.05,speed=1):
    fig1 = plt.figure()
    
    l, = plt.plot([], [], 'r-',linewidth=2)
    r, = plt.plot([], [], 'b-')
    plt.axis('equal')
    
    X = data[0,...]
    Y = data[1,...]
    midX = (min(X) + max(X))/2
    midY = (min(Y) + max(Y))/2
    xRange = max(X) - min(X)
    yRange = max(Y) - min(Y)
    range = max(xRange,yRange)+1
    
    
    plt.xlim(midX-range/2, midX+range/2)
    plt.ylim(midY-range/2, midY+range/2)
    plt.title('CP143 2012: Robot animation')
    line_ani = animation.FuncAnimation(fig1, update_line, len(X), fargs=(data, l, r),
        interval=1000*T/speed, blit=False)
    
    plt.show()
    time.sleep(2)
# End animate

if __name__ == '__main__':
    T = 0.05
    print "Enter filename:",
    filename = raw_input()
    data = readDataFromBinary(filename,T)
    animate(data,T,5)
# End main
    