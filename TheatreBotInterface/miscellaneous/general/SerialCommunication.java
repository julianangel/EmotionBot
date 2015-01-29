package general;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.util.TooManyListenersException;

import gnu.io.*;

public class SerialCommunication implements SerialPortEventListener, 
CommPortOwnershipListener{

	
	private String portName;
	private int serialConnection = 57600;
	private int dataBits = SerialPort.DATABITS_8;
	private int stopBits = SerialPort.STOPBITS_1;
	private int parityBits = SerialPort.PARITY_NONE;
	private SerialPort serialPort;
	private boolean synchronous;
    private OutputStream os;
    private InputStream is;
    private boolean isOpen;
    CommPortIdentifier portIdentifier;
	
	
    public SerialCommunication(boolean synchronous){
    	this.synchronous = synchronous;
    }
    
    public SerialCommunication(String portName, boolean synchronous){
		this.portName = portName;
		this.synchronous = synchronous;
		isOpen = false;
	}
    
    public void setPortName(String portName){
    	this.portName = portName;
    }
    
    public String getPortName(){
    	return portName;
    }
	
	public void connect(){
		
		try {
			portIdentifier = CommPortIdentifier.getPortIdentifier(portName);
			if(portIdentifier.isCurrentlyOwned()){
				System.out.println("Error: Ports is currently in use");
			} else{
				CommPort commPort = portIdentifier.open(this.getClass().getName(), 2000);
				if(commPort instanceof SerialPort){
					serialPort = (SerialPort) commPort;
					serialPort.setSerialPortParams(serialConnection, dataBits, stopBits, parityBits);
					serialPort.addEventListener(this);
	                serialPort.notifyOnDataAvailable(true);
				    os = serialPort.getOutputStream();
					isOpen = true;
					portIdentifier.addPortOwnershipListener(this);
				    is = serialPort.getInputStream();					
					if(!synchronous){
						(new Thread(new SerialWriter(os))).start();
					}
				}
				
			}
		} catch (NoSuchPortException | PortInUseException | UnsupportedCommOperationException | IOException | TooManyListenersException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public boolean isConnected(){
		return isOpen;
	}
	
	public void close(){
		// close the i/o streams.
    	try {
			os.close();
	    	is.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		serialPort.close();
		isOpen = false;
		serialPort.removeEventListener();
	}
	
	public void sendMessage(String message){
		if(synchronous){
			try {
				System.out.println(message);
				//os.write("0".getBytes("ISO-8859-1"));
				os.write(message.getBytes("ISO-8859-1"));
				//os.write("0".getBytes("ISO-8859-1"));
				os.flush();
				Thread.sleep(400);
			} catch (IOException | InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		} else{
			//TODO implement asynchronous communication
		}
	}
	
	/**
     * Handles the input coming from the serial port. A new line character
     * is treated as the end of a block in this example. 
     */
	 public void serialEvent(SerialPortEvent e) {
		 	// Create a StringBuffer and int to receive input data.
			StringBuffer inputBuffer = new StringBuffer();
			int newData = 0;
			// Determine type of event.
			switch (e.getEventType()) {

			    // Read data until -1 is returned. If \r is received substitute
			    // \n for correct newline handling.
			    case SerialPortEvent.DATA_AVAILABLE:
				    while (newData != -1) {
				    	try {
				    	    newData = is.read();
					    if (newData == -1) {
						break;
					    }
					    if ('\r' == (char)newData) {
					   	//inputBuffer.append('\n');
					    } else {
					    	inputBuffer.append((char)newData);
					    }
				    	} catch (IOException ex) {
				    	    System.err.println(ex);
				    	    return;
				      	}
		   		    }

				// Append received data to messageAreaIn.
				    System.out.println(new String(inputBuffer));
				//messageAreaIn.append(new String(inputBuffer));
				break;

			    // If break event append BREAK RECEIVED message.
			    case SerialPortEvent.BI:
			    	System.out.println("\n--- BREAK RECEIVED ---\n");
				//messageAreaIn.append("\n--- BREAK RECEIVED ---\n");
			}

		    } 
	/**
	 * This class is used to generate asynchronous messages
	 * still should be update it to manage all the version
	 * @author user
	 *
	 */
    public static class SerialWriter implements Runnable 
    {
        OutputStream out;

        
        public SerialWriter ( OutputStream out )
        {
            this.out = out;
        }
        
        public void run ()
        {
            try
            {                
                int c = 0;
                while ( true)
                {
                    this.out.write("hola\n".getBytes());
                }                
            }
            catch ( IOException e )
            {
                e.printStackTrace();
            }            
        }
    }

	

	public void disconnect(){
		serialPort.close();
	}
	
	/**
	 * Method that gives all the available ports in the system	
	 * @return return a vector with the current available ports
	 */
    public static String[] listPorts()
    {
        java.util.Enumeration<CommPortIdentifier> portEnum = CommPortIdentifier.getPortIdentifiers();
        int i =0;
        while ( portEnum.hasMoreElements() ) 
        {
        	i++;
        	portEnum.nextElement();
        }
        String ports [] = new String[i];
        i=0;
        portEnum = CommPortIdentifier.getPortIdentifiers();
        while( portEnum.hasMoreElements()){
            CommPortIdentifier portIdentifier = portEnum.nextElement();
            ports[i] = portIdentifier.getName()  +  "-" +  getPortTypeName(portIdentifier.getPortType()) ;
            i++;
        }
        return ports;
    }
    
    private static String getPortTypeName ( int portType )
    {
        switch ( portType )
        {
            case CommPortIdentifier.PORT_I2C:
                return "I2C";
            case CommPortIdentifier.PORT_PARALLEL:
                return "Parallel";
            case CommPortIdentifier.PORT_RAW:
                return "Raw";
            case CommPortIdentifier.PORT_RS485:
                return "RS485";
            case CommPortIdentifier.PORT_SERIAL:
                return "Serial";
            default:
                return "unknown type";
        }
    }

	@Override
	public void ownershipChange(int arg0) {
		// TODO Auto-generated method stub
		
	}
}
