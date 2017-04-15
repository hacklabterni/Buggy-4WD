package it.hacklabterni.buggyweb.servlets;

import java.io.BufferedReader;
import java.io.ByteArrayInputStream;
import java.io.DataInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.nio.CharBuffer;
import java.time.Duration;
import java.time.Instant;
import java.nio.charset.Charset;

import javax.servlet.ServletConfig;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.fasterxml.jackson.databind.ObjectMapper;
import com.fazecast.jSerialComm.SerialPort;
import com.sun.xml.internal.bind.v2.runtime.reflect.opt.Const;

import it.hacklabterni.buggyweb.utils.PointXY;

import org.apache.log4j.Logger;

/**
 * Servlet implementation class SendCommandServlet
 */
@WebServlet(name="SendCommandServlet", displayName="SendCommand Servlet", urlPatterns={"/sendCommand"}, loadOnStartup=0)
public class SendCommandServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
	
	private static Logger log = Logger.getLogger(SendCommandServlet.class);
	
	SerialPort comPort = null;
	
	Instant lastSend = Instant.now();

	private final Charset UTF8_CHARSET = Charset.forName("UTF-8");
	
	
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public SendCommandServlet() {
        super();        
    }

	/**
	 * @see Servlet#init(ServletConfig)
	 */
	public void init(ServletConfig config) throws ServletException {
		
		comPort = SerialPort.getCommPort("/dev/ttyUSB0");
		
//		comPort.setBaudRate(115200);
		comPort.setBaudRate(250000);
		comPort.setFlowControl(SerialPort.FLOW_CONTROL_DISABLED);
		comPort.setParity(SerialPort.NO_PARITY);
		comPort.setNumDataBits(8);
		comPort.setNumStopBits(1);
		comPort.setComPortTimeouts(SerialPort.TIMEOUT_WRITE_BLOCKING+SerialPort.TIMEOUT_READ_SEMI_BLOCKING, 50, 0);
		
		if (comPort.openPort())
			log.info(comPort.getSystemPortName() + " successfully opened.");
        else 
        	log.info(comPort.getSystemPortName() + " failed to open.");
            
		try {
			Thread.sleep(2000); //wait 2 seconds for arduino comunications
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	/**
	 * @see Servlet#destroy()
	 */
	public void destroy() {		
		if (comPort != null)
			if (comPort.closePort())
				log.info(comPort.getSystemPortName() + " successfully closed.");
	        else 
	        	log.info(comPort.getSystemPortName() + " failed to close.");
	}

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		throw new ServletException("Method not supported");
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		
		StringBuffer jb = new StringBuffer();
		  String line = null;
		  try {
		    BufferedReader reader = request.getReader();
		    while ((line = reader.readLine()) != null)
		      jb.append(line);
		  } catch (Exception e) { /*report an error*/ }
		  
		  log.info("json: " + jb.toString());
		  
		if (Duration.between(lastSend, Instant.now()).toMillis() < 50) {			
			
			ObjectMapper mapper = new ObjectMapper();
			PointXY point = mapper.readValue(jb.toString(), PointXY.class);

			if (point.getX() >= 0 && point.getY() >= 0){
				log.info("too frequent delivery");
				return;
			}
			else
				log.info("continue for stop motors");
		}
		
		synchronized(this) {
			
			lastSend = Instant.now();
			  
			  try (OutputStream output = comPort.getOutputStream()) {
		            // Wait for 100 ms
//		            Instant start = Instant.now();
//		            while (Duration.between(start, Instant.now()).toMillis() < 100) {}
	
		            try {
		                output.write(encodeUTF8(jb.toString()));
		                output.flush();
		                log.info("Sent: " + jb.toString());
	
		            } catch (Exception e) {
		            	 log.error("Failed to send",e);
		            }
		        }
			  
			  try ( DataInputStream input = new DataInputStream(comPort.getInputStream());) {
				  // Wait for 100 ms
//		            Instant start = Instant.now();
//		            while (Duration.between(start, Instant.now()).toMillis() < 100) {}
				  	StringBuffer sb = new StringBuffer();
		            log.info("bytesAvailable: " + comPort.bytesAvailable());
		            byte[] buffer  = new byte[1024];
		            try {
		            	
		            	int num = input.read(buffer);
		            	while(num > 0) {
		            		sb.append(new String(buffer, 0, num, UTF8_CHARSET));
		            		log.debug("Recv-Temp: " + sb.toString());
		            		num = input.read(buffer);		            		
		            	}
		            		            	
		            	log.info("Recv: " + sb.toString());
		            } catch (Exception e) {
		            	 log.error("Failed to recv",e);
		            }
		        }
		}
	}
	
	String decodeUTF8(byte[] bytes) {
	    return new String(bytes, UTF8_CHARSET);
	}

	byte[] encodeUTF8(String string) {
	    return string.getBytes(UTF8_CHARSET);
	}

}
