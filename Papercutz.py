from System.IO.Ports import SerialPort
#Program that controls a robot via a serial connection using wiimotes.
def update():
	global port , ws , xs , ys
	
	#Reads all bytes avaiable from serial
	diagnostics.watch(port.ReadExisting())
	

	#Weapon toggle
	if wiimote[0].buttons.button_down(WiimoteButtons.B):
		wn = "255"
	else:
		wn = "128"
	
	#Maps joysticks and does math so we have deadzones
	
	xn = filters.mapRange(wiimote[0].nunchuck.stick.x , -110, 100 , 0 , 255)
	yn = filters.mapRange(-wiimote[0].nunchuck.stick.y , -100, 100 , 0 , 255)

	if(xn > 110 and xn < 190):
		xn = 128
	if(yn > 110 and yn < 190):
		yn = 128
	if(xn < 20 and xn > 220):
		yn = 128
	
	xn = str(int(round(xn)))
	yn = str(int(round(yn)))
	
	xn = "".join("0" for i in range(3 - len(xn))) + xn
	yn = "".join("0" for i in range(3 - len(yn))) + yn
	
	xmsg = "x" + xn + ":"
	ymsg = "y" + yn + ":"
	wmsg = "w" + wn + ":"

	msg = ""
	if(xmsg != xs):
		xs = xmsg
		msg = msg + xmsg
	if(ymsg != ys):
		ys = ymsg
		msg = msg + ymsg
	if(wmsg != ws):
		ws = wmsg
		msg = msg + wmsg
		
	#Writes to serial
	port.Write(msg)
	

if starting:
	#Sets delay in loop
	system.setThreadTiming(TimingTypes.HighresSystemTimer)
	system.threadExecutionInterval = 200
	
	#Creates variables that store if we have changed speed
	global port, ws , xs , ys
	ws = 0
	xs = 0
	ys = 0
	
	#Opens Arduino serial comms
	port = SerialPort("com5" , 9600)
	port.Open()
	wiimote[0].buttons.update += update
	
if stopping:
	#Closes Ardunino comms and turns off motors
	global port
	port.Write("y128:x128:")
	port.Close()
    

    
   

 