using UnityEngine;
using System.Collections;
using System.IO.Ports;
using System.Net.Sockets;
using System.Net;
using System;
using System.Text;

public class serialSend : MonoBehaviour {

    int pan = 90;
    int tilt = 90;
    int driveX = 127;
    int driveY = 127;
    string readString = "";
    int iterator = 0;

    byte[] sendBuffer = new byte[4];
    string sendString = "";
    public SerialPort serial = new SerialPort("COM3", 9600);
    //IPEndPoint ep = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 11000);                 //make an IPEndpoint for port 696
    //Socket sck = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp); //use UDP for faster data transfer
    //Socket acc;
    // Use this for initialization
    //string lastString = "";
    void Start () {
      //  sck.Bind(new IPEndPoint(IPAddress.Parse("0.0.0.0"), 11000));              //create the server
       // sck.Listen(0);                                                          //listen for incoming connections
        //acc = sck.Accept();
             if(!serial.IsOpen) serial.Open();
        serial.ReadTimeout = 20;
    }
	
	// Update is called once per frame
	void Update () {
        //print(Input.GetAxis("Oculus_GearVR_LThumbstickY")+ "  " + Input.GetAxis("Oculus_GearVR_RThumbstickY"));
        driveX = (int)(Input.GetAxis("Oculus_GearVR_RThumbstickY") * 127 + 127);
        driveY = (int)(Input.GetAxis("Oculus_GearVR_LThumbstickY") * 127 + 127);
        pan = gameObject.GetComponent<OVRCameraRig>().sendYaw;
        tilt = gameObject.GetComponent<OVRCameraRig>().sendPitch;

        

        sendBuffer[0] = (byte)pan;
        sendBuffer[1] = (byte)tilt;
        sendBuffer[2] = (byte)driveX;
        sendBuffer[3] = (byte)driveY;
        //lastString = sendBuffer;

        print(Input.GetAxis("Oculus_GearVR_RThumbstickY") + "   " + sendBuffer[3]);

        serial.Write(sendBuffer,0,4);
        iterator++;
        
        //        print(pan + "  " + tilt+ "  "+ serial.ReadLine());
    }
}
